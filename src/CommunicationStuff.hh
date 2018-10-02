// CommunicationSetup.hpp

#ifndef COMMUNICATION_SETUP
#define COMMUNICATION_SETUP

#include "Arduino.h"
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "ReadSensors.hh"

// INFO FOR LOCAL ROUTER
const char* ssid = "WE MARS Rover"; 
const char* password = "westillfirst";

// COMMUNICATION CONSTANTS
AsyncWebServer server(80);
IPAddress staticIP(192,168,1,15);
IPAddress gateway(10,10,10,1);
IPAddress subnet(255,255,255,0);

// byte array representing MAC address
byte mac[6];
// TODO: change this
String response = "{}";

int currentSensors[6] = {};
int armDistance = 0;

void inline connectToWiFi()
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // ensure our IP is 10.10.10.10
    WiFi.config(staticIP, gateway, subnet);
    
    Serial.println("Setup done");
    delay(100);

    Serial.println("scan start");    
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("CONNECTED TO " + String(ssid));
  Serial.println(WiFi.localIP());
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}

void inline setupESPServer()
{
  /**
   * Some HTTP callbacks.
   * No parameters -> send everything in response
   */
   server.on("", HTTP_GET, [](AsyncWebServerRequest *request){

    getSensorData(currentSensors, armDistance);

    // send JSON response
    response = "{ \"Motor1\":\"" + String(currentSensors[0]) + "\",
                  \"Motor2\":\"" + String(currentSensors[1]) + "\",
                  \"Motor3\":\"" + String(currentSensors[2]) + "\",
                  \"Motor4\":\"" + String(currentSensors[3]) + "\",
                  \"Motor5\":\"" + String(currentSensors[4]) + "\",
                  \"Motor6\":\"" + String(currentSensors[5]) + "\",
                  \"ArmDistance\":\"" + String(armDistance) + "\" }";

    request->send(200, "text/plain", response);
  });
 
  server.begin();
}

#endif