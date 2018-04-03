
#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);
/**********************************************************/

byte addresses[][6] = {"Trans", "Reice"};
long a = 0;
void setup() {
  Serial.begin(9600);
  Serial.println(F("Transmitting"));
  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses

  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);


  // Start the radio listening for data
  //radio.startListening();
  radio.stopListening();
}

void loop() {
  a++;
String Stringone = "1234";
Stringone+="\t";
Stringone+=a;
Stringone+="\t";
Stringone+=1234;
Stringone+="\t";
radio.write( &Stringone, sizeof(Stringone) );
}
