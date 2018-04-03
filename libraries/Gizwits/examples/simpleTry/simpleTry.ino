/**************************************************************

Name:		  Gizwits + ArduinoUnoWiFi Library 
Author:		tli@gizwits.com / bing@arduino.org.cn 
Version:	V03030000
Init:		  2016-12-23
Modify:   2017-08-01
****************************************************************/
#include <Gizwits.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A2, A3); // A2 -> RX, A3 -> TX

Gizwits myGizwits;

/**
* Serial Init , Gizwits Init  
* @param none
* @return none
*/
void setup() {
  // put your setup code here, to run once:

  mySerial.begin(115200);
  
  myGizwits.begin();

  mySerial.println(F("GoKit init  OK!"));

}

/**
* Arduino loop 
* @param none
* @return none
*/
void loop() {  
  
  //Configure network
  //if(XXX) //Trigger Condition
  //myGizwits.setBindMode(0x02);  //0x01:Enter AP Mode;0x02:Enter Airlink Mode
    /*
  bool varW_Cold = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_Cold, varW_Cold);




  //binary datapoint handle
  */

  myGizwits.process();
}