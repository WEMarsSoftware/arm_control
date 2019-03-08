# Pinout for ESP-32 running the arm control code

# Motor PWM Signals (6 outputs)
#   Motor 1 is pin 32
# 		...
#	Motor 6 is pin 15
- PINS 32, 33, 35, 4, 2, 15

# Motor potentiometer inputs (6 inputs)
- PINS 13, 12, 14, 27, 26, 25

# Motor Current Sensors
# Outputs from sensors should be routed according 
# to motor number (see Motor PWM Signals)
# ie. sensor on motor 1 should be routed to line 000 of mux.
- Input from 3x8 multiplexer
	- PIN 37
- Select pins for multiplexer
	- S0: PIN 36 (LSb)
	- S1: PIN 39
	- S2: PIN 34 (MSb)