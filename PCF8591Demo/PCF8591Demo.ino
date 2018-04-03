// Example 52.3 PCF8591 ADC demo
// http://tronixstuff.com/tutorials Chapter 52
// John Boxall June 2013
#include "Wire.h"
#define PCF8591 0x48// I2C bus address
#define ADC0 0x00 // control bytes for reading individual ADCs
#define ADC1 0x01
#define ADC2 0x02
#define ADC3 0x03
byte value0, value1, value2, value3;
void setup()
{
 Wire.begin();
 Serial.begin(9600);
}
void loop()
{
 Wire.beginTransmission(PCF8591); // wake up PCF8591
 Wire.write(ADC0); // control byte - read ADC0
 Wire.endTransmission(); // end tranmission
 Wire.requestFrom(PCF8591, 2);
 value0=Wire.read();
 value0=Wire.read();
 Wire.beginTransmission(PCF8591); // wake up PCF8591
 Wire.write(ADC1); // control byte - read ADC1
 Wire.endTransmission(); // end tranmission
 Wire.requestFrom(PCF8591, 2);
 value1=Wire.read();
 value1=Wire.read();
 Wire.beginTransmission(PCF8591); // wake up PCF8591
 Wire.write(ADC2); // control byte - read ADC2
 Wire.endTransmission(); // end tranmission
 Wire.requestFrom(PCF8591, 2);
 value2=Wire.read();
 value2=Wire.read();
 Wire.beginTransmission(PCF8591); // wake up PCF8591
 Wire.write(ADC3); // control byte - read ADC3
 Wire.endTransmission(); // end tranmission
 Wire.requestFrom(PCF8591, 2);
 value3=Wire.read();
 value3=Wire.read();
 Serial.print(value0); Serial.print(" ");
 Serial.print(value1); Serial.print(" ");
 Serial.print(value2); Serial.print(" ");
 Serial.print(value3); Serial.print(" ");
 Serial.println();
}
