import serial
import time
from PIL import Image
import mss
import cv2
import numpy as np

MATRIX_WIDTH = 27 # prism matrix: 27, test matrix: 8
MATRIX_HEIGHT = 7 # prism matrix: 7, test matrix: 8

ser = serial.Serial('COM3', 115200)  # Change COM port as needed


# USE FOR TESTING
while True:
    data = bytearray()
    
    for y in range(MATRIX_HEIGHT):
        for x in range(MATRIX_WIDTH):
            data += bytes([50, 0, 0])
            data += bytes([0, 50, 0])
            data += bytes([0, 0, 50])
    ser.write(data)
    time.sleep(0.05)  # ~20 FPS

"""
with mss.mss() as sct:
    while True:
        img = sct.grab(sct.monitors[1])
        im = Image.frombytes('RGB', img.size, img.rgb)
        im = im.resize((MATRIX_WIDTH, MATRIX_HEIGHT)).convert('RGB')
        
        # Convert PIL image to OpenCV format
        im_cv = np.array(im)
        im_cv = cv2.cvtColor(im_cv, cv2.COLOR_RGB2BGR)
        im_cv = cv2.resize(im_cv, (MATRIX_WIDTH*10, MATRIX_HEIGHT*10), interpolation=cv2.INTER_NEAREST)  # Scale up for preview
        
        cv2.imshow('Preview', im_cv)  # This will reuse the same window
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        data = bytearray()
        dim_factor = 1  # 5% brightness
        for y in range(MATRIX_HEIGHT):
            for x in range(MATRIX_WIDTH):
                r, g, b = im.getpixel((x, y))
                r = int(r * dim_factor)
                g = int(g * dim_factor)
                b = int(b * dim_factor)
                data = bytes([g, r, b])
                print([g, r, b])
        ser.write(data)
        time.sleep(0.05)  # ~20 FPS

cv2.destroyAllWindows()
"""