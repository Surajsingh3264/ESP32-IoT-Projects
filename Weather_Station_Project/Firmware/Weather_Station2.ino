/**
 * @file Weather_Station.ino
 * @brief Complete ESP32 Smart Weather Station PRO (Thermal Halt Edition)
 */

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pins.h"
#include "webpage.h"

#ifdef __cplusplus
extern "C" {
uint8_t temprature_sens_read();
}
#endif

SensorData currentData;
SystemState currentState = STATE_BOOTING;
bool isOledLocked = false;
unsigned long appStartTime = 0;

// ==========================================
// 🎵 PREMIUM AUDIO MELODIES
// ==========================================
const int tBootF[] = {523, 659, 784, 1047}; const int tBootD[] = {100, 100, 100, 300}; 
const int tConnF[] = {1319, 1047};          const int tConnD[] = {100, 300};           
const int tClickF[]= {4000};                const int tClickD[]= {15};                 
const int tWarnF[] = {1000, 1500};          const int tWarnD[] = {150, 150};           
const int tCritF[] = {3000, 0};             const int tCritD[] = {100, 100};           
const int tEmergF[]= {2000, 1000};          const int tEmergD[]= {400, 400};           

// ==========================================
// 🎼 NON-BLOCKING AUDIO MANAGER
// ==========================================
class AudioManager {
  private:
    unsigned long lastNoteTime = 0;
    int noteIndex = 0;
    int currentSize = 0;
    const int* currentFreqs;
    const int* currentDurs;
    bool playing = false;
    
  public:
    void init() { pinMode(PIN_BUZZER, OUTPUT); noTone(PIN_BUZZER); }
    
    void play(const int* freqs, const int* durs, int size) {
      currentFreqs = freqs; currentDurs = durs; currentSize = size;
      noteIndex = 0; playing = true;
      if (currentFreqs[0] > 0) tone(PIN_BUZZER, currentFreqs[0]);
      else noTone(PIN_BUZZER);
      lastNoteTime = millis();
    }
    
    bool isPlaying() { return playing; }
    
    void update() {
      if (!playing) return;
      if (millis() - lastNoteTime >= currentDurs[noteIndex]) {
        noTone(PIN_BUZZER); noteIndex++;
        if (noteIndex >= currentSize) { playing = false; } 
        else {
          if (currentFreqs[noteIndex] > 0) tone(PIN_BUZZER, currentFreqs[noteIndex]);
          lastNoteTime = millis();
        }
      }
    }
};

AudioManager audio;

// ==========================================
// SYSTEM LOGIC & THRESHOLDS
// ==========================================
void printStartupBanner() {
  Serial.println(F("\n======================================================="));
  Serial.println(F("                 SMART WEATHER STATION                 "));
  Serial.println(F("======================================================="));
  Serial.printf(" Board:            %s\n", BOARD_NAME);
  Serial.printf(" Firmware Version: %s\n", FIRMWARE_VERSION);
  Serial.println(F("======================================================="));
}

String getSystemStateString(SystemState state) {
  switch(state) {
    case STATE_BOOTING:   return F("System Booting...");
    case STATE_NORMAL:    return F("System Normal (All Clear)");
    case STATE_WARNING:   return F("Warning (Check Room/Device)");
    case STATE_CRITICAL:  return F("Critical Alert!");
    case STATE_EMERGENCY: return F("Emergency / Hazard!");
    default:              return F("Unknown");
  }
}

String getSmokeStatusString(int gasVal) {
  if (gasVal < 0) return F("--");
  if (gasVal <= 100) return F("Clean Air (No Smoke)");
  if (gasVal <= 250) return F("Normal (Mild VOCs)");
  if (gasVal <= 380) return F("Mild Smoke / Stuffy");
  return F("Heavy Smoke / Hazard!");
}

String getLightTypeString(float lux) {
  if (lux < 0) return F("--");
  if (lux <= 10) return F("Pitch Black / Night");
  if (lux <= 200) return F("Dim / Cozy Indoor");
  if (lux <= 1000) return F("Bright / Office");
  if (lux <= 10000) return F("Daylight / Overcast");
  return F("Direct Sunlight!");
}

