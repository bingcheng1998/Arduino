/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
//#include <Wire.h>
//#include <SPI.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int ServoAngle=180;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(57600);
  inputString.reserve(200);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (stringComplete) {
    Serial.print(inputString);
    //ServoAngle = (inputString).toInt();
    Serial.println(ServoAngle = (inputString).toInt());
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  for (pos = 0; pos <= ServoAngle; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(13);                       // waits 15ms for the servo to reach the position
  }
  for (pos = ServoAngle; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(13);     
    Serial.println(pos);// waits 15ms for the servo to reach the position
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}



