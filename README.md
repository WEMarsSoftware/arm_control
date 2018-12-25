# Using the Arduino environment with the ESP-32 WiFi chips
Refer to: https://github.com/espressif/arduino-esp32#development-status


# Settings used in Arduino IDE
- Board: DOIT ESP32 DEVKIT V1
- Flash Frequency: 80 MHz
- Upload Speed: 230400
- Port: USBtoUART
- Programmer: AVRISP mkII

*Note: May need to hold down boot button while uploading programs.

# In src/
- C++ code for an ESP-32 to interface with 6 VEX Victor motor controllers, 6 current sensors, and 6 potentiometers
  - Dependencies: esp-32 SDK, as well as Arduino, AsyncTCP, ESPAsyncWebServer and espressif-esp32 tools (staging) libraries (including LEDC PWM headers)
  - Headers should be installed in Documents/Arduino/libraries
