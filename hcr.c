#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define TRIGGER 26
#define ECHO 19

int main(int argc, char *argv[]) {
	struct timeval pulseStartTime, pulseEndTime, pulseDuration;
	double distance;

    wiringPiSetupGpio();
    pinMode(TRIGGER, OUTPUT); // Set pin 15 as trigger pin
  	pinMode(ECHO, INPUT); // Set pin 14 as monitor pin

  	// like digitalWrite in wiringPi
    GPIO.output(PIN_TRIGGER, GPIO.LOW);
    digitalWrite(TRIGGER, LOW);

    printf("Waiting for sensor to settle");

    sleep(2);

    printf("Calculating distance");

    digitalWrite(TRIGGER, HIGH);

    sleep(0.00001);

    digitalWrite(TRIGGER, HIGH);
    while (digitalRead(ECHO) == 0) {
    	gettimeofday(&pulseStartTime, NULL);
    }

    while (digitalRead(ECHO) == 1) {
    	gettimeofday(&pulseEndTime, NULL);
    }

    pulseDuration = pulseEndTime - pulseStartTime;

    distance = round(pulse_duration * 17150, 2)
}