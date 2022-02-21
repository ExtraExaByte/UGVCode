import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(4, GPIO.OUT)

p = GPIO.PWM(4, 50)
p.start(10)
input('Press return to stop:') 
p.stop()
GPIO.cleanup()
