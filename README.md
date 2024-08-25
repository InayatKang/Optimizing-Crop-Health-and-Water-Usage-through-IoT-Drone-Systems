# Smart Crop Monitoring and Irrigation System

## Introduction
This project is a smart crop monitoring and irrigation system designed to help farmers optimize water usage by analyzing environmental data. It leverages IoT sensors to gather real-time data, such as temperature, humidity, crop height, and light levels, to determine the best times to irrigate crops. The system provides data-driven recommendations based on customizable thresholds and trends.

The project includes:
- Code for interfacing with sensors (DHT11, photoresistor, etc.).
- A Python-based web application that allows users to upload CSV files of sensor data and receive irrigation recommendations.

## Project Structure
```
- /code/                 # Contains Arduino and ESP8266 code for the sensors
- /web_app/              # Contains the Streamlit web application files
- /data_samples/         # Sample CSV files for testing
- README.md              # Project documentation (this file)
```

## Getting Started

### Prerequisites
- Python 3.x
- Streamlit (`pip install streamlit`)
- Arduino IDE (for uploading code to ESP8266/Arduino)
- Blynk (for sensor data logging)

### How to Use

1. **Hardware Setup:**
   - Connect the sensors (DHT11, photoresistor, etc.) to your ESP8266/Arduino following the wiring diagrams provided in the `/code/` folder.
   - Upload the relevant code from the `/code/` folder to your ESP8266/Arduino using the Arduino IDE.
   - Ensure the ESP8266/Arduino is connected to the internet or a Wi-Fi network for data logging.

2. **Web Application:**
   - Clone this repository:
     ```bash
     git clone https://github.com/your-username/Smart-Irrigation-Analyzer.git
     ```
   - Navigate to the `web_app` directory:
     ```bash
     cd Smart-Irrigation-Analyzer/web_app
     ```
   - Run the Streamlit app:
     ```bash
     streamlit run app.py
     ```
   - Upload your CSV file exported from Blynk (or use the sample files in `/data_samples/`) to get irrigation recommendations.

3. **Analyzing Data:**
   - The web app provides insights based on your data, including the best times to irrigate your crops based on historical trends and environmental conditions.

### Customizing Thresholds
You can modify the threshold conditions in the Python code (located in `web_app/app.py`) to suit your specific crop needs.

### Sample Data
You can find sample CSV files in the `/data_samples/` folder to test the web app and see how the recommendations are generated.

## Future Improvements
- Integration with machine learning models for more precise predictions.
- Automated alert systems for irrigation recommendations.
- Expanding support for additional sensors and data inputs.

## Acknowledgments
This project was developed as part of a research initiative at the Schulich School of Engineering, with funding from the WISE UCalgary program.

