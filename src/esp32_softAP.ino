/**
 * Thank you to:
 * Nuno Santos: https://techtutorialsx.com/2018/01/07/esp32-arduino-http-server-over-soft-ap/
 * me-no-dev:   https://github.com/me-no-dev/ESPAsyncWebServer
 * Random Nerd Tutorial: https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
 */
 
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "CommunicationStuff.hh"
#include "ReadSensors.hh";

/**
 * MOTOR LAYOUT [1 -> 1 mapping of array indices]
 * 0 -- 3
 *   ||
 * 1 -- 4
 *   ||
 * 2 -- 5
 */
 int motorCurrents[6] = {};  

void setup()
{
    Serial.begin(115200);
	pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
	pinMode(ULTRASONIC_ECHO_PIN, INPUT);

    // are inline
    connectToWiFi();
    setupESPServer();
}


void loop() { /* Intentionally empty. Required for Asynchronous Web Server. */ }
