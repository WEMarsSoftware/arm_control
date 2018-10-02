// ReadSensors.hh

#ifndef READ_SENSORS
#define READ_SENSORS

#include "Arduino.h"

// Note: different than Arduino
const int MAX_ANALOG_IN = 4095;
const int MIN_ANALOG_IN = 0;
// ULTRASONIC SENSOR ON ARM
// digital -> use any pin
const int ULTRASONIC_TRIG_PIN = 26;
const int ULTRASONIC_ECHO_PIN = 27;

// CURRENT SENSORS
// varies linearly with DC in
const int NUM_CURRENT_SENSORS = 6;
// GPIO on left side of board (ADCI_0 -> ADCI_5)
// > 31 when WiFi on see https://cdn.instructables.com/FQM/7X6B/J7GGGD9O/FQM7X6BJ7GGGD9O.LARGE.jpg
const int CURRENT_SENSOR_VOUT[NUM_CURRENT_SENSORS] = {36, 39, 34, 35, 32, 33}; 
const int MAX_CURRENT_IN = 50;

void inline getSensorData(int currentSensors[NUM_CURRENT_SENSORS], int& armDistance)
{
	int tempCurrentRead[NUM_CURRENT_SENSORS] = {};
	for (int i = 0; i < NUM_CURRENT_SENSORS; i++)
	{
		// some number from 0->1023
		tempCurrentRead[i] = analogRead(CURRENT_SENSOR_VOUT[i]);

		// map from analogRead min, max to 0->50 Amps
		map(tempCurrentRead[i], MIN_ANALOG_IN, MAX_ANALOG_IN, MIN_ANALOG_IN, MAX_CURRENT_IN);
	}

	// pulse ultrasonic sensor
	digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
	double duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);

	// Calculating the distance
	armDistance = duration*0.034/2;
}

#endif