String getPowerSourceString(PowerMode mode) {
  switch(mode) {
    case POWER_USB_ONLY:     return F("USB Power (No Battery)");
    case POWER_BATTERY:      return F("Battery Power");
    case POWER_USB_CHARGING: return F("USB + Charging");
    default:                 return F("Unknown");
  }
}

String getFormattedUptime() {
  unsigned long totalSeconds = (millis() - appStartTime) / 1000;
  unsigned long days = totalSeconds / 86400; totalSeconds %= 86400;
  unsigned long hours = totalSeconds / 3600; totalSeconds %= 3600;
  unsigned long minutes = totalSeconds / 60; unsigned long seconds = totalSeconds % 60;
  char buffer[30]; sprintf(buffer, "%lud %02luh %02lum %02lus", days, hours, minutes, seconds);
  return String(buffer);
}

void evaluateSystemState() {
  if (currentState == STATE_BOOTING && millis() > 8000) currentState = STATE_NORMAL;
  if (currentState == STATE_BOOTING) return;

  SystemState newState = STATE_NORMAL;
  
  // 1. Ambient Temp (Adjusted +5C)
  if (currentData.dht_ok) {
    if (currentData.temperature >= 50.0 || currentData.temperature <= 0.0) newState = max(newState, STATE_EMERGENCY);
    else if (currentData.temperature >= 45.0 || currentData.temperature <= 5.0) newState = max(newState, STATE_CRITICAL);
    else if (currentData.temperature >= 40.0 || currentData.temperature <= 10.0) newState = max(newState, STATE_WARNING);
  }
  
  // 2. Smoke Evaluation
  if (currentData.mq135_ok && currentData.gasIndex >= 0) {
    if (currentData.gasIndex > 380) newState = max(newState, STATE_EMERGENCY);
    else if (currentData.gasIndex > 250) newState = max(newState, STATE_WARNING);
  }

  // 3. ESP32 Silicon Heat Alarms
  if (currentData.coreTemp >= 60.0) newState = max(newState, STATE_EMERGENCY);
  else if (currentData.coreTemp >= 55.0) newState = max(newState, STATE_CRITICAL);
  else if (currentData.coreTemp >= 50.0) newState = max(newState, STATE_WARNING);

  currentState = newState;
}

class WebServerManager {
  private:
    WebServer server;
    int lastConnectedClients = 0;
    bool isOverheated = false;
    
    void handleRoot() { server.send_P(200, "text/html", INDEX_HTML); }
    void handleData() {
      String json = "{";
      json += "\"temperature\":\"" + String(currentData.dht_ok ? String(currentData.temperature, 1) : "--") + "\",";
      json += "\"humidity\":\"" + String(currentData.dht_ok ? String(currentData.humidity, 1) : "--") + "\",";
      json += "\"pressure\":\"" + String(currentData.bmp_ok ? String(currentData.pressure, 0) : "--") + "\",";
      json += "\"light\":\"" + String(currentData.bh1750_ok ? String(currentData.lux, 0) : "--") + "\",";
      json += "\"lightType\":\"" + getLightTypeString(currentData.lux) + "\",";
      json += "\"gasIndex\":\"" + String(currentData.mq135_ok ? String(currentData.gasIndex) : "--") + "\",";
      json += "\"smokeStatus\":\"" + getSmokeStatusString(currentData.gasIndex) + "\",";
      json += "\"batteryVolts\":\"" + String(currentData.batteryVolts, 2) + "\",";
      json += "\"batteryPct\":" + String(currentData.batteryPct) + ",";
      json += "\"powerSource\":\"" + getPowerSourceString(currentData.powerMode) + "\",";
      json += "\"systemStatus\":\"" + getSystemStateString(currentState) + "\",";
      json += "\"clients\":\"" + String(getConnectedClients()) + "\",";
      json += "\"ip\":\"" + getIpAddress() + "\",";
      json += "\"uptime\":\"" + getFormattedUptime() + "\",";
      json += "\"coreTemp\":\"" + String(currentData.coreTemp, 1) + "\",";
      json += "\"dht\":" + String(currentData.dht_ok ? "true" : "false") + ",";
      json += "\"bmp\":" + String(currentData.bmp_ok ? "true" : "false") + ",";
      json += "\"bh1750\":" + String(currentData.bh1750_ok ? "true" : "false") + ",";
      json += "\"mq135\":" + String(currentData.mq135_ok ? "true" : "false") + ",";
      json += "\"board\":\"" + String(BOARD_NAME) + "\",";
      json += "\"fw\":\"" + String(FIRMWARE_VERSION) + "\",";
      json += "\"ssid\":\"" + String(WIFI_SSID) + "\"";
      json += "}";
      server.send(200, "application/json", json);
    }
  public:
    WebServerManager() : server(80) {}
    void init() {
      WiFi.mode(WIFI_AP); WiFi.softAP(WIFI_SSID, WIFI_PASS, WIFI_CHANNEL, 0, WIFI_MAX_CONN);
      Serial.println(F(" [OK] WiFi Access Point created."));
      if (MDNS.begin(MDNS_HOSTNAME)) Serial.printf(" [OK] mDNS Responder: http://%s.local\n", MDNS_HOSTNAME);
      server.on("/", HTTP_GET, [this]() { this->handleRoot(); });
      server.on("/data", HTTP_GET, [this]() { this->handleData(); });
      server.onNotFound([this]() { server.send(404, "text/plain", "404: Not Found"); });
      server.begin();
    }
    
