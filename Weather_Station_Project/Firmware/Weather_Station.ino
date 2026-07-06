#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <BH1750.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);
Adafruit_BMP280 bmp;
BH1750 lightMeter;

float temperature=0;
float humidity=0;
float pressure=0;
float lux=0;
int aqi=0;

dht.begin();

Wire.begin();

bmp.begin(0x76);

lightMeter.begin();

void readSensors(){

temperature=dht.readTemperature();

humidity=dht.readHumidity();

pressure=bmp.readPressure()/100.0F;

lux=lightMeter.readLightLevel();

aqi=84;

}
void loop(){

server.handleClient();

readSensors();

delay(1000);

}
