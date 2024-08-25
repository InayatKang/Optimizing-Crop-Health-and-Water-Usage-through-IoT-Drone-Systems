/*************************************************************
  Blynk Project: Smart Plant Monitoring
  Components: ESP8266, DHT11, Photoresistor, Distance Sensor
  Rain Probability Code has been adapted from https://github.com/voletibhaskar/Rain-Predictor-Arduino/blob/master/Algorithm 
*************************************************************/

/* Fill-in information from Blynk Device Info here */

#define BLYNK_TEMPLATE_ID "#####" //Replace with your own
#define BLYNK_TEMPLATE_NAME "####"//Replace with your own
#define BLYNK_AUTH_TOKEN "#####"//Replace with your own

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// Your WiFi credentials
const char ssid[] = "##"; // replace with your wifi ssid
const char pass[] = "##"; // replace with your password

// Your ESP8266 baud rate
#define ESP8266_BAUD 9600

// Define pins and virtual pins
#define DHTPIN 4   // Pin which is connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define LDR_PIN A0
#define DISTANCE_TRIG_PIN 5   // Define the TRIG pin of the distance sensor
#define DISTANCE_ECHO_PIN 6   // Define the ECHO pin of the distance sensor
#define TEMP_VPIN V0
#define HUMIDITY_VPIN V1
#define LIGHT_VPIN V2
#define DISTANCE_VPIN V4  // Virtual pin for distance sensor
#define RAIN_PROB_TEXT_VPIN V3 // Virtual pin for text

// Create instances
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
SoftwareSerial EspSerial(2, 3); // RX, TX
ESP8266 wifi(&EspSerial);

void setup() {
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);

  dht.begin();

  // Initialize distance sensor pins
  pinMode(DISTANCE_TRIG_PIN, OUTPUT);
  pinMode(DISTANCE_ECHO_PIN, INPUT);

  // Setup functions to be called periodically
  timer.setInterval(1000L, readSensors);   // 1 second interval
}

void readSensors() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int lightLevel = analogRead(LDR_PIN);
  
  // Read distance
  long duration;
  float distance;

  digitalWrite(DISTANCE_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(DISTANCE_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCE_TRIG_PIN, LOW);

  duration = pulseIn(DISTANCE_ECHO_PIN, HIGH);
  distance = (duration / 2.0) * 0.0344; // Convert duration to distance in cm

  //Inverse the distance reading
  float maxDistance = 400.0; // Maximum expected distance in cm when drone is 400cm above ground//Change this number to dorne height above ground
  if (distance <= maxDistance) {
    distance = maxDistance - distance;
  } else {
    distance = 0; // Set to 0 if distance exceeds the max range
  }

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Calculate rain probability and corresponding text
  String rainProbabilityText = "Very Low Chance"; // Default to very low chance
  int possibility = -1; // Default to very low chance
  if (h > 70.0) {
    if (t >= -0 && t < 10) { //0 is the freezing point of water therefore it is at the lower scale
      if (lightLevel < 500) { possibility = 3; rainProbabilityText = "Moderate Chance"; }
      else if (lightLevel < 700) { possibility = 2; rainProbabilityText = "Slight Chance"; }
      else if (lightLevel < 800) { possibility = 1; rainProbabilityText = "Low Chance"; }
      else if (lightLevel < 1000) { possibility = 0; rainProbabilityText = "Very Low Chance"; }
      else { possibility = -1; rainProbabilityText = "Very Low Chance"; }
    } else if (t >= 10 && t < 23) {
      if (lightLevel < 500) { possibility = 4; rainProbabilityText = "High Chance"; }
      else if (lightLevel < 700) { possibility = 3; rainProbabilityText = "Moderate Chance"; }
      else if (lightLevel < 800) { possibility = 2; rainProbabilityText = "Slight Chance"; }
      else if (lightLevel < 1000) { possibility = 1; rainProbabilityText = "Low Chance"; }
      else { possibility = 0; rainProbabilityText = "Very Low Chance"; }
    } else if (t >= 23 && t < 30) {
      if (lightLevel < 500) { possibility = 5; rainProbabilityText = "Very High Chance"; }
      else if (lightLevel < 700) { possibility = 4; rainProbabilityText = "High Chance"; }
      else if (lightLevel < 800) { possibility = 3; rainProbabilityText = "Moderate Chance"; }
      else if (lightLevel < 1000) { possibility = 1; rainProbabilityText = "Low Chance"; }
      else { possibility = 0; rainProbabilityText = "Very Low Chance"; }
    } else if (t >= 30) {
      if (lightLevel < 500) { possibility = 5; rainProbabilityText = "Very High Chance"; }
      else if (lightLevel < 700) { possibility = 4; rainProbabilityText = "High Chance"; }
      else if (lightLevel < 800) { possibility = 3; rainProbabilityText = "Moderate Chance"; }
      else if (lightLevel < 1000) { possibility = 1; rainProbabilityText = "Low Chance"; }
      else { possibility = 0; rainProbabilityText = "Very Low Chance"; }
    }
  } else if (h <= 65.0) {
    possibility = 0;
    rainProbabilityText = "Very Low Chance";
  }

  // Print data to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Light Level: ");
  Serial.print(lightLevel);
  Serial.print("\tDistance: ");
  Serial.print(distance);
  //Serial.print(" cm\tRain Possibility: ");
  //Serial.print(possibility);
  Serial.print(" (");
  Serial.print(rainProbabilityText);
  Serial.println(")");

  // Send data to Blynk
  Blynk.virtualWrite(TEMP_VPIN, t);
  Blynk.virtualWrite(HUMIDITY_VPIN, h);
  Blynk.virtualWrite(LIGHT_VPIN, lightLevel);
  Blynk.virtualWrite(DISTANCE_VPIN, distance); // Send distance to Blynk
  Blynk.virtualWrite(RAIN_PROB_TEXT_VPIN, rainProbabilityText); // Send text to Blynk
}

void loop() {
  Blynk.run();
  timer.run();
}
