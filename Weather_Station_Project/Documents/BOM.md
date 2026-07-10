# Smart Environment Monitor
## Bill of Materials (BOM)

| S.No | Component | Quantity | Specification | Purpose | Approx. Price (₹) |
|------|-----------|:--------:|---------------|---------|------------------:|
| 1 | ESP32 DevKit V1 | 1 | ESP32-WROOM-32 (30-pin) | Main controller | |
| 2 | DHT22 Sensor | 1 | Temperature & Humidity | Environmental sensing | |
| 3 | BMP280 | 1 | Pressure & Altitude | Atmospheric pressure | |
| 4 | BH1750 | 1 | Digital Light Sensor | Ambient light measurement | |
| 5 | MQ135 | 1 | Air Quality Sensor | Air quality monitoring | |
| 6 | SSD1306 OLED | 1 | 0.96" I2C, 128×64 | Local display | |
| 7 | Active Buzzer | 1 | 3.3–5 V | Audible alerts | |
| 8 | RGB LED | 1 | Common Cathode/Anode (specify which you used) | Status indication | |
| 9 | Push Button | 1 | Momentary tactile switch | OLED page lock/unlock | |
| 10 | 220 Ω Resistor | 3 | ¼ W | RGB LED current limiting | |
| 11 | Breadboard | 1 | 830 tie-point | Prototyping | |
| 12 | Male–Male Jumper Wires | 1 Pack | Assorted lengths | Connections | |
| 13 | USB Cable | 1 | USB to ESP32 connector | Power & programming | |

## Software

- Arduino IDE
- ESP32 Arduino Core
- DHT Library
- Adafruit BMP280 Library
- Adafruit GFX Library
- Adafruit SSD1306 Library
- BH1750 Library

## Firmware Features

- Wi-Fi Access Point
- Responsive Web Dashboard
- Live Sensor Updates
- OLED Display
- AQI Monitoring
- RGB Status Indicator
- Active Buzzer Alerts
- Device Information Panel
- Serial Debug Logging
- Automatic Sensor Detection

## Power Requirements

- Input: 5 V via USB
- ESP32 Logic: 3.3 V
- Typical Current: Depends on attached peripherals
