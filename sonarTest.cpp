#include <wiringPi.h>
#include <iostream>
#include <pthread.h>
#include "sonar.h"

using namespace std;


void *function(void* voidSonar) {
	Sonar* sonar = (Sonar*)(voidSonar);
	cout << "Thread running sensor at position: " << sonar -> getPosition() << endl;
	cout << "Trigger pin is set to: " << sonar -> getTrigger() << endl;
    cout << "Echo pin is set to: " << sonar -> getEcho() << endl;

	while (1) {
		double distance = sonar -> distance(30000);
		if (distance < 5.0) {
			if (sonar -> getPosition() == 0) {
				cout << "LEFT";
			}
			else {
				cout << "RIGHT";
			}
			cout << "CLOSE" << endl;
		}
	}
	pthread_exit(NULL);	
}

int main(int argc, char *argv[]) {
	
	pthread_t leftThread;
	pthread_t rightThread;

    if (wiringPiSetupGpio() == -1) return -1;
    
    Sonar left(13, 6, 0);
    Sonar right(26, 19, 1);
    pthread_create(&leftThread, NULL, function, &left);
    pthread_create(&rightThread, NULL, function, &right);
    pthread_exit(NULL);
    
	return 0;
}
