# Project Architecture

## Overview

The ESP32 Wi-Fi RC Car is designed using a client-server architecture. The ESP32 acts as both the Wi-Fi Access Point and the web server. A user connects to the ESP32 using a smartphone or laptop, opens the web dashboard, and controls the vehicle through HTTP requests.

---

# High Level Architecture

```
               Smartphone / Laptop
                        │
                        │ HTTP Requests
                        ▼
               ESP32 Web Server
                        │
        ┌───────────────┼───────────────┐
        │               │               │
        ▼               ▼               ▼
   Motor Control   Accessories   Battery Monitor
        │               │               │
        ▼               ▼               ▼
   TB6612FNG       LEDs / Buzzer     ADC GPIO34
        │
        ▼
   Left & Right Motors
```

---

# Software Architecture

```
Firmware
│
├── Wi-Fi Access Point
├── Async Web Server
├── HTTP Route Handler
├── Motor Controller
├── Headlight Controller
├── Horn Controller
├── Battery Monitor
└── Web Interface
```

---

# Project Directory

```
RC_CAR_PROJECT/
│
├── Firmware/
│   ├── ESP32_HTTP_RC_CAR.ino
│   ├── pins.h
│   └── webpage.h
│
├── Web_UI/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
├── Documents/
│
├── KiCad/
│
├── Images/
│
└── tools/
    └── convert.py
```

---

# Request Flow

```
User presses button
        │
        ▼
JavaScript fetch()
        │
        ▼
HTTP Request
        │
        ▼
ESP32 Route Handler
        │
        ▼
Motor Function
        │
        ▼
TB6612FNG
        │
        ▼
Motor Movement
```

---

# Speed Control Flow

```
Speed Slider
      │
      ▼
JavaScript
      │
      ▼
/speed?value=180
      │
      ▼
ESP32 Updates PWM
      │
      ▼
Motor Speed Changes
```

---

# Battery Monitoring Flow

```
Battery Voltage
        │
        ▼
Voltage Divider
        │
        ▼
GPIO34 ADC
        │
        ▼
Battery Percentage
        │
        ▼
/status API
        │
        ▼
JavaScript
        │
        ▼
Battery Indicator
```

---

# Headlight Flow

```
Headlight Button
        │
        ▼
/light/on
/light/off
        │
        ▼
ESP32 GPIO16
        │
        ▼
LED Headlights
```

---

# Horn Flow

```
Horn Button
       │
       ▼
/horn/on
/horn/off
       │
       ▼
ESP32 GPIO4
       │
       ▼
Active Buzzer
```

---

# Advantages of This Architecture

- Modular project structure
- Responsive web-based control
- No mobile application required
- Platform independent
- Easy to maintain
- Easy to expand with additional sensors
- Lightweight firmware
- Fast communication using HTTP

---

# Future Expansion

The architecture can be extended to support:

- Live camera streaming (ESP32-CAM)
- Obstacle avoidance
- Autonomous driving
- Voice commands
- Mobile application
- Cloud connectivity
- OTA firmware updates
- GPS tracking
