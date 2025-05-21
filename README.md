# 🌡️ ESP32 DHT22 MQTT Sensor Project

This project reads temperature and humidity data from a **DHT22 sensor** using an **ESP32** microcontroller. It then publishes the data to a **Mosquitto MQTT broker** running on a local machine and also displays the readings on a **1.3-inch SH1106 OLED screen**.

---

## 🧰 Hardware Components

- ESP32 Dev Board  
- Breadboard  
- Jumper Wires (Male to Male)  
- DHT22 Temperature & Humidity Sensor  
- OLED Display (1.3" SH1106)

---

## 💻 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)  
- [Mosquitto MQTT Broker](https://mosquitto.org/download/)  
- [MQTT Explorer](https://mqtt-explorer.com/)

> ✅ *Assumes all software tools are already installed and configured.*

---

## ⚙️ Working

- The **ESP32** reads temperature and humidity values from the **DHT22 sensor** connected to **GPIO 15**.
- It displays the live data on the **OLED screen**.
- Simultaneously, the data is **published to a local MQTT broker (Mosquitto)** on port `1883`.
- The broker is assumed to be running on the **local machine**, listening for incoming messages from devices on the same Wi-Fi network.

---

## 📡 MQTT Topics Used

- `sensor/data/temperature` – Temperature data  
- `sensor/data/humidity` – Humidity data

---

## 🧪 How to Test

### 🖥️ Using Command Line

```bash
mosquitto_sub -t "sensor/data/temperature" -t "sensor/data/humidity"
```
---

## 📊 Using MQTT Explorer
Open MQTT Explorer.

Create a new connection.

Enter your local machine’s IP address (e.g., 192.168.x.x) and port 1883.

Click Connect to view the published data.

---

## 📝 Notes
Ensure the ESP32 and your computer are connected to the same Wi-Fi network.

Verify that the Mosquitto broker is running and listening on port 1883.

If data is not received:

Open Windows Defender Firewall.

Go to Advanced Settings → Inbound Rules → New Rule.

Select Port → choose TCP → either specify port 1883 or All Ports.

Click Next until the naming step.

Give a name like "MQTT Allow" and save the rule.

---