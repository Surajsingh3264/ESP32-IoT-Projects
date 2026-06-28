#ifndef PINS_H
#define PINS_H

/*
============================================
ESP32 HTTP RC CAR
Hardware Pin Configuration
============================================
*/

// ==========================================
// TB6612FNG Motor Driver
// ==========================================

// Motor A (Left)

#define AIN1 25
#define AIN2 26
#define PWMA 33

// Motor B (Right)

#define BIN1 27
#define BIN2 14
#define PWMB 32

// Driver Enable

#define STBY 13


// ==========================================
// Accessories
// ==========================================

// Headlights

#define HEADLIGHT_PIN 16

// Horn

#define BUZZER_PIN 4


// ==========================================
// Battery Monitoring
// ==========================================

// ADC Input

#define BATTERY_PIN 34


// ==========================================
// WiFi
// ==========================================

#define WIFI_NAME "RC_CAR"

#define WIFI_PASSWORD "12345678"

// ==========================================
// PWM Configuration
// ==========================================

#define PWM_FREQ 1000          // 1 kHz
#define PWM_RESOLUTION 8       // 8-bit (0-255)


#endif
