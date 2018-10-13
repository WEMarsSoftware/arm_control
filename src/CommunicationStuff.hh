// CommunicationStuff.hh

#ifndef COMMUNICATION_SETUP
#define COMMUNICATION_SETUP

#include "Arduino.h"
#include <WiFi.h>
//#include <FS.h>
#include "ESPAsyncWebServer.h"
#include "ReadSensors.hh"

// INFO FOR LOCAL ROUTER
 char* ssid = "WE MARS Rover";
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
int motorShutdown = 0;

void inline connectToWiFi()
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // ensure our IP is 10.10.10.10
    WiFi.config(staticIP, gateway, subnet);
    
    delay(100);
  
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
  

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
    }

  Serial.println("CONNECTED TO " + String(ssid));
  Serial.println(WiFi.localIP());
}

void inline setupESPServer()
{
  /**
   * Some HTTP callbacks.
   * No parameters -> send all sensor data in response
   */
   server.on("", HTTP_GET, [](AsyncWebServerRequest *request){

    getSensorData(currentSensors, armDistance);

    // send JSON response
    response = "{ \"Motor1\":\"" + String(currentSensors[0]) 
                + "\",\"Motor2\":\"" + String(currentSensors[1])
                + "\",\"Motor3\":\"" + String(currentSensors[2])
                + "\",\"Motor4\":\"" + String(currentSensors[3])
                + "\",\"Motor5\":\"" + String(currentSensors[4])
                + "\",\"Motor6\":\"" + String(currentSensors[5])
                + "\",\"ArmDistance\":\"" + String(armDistance) 
                + "\",\"MotorShutdown\":\"" + String(motorShutdown) +"\"}";

    request->send(200, "text/plain", response);
  });


   /**
    * /restart parameter -> restart motors after shutoff
    */
   server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request){

    /* Somehow restart motors */

    request->send(200, "text/plain", "SUCCESS");
  });
 
  server.begin();
}

#endif
