#!usr/bin/env python
import time
import serial
ser=serial.Serial(
        port='/dev/ttyAMA0',
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
counter=0
f=3
while counter<3:
        ser.write(f)
        time.sleep(1)
        print f
        counter+=1
