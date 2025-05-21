# 🌡️ ESP32 DHT22 MQTT Sensor Project

This project reads temperature and humidity data from a **DHT22 sensor** using an **ESP32** microcontroller. It then publishes this data to a **Mosquitto MQTT broker** running on a local host machine and also displays the readings on a **1.3-inch SH1106 OLED screen**.

---

## 🧰 Hardware Components

1. ESP32 Dev Board  
2. Breadboard  
3. Jumper Wires (Male to Male)  
4. DHT22 Temperature & Humidity Sensor  
5. OLED Display (1.3" SH1106)

---

## 💻 Software Requirements

1. [Arduino IDE](https://www.arduino.cc/en/software)  
2. [Mosquitto MQTT Broker](https://mosquitto.org/download/)  
3. [MQTT Explorer](https://mqtt-explorer.com/)

> ✅ _Assuming all software tools are already installed and configured._

---

## ⚙️ Working

- The **ESP32** reads temperature and humidity values from the **DHT22 sensor** connected to **GPIO 15**.
- It displays the live data on the **OLED screen**.
- Simultaneously, the data is **published to the local MQTT broker (Mosquitto)** on port `1883`.
- The broker is assumed to be running on the **local machine**, listening for incoming messages from devices on the same Wi-Fi network.

---

## 📡 MQTT Topics Used

- `sensor/data/temperature` – for temperature data  
- `sensor/data/humidity` – for humidity data

---

## 🧪 How to Test

### 🖥️ Using Command Line:

Run this in your terminal or command prompt:

```bash
mosquitto_sub -t "sensor/data/temperature" -t "sensor/data/humidity"

# Notes
1.The ESP32 and your computer will be on the same network
2.Check if the mosquitto broker is initialized for listening incoming data from the 1883 port
3.Even after intializing the Mosquitto broker and data is not coming , create a new rule in window firewall protection .open the window firewall protection -> advance settinng -> Inbound setting -> New rules.
  click on type of rules in our case is Port , click on type of port which TCP and click on "All ports" . Then click next until the name of the rules arrived . write the name of the rule and save.