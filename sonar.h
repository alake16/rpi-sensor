#ifndef DEF_SONAR
#define DEF_SONAR

class Sonar {
public:
	Sonar(int trigger, int echo, int position);
	double distance(int timeout);
	int getTrigger();
	int getEcho();
	int getPosition();
private:
	void recordPulseLength();
	int trigger;
	int echo;
	int position;
	volatile long startTimeUsec;
	volatile long endTimeUsec;
	double distanceCM;
	double distanceIN;
	long travelTimeUsec;
};

#endif
