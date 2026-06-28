# GPIO Mapping

## ESP32 Pin Configuration

| GPIO Pin | Connected Device | Description |
|----------:|------------------|-------------|
| GPIO 25 | AIN1 | Motor A Direction 1 |
| GPIO 26 | AIN2 | Motor A Direction 2 |
| GPIO 27 | BIN1 | Motor B Direction 1 |
| GPIO 14 | BIN2 | Motor B Direction 2 |
| GPIO 33 | PWMA | Motor A PWM Speed |
| GPIO 32 | PWMB | Motor B PWM Speed |
| GPIO 13 | STBY | Motor Driver Standby |
| GPIO 16 | LED Headlights | Front Lights |
| GPIO 4 | Active Buzzer | Horn |
| GPIO 34 | Battery Voltage | Battery Monitoring |

---

## Power Connections

| Device | Voltage |
|---------|---------|
| ESP32 | 5V USB / VIN |
| TB6612 Logic | 3.3V |
| Motors | Battery Supply |
| LEDs | 3.3V (with resistor) |
| Active Buzzer | 3.3V |

---

## Communication

- Wi-Fi Mode: Access Point (AP)
- SSID: **RC_CAR**
- Password: **12345678**
- Default IP Address: **192.168.4.1**

---

## PWM Configuration

| Parameter | Value |
|-----------|------:|
| Frequency | 1000 Hz |
| Resolution | 8-bit |
| Speed Range | 0–255 |

---

## Notes

- GPIO 34 is input-only and is used for battery voltage sensing.
- STBY must be HIGH to enable the TB6612FNG motor driver.
- PWMA and PWMB provide PWM signals for motor speed control.
