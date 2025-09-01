import serial
import time
from PIL import Image
import mss
import cv2
import numpy as np

ser = serial.Serial('COM3', 115200)  # Change COM port as needed

with mss.mss() as sct:
    while True:
        img = sct.grab(sct.monitors[1])
        im = Image.frombytes('RGB', img.size, img.rgb)
        im = im.resize((8, 8)).convert('RGB')
        
        # Convert PIL image to OpenCV format
        im_cv = np.array(im)
        im_cv = cv2.cvtColor(im_cv, cv2.COLOR_RGB2BGR)
        im_cv = cv2.resize(im_cv, (200, 200), interpolation=cv2.INTER_NEAREST)  # Scale up for preview
        
        cv2.imshow('8x8 Preview', im_cv)  # This will reuse the same window
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        data = bytearray()
        dim_factor = 0.05  # 20% brightness
        for y in range(8):
            for x in range(8):
                r, g, b = im.getpixel((x, y))
                r = int(r * dim_factor)
                g = int(g * dim_factor)
                b = int(b * dim_factor)
                data += bytes([r, g, b])
        ser.write(data)
        time.sleep(0.05)  # ~20 FPS

cv2.destroyAllWindows()