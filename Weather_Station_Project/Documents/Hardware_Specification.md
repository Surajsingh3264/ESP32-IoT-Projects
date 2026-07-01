# Hardware Specification

**Project:** ESP32 Smart Weather Station

**Version:** 1.0

---

# Hardware Overview

The ESP32 Smart Weather Station consists of multiple sensors, display modules, power management components, and user interface devices. Each component has been selected to provide reliable environmental monitoring while maintaining low power consumption and easy integration with the ESP32.

---

# System Controller

## ESP32 Dev Module (ESP-WROOM-32)

### Purpose

Acts as the brain of the entire weather station.

### Specifications

| Property | Value |
|----------|-------|
| Operating Voltage | 3.3V |
| Input Voltage | 5V (USB/VIN) |
| CPU | Dual-Core Xtensa LX6 |
| Clock Speed | Up to 240 MHz |
| SRAM | 520 KB |
| Flash Memory | 4 MB |
| Wireless | Wi-Fi + Bluetooth |

### Responsibilities

- Reads all sensors
- Hosts Web Dashboard
- Updates OLED Display
- Controls RGB LED
- Controls Active Buzzer
- Handles Push Button
- Battery Monitoring

---

# Environmental Sensors

## DHT22

### Measures

- Temperature
- Humidity

### Interface

Single Digital Pin

### Operating Voltage

3.3V–5V

### Purpose

Provides accurate temperature and humidity readings.

---

## BMP280

### Measures

- Atmospheric Pressure

*(Temperature output ignored in this project.)*

### Interface

I²C

### Operating Voltage

3.3V

### Purpose

Measures atmospheric pressure for weather analysis.

---

## BH1750

### Measures

- Light Intensity (Lux)

### Interface

I²C

### Operating Voltage

3.3V

### Purpose

Measures surrounding light intensity.

---

## MQ135

### Measures

Relative Air Quality

### Interface

Analog Output

### Operating Voltage

5V

### Purpose

Detects harmful gases and provides air quality information.

---

# Display

## SSD1306 OLED Display

### Resolution

128 × 64 Pixels

### Interface

I²C

### Operating Voltage

3.3V

### Purpose

Displays environmental information locally.

### Display Pages

- Temperature & Humidity
- Pressure
- Light Intensity
- Air Quality
- Battery Status

---

# User Interface

## RGB LED

### Purpose

Provides quick visual indication of system status.

### Indicators

| Color | Meaning |
|--------|---------|
| Blue | Booting / Connecting |
| Green | Normal Operation |
| Yellow | Moderate AQI |
| Red | Poor AQI |
| Purple | Low Battery |
| White | Sensor Error |

---

## Active Buzzer

### Purpose

Provides audible alerts.

### Alert Events

- Startup
- Wi-Fi Connected
- Poor Air Quality
- Sensor Error
- Low Battery

---

## Push Button

### Purpose

Locks or unlocks automatic OLED page switching.

### Operation

- Press once → Lock Display
- Press again → Resume Auto Switching

---

# Power System

## 18650 Li-ion Batteries

### Quantity

2

### Purpose

Portable rechargeable power source.

---

## Battery Holder

### Purpose

Securely holds both batteries.

---

## TP4056 Charging Module

### Purpose

Charges batteries safely through Micro USB.

### Protection

- Overcharge
- Over-discharge
- Short Circuit

---

# Wiring Components

## Jumper Wires

Used for temporary electrical connections.

### Types

- Male-Male
- Male-Female
- Female-Female

---

## 220Ω Resistors

Used with the RGB LED to limit current.

---

# Mechanical Components

## Wooden Mounting Board

Acts as the base for mounting all hardware components.

---

## PCB Standoffs

Used to mount modules securely above the wooden base.

---

# Communication

## Wi-Fi Access Point

The ESP32 creates its own Wi-Fi hotspot.

Users connect directly to the weather station without requiring internet access.

---

# Total Environmental Parameters

The weather station measures:

- Temperature
- Humidity
- Atmospheric Pressure
- Light Intensity
- Air Quality

Total Sensor Modules: **4**

---

# System Outputs

- OLED Display
- Responsive Web Dashboard
- RGB LED
- Active Buzzer

---

# Summary

The hardware architecture has been designed to provide reliable environmental monitoring while maintaining low power consumption, modularity, and ease of maintenance. The combination of multiple digital and analog sensors, wireless connectivity, rechargeable power, and a user-friendly interface makes the system suitable for educational demonstrations and practical IoT applications.
