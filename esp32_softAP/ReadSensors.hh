// ReadSensors.hh

#ifndef READ_SENSORS
#define READ_SENSORS

#include "Arduino.h"

// ULTRASONIC SENSOR ON ARM
const int ULTRASONIC_TRIG_PIN = 11;
const int ULTRASONIC_ECHO_PIN = 12;

// CURRENT SENSORS
// varies linearly with DC in
const int NUM_CURRENT_SENSORS = 6;
const int CURRENT_SENSOR_VOUT[NUM_CURRENT_SENSORS] = {4, 5, 6, 7, 8, 9};
const int MAX_CURRENT_IN = 50;

void inline getSensorData(int currentSensors[NUM_CURRENT_SENSORS], int& armDistance)
{
	int tempCurrentRead[NUM_CURRENT_SENSORS] = {};
	for (int i = 0; i < NUM_CURRENT_SENSORS; i++)
	{
		// some number from 0->1023
		tempCurrentRead[i] = analogRead(CURRENT_SENSOR_VOUT[i]);

		// map from analogRead min, max to 0->50 Amps
		map(tempCurrentRead[i], 0, 1023, 0, MAX_CURRENT_IN);
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
