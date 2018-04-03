
#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);  /* Use this for the 16-bit version */
Adafruit_ADS1115 ads1(0x49);
Adafruit_ADS1115 ads2(0x4A);
Adafruit_ADS1115 ads3(0x4B);
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */
int data[32] = {0};
int datanew[32] = {0};
int newdata[10][5] = {0};
/****************** User Config ***************************/

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);
/**********************************************************/

byte addresses[][6] = {"Trans", "Reice"};
int _init[5] = {1212,1212,1212,1212,1212};
int _end[5] = {1313,1313,1313,1313,1313};
//int data[10][5]={0};
//int a = 0;
int k = 0 ;
int lk = 0;

int little1 = 22;
int little2 = 30;
int little3 = 23;
int little4 = 4;
int little5 = 15;
int ring1 = 31;
int ring2 = 14;
int ring3 = 26;
int ring4 = 13;
int middle1 = 1;
int middle2 = 12;
int middle3 = 0;
int middle4 = 5;
int index1 = 10;
int index2 = 9;
int index3 = 6;
int index4 = 7;
int thumb1 = 3;
int thumb2 = 2;
int thumb3 = 8;
int thumb4 = 11;


void setup() {
  Serial.begin(250000);
  Serial.println(F("Transmitting"));
  //pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses

  ads.begin();
  ads1.begin();
  ads2.begin();
  ads3.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);


  // Start the radio listening for data
  //radio.startListening();
  radio.stopListening();
  
}

void loop() {
sendArray(_init, 5);


assignment();

   for(int i =0; i<10; i++){   
    for(int j=0; j<5; j++){
    data[j] = newdata[i][j];
    }
    sendArray(data, 5);
   }
   
sendArray(_end, 5);
}

