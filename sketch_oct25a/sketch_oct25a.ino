#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//Initialize the WiFi Network
const char* SSID = "jm";
const char* password = "jm012818";

//Declare the server of the webpage
const char* server = "http://192.168.8.105:5000/dashboard/data";

// Define the DHT sensor type and pin
#define DHTPIN 17      // Pin connected to the DHT11 sensor's DATA pin
#define DHTTYPE DHT11  // DHT 11

//define pin for trig and echo pin for Ultrasonic Sensor
#define TrigPin 19
#define EchoPin 18

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial monitor
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  //pin mode for trig and echo for Ultrasonic Sensor
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  //connect to the WiFi network
  WiFi.begin(SSID, password);
  Serial.println("Connecting to WiFi...");

  //Check the status of the WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Wait a few seconds between sensor readings
  delay(3000);

  // Reading humidity
  float humidity = dht.readHumidity();

  // Check if any readings failed and exit early (to try again).
  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //variables for reading ultrasonic sensor
  long duration, distance;

  //clear the TrigPin
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);

  //set TrigPin to HIGH for 10 microseconds
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  //read the duration from the EchoPin
  duration = pulseIn(EchoPin, HIGH);

  distance = duration * 0.034 / 2;

  // Print the results to the serial monitor
  Serial.print("\nHumidity: ");
  Serial.print(humidity);

  //Print the distance measured from the Ultrasonic Sensor
  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.print("cm");

  //for sending data from DHT 11 to the webpage
  //checking the the status of the wifi if it is connected
  if(WiFi.status() == WL_CONNECTED){

    //Initialize the HTTP client
    HTTPClient http;

    //destination of the URL
    http.begin(server);
    //http.begin(server2);
    http.addHeader("Content-Type", "application/json");

    //create a JSON object with sensor datas
    StaticJsonDocument<200> jsonDoc;

    jsonDoc["humidity"] = humidity;
    jsonDoc["distance"] = distance;

    //Convert the jsonDoc into String
    String requestBody;
    serializeJson(jsonDoc, requestBody);

    //send HTTP Post request with JSON Body
    int httpResponseCode = http.POST(requestBody);

    //check the response code
    if(httpResponseCode > 0){
      Serial.print("\nServer recieved data: ");
      Serial.println(requestBody);
    }else{
      Serial.print("\nError on sending POST: ");
      Serial.println(httpResponseCode);
    }

    //end the HTTP connection
    http.end();
  }else{
    Serial.println("WiFi not connected");
  }

}
