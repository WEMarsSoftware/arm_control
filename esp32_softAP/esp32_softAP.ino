/**
 * Thank you to:
 * Nuno Santos: https://techtutorialsx.com/2018/01/07/esp32-arduino-http-server-over-soft-ap/
 * me-no-dev:   https://github.com/me-no-dev/ESPAsyncWebServer
 */
 
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "MY_ESP32_WIFI"; 
const char* password = "password1"; // MUST be 8 characters or more (will default to unsecured)
String header;

AsyncWebServer server(80);
IPAddress staticIP(10,10,10,10);
IPAddress gateway(10,10,10,1);
IPAddress subnet(255,255,255,0);  

String response = "Hello World!";

void setup(){
  Serial.begin(115200);
 
  WiFi.softAP(ssid, password);

  // can also set max number of connections
  WiFi.softAPConfig(staticIP, gateway, subnet);
  
  Serial.println();
  Serial.print("IP Address:");
  Serial.println(WiFi.softAPIP());
  Serial.println(WiFi.localIP());

  // callback (if url is <staticIP>/hello)
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    // read from a sensor here

    // send response
    request->send(200, "text/plain", response);
  });
 
  server.begin();
}
 
void loop(){}
