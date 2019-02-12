# Pinout for ESP-32 running the arm control code

# Motor PWM Signals (6 outputs)
- PINS 32, 33, 35, 4, 2, 15

# Motor potentiometer inputs (6 inputs)
- PINS 13, 12, 14, 27, 26, 25

# Motor Current Sensors
- Input from 3x8 multiplexer
	- PIN 37
- Select pins for multiplexer
	- S0: PIN 36 (LSb)
	- S1: PIN 39
	- S2: PIN 34 (MSb)