# Smart Flower Pot 🌼

## Project Demo 🎥

Download and watch the demo video from the repository:  
[Smart_Flower_Pot_Demo.mp4](https://github.com/Vimukthixsandeepa/smart-flower-pot/blob/main/project%20prototype.mp4)
https://github.com/Vimukthixsandeepa/smart-flower-pot/blob/main/project%20prototype.mp4
An IoT-based smart system designed to monitor and maintain the health of plants by automating watering and providing real-time environmental data.

## Features 🚀
- Monitors soil moisture, temperature, and humidity levels.
- Automatically waters plants based on soil moisture threshold.
- Displays real-time data on a mobile application or web dashboard.
- Sends alerts for extreme environmental conditions.

## Technology Stack 🛠️
- **Hardware:**
  - ESP32 microcontroller
  - Soil moisture sensor
  - DHT11/DHT22 sensor for temperature and humidity
  - Water pump and relay module
- **Software:**
  - **Programming Languages:** Python, C++
  - **Frameworks & Libraries:** Arduino IDE, Flask
  - **Mobile App:** blynk app

## How It Works 🌀
1. **Data Collection:**
   - Sensors collect data on soil moisture, temperature, and humidity.
2. **Data Processing:**
   - The ESP32 processes sensor data and determines if watering is required.
3. **Automation:**
   - If the soil moisture is below the set threshold, the water pump is activated.
4. **User Interface:**
   - Real-time data is sent to a Firebase database and visualized on a mobile app or web interface.

## System Architecture 🏗️
```text
Sensors (Soil Moisture, Temperature, Humidity)
        |
        v
      ESP32 (Data Processing)
        |
        v

Mobile App / Web Dashboard (Real-Time Visualization-blynk app)
