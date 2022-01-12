# Tom Powell 2022
# Desktop readout software for open-source flight computer
# Python 3.9 on RasPi4

# Serial IO Utilites
import serial

# Matplotlib and analysis libs
import numpy as np
import matplotlib.pyplot as plt

# Program Division
try:
    interface = serial.Serial("/dev/ttyACM0",baudrate=115200 ,timeout=1)
    while True :
        print(str(interface.readline()))
except KeyboardInterrupt:
    exit()