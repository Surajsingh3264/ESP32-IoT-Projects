# Hardware Specification

## Project Overview

The ESP32 Wi-Fi RC Car is a wireless robotic vehicle controlled through a responsive web dashboard hosted directly on the ESP32. The vehicle creates its own Wi-Fi Access Point, allowing any smartphone or laptop to connect and control it without requiring an internet connection.

---

# Microcontroller

## ESP32 Dev Module

| Parameter | Specification |
|-----------|---------------|
| MCU | ESP32-WROOM-32 |
| CPU | Dual-Core Xtensa LX6 |
| Clock Speed | Up to 240 MHz |
| SRAM | 520 KB |
| Flash Memory | 4 MB |
| Wi-Fi | IEEE 802.11 b/g/n |
| Bluetooth | Bluetooth 4.2 + BLE |
| Operating Voltage | 3.3V |
| USB Interface | Micro USB |
| GPIO Pins | 30-pin Development Board |

---

# Motor Driver

## TB6612FNG

| Parameter | Specification |
|-----------|---------------|
| Driver Type | Dual H-Bridge |
| Motor Channels | 2 |
| Logic Voltage | 2.7V – 5.5V |
| Motor Voltage | 4.5V – 13.5V |
| Continuous Current | 1.2A per channel |
| Peak Current | 3.2A |
| Standby Mode | Supported |

---

# Motors

## BO DC Gear Motors

| Parameter | Specification |
|-----------|---------------|
| Quantity | 2 |
| Rated Voltage | 6V |
| Type | DC Geared Motor |
| Drive | Differential Drive |

---

# Power System

| Component | Specification |
|-----------|---------------|
| Battery | 2×18650 Li-ion Battery Pack (Recommended) |
| Motor Supply | Battery Output |
| ESP32 Supply | USB / VIN |
| Battery Monitoring | GPIO34 (Voltage Divider Required) |

---

# Accessories

| Component | Purpose |
|-----------|----------|
| LED Headlights | Front Illumination |
| Active Buzzer | Horn |
| Wi-Fi Antenna | Built into ESP32 |

---

# Communication

| Parameter | Value |
|-----------|-------|
| Protocol | HTTP |
| Network Mode | Wi-Fi Access Point |
| Default SSID | RC_CAR |
| Default Password | 12345678 |
| Default IP | 192.168.4.1 |

---

# Software Stack

- Arduino IDE
- ESP32 Arduino Core 3.x
- ESPAsyncWebServer
- AsyncTCP
- HTML
- CSS
- JavaScript

---

# Functional Features

- Wi-Fi Remote Control
- Forward Movement
- Backward Movement
- Left Turn
- Right Turn
- Emergency Stop
- Adjustable Speed
- Headlight Control
- Horn Control
- Battery Level Display
- Real-Time Status Monitoring

---

# System Architecture

```

Smartphone / Laptop
        │
     Wi-Fi HTTP
        │
     ESP32 Dev Module
        │
   TB6612FNG Driver
        │
   ┌───────────────┐
   │               │
Motor A        Motor B

        │
   Accessories
   ├── LED Headlights
   ├── Active Buzzer
   └── Battery Monitor

```

---

# Future Expansion

The hardware design allows future integration of:

- ESP32-CAM Module
- Ultrasonic Obstacle Detection
- Line Following Sensors
- GPS Module
- Voice Control
- OTA Firmware Updates
- Mobile Application
- Joystick Controller
