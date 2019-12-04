#include <wiringSerial.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

unsigned long pulse_width;

int setup(){
  wiringPiSetupGpio();
  int s = serialOpen("pi", 9600); // Start serial communications
  pinMode(15, OUTPUT); // Set pin 15 as trigger pin
  pinMode(14, INPUT); // Set pin 14 as monitor pin
  digitalWrite(2, LOW); // Set trigger LOW for continuous read
  return s;
}

int pulseIn(int pin, int level, int timeout){
   struct timeval tn, t0, t1;
   long micros;
   gettimeofday(&t0, NULL);
   micros = 0;

   while (digitalRead(pin) != level){
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);

      if (micros > timeout) return 0;
   }
   gettimeofday(&t1, NULL);

   while (digitalRead(pin) == level){
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);

      if (micros > timeout) return 0;
   }
   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);

   return micros;
}

int read_distance(int s){
  pulse_width = pulseIn(14, HIGH, 1000000); // Count how long the pulse is high in microseconds
  if(pulse_width < 4000 && pulse_width >= 0){ // If we get a reading that isn't zero, let's print it
        pulse_width = pulse_width/10; // 10usec = 1 cm of distance for LIDAR-Lite
  	//Serial.println(pulse_width); // Print the distance
	serialPrintf(s, "test message");
	//if(pulse_width < 4000 && pulse_width >= 0){
	//	printf("%d\n", pulse_width);
	//}
	delay(2);
	return pulse_width;
  } 
  delay(2); //Delay so we don't overload the serial port
}

int main(int argc, char *argv[]) {
    int s = setup();
    while(1) {
	    int sum = 0;
	    for(int i = 0; i < 10; i++){
		sum += read_distance(s);
	    }
	    double average = sum/10.0;

	    if(average > 100) printf("You good: ");
	    if(average <= 100 && average > 50) printf("Long: ");
	    if(average <= 50 && average > 25) printf("Medium: ");
	    if(average <=25) printf("Short: ");

	    printf("%f\n", average);
	    //delay(2);
    }



    return 0;
}
