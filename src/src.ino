/**
 * src.ino -> main setup and loop
 * 
 * Thank you to:
 * Nuno Santos: https://techtutorialsx.com/2018/01/07/esp32-arduino-http-server-over-soft-ap/
 * me-no-dev:   https://github.com/me-no-dev/ESPAsyncWebServer
 * Random Nerd Tutorial: https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
 */
 
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "CommunicationStuff.hh"
#include "ReadSensors.hh";

const int ARM_DRIVE_PINS[] = {32, 33, 35, 4, 2, 15};
const int ARM_DRIVE_CHANNELS[] = {1, 2, 3, 4, 5, 6};
const int NUM_ARM_MOTORS = 6;

void setup()
{
  Serial.begin(115200);

  // setup electrical stuff
  for (int i = 0; i < NUM_ARM_MOTORS; i++) {
    setup(ARM_DRIVE_PINS[i], ARM_DRIVE_CHANNELS[i]);
    setDriveChannel(i, ARM_DRIVE_CHANNELS[i]);
  }

  // are inline
  connectToWiFi();
  setupESPServer();
}


void loop() { /* Intentionally empty. Required for Asynchronous Web Server. */ }
