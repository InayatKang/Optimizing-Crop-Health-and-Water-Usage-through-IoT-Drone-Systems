# Optimizing-Crop-Health-and-Water-Usage-through-IoT-Drone-Systems
This repository contains all the files and documentation for my final project: optimizing crop health and water usage through IoT drone systems. The project integrates various sensors with a drone to monitor environmental conditions and provide actionable insights for irrigation.

Project Overview
The project aims to develop a real-time crop monitoring drone system with IoT sensor integration. The system tracks trends in crop health and optimizes water usage by collecting data on temperature, humidity, and light levels. This data is then analyzed to determine the optimal times for irrigation, helping farmers make more informed decisions.

**Repository Contents**
Arduino Code: Includes code for interfacing with sensors (DHT11, photoresistor, HC-SR04) and controlling the bicopter.

CAD Files: Detailed designs and models of the bicopter used in the project.

Python Scripts: Code for analyzing sensor data and generating irrigation recommendations based on collected data.

Web App: Streamlit-based web application for users to upload CSV files, analyze data, and get irrigation recommendations.

**Key Features**
IoT Integration: Utilizes ESP8266 and various sensors to collect and transmit data.

Real-time Monitoring: Provides up-to-date environmental data for better decision-making.

Data Analysis: Analyzes historical and real-time data to recommend optimal irrigation times.

Web Interface: Allows users to upload data, view analysis results, and get recommendations.

**Set Up Hardware:**
Connect sensors to the Arduino according to the provided schematics.

Upload the Arduino code to your board.

**Run the Web App:**
Install required Python libraries.
Run the Streamlit app to start analyzing your data.

**Upload Data:**
Upload CSV files exported from IoT devices to the web app to get irrigation recommendations.

Feel free to explore the code and documentation, and let me know if you have any questions or need further assistance!
