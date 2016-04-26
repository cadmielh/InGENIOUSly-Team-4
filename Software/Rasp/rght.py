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
f="a"
while counter<3:
        ser.write(f)
        time.sleep(1)
        print f
        counter+=1
#!/usr/bin/env python
          
      
import time
import serial
          
      
ser = serial.Serial(
	port='/dev/ttyAMA0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
while 1:
    x=ser.readline()
    x=x/2.12
    return x
#!/usr/bin/env python
          
      
import time
import serial
          
      
ser = serial.Serial(
	port='/dev/ttyAMA0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)
while 1:
    x=ser.readline()
    return x
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
f="m"
while counter<3:
	ser.write(f)
	time.sleep(1)	
	print f
	counter+=1
import functools
import os
import random
import time
from piui import PiUi
from subprocess import call
current_dir = os.path.dirname(os.path.abspath(__file__))


class DemoPiUi(object):

    def __init__(self):
        self.title = None
        self.txt = None
        self.img = None
        self.ui = PiUi(img_dir=os.path.join(current_dir, 'imgs'))
       # self.src = "sunset.png"
    def main_menu(self):
        self.page = self.ui.new_ui_page(title="Controlul Masinii")
        self.title=self.page.add_textbox("Fata Spate", "h1")
        fwd=self.page.add_button("&uarr;", self.onupclick)
        bwd=self.page.add_button("&darr;", self.ondownclick)
	self.title2=self.page.add_textbox("Stanga dreapta", "h1")
	lft=self.page.add_button("&larr;", self.onleftclick)
	rht=self.page.add_button("&rarr;", self.onrightclick)
	self.page.add_textbox("Viteza: ", "h1")
	speed=self.page.add_textbox("%d m\s",%self.reads.a)
	self.page.add_textbox("Distanta: ","h1")
	dist=self.page.add_textbox("%d m",%self.readd.b)
	self.page.add_element("hr")
	stop=self.page.add_button("Stop", self.onstopclick)	
	self.ui.done()
	def main(self):
        self.main_menu()
        self.ui.done()

    def reads (self):
	a=call(["sudo python /home/piui/uart/reads.py &"],shell=true)
    
    def readd (self):
	b=call(["sudo python /home/piui/uart/readd.py &"],shell=true)

    def onupclick(self):
        self.title.set_text("Forward ")
        print "Forward"
	call(["sudo python /home/pi/piui/uart/fwd.py &"],shell=true)

    def ondownclick(self):
        self.title.set_text("Down")
        print "Down"
	call(["sudo python /home/pi/piui/uart/bwd.py &"],shell=true)

    def onleftclick(self):
	self.title2.set_text("left")
	call(["sudo python /home/pi/piui/uart/left.py &"],shell=true)

    def onrightclick(self):
	self.title2.set_text("right")
	call(["sudo python /home/pi/piui/uart/rght.py &"],shell=true)

    def onstopclick(self):
	self.title.set_text("Stop")
        call(["sudo python /home/pi/piui/uart/stop.py &"],shell=true)

def main():
  piui = DemoPiUi()
  piui.main()

if __name__ == '__main__':
    main()
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
f="8"
while counter<3:
        ser.write(f)
        time.sleep(1)
        print f
        counter+=1
