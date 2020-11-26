// WiThrottle library: FastTime example
//
// Shows how to use the Time library (https://github.com/PaulStoffregen/Time)
// to parse FastTime timestamp 
// DO NOT use Serial Monitor but a "real" terminal (PuTTY, RealTerm) 
// Tested with ESP32-DEVKITC development board
//
// Luca Dentella, 2020

#include <WiFi.h>
#include <WiThrottle.h>
#include <TimeLib.h>

// WiFi and server configuration
const char* ssid = "MySSID";
const char* password =  "MyPWD";
IPAddress serverAddress(192,168,1,1);
int serverPort = 12090;

// Global objects
WiFiClient client;
WiThrottle wiThrottle;
unsigned long lastPrint = 0;
  
void setup() {
  
  Serial.begin(115200);
  Serial.println("WiThrottle FastTime Demo");
  Serial.println();

  // Connect to WiFi network
  Serial.println("Connecting to WiFi.."); 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) delay(1000);  
  Serial.print("Connected with IP: "); Serial.println(WiFi.localIP());

  // Connect to the server
  Serial.println("Connecting to the server...");
  if (!client.connect(serverAddress, serverPort)) {
    Serial.println("connection failed");
    while(1) delay(1000);
  }
  Serial.println("Connected to the server");

  // Uncomment for logging on Serial
  //wiThrottle.setLogStream(&Serial);

  // Pass the communication to WiThrottle
  wiThrottle.connect(&client);
  Serial.println("WiThrottle connected");
  wiThrottle.setDeviceName("myFirstThrottle");  
}
  
void loop() {

  // parse incoming messages
  wiThrottle.check();

  // every second, get the current fasttime, parse and print
  if(millis() - lastPrint > 1000) {
    time_t fastTime = (time_t)wiThrottle.getCurrentFastTime();
    Serial.print(hour(fastTime));
    Serial.print(":");
    Serial.print(minute(fastTime));
    Serial.print("\r");
    lastPrint = millis();    
  }  
}
