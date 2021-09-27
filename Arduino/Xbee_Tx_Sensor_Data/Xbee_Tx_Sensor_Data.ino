/*****************************************************************
XBee_Serial_Passthrough.ino

Set up a software serial port to pass data between an XBee Shield
and the serial monitor.

Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.

*****************************************************************/
#include "SparkFun_SGP40_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP40_Arduino_Library
#include <Adafruit_AHTX0.h>
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
#include <Wire.h>

//For Atmega328P's
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

//For Atmega2560, ATmega32U4, etc.
// XBee's DOUT (TX) is connected to pin 10 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 11 (Arduino's Software TX)
// SoftwareSerial XBee(10, 11); // RX, TX


SGP40 mySensor; // create an object of the SGP40 class
Adafruit_AHTX0 aht;

typedef struct {
// header and data size
  uint8_t header;
  uint8_t dataSize;
// data fields
  uint8_t temp[2];
  //uint8_t humidity[2];
  //uint8_t vocIndex[2];
} packet;
packet rf_data;

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);
  Serial.println("Xbee Tx Sensor Data");
  
  Wire.begin();

  //mySensor.enableDebugging(); // Uncomment this line to print useful debug messages to Serial

  //Initialize sensor
  if (mySensor.begin() == false)
  {
    Serial.println(F("SGP40 not detected. Check connections. Freezing..."));
    while (1); // Do nothing more
  }
  Serial.println("SGP40 found");
    
  if (! aht.begin()) 
  {
    Serial.println("Could not find AHT? Check wiring");
    while (1); // Do nothing more
  }
  Serial.println("AHT10 or AHT20 found");
}

void loop()
{
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

  unsigned int count = 0;

    // header and data size must be set appropriately for packet type
    rf_data.header = 'S';
    rf_data.dataSize = 12;

    //unsigned int vocIndex = mySensor.getVOCindex();
    memcpy(rf_data.temp, &temp.temperature, sizeof(rf_data.temp));
    //memcpy(rf_data.humidity, &humidity.relative_humidity, sizeof(rf_data.humidity));
    //memcpy(rf_data.vocIndex, &vocIndex, sizeof(rf_data.vocIndex));
    
    sendRfData(&rf_data);
    
    Serial.println();
    count++;
    
    delay(1000); // Wait 1 second
}


void sendRfData(packet *data)
{
  uint16_t count = 0;
  
  while(count < sizeof(packet))
  {
    Serial.print(*((char*)data + count));
    XBee.write(*((char*)data + count));    
    count++;
  }
}
