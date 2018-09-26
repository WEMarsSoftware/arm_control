/**
 * Thank you to:
 * Nuno Santos: https://techtutorialsx.com/2018/01/07/esp32-arduino-http-server-over-soft-ap/
 * me-no-dev:   https://github.com/me-no-dev/ESPAsyncWebServer
 * Random Nerd Tutorial: https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
 */
 
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

// INFO FOR LOCAL ROUTER
const char* ssid = "WE MARS Rover"; 
const char* password = "westillfirst";

// PIN CONSTANTS
const int ULTRASONIC_TRIG_PIN = 11;
const int ULTRASONIC_ECHO_PIN = 12;

// Sensor values
int armDistance = 0;

/**
 * MOTOR LAYOUT [1 -> 1 mapping of array indices]
 * 0 -- 3
 *   ||
 * 1 -- 4
 *   ||
 * 2 -- 5
 */
 int motorCurrents[6] = {};
 
// COMMUNICATION CONSTANTS
AsyncWebServer server(80);
IPAddress staticIP(10,10,10,10);
//IPAddress gateway(10,10,10,1);
//IPAddress subnet(255,255,255,0);  

// TODO: change this
String response = "{}";


/**
 * Connect to Rover WiFi,
 * define HTTP callbacks,
 * set static IP.
 */
void setup()
{
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // ensure our IP is 10.10.10.10
    Wifi.config(staticIP);
    
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

  /**
   * Some HTTP callbacks.
   * No parameters -> send everything in response
   * 
   * TODO: add specific sensor values.
   */
   server.on("", HTTP_GET, [](AsyncWebServerRequest *request){
    // read from a sensor here
    int temp = 0;
    
    String temp_string(temp);
    response = "temperature: "+ temp_string;
    // send response
    request->send(200, "text/plain", response);
  });
 
  server.begin();
}

/**
 * Update sensor values every little while.
 */
void loop()
{
    delay(100);

    // read for all sensors

    // check currents for exceeding MAX_CURRENT_ALLOWED
    // output to direct line to another esp32 which listens for
    
    // Digi-Key 620-1542-5-ND Current Transducer
}
