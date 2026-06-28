# 🚗 ESP32 Wi-Fi RC Car

A professional Wi-Fi controlled RC Car built using the ESP32 microcontroller and TB6612FNG motor driver. The car is controlled through a modern web dashboard hosted directly on the ESP32, allowing any smartphone or computer to drive the vehicle without installing an app.

---

## Features

- 📶 Wi-Fi Access Point Mode
- 🌐 Responsive Web Dashboard
- 🎮 Real-time Car Control
- ⚡ Adjustable Motor Speed
- 💡 Headlight Control
- 📢 Horn Control
- 🔋 Battery Level Monitoring
- 📱 Mobile Friendly Interface

---

## Hardware Used

| Component | Quantity |
|-----------|---------:|
| ESP32 Dev Module | 1 |
| TB6612FNG Motor Driver | 1 |
| BO DC Motor | 2 |
| Wheels | 2 |
| Chassis | 1 |
| Battery Pack | 1 |
| LEDs | 2 |
| Active Buzzer | 1 |
| Jumper Wires | As Required |

---

## Software Stack

- Arduino IDE
- ESP32 Arduino Core
- ESPAsyncWebServer
- AsyncTCP
- HTML
- CSS
- JavaScript

---

## Project Structure

```
RC_CAR_PROJECT/
│
├── Firmware/
├── Web_UI/
├── Documents/
├── Images/
├── KiCad/
└── tools/
```

---

## Folder Description

### Firmware
Contains ESP32 source code.

### Web_UI
Contains the web interface.

### Documents
Project documentation.

### KiCad
Circuit schematic and PCB files.

### Images
Screenshots and project photos.

### tools
Utility scripts for generating webpage.h.

---

## Working Principle

1. ESP32 creates a Wi-Fi hotspot.
2. User connects to the hotspot.
3. Browser opens the control dashboard.
4. Commands are sent to ESP32 using HTTP.
5. ESP32 controls the TB6612FNG motor driver.
6. Motors move according to the received command.

---

## Future Improvements

- Camera Streaming
- Obstacle Avoidance
- Voice Commands
- Mobile Application
- OTA Firmware Updates
- GPS Tracking

---

## Developed By

Engineering Mini Project

2026
