# GPIO Mapping

**Project:** ESP32 Smart Weather Station

**Version:** 1.0

---

# GPIO Overview

This document lists every GPIO pin used in the weather station along with its purpose and connected component.

---

# GPIO Assignment Table

| GPIO | Component | Signal | Notes |
|------|-----------|--------|------|
| GPIO21 | OLED Display | SDA | Shared I²C Bus |
| GPIO21 | BMP280 | SDA | Shared I²C Bus |
| GPIO21 | BH1750 | SDA | Shared I²C Bus |
| GPIO22 | OLED Display | SCL | Shared I²C Bus |
| GPIO22 | BMP280 | SCL | Shared I²C Bus |
| GPIO22 | BH1750 | SCL | Shared I²C Bus |
| GPIO4 | DHT22 | DATA | Digital Input |
| GPIO34 | MQ135 | Analog Output | ADC Input |
| GPIO18 | RGB LED | Red | PWM Output |
| GPIO19 | RGB LED | Green | PWM Output |
| GPIO23 | RGB LED | Blue | PWM Output |
| GPIO13 | Active Buzzer | Signal | Digital Output |
| GPIO27 | Push Button | Input | Internal Pull-up |
| GPIO35 | Battery Voltage | Analog Input | Voltage Divider Required |

---

# I²C Bus

The following components share the same I²C bus.

| Device | Address |
|---------|---------|
| OLED SSD1306 | 0x3C |
| BMP280 | 0x76 |
| BH1750 | 0x23 |

---

# Power Connections

## 3.3V

Connected to:

- OLED Display
- BMP280
- BH1750
- DHT22

---

## 5V

Connected to:

- TP4056 Output
- MQ135 Sensor

---

## GND

Common Ground shared by:

- ESP32
- OLED
- DHT22
- BMP280
- BH1750
- MQ135
- RGB LED
- Push Button
- Active Buzzer
- TP4056

---

# Analog Inputs

| GPIO | Device |
|------|--------|
| GPIO34 | MQ135 |
| GPIO35 | Battery Voltage |

---

# PWM Outputs

| GPIO | Device |
|------|--------|
| GPIO18 | RGB Red |
| GPIO19 | RGB Green |
| GPIO23 | RGB Blue |

---

# Digital Outputs

| GPIO | Device |
|------|--------|
| GPIO13 | Active Buzzer |

---

# Digital Inputs

| GPIO | Device |
|------|--------|
| GPIO4 | DHT22 |
| GPIO27 | Push Button |

---

# Reserved Pins

The following pins are intentionally left unused for future expansion.

- GPIO14
- GPIO16
- GPIO17
- GPIO25
- GPIO26
- GPIO32
- GPIO33

---

# Notes

• OLED, BMP280 and BH1750 share the same I²C bus.

• MQ135 uses the analog output only.

• RGB LED requires a 220Ω resistor on each color channel.

• Battery voltage must be measured through a voltage divider before connecting to GPIO35.

• Push button uses the ESP32 internal pull-up resistor.

---

# GPIO Usage Summary

Total GPIO Used : 10

I²C Devices : 3

Analog Inputs : 2

Digital Inputs : 2

PWM Outputs : 3

Digital Outputs : 1