    void checkNewConnections() {
      int currentClients = getConnectedClients();
      if (currentClients > lastConnectedClients) {
        Serial.println(F(" [WIFI] New device connected! Playing chime."));
        audio.play(tConnF, tConnD, 2);
      }
      lastConnectedClients = currentClients;
    }
    
    bool isServerHalted() { return isOverheated; }
    
    void update() { 
      // 🌡️ THERMAL SHUTDOWN LOGIC
      if (currentData.coreTemp >= 70.0 && !isOverheated) {
        isOverheated = true;
        WiFi.mode(WIFI_OFF); // Kills the radio to drop chip temperature!
        Serial.println(F("\n[ALARM] CPU Overheated (70C+)! Web Server and WiFi SHUT DOWN to cool off."));
      } 
      else if (currentData.coreTemp <= 40.0 && isOverheated) {
        isOverheated = false;
        Serial.println(F("\n[ALARM] CPU Cooled to 40C. Restarting Web Server..."));
        WiFi.mode(WIFI_AP);
        WiFi.softAP(WIFI_SSID, WIFI_PASS, WIFI_CHANNEL, 0, WIFI_MAX_CONN);
        if (MDNS.begin(MDNS_HOSTNAME)) Serial.printf(" [OK] mDNS Responder: http://%s.local\n", MDNS_HOSTNAME);
      }

      // If we are currently halted for cooling, skip all web traffic
      if (isOverheated) return;

      server.handleClient(); 
      checkNewConnections();
    }
    
    int getConnectedClients() { return WiFi.softAPgetStationNum(); }
    String getIpAddress() { return WiFi.softAPIP().toString(); }
};

WebServerManager webServer;

class SensorManager {
  private:
    DHT dht; Adafruit_BMP280 bmp; BH1750 bh1750;
    unsigned long lastDhtRead = 0, lastBmpRead = 0, lastBh1750Read = 0, lastMq135Read = 0, lastBatRead = 0, lastSerialPrint = 0;
    bool bmpFound = false, bhFound = false;

    void readBattery() {
      long rawSum = 0;
      for (int i = 0; i < 10; i++) rawSum += analogRead(PIN_BATTERY);
      float pinVoltage = ((rawSum / 10.0f) / 4095.0f) * ADC_VOLTAGE_REF;
      currentData.batteryVolts = pinVoltage * VOLTAGE_DIVIDER_R;
      
      if (currentData.batteryVolts < NO_BATTERY_THRESH) { currentData.powerMode = POWER_USB_ONLY; currentData.batteryPct = -1; } 
      else if (currentData.batteryVolts >= USB_VOLTAGE_THRESH) { currentData.powerMode = POWER_USB_CHARGING; currentData.batteryPct = 100; } 
      else {
        currentData.powerMode = POWER_BATTERY;
        float pct = ((currentData.batteryVolts - BATTERY_MIN_V) / (BATTERY_MAX_V - BATTERY_MIN_V)) * 100.0f;
        currentData.batteryPct = constrain((int)pct, 0, 100);
      }
    }
    
