/**
 * @file Weather_Station.ino
 * @brief Complete ESP32 Smart Environment Monitoring System PRO
 * Hardware: ESP32 DevKit V1 (30-Pin)
 */

// 1. Core System & Network Libraries First
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>

// 2. Hardware Sensor & Display Libraries
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 3. Local Project Files
#include "pins.h"
#include "webpage.h"

// ==========================================
// GLOBAL STATE & VARIABLES
// ==========================================
SensorData currentData;
SystemState currentState = STATE_NORMAL;
bool isOledLocked = false;
unsigned long appStartTime = 0;

// ==========================================
// UTILITY FUNCTIONS
// ==========================================
void printStartupBanner() {
  Serial.println(F("\n======================================================="));
  Serial.println(F("         SMART ENVIRONMENT MONITOR SYSTEM         "));
  Serial.println(F("======================================================="));
  Serial.printf(" Board:            %s\n", BOARD_NAME);
  Serial.printf(" Firmware Version: %s\n", FIRMWARE_VERSION);
  Serial.println(F(" Initializing peripherals and reading sensor buses..."));
  Serial.println(F("======================================================="));
}

String getSystemStateString(SystemState state) {
  switch(state) {
    case STATE_NORMAL:    return F("NORMAL (ALL CLEAR)");
    case STATE_WARNING:   return F("WARNING (CHECK ROOM)");
    case STATE_CRITICAL:  return F("CRITICAL ALERT");
    case STATE_EMERGENCY: return F("EMERGENCY / HAZARD");
    default:              return F("UNKNOWN");
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
  if (lux <= 200) return F("Dim Indoor Lighting");
  if (lux <= 1000) return F("Bright Indoor / Office");
  if (lux <= 10000) return F("Overcast / Daylight");
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
  unsigned long days = totalSeconds / 86400;
  totalSeconds %= 86400;
  unsigned long hours = totalSeconds / 3600;
  totalSeconds %= 3600;
  unsigned long minutes = totalSeconds / 60;
  unsigned long seconds = totalSeconds % 60;
  char buffer[30];
  sprintf(buffer, "%lud %02luh %02lum %02lus", days, hours, minutes, seconds);
  return String(buffer);
}

void evaluateSystemState() {
  SystemState newState = STATE_NORMAL;

  // Thermal evaluation
  if (currentData.dht_ok) {
    if (currentData.temperature >= 40.0 || currentData.temperature <= 0.0) {
      newState = max(newState, STATE_EMERGENCY);
    } else if (currentData.temperature >= 35.0 || currentData.temperature <= 5.0) {
      newState = max(newState, STATE_CRITICAL);
    } else if (currentData.temperature >= 30.0 || currentData.temperature <= 10.0) {
      newState = max(newState, STATE_WARNING);
    }
  }

  // Honest Smoke/Gas evaluation
  if (currentData.mq135_ok && currentData.gasIndex >= 0) {
    if (currentData.gasIndex > 380) {
      newState = max(newState, STATE_EMERGENCY); // Heavy smoke
    } else if (currentData.gasIndex > 250) {
      newState = max(newState, STATE_WARNING);   // Mild smoke / stuffy
    }
  }
  currentState = newState;
}

// ==========================================
// WEBSERVER MANAGER CLASS
// ==========================================
class WebServerManager {
  private:
    WebServer server;
    
    void handleRoot() {
      server.send_P(200, "text/html", INDEX_HTML);
    }

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

    void handleNotFound() {
      server.send(404, "text/plain", F("404: Resource Not Found"));
    }

  public:
    WebServerManager() : server(80) {}

    void init() {
      WiFi.mode(WIFI_AP);
      WiFi.softAP(WIFI_SSID, WIFI_PASS, WIFI_CHANNEL, 0, WIFI_MAX_CONN);
      Serial.println(F(" [OK] WiFi Access Point created successfully."));
      Serial.printf(" [AP] SSID: %s | Password: %s\n", WIFI_SSID, WIFI_PASS);
      Serial.printf(" [AP] IP Address: %s\n", WiFi.softAPIP().toString().c_str());

      server.on("/", HTTP_GET, [this]() { this->handleRoot(); });
      server.on("/data", HTTP_GET, [this]() { this->handleData(); });
      server.onNotFound([this]() { this->handleNotFound(); });

      server.begin();
      Serial.println(F(" [OK] HTTP Web Server started on port 80."));
    }

    void update() { server.handleClient(); }
    int getConnectedClients() { return WiFi.softAPgetStationNum(); }
    String getIpAddress() { return WiFi.softAPIP().toString(); }
};

WebServerManager webServer;

// ==========================================
// SENSOR MANAGER CLASS
// ==========================================
class SensorManager {
  private:
    DHT dht;
    Adafruit_BMP280 bmp;
    BH1750 bh1750;
    
    unsigned long lastDhtRead = 0, lastBmpRead = 0, lastBh1750Read = 0;
    unsigned long lastMq135Read = 0, lastBatRead = 0, lastSerialPrint = 0;
    bool bmpFound = false, bhFound = false;
    float sealevelPressure = 1013.25;

    void readBattery() {
      // Average 10 ADC samples for rock-solid stability
      long rawSum = 0;
      for (int i = 0; i < 10; i++) {
        rawSum += analogRead(PIN_BATTERY);
      }
      float rawAvg = rawSum / 10.0f;
      
      // Calculate voltage at pin, then multiply by divider ratio (2.0 for 10k+10k)
      float pinVoltage = (rawAvg / 4095.0f) * ADC_VOLTAGE_REF;
      currentData.batteryVolts = pinVoltage * VOLTAGE_DIVIDER_R;
      
      // Determine Power Mode and Percentage
      if (currentData.batteryVolts < NO_BATTERY_THRESH) {
        currentData.powerMode = POWER_USB_ONLY;
        currentData.batteryPct = -1; // -1 represents "No Battery"
      } else if (currentData.batteryVolts >= USB_VOLTAGE_THRESH) {
        currentData.powerMode = POWER_USB_CHARGING;
        currentData.batteryPct = 100;
      } else {
        currentData.powerMode = POWER_BATTERY;
        // Map voltage between 3.0V (0%) and 4.2V (100%)
        float pct = ((currentData.batteryVolts - BATTERY_MIN_V) / (BATTERY_MAX_V - BATTERY_MIN_V)) * 100.0f;
        currentData.batteryPct = constrain((int)pct, 0, 100);
      }
    }

  public:
    SensorManager() : dht(PIN_DHT22, DHT22) {}

    void init() {
      dht.begin();
      currentData.dht_ok = false;
      Serial.println(F(" [OK] DHT22 bus initialized."));

      if (bmp.begin(0x76) || bmp.begin(0x77)) {
        bmpFound = true;
        bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, Adafruit_BMP280::SAMPLING_X2, Adafruit_BMP280::SAMPLING_X16, Adafruit_BMP280::FILTER_X16, Adafruit_BMP280::STANDBY_MS_500);
        currentData.bmp_ok = true;
        Serial.println(F(" [OK] BMP280 barometric sensor found."));
      } else {
        bmpFound = false;
        currentData.bmp_ok = false;
        Serial.println(F(" [ERR] BMP280 sensor not found!"));
      }

      if (bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
        bhFound = true;
        currentData.bh1750_ok = true;
        Serial.println(F(" [OK] BH1750 light sensor found."));
      } else {
        bhFound = false;
        currentData.bh1750_ok = false;
        Serial.println(F(" [ERR] BH1750 sensor not found!"));
      }

      pinMode(PIN_MQ135, INPUT);
      pinMode(PIN_BATTERY, INPUT);
      analogReadResolution(12);
      currentData.mq135_ok = true;
      Serial.println(F(" [OK] MQ135 & Battery ADCs initialized."));
      
      currentData.temperature = currentData.humidity = currentData.pressure = currentData.altitude = currentData.lux = -999;
      currentData.gasIndex = -1;
      currentData.batteryVolts = 0.0f;
      currentData.batteryPct = -1;
    }

    void update() {
      unsigned long now = millis();

      if (now - lastDhtRead >= INTERVAL_DHT) {
        lastDhtRead = now;
        float t = dht.readTemperature();
        float h = dht.readHumidity();
        if (!isnan(t) && !isnan(h)) {
          currentData.temperature = t; currentData.humidity = h; currentData.dht_ok = true;
        } else {
          currentData.dht_ok = false;
        }
      }

      if (now - lastBmpRead >= INTERVAL_BMP && bmpFound) {
        lastBmpRead = now;
        float p = bmp.readPressure() / 100.0F;
        float a = bmp.readAltitude(sealevelPressure);
        if (!isnan(p) && p > 0) {
          currentData.pressure = p; currentData.altitude = a; currentData.bmp_ok = true;
        } else {
          currentData.bmp_ok = false;
        }
      }

      if (now - lastBh1750Read >= INTERVAL_BH1750 && bhFound) {
        lastBh1750Read = now;
        float l = bh1750.readLightLevel();
        if (l >= 0.0) {
          currentData.lux = l; currentData.bh1750_ok = true;
        } else {
          currentData.bh1750_ok = false;
        }
      }

      if (now - lastMq135Read >= INTERVAL_MQ135) {
        lastMq135Read = now;
        int raw = analogRead(PIN_MQ135);
        if (raw >= 0 && raw <= 4095) {
          currentData.gasIndex = map(raw, MQ135_RAW_MIN, MQ135_RAW_MAX, 0, GAS_MAX_VAL);
          currentData.mq135_ok = true;
        } else {
          currentData.mq135_ok = false;
        }
      }

      if (now - lastBatRead >= INTERVAL_BATTERY) {
        lastBatRead = now;
        readBattery();
      }

      evaluateSystemState();
    }

    void printSerialReport() {
      unsigned long now = millis();
      if (now - lastSerialPrint >= INTERVAL_SERIAL) {
        lastSerialPrint = now;
        Serial.println(F("\n--- ENVIRONMENTAL STATUS REPORT ---"));
        Serial.printf(" System State:      %s\n", getSystemStateString(currentState).c_str());
        Serial.printf(" Power Source:      %s", getPowerSourceString(currentData.powerMode).c_str());
        if (currentData.batteryPct >= 0) Serial.printf(" (%d%% | %.2fV)\n", currentData.batteryPct, currentData.batteryVolts);
        else Serial.println(F(" (%.2fV)"));
        
        if (currentData.dht_ok) { Serial.printf(" Temperature:       %.1f C\n Humidity:          %.1f %%\n", currentData.temperature, currentData.humidity); } 
        else { Serial.println(F(" Temperature:       [NO DATA]\n Humidity:          [NO DATA]")); }

        if (currentData.bmp_ok) Serial.printf(" Pressure:          %.1f hPa\n", currentData.pressure);
        else Serial.println(F(" Pressure:          [NO DATA]"));

        if (currentData.bh1750_ok) Serial.printf(" Light:             %.1f lx (%s)\n", currentData.lux, getLightTypeString(currentData.lux).c_str());
        else Serial.println(F(" Light:             [NO DATA]"));

        if (currentData.mq135_ok) Serial.printf(" Gas/Smoke:         %d (%s)\n", currentData.gasIndex, getSmokeStatusString(currentData.gasIndex).c_str());
        else Serial.println(F(" Gas/Smoke:         [NO DATA]"));

        Serial.printf(" Connected Clients: %d\n", webServer.getConnectedClients());
        Serial.println(F("-----------------------------------"));
      }
    }
};

