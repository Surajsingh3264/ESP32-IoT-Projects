# ESP32 Smart Weather Station

**Version:** 1.0

**Project Type:** IoT Weather Monitoring System

**Platform:** ESP32 Dev Module (ESP-WROOM-32)

**Programming Language:** Arduino C++

**Communication:** Wi-Fi (Access Point Mode)

**Display:** SSD1306 0.96" OLED + Responsive Web Dashboard

---

# Project Overview

The ESP32 Smart Weather Station is an Internet of Things (IoT) project designed to monitor real-time environmental conditions using multiple sensors. The ESP32 collects data from all connected sensors, processes it, and simultaneously displays the information on a local OLED display and a responsive web dashboard hosted directly on the ESP32.

The system is completely portable and battery-powered using rechargeable 18650 lithium-ion cells. It creates its own Wi-Fi hotspot, allowing any nearby smartphone, tablet, or computer to connect without requiring an internet connection.

In addition to environmental monitoring, the system provides visual and audible status notifications using an RGB LED and an active buzzer, making it both informative and interactive.

---

# Objectives

- Develop a portable IoT weather monitoring system.
- Monitor multiple environmental parameters in real time.
- Host a wireless web dashboard using ESP32.
- Display live sensor readings on an OLED display.
- Provide RGB LED status indications.
- Generate buzzer alerts for important events.
- Create a clean, modular, and well-documented project suitable for academic demonstrations.

---

# Environmental Parameters

The weather station measures the following parameters:

- Temperature
- Humidity
- Atmospheric Pressure
- Light Intensity
- Air Quality

---

# Hardware Used

- ESP32 Dev Module
- DHT22 Temperature & Humidity Sensor
- BMP280 Pressure Sensor
- BH1750 Light Sensor
- MQ135 Air Quality Sensor
- SSD1306 OLED Display
- RGB LED
- Active Buzzer
- Push Button
- TP4056 Charging Module
- 2 × 18650 Li-ion Batteries

---

# Working Principle

1. The ESP32 initializes all connected sensors during startup.

2. Sensor readings are collected periodically.

3. The collected data is displayed on the OLED display.

4. The OLED automatically switches between information pages every few seconds.

5. The push button allows the user to lock or unlock automatic page switching.

6. The RGB LED indicates the current operating status of the system.

7. The active buzzer generates audible alerts whenever necessary.

8. The ESP32 hosts a responsive web dashboard over Wi-Fi.

9. Users can connect to the ESP32 hotspot using any smartphone or computer to monitor live environmental data.

---

# OLED Display System

The OLED display automatically cycles through multiple pages every few seconds.

Available pages include:

- Temperature & Humidity
- Atmospheric Pressure
- Light Intensity
- Air Quality
- Battery Status

The user can freeze the current page using the push button.

---

# RGB LED Status Indications

The RGB LED provides quick visual feedback.

Examples:

- Blue → Booting / Connecting
- Green → Normal Operation
- Yellow → Moderate Air Quality
- Red → Poor Air Quality
- Purple → Low Battery
- White → Sensor Error

---

# Power System

The weather station is powered using two rechargeable 18650 lithium-ion batteries.

The TP4056 charging module provides safe USB charging while protecting the batteries from overcharging and deep discharge.

---

# Applications

- Indoor Weather Monitoring
- Smart Home Systems
- Air Quality Monitoring
- Educational IoT Projects
- Environmental Monitoring
- College Mini Project Demonstrations

---

# Future Improvements

Possible future upgrades include:

- Cloud Data Logging
- Mobile Application
- Weather Forecast API
- Rain Sensor
- Wind Speed Measurement
- GPS Integration
- SD Card Data Logging

---

# Conclusion

The ESP32 Smart Weather Station combines multiple environmental sensors with wireless communication, real-time monitoring, and an intuitive user interface. The project demonstrates the practical implementation of IoT technology while maintaining a modular, expandable, and user-friendly design suitable for both learning and real-world applications.
