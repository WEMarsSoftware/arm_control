// ReadSensors.hh

#ifndef READ_SENSORS
#define READ_SENSORS

#include "Arduino.h"

// ULTRASONIC SENSOR ON ARM
const int ULTRASONIC_TRIG_PIN = 11;
const int ULTRASONIC_ECHO_PIN = 12;

// CURRENT SENSORS
// see https://www.digikey.ca/en/datasheets/allegromicrosystemsllc/allegro-microsystems-llcacs770datasheet
// varies linearly with A/C in
const int CURRENT_SENSOR_VOUT[6] = {4, 5, 6, 7, 8, 9};

void inline getSensorData(int currentSensors[6], int& armDistance)
{
	int tempCurrentRead[6] = {};
	for (int i = 0; i < 6; i++)
	{
		// some number from 0->1023
		tempCurrentRead[i] = analogRead(CURRENT_SENSOR_VOUT[i]);

		// somewhere from 0->60 amps
		map(tempCurrentRead[i], 0, 1023, 0, 60);
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
