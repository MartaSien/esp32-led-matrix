import serial
import time
import mss
from PIL import Image
from math import sqrt, ceil
import cv2
import numpy as np

SER = serial.Serial('COM3', 115200)
MATRIX_SIZE = 200

def send_matrix(colors):
    """Send the matrix colors to ESP32 as a byte array to serial port."""
    data = bytearray()

    for color in colors:
        data.extend(color)
    SER.write(data)
    print(f"Sent {len(data)} bytes to {SER.port}")

if __name__ == "__main__":
        while True:
            matrix_side = ceil(sqrt(MATRIX_SIZE))
            with mss.mss() as sct:
                img = sct.grab(sct.monitors[1])
                im = Image.frombytes('RGB', img.size, img.rgb)
                im = im.resize((matrix_side, matrix_side)).convert('RGB')
                colors = list(im.getdata())
                
                # Convert PIL image to OpenCV format
                im_cv = np.array(im)
                im_cv = cv2.cvtColor(im_cv, cv2.COLOR_RGB2BGR)
                im_cv = cv2.resize(im_cv, (400, 400), interpolation=cv2.INTER_NEAREST)
                cv2.imshow('LED Matrix Preview', im_cv)
                
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            send_matrix(colors)
            time.sleep(0.3) # seconds