// ==========================================
// OUTPUT MANAGER CLASS
// ==========================================
class OutputManager {
  private:
    unsigned long lastBuzzerTick = 0;
    int buzzerCounter = 0;
    bool lastButtonState = HIGH;
    unsigned long lastDebounceTime = 0;
    
    void setRgb(bool r, bool g, bool b) {
      digitalWrite(PIN_LED_RED, r ? HIGH : LOW);
      digitalWrite(PIN_LED_GREEN, g ? HIGH : LOW);
      digitalWrite(PIN_LED_BLUE, b ? HIGH : LOW);
    }

    void writeBuzzer(int dutyCycle) {
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcWrite(PIN_BUZZER, dutyCycle);
      #else
        ledcWrite(BUZZER_PWM_CHAN, dutyCycle);
      #endif
    }

  public:
    void init() {
      pinMode(PIN_LED_RED, OUTPUT);
      pinMode(PIN_LED_GREEN, OUTPUT);
      pinMode(PIN_LED_BLUE, OUTPUT);
      pinMode(PIN_BUTTON, INPUT_PULLUP);

      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
        ledcAttach(PIN_BUZZER, BUZZER_FREQ, BUZZER_RES);
      #else
        ledcSetup(BUZZER_PWM_CHAN, BUZZER_FREQ, BUZZER_RES);
        ledcAttachPin(PIN_BUZZER, BUZZER_PWM_CHAN);
      #endif

      writeBuzzer(0); 
      setRgb(false, false, false);
      Serial.println(F(" [OK] Output peripherals & GPIO initialized."));
    }

