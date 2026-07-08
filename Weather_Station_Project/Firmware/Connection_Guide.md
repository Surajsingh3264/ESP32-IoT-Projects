# 🌩️ Smart Weather Station: Master Hardware & Connection Guide

Complete hardware documentation, wiring tables, and safety guidelines for assembling the **ESP32 DevKit V1 (30-Pin)** Smart Weather Station with IAQ, Smoke Detection, Ambient Light Classification, and Battery Monitoring.

---

## ⚠️ Section 1: "Cautious Connections" & Danger Zones (Read First!)

Before plugging in a single wire or connecting USB power, review these **5 critical hardware safety rules** to prevent damaging your ESP32 or sensors.

### 1. ⚡ The Battery Voltage Divider Trap (`GPIO 35`)
* **The Danger:** Never connect a 3.7V / 4.2V LiPo or Li-Ion battery directly to `GPIO 35`. ESP32 Analog-to-Digital Converter (ADC) pins have a strict absolute maximum voltage rating of **3.3V**. Direct 4.2V battery voltage will permanently destroy the ADC channel and potentially fry the entire microcontroller.
* **The Solution:** You **must** use a 1:1 voltage divider circuit (two equal resistors) to step the battery voltage down by 50% (to ~2.1V max), which is safely within the ESP32's limits.

### 2. 🔌 The 5V vs. 3.3V Power Mix-Up
* **`VIN` Pin (5V):** Outputs ~5V when the ESP32 is powered via USB. **Only** connect the **MQ135 Gas Sensor VCC** to this pin, as its internal heater requires 5V to function accurately.
* **`3V3` Pin (3.3V):** Outputs regulated 3.3V from the onboard voltage regulator. Power your **OLED, BMP280, BH1750, DHT22, and Active Buzzer** from this pin.
* **The Danger:** Connecting 3.3V-rated sensors (like the SSD1306 OLED or BMP280) to the 5V `VIN` line will instantly destroy them.

### 3. 💡 RGB LED Current Limiting
* **The Danger:** Never wire the Red, Green, or Blue legs of an RGB LED directly to `GPIO 13`, `GPIO 12`, or `GPIO 14` without resistors. Without current-limiting resistors, the LED will draw excess current, burning out the LED diodes and damaging the ESP32 GPIO pins.
* **The Solution:** Place a **220Ω or 330Ω resistor** in series between each GPIO pin and the R, G, and B legs of the LED.

### 4. 🥾 The Boot-Strapping Button Warning (`GPIO 15`)
* **The Danger:** `GPIO 15` is a special **boot-strapping pin**. The ESP32 checks the electrical state of this pin during its power-up boot sequence to determine its boot mode.
* **The Solution:** **Do not hold the push button down while plugging in USB power or pressing the RESET button!** Holding it down at startup will pull the pin LOW and cause the ESP32 to fail to boot. Only press the button *after* the system has fully powered on.

### 5. 📡 Floating Analog Inputs
* **The Danger:** Unconnected analog input pins (`GPIO 34` and `GPIO 35`) act like microscopic radio antennas, absorbing room electromagnetic interference (EMI), Wi-Fi radio waves, and static electricity.
* **The Solution:** If you test the code without the MQ135 or Battery connected, those cards on the dashboard will display erratic, jumping numbers. To stabilize them during testing without sensors, tie those unused pins directly to `GND`.

---

## 📋 Section 2: Master Pin-by-Pin Wiring Table

| Component | Component Pin | ESP32 (30-Pin) | Notes & Required Resistors |
| :--- | :--- | :--- | :--- |
| **SSD1306 OLED** | VCC <br> GND <br> **SCL** <br> **SDA** | **3V3** <br> **GND** <br> **GPIO 22** <br> **GPIO 21** | Shares the 2-wire I²C bus with BMP280 and BH1750. |
| **BMP280 Sensor** | VCC <br> GND <br> **SCL / SCK** <br> **SDA / SDI** | **3V3** <br> **GND** <br> **GPIO 22** <br> **GPIO 21** | Shares the I²C bus. Leave `CS` and `SDO` disconnected/floating. |
| **BH1750 Light** | VCC <br> GND <br> **SCL** <br> **SDA** <br> **ADDR** | **3V3** <br> **GND** <br> **GPIO 22** <br> **GPIO 21** <br> **GND** | Shares the I²C bus. **Connect ADDR to GND** to assign default address `0x23`. |
| **DHT22 Temp/Hum**| VCC (+) <br> GND (-) <br> **OUT / DATA** | **3V3** <br> **GND** <br> **GPIO 4** | If using a bare white sensor (non-PCB module), add a **10kΩ pull-up resistor** between `VCC` and `DATA`. |
| **MQ135 Gas/Smoke**| VCC <br> GND <br> **AO (Analog Out)** | **VIN (5V)** <br> **GND** <br> **GPIO 34** | **Must power from VIN (5V)** for internal heating element. Do **not** use `DO` (Digital Out). |
| **Battery Divider** | Middle Junction <br> Resistor A <br> Resistor B | **GPIO 35** <br> Battery (+) <br> **GND** & Bat (-) | Uses two identical resistors (10kΩ, 47kΩ, or 100kΩ) in series. See Section 3 below. |
| **RGB LED** <br> *(Common Cathode)* | **R** (Red Leg) <br> **G** (Green Leg) <br> **B** (Blue Leg) <br> **GND** (Longest Leg) | **GPIO 13** <br> **GPIO 12** <br> **GPIO 14** <br> **GND** | **Must use 220Ω resistors** in series on the R, G, and B data lines! |
| **Active Buzzer** | VCC (+) <br> GND (-) <br> **I/O / SIG** | **3V3** <br> **GND** <br> **GPIO 27** | For 3-pin modules. For 2-pin buzzers, wire (+) directly to `GPIO 27` and (-) to `GND`. |
| **Push Button** | Pin 1 <br> Pin 2 | **GPIO 15** <br> **GND** | No resistor needed. Firmware uses internal pull-up (`INPUT_PULLUP`). |

