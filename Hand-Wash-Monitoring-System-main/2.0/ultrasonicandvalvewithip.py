#Libraries
import RPi.GPIO as GPIO
import time
from picamera import PiCamera
from lobe import ImageModel


#Create input, output, and camera objects
camera = PiCamera()


# Load Lobe TF model
# --> Change model file path as needed
model = ImageModel.load('/home/pi/Lobe/hw')

 
#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)
 
#set GPIO Pins
GPIO_TRIGGER = 13
GPIO_ECHO = 19
#relay GPIO Pins
in1 = 16
in2 = 21
 
 
#set GPIO direction (IN / OUT) for ultrasonic sensor
GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)
#set GPIO direction (IN / OUT) for relay
GPIO.setup(in1, GPIO.OUT)
GPIO.setup(in2, GPIO.OUT)

#turn off relay at starting
GPIO.output(in1, True)
GPIO.output(in2, True)


#ultrasonic sensor code
def distance():
    # set Trigger to HIGH
    GPIO.output(GPIO_TRIGGER, True)
 
    # set Trigger after 0.01ms to LOW
    time.sleep(0.00001)
    GPIO.output(GPIO_TRIGGER, False)
 
    StartTime = time.time()
    StopTime = time.time()
 
    # save StartTime
    while GPIO.input(GPIO_ECHO) == 0:
        StartTime = time.time()
 
    # save time of arrival
    while GPIO.input(GPIO_ECHO) == 1:
        StopTime = time.time()
 
    # time difference between start and arrival
    TimeElapsed = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distance = (TimeElapsed * 34300) / 2
 
    return distance



# Take Photo
def take_photo():
    # Start the camera preview
    camera.start_preview(alpha=200)
    # wait 2s or more for light adjustment
    time.sleep(3)
    # Optional image rotation for camera
    # --> Change or comment out as needed
    camera.rotation = 270
    #Input image file path here
    # --> Change image path as needed
    camera.capture('/home/pi/Pictures/image.jpg')
    #Stop camera
    camera.stop_preview()
    time.sleep(1)

def ip():
  n=0
  for i in range(5):
    take_photo()
    # Run photo through Lobe TF model
    # --> Change image path
    result = model.predict_from_file('/home/pi/Pictures/image.jpg')
    print(result.prediction)
    n = n + 1
    #to print the no. of times the program has run
    print(n)
    #delay between each step
    time.sleep(1)


#relay controls for soap and valve
def soap():
        print("soap")
        GPIO.output(in1, False)
        time.sleep(2)
        GPIO.output(in1, True)
        

        
def valve():
        print("valve")
        GPIO.output(in2, False)
        time.sleep(5)
        GPIO.output(in2, True)


 
if __name__ == '__main__':
    try:
        while True:
            dist = distance()
            if dist > 0 and dist<=25 :
                print("ON")
                valve()
                time.sleep(0.5)
                soap()
                ip()
                time.sleep(0.5)
                valve()
                time.sleep(1)
            else:
                print("off")
                time.sleep(1)

        # Reset by pressing CTRL + C
    except KeyboardInterrupt:
        print("Measurement stopped by User")
        GPIO.cleanup()