    void readInternalSensors() {
      float fTemp = (temprature_sens_read() - 32) / 1.8; 
      currentData.coreTemp = fTemp;
    }
    
  public:
    SensorManager() : dht(PIN_DHT22, DHT22) {}
    void init() {
      dht.begin();
      if (bmp.begin(0x76) || bmp.begin(0x77)) { bmpFound = true; currentData.bmp_ok = true; } else currentData.bmp_ok = false;
      if (bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) { bhFound = true; currentData.bh1750_ok = true; } else currentData.bh1750_ok = false;
      pinMode(PIN_MQ135, INPUT); pinMode(PIN_BATTERY, INPUT); analogReadResolution(12);
      currentData.temperature = currentData.humidity = currentData.pressure = currentData.altitude = currentData.lux = -999;
      currentData.gasIndex = -1; currentData.batteryVolts = 0.0f; currentData.batteryPct = -1;
    }
    void update() {
      unsigned long now = millis();
      if (now - lastDhtRead >= INTERVAL_DHT) { lastDhtRead = now; float t = dht.readTemperature(), h = dht.readHumidity(); if (!isnan(t) && !isnan(h)) { currentData.temperature = t; currentData.humidity = h; currentData.dht_ok = true; } else currentData.dht_ok = false; }
      if (now - lastBmpRead >= INTERVAL_BMP && bmpFound) { lastBmpRead = now; float p = bmp.readPressure() / 100.0F; if (!isnan(p) && p > 0) { currentData.pressure = p; currentData.bmp_ok = true; } else currentData.bmp_ok = false; }
      if (now - lastBh1750Read >= INTERVAL_BH1750 && bhFound) { lastBh1750Read = now; float l = bh1750.readLightLevel(); if (l >= 0.0) { currentData.lux = l; currentData.bh1750_ok = true; } else currentData.bh1750_ok = false; }
      if (now - lastMq135Read >= INTERVAL_MQ135) { lastMq135Read = now; int raw = analogRead(PIN_MQ135); if (raw >= 0 && raw <= 4095) { currentData.gasIndex = map(raw, MQ135_RAW_MIN, MQ135_RAW_MAX, 0, GAS_MAX_VAL); currentData.mq135_ok = true; } else currentData.mq135_ok = false; }
      if (now - lastBatRead >= INTERVAL_BATTERY) { lastBatRead = now; readBattery(); readInternalSensors(); }
      evaluateSystemState();
    }
    void printSerialReport() {
      if (millis() - lastSerialPrint >= INTERVAL_SERIAL) {
        lastSerialPrint = millis();
        Serial.printf("\n[STATUS] State: %s | Ambient: %.1f C | Smoke: %s | Chip Heat: %.1f C\n", getSystemStateString(currentState).c_str(), currentData.temperature, getSmokeStatusString(currentData.gasIndex).c_str(), currentData.coreTemp);
      }
    }
};

class OutputManager {
  private:
    unsigned long lastAlarmTick = 0;
    bool lastButtonState = HIGH; unsigned long lastDebounceTime = 0;
    
    void setLedColor(int r, int g, int b) {
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(PIN_LED_RED, r); ledcWrite(PIN_LED_GREEN, g); ledcWrite(PIN_LED_BLUE, b);
      #else
        ledcWrite(LED_R_CHAN, r);  ledcWrite(LED_G_CHAN, g);  ledcWrite(LED_B_CHAN, b);
      #endif
    }
    
