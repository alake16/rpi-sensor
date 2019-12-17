#include <wiringPi.h>
#include "sonar.h"

Sonar::Sonar(int triggerIn, int echoIn, int positionIn) :
	trigger(triggerIn), echo(echoIn), position(positionIn) {
		pinMode(trigger, OUTPUT);
		pinMode(echo, INPUT);
		digitalWrite(trigger, LOW);
		delay(500);
	}
	
int Sonar::getTrigger() {
	return trigger;
}

int Sonar::getEcho() {
	return echo;
}

int Sonar::getPosition() {
	return position;
}
	
double Sonar::distance(int timeout) {
	delay(10);
	digitalWrite(trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);

	while (digitalRead(echo) == LOW) startTimeUsec = micros();
    while (digitalRead(echo) == HIGH) endTimeUsec = micros();
    
    travelTimeUsec = endTimeUsec - startTimeUsec;
	
	distanceCM = 100 * ((travelTimeUsec / 1000000.0) * 340.29) / 2;
	distanceIN = 0.3937008 * distanceCM;
	return distanceIN;
}

void Sonar::recordPulseLength() {
	startTimeUsec = micros();
	while (digitalRead(echo) == HIGH);
	endTimeUsec = micros();
}
