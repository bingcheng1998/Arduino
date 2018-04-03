#include <LedControl.h>
#include <Servo.h>

Servo myservo;

// LED matrix 8x8
const int DIN = 12;
const int CS =  11;
const int CLK = 9;

LedControl lc = LedControl(DIN, CLK, CS, 0);
// motor A
const int dir1PinA = 6;
const int dir2PinA = 10;
//const int speedPinA = 5;
// motor B

const int dir1PinB = 5;
const int dir2PinB = 3;
//const int speedPinB = 3;

// the BW sensor

const int LIn = A1;
const int MIn = A2;
const int RIn = A3;

const int servoStart = 90;
const int servoEnd = 20;

const int water = 13;
const int servoPin = 7;
const int speed = 120;

unsigned long starttime;
    unsigned long stoptime;
    unsigned long looptime;

byte JI[8] =    {0xF7, 0x22, 0x22, 0x22, 0x22, 0x22, 0xA2, 0x47};
byte _10[8] =   {0x46, 0xC9, 0x49, 0x49, 0x49, 0x49, 0x49, 0xE6};
byte _9[8] =    {0x18, 0x24, 0x24, 0x1C, 0x04, 0x24, 0x18, 0x00};
byte  _8[8] =   {0x18, 0x24, 0x24, 0x18, 0x24, 0x24, 0x24, 0x18};
byte _7[8] =   {0x7C, 0x44, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10};
byte  _6[8] =  {0x18, 0x24, 0x20, 0x38, 0x24, 0x24, 0x24, 0x18};
byte  _5[8] =  {0x20, 0x3C, 0x20, 0x38, 0x04, 0x04, 0x24, 0x18};
byte  _4[8] =  {0x04, 0x0C, 0x14, 0x24, 0x3E, 0x04, 0x04, 0x00};
byte  _3[8] =  {0x3C, 0x24, 0x08, 0x38, 0x04, 0x04, 0x24, 0x18};
byte  _2[8] =  {0x18, 0x24, 0x24, 0x08, 0x10, 0x20, 0x3C, 0x00};
byte  _1[8] =  {0x08, 0x18, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00};
byte  _I[8] =  {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C};
byte  B_love[8] =  {0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00};
byte  S_love[8] =  {0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00, 0x00};
byte smile[8] =    {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
byte neutral[8] =  {0x3C, 0x42, 0xA5, 0x81, 0xBD, 0x81, 0x42, 0x3C};
byte frown[8] =    {0x3C, 0x42, 0xA5, 0x81, 0x99, 0xA5, 0x42, 0x3C};



void setup() {

  Serial.begin(9600);
  Serial.println("water car start!!!!!!");
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(servoStart);
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  //pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(water, INPUT);
  //pinMode(speedPinB, OUTPUT);
  // analogWrite(speedPinA, speed);
  // analogWrite(speedPinB, speed);
  lc.shutdown(0, false);      //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 15);     // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
  starttime=millis();
}

void loop() {
//
delay(60000);
//GoAhead();
//delay(10000);
//CarStart();
stoptime=millis();
looptime=stoptime-starttime;
  if (digitalRead(water) == 0 || looptime>100000) {
    Serial.println("OK!!");
    print1_10();
    printByte(JI);
    CarStart();
  };
  Serial.println("Not OK");
}

void CarStart() {
  while (1) {
    if (digitalRead(LIn) == 0 && digitalRead(MIn) == 1 && digitalRead(RIn) == 0) {
      GoAhead();
      delay(5);
    }
    else if (digitalRead(LIn) == 0 && digitalRead(MIn) == 0 && digitalRead(RIn) == 1) {
      TurnLeft();
      delay(5);
    }
    else if (digitalRead(LIn) == 1 && digitalRead(MIn) == 0 && digitalRead(RIn) == 0) {
      TurnRight();
      delay(5);
    }
    else if (digitalRead(LIn) == 1 && digitalRead(MIn) == 1 && digitalRead(RIn) == 1) {
//      GoAhead();
//      delay(50);
//      if (digitalRead(LIn) == 1 && digitalRead(MIn) == 1 && digitalRead(RIn) == 1) {
//        GoAhead();
//        delay(50);
//        if (digitalRead(LIn) == 1 && digitalRead(MIn) == 1 && digitalRead(RIn) == 1) {
          Stop;
          PourWater();
//        };
//      };
    }
    else {
      GoAhead();
      delay(20);
    };
  };

}

void print1_10() {
  Serial.println("start print!");
  printByte(_10);
  delay(1000);
  printByte(_9);
  delay(1000);
  printByte(_8);
  delay(1000);
  printByte(_7);
  delay(1000);
  printByte(_6);
  delay(1000);
  printByte(_5);
  delay(1000);
  printByte(_4);
  delay(1000);
  printByte(_3);
  delay(1000);
  printByte(_2);
  delay(1000);
  printByte(_1);
  delay(1000);
  printByte(JI);
  lc.clearDisplay(0);
  Serial.println("end print");
}

void PourWater() {
  Stop() ;
  Serial.println("start print 2nd ; and pour water");
  delay(1000);
  myservo.write(servoEnd);
  delay(2000);
  myservo.write(servoStart);
  delay(1000);
  for (int i = 0; i < 10; i++) {

    printByte(_I);
    delay(1000);
    printByte(B_love);
    delay(300);
    printByte(S_love);
    delay(300);
    printByte(B_love);
    delay(300);
    printByte(JI);
    delay(2000);
    lc.clearDisplay(0);
  };
  Serial.println("_____  END   ______");
  while (1);
}

void GoAhead() {
  Serial.println("GoAhead()");
  analogWrite(dir1PinA, speed);
  analogWrite(dir2PinA, 0);
  analogWrite(dir1PinB, speed+20);
  analogWrite(dir2PinB, 0);
}

void GoBack() {
  Serial.println("GoBack()");
  analogWrite(dir1PinA, LOW);
  analogWrite(dir2PinA, speed);
  analogWrite(dir1PinB, LOW);
  analogWrite(dir2PinB, speed);
}

void TurnLeft() {
  Serial.println("TurnLeft() ");
  analogWrite(dir1PinA, speed);
  analogWrite(dir2PinA, LOW);
  analogWrite(dir1PinB, LOW);
  analogWrite(dir2PinB, LOW);
}

void TurnRight() {
  Serial.println("TurnRight()");
  analogWrite(dir1PinA, LOW);
  analogWrite(dir2PinA, LOW);
  analogWrite(dir1PinB, speed+20);
  analogWrite(dir2PinB, LOW);

}

void Stop() {
  Serial.println(" Stop() ");
  analogWrite(dir1PinA, LOW);
  analogWrite(dir2PinA, LOW);
  analogWrite(dir1PinB, LOW);
  analogWrite(dir2PinB, LOW);
}

void printByte(byte character [])
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  }
}
