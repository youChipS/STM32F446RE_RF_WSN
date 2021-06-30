/* 	~ Simple Arduino - xBee Transmitter sketch ~

	Read an analog value from potentiometer, then convert it to PWM and finally send it through serial port to xBee.
	The xBee serial module will send it to another xBee (resiver) and an Arduino will turn on (fade) an LED.
	The sending message starts with '<' and closes with '>' symbol. 
	
	Dev: Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA                    */

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

//For Atmega328P's
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

//For Atmega2560, ATmega32U4, etc.
// XBee's DOUT (TX) is connected to pin 10 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 11 (Arduino's Software TX)
//SoftwareSerial XBee(10, 11); // RX, TX

//Constants: 
const int potPin = A0; //Pot at Arduino A0 pin 
//Variables:
int value ; //Value from pot

void setup() {

  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
	Serial.begin(9600); //Baud rate must be the same as is on xBee module

}

void loop() {
  	
  	//Read the analog value from pot and store it to "value" variable
  	value = analogRead(A0);
  	//Map the analog value to pwm value
  	value = map (value, 0, 1023, 0, 255);
	//Send the message:
	Serial.print('<'); 	//Starting symbol
 	Serial.print(value);//Value from 0 to 255
	Serial.println('>');//Ending symbol
  XBee.write('A'); // write value to xbee
  delay(1000);

}
  
