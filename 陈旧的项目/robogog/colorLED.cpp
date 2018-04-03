#include"Arduino.h"
#include "colorLED.h"

    int redPin = 9;
    int greenPin = 10;
    int bluePin = 11;
void colorLED::red(){
   analogWrite(redPin,255);
   analogWrite(greenPin,0);
   analogWrite(bluePin,0);
}
void colorLED::red_blink(){
}
void colorLED::green(){
   analogWrite(redPin,0);
   analogWrite(greenPin,255);
   analogWrite(bluePin,0);
}
void colorLED::green_blink(){
}
void colorLED::blue(){
   analogWrite(redPin,0);
   analogWrite(greenPin,0);
   analogWrite(bluePin,255);
}
void colorLED::blue_blink(){
}
//void colorLED::color(){
//   analogWrite(redPin,random(0,255));
//   analogWrite(greenPin,random(0,255));
//   analogWrite(bluePin,random(0,255));
//}
void colorLED::setup(){
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
}
//void colorLED::randcolor(){
//   //R:0-255 G:0-255 B:0-255
//   analogWrite(redPin,random(0,255));
//   analogWrite(greenPin,random(0,255));
//   analogWrite(bluePin,random(0,255));
//}
