#include <WiFi.h>
#include <WiFiUdp.h>
#include "DHT.h"

// Wi-Fi credentials
const char* ssid = "X-Treme";
const char* password = "VersePass@";

// UDP server
const char* udpAddress = "192.168.1.174"; 
const int udpPort = 5005;

WiFiUDP udp;

// DHT sensor setup
#define DHTPIN 4          
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String message = "Sensor-1|" + String(temp) + "|°C";

  udp.beginPacket(udpAddress, udpPort);
  udp.print(message);
  udp.endPacket();

  Serial.println("Sent: " + message);

  delay(2000); // Send every 2 seconds
}
