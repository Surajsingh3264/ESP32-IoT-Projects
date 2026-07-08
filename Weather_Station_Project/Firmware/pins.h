#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// ==========================================
// FIRMWARE & SYSTEM DETAILS
// ==========================================
#define PROJECT_NAME       "Smart Env Monitor"
#define FIRMWARE_VERSION   "v1.1.0-PROD"
#define BOARD_NAME         "ESP32 DevKit V1 (30-Pin)"
#define SERIAL_BAUD_RATE   115200

// ==========================================
// WIFI ACCESS POINT CONFIGURATION
// ==========================================
#define WIFI_SSID          "ESP32_Weather"
#define WIFI_PASS          "12345678"
#define WIFI_CHANNEL       1
#define WIFI_MAX_CONN      4

// ==========================================
// HARDWARE PIN DEFINITIONS
// ==========================================
// I2C Bus (SSD1306, BMP280, BH1750)
#define PIN_I2C_SDA        21
#define PIN_I2C_SCL        22

// Sensors
#define PIN_DHT22          4
#define PIN_MQ135          34  // Analog Input (ADC1_CH6)

// Outputs & UI
#define PIN_LED_RED        13
#define PIN_LED_GREEN      12
#define PIN_LED_BLUE       14
#define PIN_BUZZER         27
#define PIN_BUTTON         15  // Pull-up active low

// ==========================================
// OLED DISPLAY SETTINGS
// ==========================================
#define OLED_WIDTH         128
#define OLED_HEIGHT        64
#define OLED_I2C_ADDR      0x3C
#define OLED_PAGE_INTERVAL 3000 // 3 seconds per page

// ==========================================
// TIMING INTERVALS (in milliseconds)
// ==========================================
#define INTERVAL_DHT       2000
#define INTERVAL_BMP       1000
#define INTERVAL_BH1750    1000
#define INTERVAL_MQ135     2000
#define INTERVAL_SERIAL    5000
#define INTERVAL_BUZZER    100  // Base clock for non-blocking acoustic patterns

// ==========================================
// THRESHOLDS & CALIBRATION
// ==========================================
#define MQ135_RAW_MIN      0
#define MQ135_RAW_MAX      4095
#define AQI_MAX_VAL        500

#define AQI_MODERATE       51
#define AQI_POOR           151
#define AQI_HAZARDOUS      301

// Buzzer PWM Settings
#define BUZZER_PWM_CHAN    0
#define BUZZER_FREQ        2000 // 2 kHz tone
#define BUZZER_RES         8    // 8-bit resolution

// ==========================================
// SYSTEM ENUMS & TYPES
// ==========================================
enum SystemState {
  STATE_NORMAL,
  STATE_WARNING,
  STATE_CRITICAL,
  STATE_EMERGENCY
};

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float altitude;
  float lux;
  int aqi;
  
  bool dht_ok;
  bool bmp_ok;
  bool bh1750_ok;
  bool mq135_ok;
};

#endif // PINS_H
