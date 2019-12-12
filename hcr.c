#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>

#define TRIGGER 26
#define ECHO 19

int main(int argc, char *argv[]) {
	struct timeval pulseStartTime, pulseEndTime;
    long pulseDuration;
	double distance;

    wiringPiSetupGpio();
    pinMode(TRIGGER, OUTPUT); // Set pin 15 as trigger pin
  	pinMode(ECHO, INPUT); // Set pin 14 as monitor pin

  	// like digitalWrite in wiringPi
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

    pulseDuration = pulseEndTime.tv_usec - pulseStartTime.tv_usec;

    distance = (pulseDuration * 17150);
    printf("%.2f", 2);
    return 0;
}
