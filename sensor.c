#include <wiringSerial.h>
#include <wiringPi.h>

unsigned long pulse_width;

int setup()
{
 // Serial.begin(9600); // Start serial communications
  int s = serialOpen("pi", 9600);
  pinMode(15, OUTPUT); // Set pin 2 as trigger pin
  pinMode(14, INPUT); // Set pin 3 as monitor pin
  digitalWrite(2, LOW); // Set trigger LOW for continuous read
  return s;
}

void loop(int s)
{
  pulse_width = pulseIn(3, HIGH); // Count how long the pulse is high in microseconds
  if(pulse_width != 0){ // If we get a reading that isn't zero, let's print it
        pulse_width = pulse_width/10; // 10usec = 1 cm of distance for LIDAR-Lite
  	//Serial.println(pulse_width); // Print the distance
	serialPrintf(s, "test message");
  }
  delay(20); //Delay so we don't overload the serial port
}

int main(int argc, char *argv[]) {
    int s = setup();
    loop(s);
    return 0;
}
