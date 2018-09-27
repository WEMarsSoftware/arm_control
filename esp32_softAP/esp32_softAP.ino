/**
 * Thank you to:
 * Nuno Santos: https://techtutorialsx.com/2018/01/07/esp32-arduino-http-server-over-soft-ap/
 * me-no-dev:   https://github.com/me-no-dev/ESPAsyncWebServer
 * Random Nerd Tutorial: https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
 */
 
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

// custom connectToWiFI()
// and setupESPServer() functions
#include "CommunicationStuff.hh"

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

/**
 * Connect to Rover WiFi,
 * define HTTP callbacks,
 * set static IP.
 */
void setup()
{
    Serial.begin(115200);

    // inline
    connectToWiFi();
    setupESPServer();
}

/**
 * Update sensor values every little while.
 */
void loop()
{
    // read for all sensors

    // check currents for exceeding MAX_CURRENT_ALLOWED
    // output to direct line to another esp32 which listens for
    
    // Digi-Key 620-1542-5-ND Current Transducer
}
