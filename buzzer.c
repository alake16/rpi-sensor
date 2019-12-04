#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <stdlib.h>

#define BuzPin 4

void setupBuzzer() {
    if (softToneCreate(BuzPin) == -1){
      printf("setup softTone failed !");
      exit(1); 
    }
}

void buzz() {
      printf("buzzer sounding\n");
      softToneWrite(BuzPin, 500);
      delay(500);
      softToneWrite(BuzPin, 0);
      // delay(distance);
}
