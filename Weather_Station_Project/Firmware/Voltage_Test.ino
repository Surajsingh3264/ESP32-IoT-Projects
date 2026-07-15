/*
  ESP32 Boost Converter Voltage Tester
  ------------------------------------
  ADC Pin: GPIO34
  Divider: 100k (top) + 10k (bottom)
  Divider Ratio = 11

  Wiring:

  Boost OUT+ ----100k----+---- GPIO34
                          |
                         10k
                          |
  Boost OUT------------- GND

  ESP32 is powered by USB while testing.
*/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-Voltage-Test";
const char* password = "12345678";

WebServer server(80);

#define ADC_PIN 34

const float ADC_REF = 3.3;
const float DIVIDER_RATIO = 11.0;
const float CALIBRATION = 1.00;    // Change if required

float readVoltage()
{
  long total = 0;

  for (int i = 0; i < 100; i++)
  {
    total += analogRead(ADC_PIN);
    delay(2);
  }

  float adc = total / 100.0;

  float adcVoltage = (adc / 4095.0) * ADC_REF;

  float voltage = adcVoltage * DIVIDER_RATIO * CALIBRATION;

  return voltage;
}

void handleRoot()
{
  float voltage = readVoltage();

  String page =
  "<!DOCTYPE html>"
  "<html>"
  "<head>"
  "<meta name='viewport' content='width=device-width,initial-scale=1'>"
  "<meta http-equiv='refresh' content='1'>"
  "<title>Voltage Test</title>"
  "<style>"
  "body{background:#111;color:white;font-family:Arial;text-align:center;padding-top:60px;}"
  "h1{font-size:42px;}"
  "h2{font-size:75px;color:#00ff66;margin-top:40px;}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Boost Converter Voltage</h1>"
  "<h2>" + String(voltage,2) + " V</h2>"
  "</body>"
  "</html>";

  server.send(200,"text/html",page);
}

void setup()
{
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.print("Connect to WiFi: ");
  Serial.println(ssid);

  Serial.print("Open: http://");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);

  server.begin();
}

void loop()
{
  server.handleClient();
}
