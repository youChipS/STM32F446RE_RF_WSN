/*****************************************************************
Leonardo_XBee_Serial_Passthrough.ino

Set up a serial port to pass data between an XBee Shield
and the serial monitor.

Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "UART" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 0 and 1.
*****************************************************************/

// Leonardo Serial  is the USB port
// Leonardo Serial1 is pins 0 and 1

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  Serial1.begin(9600);  //XBee/UART1/pins 0 and 1
  Serial.begin(9600);   //USB

}

void loop()
{
  if (Serial.available()) //USB
  { // If data comes in from serial monitor, send it out to XBee
  Serial1.write(Serial.read()); //XBee/UART1/pins 0 and 1

  }
  if (Serial1.available())   //XBee/UART1/pins 0 and 1
  { // If data comes in from XBee, send it out to serial monitor
    Serial.write(Serial1.read());  //Serial port

  }
}
