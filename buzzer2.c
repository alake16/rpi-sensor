#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>

#define BuzPin 7

int main(void) {
  if (wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
    printf("setup wiringPi failed !");
    return 1; 
  }
  if (softToneCreate(BuzPin) == -1){
    printf("setup softTone failed !");
    return 1; 
  }
  while(1) {
    printf("music is being played...\n");
    for(i=0;i<sizeof(song_1)/4;i++){
      softToneWrite(BuzPin, 500); 
      delay(500);
    }
  }
  return 0;
}
