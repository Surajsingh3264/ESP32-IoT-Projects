#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// ==========================================
// FIRMWARE & SYSTEM DETAILS
// ==========================================
#define PROJECT_NAME       "Smart Weather Station"
#define FIRMWARE_VERSION   "v2.0.0-PROD"
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
#define PIN_MQ135          34  // Analog Input (ADC1_CH6) - Gas/Smoke
#define PIN_BATTERY        35  // Analog Input (ADC1_CH7) - Voltage Divider

// Outputs & UI
#define PIN_LED_RED        13
#define PIN_LED_GREEN      12
#define PIN_LED_BLUE       14
#define PIN_BUZZER         27
#define PIN_BUTTON         15  // Pull-up active low

// ==========================================
// BATTERY CALIBRATION (1:1 Voltage Divider)
// ==========================================
// If connecting two 10k, 47k, or 100k resistors in series across battery:
#define BATTERY_MAX_V      4.20f
#define BATTERY_MIN_V      3.00f
#define USB_VOLTAGE_THRESH 4.25f // Above this = USB Power plugged in
#define NO_BATTERY_THRESH  1.00f // Below this = No battery attached (USB only)
#define ADC_VOLTAGE_REF    3.30f
#define VOLTAGE_DIVIDER_R  2.00f // Multiplier for 1:1 resistor divider

// ==========================================
// OLED DISPLAY SETTINGS
// ==========================================
#define OLED_WIDTH         128
#define OLED_HEIGHT        64
#define OLED_I2C_ADDR      0x3C
#define OLED_PAGE_INTERVAL 3000

// ==========================================
// TIMING INTERVALS (in milliseconds)
// ==========================================
#define INTERVAL_DHT       2000
#define INTERVAL_BMP       1000
#define INTERVAL_BH1750    1000
#define INTERVAL_MQ135     2000
#define INTERVAL_BATTERY   2000
#define INTERVAL_SERIAL    5000
#define INTERVAL_BUZZER    100

// ==========================================
// THRESHOLDS & BUZZER
// ==========================================
#define MQ135_RAW_MIN      0
#define MQ135_RAW_MAX      4095
#define GAS_MAX_VAL        500

#define BUZZER_PWM_CHAN    0
#define BUZZER_FREQ        2000
#define BUZZER_RES         8

// ==========================================
// SYSTEM ENUMS & DATA STRUCTURES
// ==========================================
enum SystemState {
  STATE_NORMAL,
  STATE_WARNING,
  STATE_CRITICAL,
  STATE_EMERGENCY
};

enum PowerMode {
  POWER_USB_ONLY,
  POWER_BATTERY,
  POWER_USB_CHARGING
};

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float altitude;
  float lux;
  int gasIndex;
  
  float batteryVolts;
  int batteryPct;
  PowerMode powerMode;
  
  bool dht_ok;
  bool bmp_ok;
  bool bh1750_ok;
  bool mq135_ok;
};

#endif // PINS_H
