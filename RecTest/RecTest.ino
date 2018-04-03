
#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/


/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);
/**********************************************************/

byte addresses[][6] = {"Trans", "Reice"};

// Used to control whether this node is sending or receiving
bool role = 0;
int current[5] = {0};
int repeat = 0;
int sequence = 0;
void setup() {
  Serial.begin(9600);
  Serial.println(F("Reiceiving"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);


  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  Recint();



}



void Recint() {
  int recData;

  if ( radio.available()) {
    // Variable for the received timestamp
    while (radio.available()) {                                   // While there is data ready
      radio.read( &recData, sizeof(int) );             // Get the payload
    }

    radio.stopListening();                                        // First, stop listening so we can talk
    radio.write( &recData, sizeof(int) );              // Send the final one back.
    radio.startListening();                                       // Now, resume listening so we catch the next packets.
    //Serial.print(F("Received Data:\t"));
    //Serial.println(recData);


    if (recData == 10101) {
      repeat++;
    }
    else if (repeat == 0) {
      current[sequence] = recData;
      Serial.print(recData);
      Serial.print("\t");
      sequence++;
    };
    if (repeat == 2) {
      Serial.print("\n");
      repeat = 0;
      sequence = 0;
    };

  }
}