  public:
    void init() {
      pinMode(PIN_BUTTON, INPUT_PULLUP);
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcAttach(PIN_LED_RED, PWM_FREQ, PWM_RES); ledcAttach(PIN_LED_GREEN, PWM_FREQ, PWM_RES); ledcAttach(PIN_LED_BLUE, PWM_FREQ, PWM_RES);
      #else
        ledcSetup(LED_R_CHAN, PWM_FREQ, PWM_RES); ledcAttachPin(PIN_LED_RED, LED_R_CHAN);
        ledcSetup(LED_G_CHAN, PWM_FREQ, PWM_RES); ledcAttachPin(PIN_LED_GREEN, LED_G_CHAN);
        ledcSetup(LED_B_CHAN, PWM_FREQ, PWM_RES); ledcAttachPin(PIN_LED_BLUE, LED_B_CHAN);
      #endif
      setLedColor(0,0,0);
    }
    
    void updateLed() {
      unsigned long now = millis();
      switch (currentState) {
        case STATE_BOOTING:   setLedColor(0, (sin(now / 150.0) * 127 + 128), (sin(now / 150.0) * 127 + 128)); break; 
        case STATE_NORMAL:    setLedColor(0, (sin(now / 600.0) * 80 + 100), 0); break;   
        case STATE_WARNING:   setLedColor(255, (sin(now / 200.0) * 60 + 60), 0); break; 
        case STATE_CRITICAL:  ((now / 100) % 2 == 0) ? setLedColor(255, 0, 0) : setLedColor(0, 0, 0); break; 
        case STATE_EMERGENCY: ((now / 250) % 2 == 0) ? setLedColor(255, 0, 0) : setLedColor(0, 0, 255); break; 
      }
    }
    
    void updateAlarms() {
      if (audio.isPlaying()) return; 
      unsigned long now = millis();
      switch (currentState) {
        case STATE_WARNING: 
          if (now - lastAlarmTick > 10000) { audio.play(tWarnF, tWarnD, 2); lastAlarmTick = now; } break;
        case STATE_CRITICAL:  audio.play(tCritF, tCritD, 2); break;
        case STATE_EMERGENCY: audio.play(tEmergF, tEmergD, 2); break;
        default: break;
      }
    }
    
    void checkButton();
    void update() { checkButton(); updateLed(); updateAlarms(); }
};

class DisplayManager {
  private:
    Adafruit_SSD1306 oled;
    int currentPage = 1; unsigned long lastPageSwitch = 0;
    bool initialized = false, isScreenOn = true; unsigned long lastActivityTime = 0;

