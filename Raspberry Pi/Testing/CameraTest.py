import cv2
import numpy as np
from picamera2 import Picamera2

# 1. Setup the Camera
picam2 = Picamera2()
# Configure for a smaller resolution to boost FPS on Pi
config = picam2.create_preview_configuration(main={"format": "BGR888", "size": (640, 480)})
picam2.configure(config)
picam2.start()

print("Camera started. Press Ctrl+C to stop.")

try:
    while True:
        # Capture a frame directly into a numpy array
        frame = picam2.capture_array()

        # Preprocess
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.medianBlur(gray, 1)

        # Detect
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

        # Draw results
        if circles is not None:
            circles = np.round(circles[0, :]).astype("int")
            for (x, y, r) in circles:
                cv2.circle(frame, (x, y), r, (0, 255, 0), 3)
                cv2.circle(frame, (x, y), 2, (0, 0, 255), 3)
                break

        # Show the window
        cv2.imshow('Pi Cam Circles', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    picam2.stop()
    cv2.destroyAllWindows()
