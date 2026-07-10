#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// ==========================================
// FIRMWARE & SYSTEM DETAILS
// ==========================================
#define PROJECT_NAME       "Smart Weather Station"
#define FIRMWARE_VERSION   "v3.2.0-PRO"
#define BOARD_NAME         "ESP32 DevKit V1 (30-Pin)"
#define SERIAL_BAUD_RATE   115200

// ==========================================
// WIFI & mDNS CONFIGURATION
// ==========================================
#define WIFI_SSID          "ESP32_Weather"
#define WIFI_PASS          "12345678"
#define WIFI_CHANNEL       1
#define WIFI_MAX_CONN      4
#define MDNS_HOSTNAME      "weather" 

// ==========================================
// HARDWARE PIN DEFINITIONS
// ==========================================
#define PIN_I2C_SDA        21
#define PIN_I2C_SCL        22
#define PIN_DHT22          4
#define PIN_MQ135          34  
#define PIN_BATTERY        35  
#define PIN_LED_RED        13
#define PIN_LED_GREEN      12
#define PIN_LED_BLUE       14
#define PIN_BUZZER         27
#define PIN_BUTTON         15  

// ==========================================
// BATTERY CALIBRATION
// ==========================================
#define BATTERY_MAX_V      4.20f
#define BATTERY_MIN_V      3.00f
#define USB_VOLTAGE_THRESH 4.25f
#define NO_BATTERY_THRESH  1.00f
#define ADC_VOLTAGE_REF    3.30f
#define VOLTAGE_DIVIDER_R  2.00f

// ==========================================
// OLED DISPLAY & TIMERS
// ==========================================
#define OLED_WIDTH         128
#define OLED_HEIGHT        64
#define OLED_I2C_ADDR      0x3C
#define OLED_PAGE_INTERVAL 3500
#define OLED_TIMEOUT_MS    60000 

// ==========================================
// TIMING & PWM CHANNELS
// ==========================================
#define INTERVAL_DHT       2000
#define INTERVAL_BMP       1000
#define INTERVAL_BH1750    1000
#define INTERVAL_MQ135     2000
#define INTERVAL_BATTERY   2000
#define INTERVAL_SERIAL    5000
#define INTERVAL_BUZZER    100

#define MQ135_RAW_MIN      0
#define MQ135_RAW_MAX      4095
#define GAS_MAX_VAL        500

// Restored the Buzzer variables!
#define BUZZER_PWM_CHAN    0
#define BUZZER_FREQ        2000
#define BUZZER_RES         8

#define LED_R_CHAN         1
#define LED_G_CHAN         2
#define LED_B_CHAN         3
#define PWM_FREQ           5000
#define PWM_RES            8

enum SystemState { STATE_BOOTING, STATE_NORMAL, STATE_WARNING, STATE_CRITICAL, STATE_EMERGENCY };
enum PowerMode   { POWER_USB_ONLY, POWER_BATTERY, POWER_USB_CHARGING };

struct SensorData {
  float temperature, humidity, pressure, altitude, lux;
  int gasIndex;
  float batteryVolts;
  int batteryPct;
  PowerMode powerMode;
  bool dht_ok, bmp_ok, bh1750_ok, mq135_ok;
  
  // Internal Sensor (Hall effect removed, keeping Temp)
  float coreTemp;
};

#endif // PINS_H
