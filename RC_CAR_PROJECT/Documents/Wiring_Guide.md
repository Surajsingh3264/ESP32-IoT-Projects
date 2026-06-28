# Wiring Guide

## Overview

This guide describes all electrical connections required to assemble the ESP32 Wi-Fi RC Car.

---

# Required Components

- ESP32 Dev Module
- TB6612FNG Motor Driver
- 2 × BO DC Gear Motors
- 2 × LED Headlights
- 1 × Active Buzzer
- Battery Pack
- Power Switch
- Jumper Wires

---

# ESP32 → TB6612FNG

| ESP32 GPIO | TB6612FNG Pin | Purpose |
|------------|---------------|---------|
| GPIO25 | AIN1 | Left Motor Direction 1 |
| GPIO26 | AIN2 | Left Motor Direction 2 |
| GPIO33 | PWMA | Left Motor Speed (PWM) |
| GPIO27 | BIN1 | Right Motor Direction 1 |
| GPIO14 | BIN2 | Right Motor Direction 2 |
| GPIO32 | PWMB | Right Motor Speed (PWM) |
| GPIO13 | STBY | Driver Enable |
| GND | GND | Common Ground |

---

# Motor Connections

## Left Motor

| TB6612 Pin | Motor Wire |
|-------------|------------|
| A01 | Left Motor Terminal 1 |
| A02 | Left Motor Terminal 2 |

---

## Right Motor

| TB6612 Pin | Motor Wire |
|-------------|------------|
| B01 | Right Motor Terminal 1 |
| B02 | Right Motor Terminal 2 |

> If a motor rotates in the wrong direction, swap its two wires.

---

# Headlights

| ESP32 GPIO | Component |
|------------|-----------|
| GPIO16 | LED Positive (through 220Ω resistor) |
| GND | LED Negative |

For two LEDs, connect them in parallel, each with its own resistor.

---

# Horn

| ESP32 GPIO | Component |
|------------|-----------|
| GPIO4 | Active Buzzer Positive |
| GND | Active Buzzer Negative |

---

# Battery Monitoring

| ESP32 GPIO | Component |
|------------|-----------|
| GPIO34 | Voltage Divider Output |

> Never connect the battery directly to GPIO34. Use a suitable voltage divider to keep the voltage within the ESP32 ADC input range.

---

# Power Connections

## Battery

| Battery | Connect To |
|----------|------------|
| Positive | TB6612 VM |
| Negative | TB6612 GND |

---

## ESP32 Power

Choose one method:

### Option 1 (Recommended)

Battery → Buck Converter (5V) → ESP32 VIN

### Option 2

USB Cable → ESP32

---

# Common Ground

The following grounds **must** be connected together:

- ESP32 GND
- TB6612 GND
- Battery Negative
- Buzzer GND
- LED GND

A shared ground is required for reliable operation.

---

# Wi-Fi Connection

1. Power on the RC Car.
2. Connect your phone to the Wi-Fi network:

```

SSID: RC_CAR
Password: 12345678

```

3. Open:

```

http://192.168.4.1

```

4. The control dashboard will appear.

---

# Power-On Checklist

- Battery connected
- ESP32 powered
- TB6612 STBY connected
- Motors connected
- LEDs connected
- Buzzer connected
- Common GND connected
- Firmware uploaded

---

# Safety Notes

- Double-check all wiring before applying power.
- Do not reverse battery polarity.
- Do not short motor terminals.
- Disconnect power before modifying wiring.
- Ensure the battery is adequately charged before testing.
- Test the car with the wheels lifted off the ground before placing it on the floor.

---

# Initial Functional Test

After uploading the firmware:

- Test Forward
- Test Backward
- Test Left
- Test Right
- Test Stop
- Test Speed Slider
- Test Headlights
- Test Horn
- Check Battery Indicator
