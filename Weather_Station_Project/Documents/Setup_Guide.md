# Installation Guide

**Project:** ESP32 Smart Weather Station

**Version:** 1.0

---

# Introduction

This guide explains how to set up, wire, program, and run the ESP32 Smart Weather Station.

---

# Requirements

## Hardware

- ESP32 Dev Module
- DHT22 Sensor
- BMP280 Sensor
- BH1750 Sensor
- MQ135 Sensor
- SSD1306 OLED Display
- RGB LED
- Active Buzzer
- Push Button
- TP4056 Charging Module
- 2 × 18650 Batteries
- Battery Holder
- Jumper Wires
- Breadboard / Wooden Mounting Board

---

## Software

- Arduino IDE 2.x
- USB Driver for ESP32 (if required)

---

# Required Libraries

Install the following libraries from the Arduino Library Manager.

- WiFi
- WebServer
- Adafruit GFX
- Adafruit SSD1306
- DHT Sensor Library
- Adafruit Unified Sensor
- Adafruit BMP280 Library
- BH1750
- ArduinoJson

---

# Hardware Assembly

1. Connect all sensors according to `GPIO_Mapping.md`.
2. Verify all power connections.
3. Ensure all GND pins share a common ground.
4. Check I²C wiring before powering the board.

---

# Uploading Firmware

1. Connect the ESP32 to the computer using a Micro USB cable.
2. Open the project in Arduino IDE.
3. Select the correct ESP32 board.
4. Select the correct COM port.
5. Click **Upload**.
6. Wait until the upload is completed successfully.

---

# Powering the Device

The weather station can be powered by:

- USB Cable
- 2 × 18650 Rechargeable Batteries

---

# Connecting to the Dashboard

1. Power on the weather station.
2. Open Wi-Fi settings on your phone or computer.
3. Connect to the ESP32 hotspot.

Example:

SSID

ESP32_Weather_Station

Password

12345678

4. Open any web browser.

5. Visit

http://192.168.4.1

The weather dashboard will load automatically.

---

# OLED Operation

The OLED display automatically changes pages every few seconds.

Press the push button to:

- Lock the current page.
- Unlock automatic page switching.

---

# RGB LED Indicators

| Color | Status |
|--------|--------|
| Blue | Booting |
| Green | Normal Operation |
| Yellow | Moderate Air Quality |
| Red | Poor Air Quality |
| White | Sensor Error |

---

# Troubleshooting

## OLED Not Working

- Check SDA and SCL connections.
- Verify the I²C address.

---

## Wi-Fi Not Visible

- Restart the ESP32.
- Confirm the firmware uploaded successfully.

---

## Sensor Not Responding

- Verify wiring.
- Check power supply.
- Confirm the correct GPIO pin.

---

## Dashboard Not Loading

- Ensure the device is connected to the ESP32 Wi-Fi.
- Open:

http://192.168.4.1

---

# Project Ready

If all sensors display values on the OLED and the web dashboard updates correctly, the installation has been completed successfully.
