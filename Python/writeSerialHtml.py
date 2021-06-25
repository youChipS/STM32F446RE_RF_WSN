# write-html-2-windows.py

import webbrowser
import serial



# this port address is for the serial tx/rx pins on the GPIO header
SERIAL_PORT = '/dev/ttyACM0'
# be sure to set this to the same rate used on the Arduino
SERIAL_RATE = 9600

def main():
    ser = serial.Serial(SERIAL_PORT, SERIAL_RATE)
    while True:

       # using ser.readline() assumes each line contains a single reading
       # sent using Serial.println() on the Arduino
       reading = ser.readline().decode('utf-8')
       # reading is a string...do whatever you want from here
       print(reading)

       f = open('helloSerial.html','w')

       message = """<html>
       <head></head>
       <body><p>Hello Serial! - """ + reading + """</p></body>
       </html>"""

       f.write(message)
       f.close()

       webbrowser.open_new_tab('helloSerial.html')

if __name__ == "__main__":
    main()
