// CommunicationStuff.hh

#ifndef COMMUNICATION_STUFF
#define COMMUNICATION_STUFF

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
IPAddress staticIP(20,20,20,20);
IPAddress gateway(10,10,10,1);
IPAddress subnet(255,255,255,0);
const String GET_PARAMS[] = {"motor1", "motor2", "motor3", "motor4", "motor5", "motor6"};

// TODO: change this
String response = "{}";

int numPings = 0;

int currentSensors[6] = {};
int potVals[6] = {};

void inline connectToWiFi()
{
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // ensure our IP is 20.20.20.20 (other ESP is 10.10.10.10)
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

int numParams = request->params();
int motorParams[6] = {};
void inline setupESPServer()
{
  /**
   * Some HTTP callbacks.
   * This expects a GET to:
   * <IP>/?motor1=10&motor2=....
   * ie. a number between -100 and +100 for each motor1 -> motor6 of arm
   */
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      numPings++;

      for ( int i = 0; i < numParams; i++ ) {
        AsyncWebParameter* p = request->getParam(i);
        motorParams[i] = (p->value()).toInt();
      }
       
      // if all went well, we now have the 6 power percentage values
      // use our Electrical API to move arm motors
      moveMotors(&motors[0]);

      // grab current and potentiometer values 
      getSensorData(&currentSensors[0], &potVals[0]);

      // send JSON response
      response = "{ \"Current-Motor1\":\"" + String(currentSensors[0]) 
                + "\",\"Current-Motor2\":\"" + String(currentSensors[1])
                + "\",\"Current-Motor3\":\"" + String(currentSensors[2])
                + "\",\"Current-Motor4\":\"" + String(currentSensors[3])
                + "\",\"Current-Motor5\":\"" + String(currentSensors[4])
                + "\",\"Current-Motor6\":\"" + String(currentSensors[5])
                + "\",\"Pot-Motor1\":\"" + String(potVals[0])
                + "\",\"Pot-Motor2\":\"" + String(potVals[1])
                + "\",\"Pot-Motor3\":\"" + String(potVals[2])
                + "\",\"Pot-Motor4\":\"" + String(potVals[3])
                + "\",\"Pot-Motor5\":\"" + String(potVals[4])
                + "\",\"Pot-Motor6\":\"" + String(potVals[5])
                + "\"}";

      request->send(200, "text/plain", response);
    });


  // used to test connection 
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){ 
        numPings++;
        
       // send hello back
       request->send(200, "text/plain", "Hello!");
   });
 
  server.begin();
}

#endif
