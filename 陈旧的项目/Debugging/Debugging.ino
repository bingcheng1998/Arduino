#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  130 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define L 0 //these are the pin we choose in the servo board
#define R 2
#define F 4
#define B 6
#define Lmin  150 // this is the 'minimum' pulse length count (out of 4096)
#define Lmax  600 // this is the 'maximum' pulse length count (out of 4096)
#define Rmin  150 // this is the 'minimum' pulse length count (out of 4096)
#define Rmax  578 // this is the 'maximum' pulse length count (out of 4096)
#define Fmin  150 // this is the 'minimum' pulse length count (out of 4096)
#define Fmax  600 // this is the 'maximum' pulse length count (out of 4096)
#define Bmin  150 // this is the 'minimum' pulse length count (out of 4096)
#define Bmax  600 // this is the 'maximum' pulse length count (out of 4096)

const int ServoIn = 8;//机会可能冀东水泥附加费戽水抗旱


const int autoPin = 11;
const int notAutoPin = 12;
const int nextPin = 13;
const int startPin = 10;
const int colorful = 9;
const int redBlink = 8;
const int blueBlink = 2;
const int greenBlink = 7;
const int L1 = 6;
const int L2 = 5;
const int R1 = 4;
const int R2 = 3;
int incomingByte = 0;   // for incoming serial data
int number = 0;
int AorM=1;
int pulselen=370;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
pwm.begin();
  pwm.setPWMFreq(60);
  yield();
}

void loop() {
int changed = 0;
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.println(incomingByte, DEC);
    if (incomingByte == 113) {
      
    };
    if (incomingByte == 45) { //负数
      AorM=-1;
      changed=1;
    }
    if (incomingByte == 43) { //正数
      AorM=1;
      changed=1;
    };
    if(changed==0){
      number=(incomingByte-48)*AorM;
      if(number>-10 && number<10){
        runIt(ServoIn, number);
        Serial.print("I received: ");
      Serial.println(number, DEC);
      }
    }
  }
}

void runIt(int servonum, int changed){
  pulselen+=changed;
  if(pulselen>SERVOMAX){
    pulselen=SERVOMAX;
  }
  else if(pulselen<SERVOMIN){
    pulselen=SERVOMIN;
  }
  Serial.print("The pulselen number is ");
  Serial.println(pulselen);
  pwm.setPWM(servonum, 0, pulselen);
}

