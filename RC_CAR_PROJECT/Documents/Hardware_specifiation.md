# ESP32 HTTP RC Car Hardware Specification

## Controller
- ESP32 DevKit V1 (38-pin)

## Power System
- 2 × 18650 Li-ion Batteries (Series)
- 2S BMS Protection Board
- LM2596 Buck Converter (5V Output)
- Rocker Switch

## Motion System
- TB6612FNG Motor Driver
- 2 × BO Geared Motors
- 4-Wheel Chassis (Rear Wheel Drive)

## Accessories
- 2 × White LEDs (Headlights)
- Active Buzzer

## Communication
- Wi-Fi HTTP Server

## Power Flow

Battery
↓
2S BMS
↓
Power Switch
↓
├── TB6612 VM
└── LM2596
        ↓
     ESP32 VIN

## Notes

- Rear motors only
- Differential steering
- No servo
- Battery powered
