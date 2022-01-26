#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

///Define WiFi Credentials
#ifndef APSSID
#define APSSID "ESP.net"
#define APPSK  "thereisnospoon"
#endif
const char *ssid = APSSID;
const char *password = APPSK;

#define DHTTYPE DHT11

#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

ESP8266WebServer server(80);


void handleRoot() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  String res = "Temperature: " + String(t) + "&#8451;<br>Humidity: " + String(h) + "%";
  server.send(200, "text/html", res);
}

void handleTemperature(){
  float t = dht.readTemperature();
  server.send(200, "text/html", String(t));
}

void handleHumidity(){
  float h = dht.readHumidity();
  server.send(200, "text/html", String(h));
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/temperature", handleTemperature);
  server.on("/humidity", handleHumidity);
  server.begin();
  Serial.println("HTTP server started");

  while(1){
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    server.handleClient();
    display.clearDisplay();
    server.handleClient();
    display.setTextSize(2);
    server.handleClient();
    display.setTextColor(WHITE);
    server.handleClient();
    display.setCursor(0,0);
    server.handleClient();
    display.println("Temp.:-");
    server.handleClient();
    display.setCursor(0, 15);
    server.handleClient();
    display.println(t);
    server.handleClient();
    display.setCursor(0,30);
    server.handleClient();
    display.println("Humidity:-");
    server.handleClient();
    display.setCursor(0,45);
    server.handleClient();
    display.println(h);
    server.handleClient();
    display.display();
    server.handleClient();
    delay(100);
    server.handleClient();
  }
}

void loop() {
  
}
