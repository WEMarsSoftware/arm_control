# Using the Arduino environment with the ESP-32 WiFi chips
Refer to: https://github.com/espressif/arduino-esp32#development-status


# Settings used in Arduino IDE
- Board: DOIT ESP32 DEVKIT V1
- Flash Frequency: 80 MHz
- Upload Speed: 230400
- Port: USBtoUART
- Programmer: AVRISP mkII

*Note: May need to hold down boot button while uploading programs.

# esp32_softAP (to be renamed)
- C++ code for esp-32 to interface with 6 current sensors and 1 ultrasonic sensor
  - Dependencies: esp-32 SDK, as well as Arduino and ESPAsyncWebServer libraries 
- HTML and JavaScript for running at the driver's control station
  - Known Browser Support: Microsoft Edge (2018), Google Chrome (2016), Firefox (2018)
