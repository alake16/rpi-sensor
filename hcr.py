import RPi.GPIO as GPIO
import time

while(1):

    # setup GPIO BCM mode
    GPIO.setmode(GPIO.BCM)

    # indicate BCM GPIO pins
    PIN_TRIGGER = 26
    PIN_ECHO = 19

    # set up trigger pin as output
    GPIO.setup(PIN_TRIGGER, GPIO.OUT)
    # set up echo pin as input
    GPIO.setup(PIN_ECHO, GPIO.IN)

    # like digitalWrite in wiringPi
    GPIO.output(PIN_TRIGGER, GPIO.LOW)

    time.sleep(0.0001)

    GPIO.output(PIN_TRIGGER, GPIO.HIGH)

    time.sleep(0.0001)

    GPIO.output(PIN_TRIGGER, GPIO.LOW)

    while GPIO.input(PIN_ECHO)==0:
          pulse_start_time = time.time()
    while GPIO.input(PIN_ECHO)==1:
          pulse_end_time = time.time()

    pulse_duration = pulse_end_time - pulse_start_time

    distance = round(pulse_duration * 17150, 2)

    print("Distance:",distance,"cm")