---

## 🔋 Section 3: How to Safely Wire the Battery Voltage Divider

To measure LiPo / Li-Ion battery percentage safely without exceeding the ESP32's 3.3V ADC limit, build a **1:1 Voltage Divider** on your breadboard:



### Components Required
* 2× Identical Resistors (e.g., two **10kΩ**, **47kΩ**, or **100kΩ** resistors). Let's call them **Resistor A** and **Resistor B**.

### Step-by-Step Wiring
1. **Connect to Battery (+):** Insert one leg of **Resistor A** into the row connected to your Battery Positive (`+`) terminal.
2. **Connect to Ground (-):** Insert one leg of **Resistor B** into the row connected to your Battery Negative (`-`) terminal and ESP32 `GND`.
3. **Create the Center Junction:** Connect the remaining middle legs of **Resistor A** and **Resistor B** together on a vacant breadboard row.
4. **Connect to Microcontroller:** Run a single jumper wire from that **middle junction row** directly to **`GPIO 35`**.

> **How it works:** When a 4.2V battery is attached, the two equal resistors divide the voltage exactly in half. `GPIO 35` reads 2.1V. Our firmware multiplies this reading by `2.0` (`VOLTAGE_DIVIDER_R`) to accurately display 4.20V and 100% on the dashboard! When disconnected, it drops near 0V and displays `"USB Power (No Battery)"`.

---

## 🌐 Section 4: Wiring the Shared I²C Bus (`SDA` / `SCL`)

The **SSD1306 OLED**, **BMP280 Barometer**, and **BH1750 Light Sensor** all communicate using the I²C protocol. They must be wired in parallel to the exact same two GPIO pins.



### Step-by-Step Breadboard Setup
1. **Establish Bus Rows:** Dedicate one full 5-hole row on your breadboard as the **SDA Bus** and a second row as the **SCL Bus**.
2. **Link to ESP32:**
   * Connect a jumper wire from ESP32 **`GPIO 21`** to your dedicated **SDA Bus** row.
   * Connect a jumper wire from ESP32 **`GPIO 22`** to your dedicated **SCL Bus** row.
3. **Connect Sensors in Parallel:**
   * Plug the `SDA` pin of the **OLED**, **BMP280**, and **BH1750** into the **SDA Bus** row.
   * Plug the `SCL` pin of the **OLED**, **BMP280**, and **BH1750** into the **SCL Bus** row.
4. **Power the Bus:** Connect the `VCC` pins of all three modules to the breadboard's **`3V3` Red Rail** and their `GND` pins to the **`GND` Blue Rail**.

---

## 🛠️ Section 5: Step-by-Step Breadboard Assembly

Follow this logical assembly order to keep your wiring clean and easy to troubleshoot:

1. **Power Rails First:**
   * Connect ESP32 **`3V3`** to the breadboard **Red (+) Rail**.
   * Connect ESP32 **`GND`** to the breadboard **Blue (-) Rail**.
   * *Do not connect `VIN` to the red rail!* Leave `VIN` isolated for the MQ135 heater.
2. **I²C Display & Sensors:** Wire the OLED, BMP280, and BH1750 to `GPIO 21` and `GPIO 22` as outlined in Section 4.
3. **Environment & Gas Sensors:**
   * Wire the **DHT22** data pin to `GPIO 4` (power from `3V3`).
   * Wire the **MQ135** analog output (`AO`) to `GPIO 34` (power heater from `VIN` 5V).
4. **Indicators & Controls:**
   * Wire the **RGB LED** cathodes/resistors to `GPIO 13`, `12`, and `14` (common pin to `GND`).
   * Wire the **Active Buzzer** signal to `GPIO 27` (power from `3V3`).
   * Wire the **Tactile Push Button** across `GPIO 15` and `GND`.
5. **Battery Monitoring:** Assemble the resistor voltage divider on `GPIO 35` as outlined in Section 3.

---

## 🚀 Section 6: Pre-Power Checklist

Before plugging the Micro-USB cable into your computer or power bank, complete this physical audit:

- [ ] **No 5V on 3.3V Rail:** Check that only the MQ135 is wired to `VIN` (5V). The OLED, BMP280, BH1750, DHT22, and Buzzer must be wired to `3V3`.
- [ ] **I²C Lines Correct:** Verify that `GPIO 21` goes exclusively to `SDA` pins and `GPIO 22` goes exclusively to `SCL` pins. Reversing them will result in an empty OLED screen and serial bus errors.
- [ ] **Resistors Installed:** Confirm that 220Ω/330Ω resistors are placed on the R, G, and B lines of the LED, and that the battery divider resistors are properly seated.
- [ ] **Shared Ground:** Verify that all sensor `GND` pins, the RGB LED cathode, the button ground, the battery negative terminal, and the ESP32 `GND` pin all connect to the common ground rail.
- [ ] **No Short Circuits:** Ensure no bare resistor leads or jumper wires are touching adjacent pins or crossing metal components.

---

## 🏁 System Boot & Verification

1. Plug in the Micro-USB cable. The RGB LED should briefly flash Green, and the OLED will light up with the **Smart Weather Station** splash screen.
2. Open your smartphone or laptop Wi-Fi settings and connect to the access point:
   * **SSID:** `ESP32_Weather`
   * **Password:** `12345678`
3. Open a web browser and navigate to **`http://192.168.4.1`** to view your live, SVG-loaded daylight web dashboard!
