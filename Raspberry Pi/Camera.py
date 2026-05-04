import cv2
import numpy as np
from picamera2 import Picamera2

picam2 = Picamera2()

def CameraBegin():
    config = picam2.create_preview_configuration(main={"format": "BGR888", "size": (640, 480)})
    picam2.configure(config)
    picam2.start()

def CameraStop():
    picam2.stop()

def CameraFindCircle():
    frame = picam2.capture_array()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.medianBlur(gray, 1)

    circles = cv2.HoughCircles(
        gray,
        cv2.HOUGH_GRADIENT_ALT,
        dp=1.5,
        minDist=30,
        param1=200,
        param2=.7,
        minRadius=10,
        maxRadius=400,
    )
    
    if circles is not None:
        circles = np.round(circles[0, :]).astype("int")
        for (x, y, r) in circles:
            cv2.circle(frame, (x, y), r, (0, 255, 0), 3)
            cv2.circle(frame, (x, y), 2, (0, 0, 255), 3)
            return np.array([x, y])
        
    return None