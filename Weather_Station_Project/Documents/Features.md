# Features

**Project:** ESP32 Smart Weather Station

**Version:** 1.0

---

# Overview

The ESP32 Smart Weather Station is a portable IoT-based environmental monitoring system capable of measuring multiple weather parameters while providing real-time wireless monitoring through an OLED display and a responsive web dashboard.

---

# Environmental Monitoring

The system continuously measures:

- Temperature
- Humidity
- Atmospheric Pressure
- Light Intensity
- Air Quality

Sensor readings are updated periodically and displayed in real time.

---

# OLED Display

The SSD1306 OLED provides a compact local display.

Features:

- Automatic page switching every 3–5 seconds
- Manual page lock/unlock
- Easy-to-read layout
- Live sensor updates

Display Pages:

### Page 1
- Temperature
- Humidity

### Page 2
- Atmospheric Pressure

### Page 3
- Light Intensity

### Page 4
- Air Quality

### Page 5
- System Status
  - Wi-Fi Status
  - Device IP Address
  - Display Mode

---

# Push Button

The push button controls the OLED display mode.

Functions:

- Press once → Lock current page
- Press again → Resume automatic page switching

---

# RGB LED Status

The RGB LED provides instant visual feedback.

| Color | Status |
|--------|--------|
| 🔵 Blue | Booting / Connecting |
| 🟢 Green | Normal Operation |
| 🟡 Yellow | Moderate Air Quality |
| 🔴 Red | Poor Air Quality |
| ⚪ White | Sensor Error |

---

# Active Buzzer

The buzzer provides audible notifications.

Alerts:

- System Startup
- Wi-Fi Connected
- Poor Air Quality
- Sensor Error

---

# Web Dashboard

The ESP32 hosts a responsive web dashboard.

Features:

- Real-time sensor values
- Mobile-friendly interface
- Automatic updates
- Works without internet
- Accessible from phones, tablets and laptops

---

# Wi-Fi Access Point

The ESP32 creates its own wireless hotspot.

Advantages:

- No internet required
- Direct device connection
- Easy project demonstration
- Portable operation

---

# User Interface

The weather station provides three methods of interaction:

- OLED Display
- Web Dashboard
- RGB LED + Buzzer

---

# Power System

Features:

- Rechargeable batteries
- USB charging
- Portable operation

---

# System Design

The project is designed to be:

- Modular
- Expandable
- Low Power
- Easy to Maintain
- Easy to Upgrade

---

# Safety Features

- Safe battery charging using TP4056
- Current limiting resistors for RGB LED
- Stable I²C communication
- Shared common ground

---

# Applications

- Weather Monitoring
- Indoor Environment Monitoring
- Smart Home Projects
- Educational Demonstrations
- IoT Learning
- Environmental Analysis

---

# Future Improvements

Possible future upgrades:

- Battery percentage monitoring
- Rain sensor
- Wind speed sensor
- SD card data logging
- Mobile application
- Cloud integration
- Weather forecasting API

---

# Feature Summary

✓ Temperature Monitoring

✓ Humidity Monitoring

✓ Pressure Monitoring

✓ Light Monitoring

✓ Air Quality Monitoring

✓ OLED Display

✓ Auto Page Switching

✓ Display Lock

✓ RGB Status Indicator

✓ Active Buzzer

✓ Wi-Fi Hotspot

✓ Responsive Web Dashboard

✓ Rechargeable Battery

✓ Portable Design

✓ Modular Architecture
