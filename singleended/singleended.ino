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

void setup(void)
{
  Serial.begin(250000);
  Serial.println("Hello!");

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  ads.begin();
  ads1.begin();
  ads2.begin();
  ads3.begin();
}

void loop(void)
{
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
  //  Serial.print("adc0 \t");
  //  Serial.print(adc0); Serial.print("\t"); Serial.print(adc1); Serial.print("\t");
  //  Serial.print(adc2);  Serial.print("\t");Serial.print(adc3);
  //  Serial.print("\nk=");Serial.print(k);Serial.print("\n");
  //  //delay(1000);

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

  int  data99[] = {28, 29, 27};

  for (int i = 0; i < 3; i++) {
    //if ((datanew[i] - data[i]) * (datanew[i] - data[i]) > 900) {
    //Serial.print("[");
    //Serial.print(i);
    Serial.print(" ");
    Serial.print(datanew[data99[i]]);
    //Serial.print("]");
    //Serial.print("\t");
    //Serial.print("\t");
    lk = 1;
    //}

    data[i] = datanew[i];
  };
  if (lk = 1) {
    lk = 0;
    Serial.print("\n");
  }
  int quotient;
  int remainder;

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

for(int i =0; i<10; i++){   
    for(int j=0; j<5; j++){
    data[j] = newdata[i][j];
    Serial.print(newdata[i][j]);
    Serial.print("\t");
    }
    Serial.println();

   }
   delay(300);
}
