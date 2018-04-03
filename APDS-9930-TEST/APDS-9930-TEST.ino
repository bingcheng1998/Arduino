/****************************************************************
 
 Arduino Pin  APDS-9930 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
****************************************************************/
 
#define DUMP_REGS
 
#include <Wire.h>
#include <APDS9930.h>
 
// Global Variables
APDS9930 apds = APDS9930();
float ambient_light = 0; // can also be an unsigned long
uint16_t ch0 = 0;
uint16_t ch1 = 1;
 
void setup() 
{
 
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
 
  // Initialize APDS-9930 (configure I2C and initial values)
  if ( apds.init() ) 
  {
    Serial.println(F("APDS-9930 initialization complete"));
  } 
  else 
  {
    Serial.println(F("Something went wrong during APDS-9930 init!"));
  }
 
  // Start running the APDS-9930 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) 
  {
    Serial.println(F("Light sensor is now running"));
  } 
  else 
  {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
 
  // Wait for initialization and calibration to finish
  delay(500);
}
 
 
void loop() 
{
 
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readAmbientLightLux(ambient_light) ||
        !apds.readCh0Light(ch0) || 
        !apds.readCh1Light(ch1) ) {
    Serial.println(F("Error reading light values"));
  } 
  else 
  {
    Serial.print(F("Ambient: "));
    Serial.print(ambient_light);
    Serial.print(F("  Ch0: "));
    Serial.print(ch0);
    Serial.print(F("  Ch1: "));
    Serial.println(ch1);
  }
 
  // Wait 1 second before next reading
  delay(1000);
}