    void drawHeader(String title) {
      oled.setTextSize(1); oled.setCursor(0, 0); oled.print(title); oled.setCursor(108, 0); 
      if (isOledLocked) oled.print(F("LCK")); else oled.printf("P%d/5", currentPage);
      oled.drawFastHLine(0, 10, OLED_WIDTH, SSD1306_WHITE);
    }
  public:
    DisplayManager() : oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1) {}
    void init() { if (oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) { initialized = true; oled.clearDisplay(); oled.setTextColor(SSD1306_WHITE); } lastActivityTime = millis(); }
    void showSplash(String ipAddress) {
      if (!initialized) return; oled.clearDisplay(); oled.setTextSize(1);
      oled.setCursor(1, 5); oled.println(F("SMART WEATHER STATION")); oled.drawFastHLine(0, 16, OLED_WIDTH, SSD1306_WHITE);
      oled.setCursor(0, 26); oled.print(F("Host: weather.local")); oled.setCursor(0, 42); oled.print(F("IP:   ")); oled.println(ipAddress);
      oled.display(); delay(3000); lastActivityTime = millis();
    }
    void wakeUpOrToggleLock() {
      lastActivityTime = millis();
      audio.play(tClickF, tClickD, 1);
      if (!isScreenOn) { isScreenOn = true; return; }
      isOledLocked = !isOledLocked; if (!initialized) return;
      oled.clearDisplay(); oled.setTextSize(2); oled.setCursor(20, 25);
      oled.println(isOledLocked ? F("LOCKED") : F("UNLOCKED")); oled.display(); delay(600); lastPageSwitch = millis();
    }
    void update() {
      if (!initialized) return; unsigned long now = millis();
      if (isScreenOn && (now - lastActivityTime > OLED_TIMEOUT_MS)) { isScreenOn = false; oled.clearDisplay(); oled.display(); }
      if (!isScreenOn) return;
      if (!isOledLocked && (now - lastPageSwitch >= OLED_PAGE_INTERVAL)) { lastPageSwitch = now; currentPage = (currentPage % 5) + 1; }
      oled.clearDisplay();
      switch (currentPage) {
        case 1: drawHeader(F("TEMPERATURE")); oled.setTextSize(1); oled.setCursor(0, 20); oled.print(F("Temp: ")); oled.setTextSize(2); currentData.dht_ok ? oled.printf("%.1f C", currentData.temperature) : oled.print(F("--")); oled.setTextSize(1); oled.setCursor(0, 44); oled.print(F("Hum:  ")); oled.setTextSize(2); currentData.dht_ok ? oled.printf("%.1f %%", currentData.humidity) : oled.print(F("--")); break;
        case 2: drawHeader(F("LIGHT & PRESSURE")); oled.setTextSize(1); oled.setCursor(0, 20); oled.print(F("Light: ")); oled.setTextSize(1); currentData.bh1750_ok ? oled.printf("%.0f lx (%s)", currentData.lux, getLightTypeString(currentData.lux).c_str()) : oled.print(F("--")); oled.setCursor(0, 42); oled.print(F("Pres: ")); oled.setTextSize(2); currentData.bmp_ok ? oled.printf("%.0f hPa", currentData.pressure) : oled.print(F("--")); break;
        case 3: drawHeader(F("SMOKE & AIR")); oled.setTextSize(1); oled.setCursor(0, 20); oled.print(F("Index: ")); oled.setTextSize(2); currentData.mq135_ok ? oled.printf("%d", currentData.gasIndex) : oled.print(F("--")); oled.setTextSize(1); oled.setCursor(0, 44); oled.print(getSmokeStatusString(currentData.gasIndex)); break;
        case 4: drawHeader(F("POWER & BATTERY")); oled.setTextSize(1); oled.setCursor(0, 20); oled.print(F("Mode: ")); oled.println(getPowerSourceString(currentData.powerMode)); oled.setCursor(0, 36); oled.print(F("Level: ")); oled.setTextSize(2); currentData.batteryPct >= 0 ? oled.printf("%d %%", currentData.batteryPct) : oled.print(F("No Bat")); oled.setTextSize(1); oled.setCursor(0, 54); oled.printf("Volts: %.2f V", currentData.batteryVolts); break;
        case 5: 
          drawHeader(F("INTERNAL CHIP HEAT")); 
          oled.setTextSize(1); oled.setCursor(0, 20); oled.print(F("Temp: ")); oled.setTextSize(2); oled.printf("%.1f C", currentData.coreTemp); 
          oled.setTextSize(1); oled.setCursor(0, 44); oled.print(F("Stat: ")); oled.setTextSize(2); 
          
          // 🌡️ The OLED Shutdown Note!
          if (webServer.isServerHalted()) oled.print(F("WIFI CUT")); 
          else oled.print(currentData.coreTemp >= 50.0 ? F("WARNING") : F("NORMAL")); 
          break;
      }
      oled.display();
    }
};

SensorManager sensors; DisplayManager display; OutputManager outputs;

void OutputManager::checkButton() {
  bool reading = digitalRead(PIN_BUTTON);
  if (reading != lastButtonState) lastDebounceTime = millis();
  if ((millis() - lastDebounceTime) > 50) { if (reading == LOW && lastButtonState == HIGH) display.wakeUpOrToggleLock(); }
  lastButtonState = reading;
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE); while (!Serial && millis() < 3000);
  appStartTime = millis(); printStartupBanner();
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  
  audio.init(); audio.play(tBootF, tBootD, 4); 
  
  outputs.init(); display.init(); sensors.init(); webServer.init();
  display.showSplash(webServer.getIpAddress());
  Serial.println(F(" [SYSTEM READY] Running monitoring loop...\n"));
}

void loop() { 
  sensors.update(); 
  outputs.update(); 
  display.update(); 
  webServer.update(); 
  sensors.printSerialReport(); 
  audio.update(); 
}
