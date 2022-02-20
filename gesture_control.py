from djitellopy import tello
from pyfirmata import Arduino, util
import threading
import time


def fly(direction, flydo):
    '''direction is a list of four variables dictating Flydo's flight actions.'''
    flydo.send_rc_control(direction[0], direction[1], direction[2], direction[3])
    time.sleep(0.05)


if __name__ == '__main__':
    # Tello setup
    flydo = tello.Tello()
    flydo.connect()
    flying = False

    board = Arduino("COM10")

    # Always get pin before iterator starts
    # Never put in while loop
    forward = board.get_pin("d:12:i")
    backward = board.get_pin("d:11:i")
    right = board.get_pin("d:10:i")
    left = board.get_pin("d:9:i")

    iterator = util.Iterator(board)
    iterator.start()
    print("Successfully connected to Arduino.")
    
    while True:
        lr = 0
        fb = 0

        if forward.read():
            fb = 25
        elif backward.read():
            fb = -25
        
        if right.read():
            lr = 25
        elif left.read():
            lr = -25

        if [lr, fb, 0, 0] != [0, 0, 0, 0]:
            threading.Thread(target=lambda: fly([lr, fb, 0, 0], flydo)).start()