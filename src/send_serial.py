import serial
import time

SER = serial.Serial('COM3', 115200)
MATRIX_SIZE = 64

def send_matrix(colors):
    # colors is a list of (r, g, b) tuples for each LED
    data = bytearray()

    for color in colors:
        data.extend(color)
        SER.write(data)

if __name__ == "__main__":
    red = (255, 0, 0)
    colors = [red] * MATRIX_SIZE

    while True:
        send_matrix(colors)
        time.sleep(1) # wait for 1 second