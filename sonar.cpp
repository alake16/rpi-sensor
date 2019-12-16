#include <wiringPi.h>
#include "sonar.h"

Sonar::Sonar(int triggerIn, int echoIn) :
	trigger(triggerIn), echo(echoIn) {
		pinMode(trigger, OUTPUT);
		pinMode(echo, INPUT);
		digitalWrite(trigger, LOW);
		delay(500);
	}

Sonar::distance(int timeout) {
	delay(10);
	digitalWrite(trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);

	now = micros();

	while (digitalRead(echo == LOW) && micros() - now < timeout);
		recordPulseLength();

	travelTimeUsec = endTimeUsec - startTimeUsec;
	distanceMeters = 100 * ((travelTimeUsec / 1000000.0) * 340.29) / 2;
}

Sonar::recordPulseLength() {
	startTimeUsec = micros();
	while (digitalRead(echo) == HIGH);
	endTimeUsec = micros()
}