    void updateLed() {
      switch (currentState) {
        case STATE_NORMAL:    setRgb(false, true, false); break; 
        case STATE_WARNING:   setRgb(true, true, false);  break; 
        case STATE_CRITICAL:  setRgb(true, false, false); break; 
        case STATE_EMERGENCY: setRgb(true, false, true);  break; 
      }
    }

    void updateBuzzer() {
      unsigned long now = millis();
      if (now - lastBuzzerTick >= INTERVAL_BUZZER) {
        lastBuzzerTick = now;
        buzzerCounter++;
        switch (currentState) {
          case STATE_NORMAL: writeBuzzer(0); break;
          case STATE_WARNING: (buzzerCounter % 20 < 2) ? writeBuzzer(128) : writeBuzzer(0); break;
          case STATE_CRITICAL: (buzzerCounter % 2 == 0) ? writeBuzzer(128) : writeBuzzer(0); break;
          case STATE_EMERGENCY: writeBuzzer(128); break;
        }
      }
    }

    void checkButton();
    
    void update() {
      checkButton();
      updateLed();
      updateBuzzer();
    }
};

// ==========================================
// DISPLAY MANAGER CLASS
// ==========================================
class DisplayManager {
  private:
    Adafruit_SSD1306 oled;
    int currentPage = 1;
    unsigned long lastPageSwitch = 0;
    bool initialized = false;

