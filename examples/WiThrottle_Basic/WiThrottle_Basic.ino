// WiThrottle library: Basic example
//
// Shows how to create an instance of WiThrottle
// and how to connect to a WiThrottle server using static IP
// Tested with ESP32-DEVKITC development board
//
// Luca Dentella, 2020

#include <WiFi.h>
#include <WiThrottle.h>

// WiFi and server configuration
const char* ssid = "MySSID";
const char* password =  "MyPWD";
IPAddress serverAddress(192,168,1,1);
int serverPort = 12090;

// Global objects
WiFiClient client;
WiThrottle wiThrottle;
  
void setup() {
  
  Serial.begin(115200);
  Serial.println("WiThrottle Basic Demo");
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
}