void assignment(){
  int16_t adc0, adc1, adc2, adc3;
  k++;
  lk = 0;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  datanew[0] = adc0;
  datanew[1] = adc1;
  datanew[2] = adc2;
  datanew[3] = adc3;

  //  Serial.print("adc0 \t");
  //  Serial.print(adc0); Serial.print("\t"); Serial.print(adc1); Serial.print("\t");
  //  Serial.print(adc2);  Serial.print("\t");Serial.print(adc3);
  //  Serial.print("\n");

  adc0 = ads1.readADC_SingleEnded(0);
  adc1 = ads1.readADC_SingleEnded(1);
  adc2 = ads1.readADC_SingleEnded(2);
  adc3 = ads1.readADC_SingleEnded(3);
  datanew[4] = adc0;
  datanew[5] = adc1;
  datanew[6] = adc2;
  datanew[7] = adc3;
  //  Serial.print("adc1 \t");
  //  Serial.print(adc0); Serial.print("\t"); Serial.print(adc1); Serial.print("\t");
  //  Serial.print(adc2);  Serial.print("\t");Serial.print(adc3);
  //  Serial.print("\n");

  adc0 = ads2.readADC_SingleEnded(0);
  adc1 = ads2.readADC_SingleEnded(1);
  adc2 = ads2.readADC_SingleEnded(2);
  adc3 = ads2.readADC_SingleEnded(3);
  datanew[8] = adc0;
  datanew[9] = adc1;
  datanew[10] = adc2;
  datanew[11] = adc3;
  //  Serial.print("adc2 \t");
  //  Serial.print(adc0); Serial.print("\t"); Serial.print(adc1); Serial.print("\t");
  //  Serial.print(adc2);  Serial.print("\t");Serial.print(adc3);
  //  Serial.print("\n");

  adc0 = ads3.readADC_SingleEnded(0);
  adc1 = ads3.readADC_SingleEnded(1);
  adc2 = ads3.readADC_SingleEnded(2);
  adc3 = ads3.readADC_SingleEnded(3);
  datanew[12] = adc0;
  datanew[13] = adc1;
  datanew[14] = adc2;
  datanew[15] = adc3;
  //
//    Serial.print("adc0 \t");
//    Serial.print(adc0); Serial.print("\t"); Serial.print(adc1); Serial.print("\t");
//    Serial.print(adc2);  Serial.print("\t");Serial.print(adc3);
//    Serial.print("\nk=");Serial.print(k);Serial.print("\n");
//  delay(1000);

  datanew[16] = analogRead(A0);
  datanew[17] = analogRead(A1);
  datanew[18] = analogRead(A2);
  datanew[19] = analogRead(A3);
  datanew[20] = analogRead(A4);
  datanew[21] = analogRead(A5);
  datanew[22] = analogRead(A6);
  datanew[23] = analogRead(A7);
  datanew[24] = analogRead(A8);
  datanew[25] = analogRead(A9);
  datanew[26] = analogRead(A10);
  datanew[27] = analogRead(A11);
  datanew[28] = analogRead(A12);
  datanew[29] = analogRead(A13);
  datanew[30] = analogRead(A14);
  datanew[31] = analogRead(A15);

  newdata[0][0] = datanew[little1];
  newdata[0][1] = datanew[little2];
  newdata[0][2] = datanew[little3];
  newdata[0][3] = datanew[little4];
  newdata[0][4] = datanew[little5];


  newdata[1][0] = datanew[ring1];
  newdata[1][1] = datanew[ring2];
  newdata[1][2] = datanew[ring3];
  newdata[1][3] = datanew[ring4];

  newdata[2][0] = datanew[middle1];
  newdata[2][1] = datanew[middle2];
  newdata[2][2] = datanew[middle3];
  newdata[2][3] = datanew[middle4];

  newdata[3][0] = datanew[index1];
  newdata[3][1] = datanew[index2];
  newdata[3][2] = datanew[index3];
  newdata[3][3] = datanew[index4];

  newdata[4][0] = datanew[thumb1];
  newdata[4][1] = datanew[thumb2];
  newdata[4][2] = datanew[thumb3];
  newdata[4][3] = datanew[thumb4];

  newdata[5][0] = datanew[18];
  newdata[5][1] = datanew[21];
  newdata[5][2] = datanew[17];
  newdata[5][3] = datanew[16];
  
  newdata[6][0] = datanew[25];
  newdata[6][1] = datanew[20];
  newdata[6][2] = datanew[19];
  newdata[6][3] = datanew[24];
  
  newdata[7][0] = datanew[28];
  newdata[7][1] = datanew[29];
  newdata[7][2] = datanew[27];  
//for(int i =0; i<10; i++){   
//    for(int j=0; j<5; j++){
//    data[j] = newdata[i][j];
//    Serial.print(newdata[i][j]);
//    Serial.print("\t");
//    }
//    Serial.println();
//
//   }
//   delay(300);

}

void sendArray(int Array[], int ArraySize){
  sendint(2222);
  for(int i = 0; i<ArraySize; i++){
    sendint(Array[i]);
  };
  
  sendint(3333);
  //sendint(10101);
  Serial.print("\n");
  //delayMicroseconds(10);
}


void sendint(int one) {
  
  radio.stopListening();                                    // First, stop listening so we can talk.


  //Serial.print(F("Now sending-----\t"));


  int sendData = one;                             // Take the time, and send it.  This will block until complete
  if (!radio.write( &sendData, sizeof(int) )) {
    //Serial.println(F("failed"));
  } else {
    if(sendData!=10101){
    Serial.print(sendData);
    Serial.print("\t");
    }
  }






//-------------------------注释段落-----------------------------//
//  radio.startListening();                                    // Now, continue listening
//
//  unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
//  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
//
//  while ( ! radio.available() ) {                            // While nothing is received
//    if (micros() - started_waiting_at > 20000 ) {           // If waited longer than 200ms, indicate timeout and exit while loop
//      timeout = true;
//      break;
//    }
//  }
//
//  if ( timeout ) {                                            // Describe the results
//    //Serial.println(F("response timed out."));
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//    //delay(1000);
//  } else {
//    int recData;                                 // Grab the response, compare, and send to debugging spew
//    radio.read( &recData, sizeof(int) );
//    int end_time = micros();
//digitalWrite(LED_BUILTIN, LOW);
//-------------------------注释段落-----------------------------//
    
    //Serial.print(F("Sent:\t"));
    Serial.print(sendData);
    Serial.print(F("\t"));
    //Serial.println(recData);
    
  //}
  
}