    void drawHeader(String title) {
      oled.setTextSize(1); oled.setCursor(0, 0); oled.print(title);
      oled.setCursor(108, 0);
      if (isOledLocked) oled.print(F("LCK"));
      else oled.printf("P%d/5", currentPage);
      oled.drawFastHLine(0, 10, OLED_WIDTH, SSD1306_WHITE);
    }

  public:
    DisplayManager() : oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1) {}

    void init() {
      if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println(F(" [ERR] SSD1306 allocation failed!"));
        initialized = false;
        return;
      }
      initialized = true; oled.clearDisplay(); oled.setTextColor(SSD1306_WHITE);
      Serial.println(F(" [OK] SSD1306 OLED display initialized."));
    }

    void showSplash(String ipAddress) {
      if (!initialized) return;
      oled.clearDisplay(); oled.setTextSize(1);
      oled.setCursor(1, 5); oled.println(F("SMART WEATHER STATION"));
      oled.drawFastHLine(0, 16, OLED_WIDTH, SSD1306_WHITE);
      oled.setCursor(0, 25); oled.print(F("Firmware: ")); oled.println(FIRMWARE_VERSION);
      oled.setCursor(0, 40); oled.println(F("WiFi Access Point:"));
      oled.setCursor(0, 50); oled.print(F("IP: ")); oled.println(ipAddress);
      oled.display(); delay(3000);
    }

    void toggleLock() {
      isOledLocked = !isOledLocked;
      Serial.printf(" [UI] OLED Page Switching: %s\n", isOledLocked ? "LOCKED" : "UNLOCKED");
      if (!initialized) return;
      oled.clearDisplay(); oled.setTextSize(2); oled.setCursor(20, 25);
      oled.println(isOledLocked ? F("LOCKED") : F("UNLOCKED")); oled.display();
      delay(800);
      lastPageSwitch = millis();
    }

    void update() {
      if (!initialized) return;
      unsigned long now = millis();
      if (!isOledLocked && (now - lastPageSwitch >= OLED_PAGE_INTERVAL)) {
        lastPageSwitch = now;
        currentPage++;
        if (currentPage > 5) currentPage = 1;
      }
      oled.clearDisplay();
      switch (currentPage) {
        case 1: drawHeader(F("TEMPERATURE FOCUS")); 
                oled.setTextSize(1); oled.setCursor(0, 18); oled.print(F("Temp: ")); oled.setTextSize(2);
                currentData.dht_ok ? oled.printf("%.1f C", currentData.temperature) : oled.print(F("--"));
                oled.setTextSize(1); oled.setCursor(0, 42); oled.print(F("Hum:  ")); oled.setTextSize(2);
                currentData.dht_ok ? oled.printf("%.1f %%", currentData.humidity) : oled.print(F("--"));
                break;
        case 2: drawHeader(F("LIGHT & PRESSURE")); 
                oled.setTextSize(1); oled.setCursor(0, 18); oled.print(F("Light: ")); oled.setTextSize(1);
                currentData.bh1750_ok ? oled.printf("%.0f lx (%s)", currentData.lux, getLightTypeString(currentData.lux).c_str()) : oled.print(F("--"));
                oled.setCursor(0, 40); oled.print(F("Pres: ")); oled.setTextSize(2);
                currentData.bmp_ok ? oled.printf("%.0f hPa", currentData.pressure) : oled.print(F("--"));
                break;
        case 3: drawHeader(F("SMOKE & GAS MONITOR")); 
                oled.setTextSize(1); oled.setCursor(0, 18); oled.print(F("Index: ")); oled.setTextSize(2);
                currentData.mq135_ok ? oled.printf("%d", currentData.gasIndex) : oled.print(F("--"));
                oled.setTextSize(1); oled.setCursor(0, 42); oled.print(F("Status: ")); oled.setTextSize(1);
                oled.print(getSmokeStatusString(currentData.gasIndex));
                break;
        case 4: drawHeader(F("POWER & BATTERY")); 
                oled.setTextSize(1); oled.setCursor(0, 18); oled.print(F("Mode: ")); oled.println(getPowerSourceString(currentData.powerMode));
                oled.setCursor(0, 34); oled.print(F("Level: ")); oled.setTextSize(2);
                currentData.batteryPct >= 0 ? oled.printf("%d %%", currentData.batteryPct) : oled.print(F("No Bat"));
                oled.setTextSize(1); oled.setCursor(0, 54); oled.printf("Volts: %.2f V", currentData.batteryVolts);
                break;
        case 5: drawHeader(F("SYSTEM STATUS")); 
                oled.setTextSize(1); oled.setCursor(0, 18); oled.print(F("State: ")); oled.println(getSystemStateString(currentState));
                oled.setCursor(0, 34); oled.print(F("IP: ")); oled.println(webServer.getIpAddress());
                oled.setCursor(0, 48); oled.print(F("Up: ")); oled.println(getFormattedUptime());
                break;
      }
      oled.display();
    }
};

SensorManager sensors;
DisplayManager display;
OutputManager outputs;

void OutputManager::checkButton() {
  bool reading = digitalRead(PIN_BUTTON);
  if (reading != lastButtonState) lastDebounceTime = millis();
  if ((millis() - lastDebounceTime) > 50) {
    if (reading == LOW && lastButtonState == HIGH) display.toggleLock();
  }
  lastButtonState = reading;
}

// ==========================================
// ARDUINO SETUP & LOOP
// ==========================================
void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  while (!Serial && millis() < 3000);
  
  appStartTime = millis();
  printStartupBanner();

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Serial.println(F(" [OK] I2C Bus initialized."));

  outputs.init();
  display.init();
  sensors.init();
  webServer.init();

  display.showSplash(webServer.getIpAddress());
  
  Serial.println(F("======================================================="));
  Serial.println(F(" [SYSTEM READY] Running continuous monitoring loop...  "));
  Serial.println(F("=======================================================\n"));
}

void loop() {
  sensors.update();
  outputs.update();
  display.update();
  webServer.update();
  sensors.printSerialReport();
}
