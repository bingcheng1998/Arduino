//最终版

#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/

RF24 radio(7, 8);
byte addresses[][6] = {"Trans", "Reice"};

void setup()
{
 
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);


  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  // Start the radio listening for data
  radio.startListening();
  //delay(2000);
  Serial.begin(9600);
}

void loop()
{
String recData;
String Stringone = "1234";
Stringone+="\t";
Stringone+=1234;
Stringone+="\t";
Stringone+=1234;
Stringone+="\t";

  if ( radio.available()) {
    // Variable for the received timestamp
    while (radio.available()) {                                   // While there is data ready
      radio.read( &recData, 40 );             // Get the payload
    };
    Serial.println(recData);
}
}


