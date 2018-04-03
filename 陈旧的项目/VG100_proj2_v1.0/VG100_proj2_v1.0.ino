#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <IRremote.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define L 8 //these are the pin we choose in the servo board
#define R 2
#define F 4
#define B 6
#define Lmin  469 // this is the 'minimum' pulse length count (out of 4096)
#define Lmax  154 //136 this is the 'maximum' pulse length count (out of 4096)
#define Rmin  191 // this is the 'minimum' pulse length count (out of 4096)
#define Rmax  578 // this is the 'maximum' pulse length count (out of 4096)
#define Fmin  499 //600 this is the 'minimum' pulse length count (out of 4096)
#define Fmax  150 // this is the 'maximum' pulse length count (out of 4096)
#define Bmin  393 // 合上this is the 'minimum' pulse length count (out of 4096)
#define Bmax  130 // 打开this is the 'maximum' pulse length count (out of 4096)




#define left  16720605
#define right 16761405
#define up    16736925
#define down  16754775
#define OK 16712445
#define _1 16738455
#define _2 16750695
#define _3 16756815
#define _4 16724175
#define _5 16718055
#define _6 16743045
#define _7 16716015
#define _8 16726215
#define _9 16734885

//注意!!!!!max为舒展状态,放衣服前全为max!!!!!!
uint8_t servonum = 0;
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
const int RECV_PIN = A3;
static void (*restartArduino)(void) = 0x0000;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  yield();
  pwm.setPWM(B, 0, Bmax);
  pwm.setPWM(F, 0, Fmax);
  pwm.setPWM(R, 0, Rmax);
  pwm.setPWM(L, 0, Lmax);
  delay(500);
  pinMode(autoPin, INPUT);
  pinMode(nextPin, INPUT);
  pinMode(startPin, INPUT);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  pinMode(colorful, OUTPUT);
  pinMode(redBlink, OUTPUT);
  pinMode(greenBlink, OUTPUT);
  pinMode(blueBlink, OUTPUT);
  digitalWrite(greenBlink, LOW);
  digitalWrite(redBlink, LOW);
  digitalWrite(colorful, LOW);
  digitalWrite(blueBlink, LOW);
  Serial.println("\n");
  irrecv.enableIRIn(); // Start the receiver
  printStart();
}

void loop() {
  if (isStart() == 1) {
    Serial.println("\tstart folding------initialization\n");
    digitalWrite(colorful, HIGH);
    delay(1000);
    digitalWrite(colorful, LOW);
    digitalWrite(blueBlink, LOW);
    sweep(R, Rmax, Rmax);
    sweep(L, Lmax, Lmax);
    //sweep(B, Bmin, Bmax);
    //sweep(F, Fmin, Fmax);
    loopGet();
  };
}
void endIt() {
  Serial.println("\n\tthe board is closed");
  digitalWrite(colorful, HIGH);
  delay(200);
  digitalWrite(colorful, LOW);
  delay(1000);
  //sweep(F, Fmax, Fmin);
  //sweep(B, Bmax, Bmin);
  sweep(L, Lmax, Lmax);
  sweep(R, Rmax, Rmax);
  delay(200);
  restartArduino();//软件重启
  //while (1);
}
void loopGet() {
  while (1) {
    if (isNotAuto() == 1) { // if isStart() == 1 the arduino will run the auto mode
      Serial.println("\n\tthe hand test mode is on**");
      handMode();
    }
    else if (isAuto() == 1) { // if isAuto() == 1 the arduino will run the hand mode
      Serial.println("\n\tthe auto test mode is on");
      autoMode();
    }
    else if (isStart() == 1) {
      endIt(); //close the board;
    }
    else;
  };
}
void autoMode() {
  delay(500);
  int foldTime = 0;
  digitalWrite(blueBlink, LOW);
  while (1) {
    foldTime++;
    Serial.print("\nfold the no.");
    Serial.print(foldTime);
    Serial.print(" clothes\n");
    foldOneTime();
    //       if (isNotAuto() == 1) { // if isStart() == 1 the arduino will run the auto mode
    //      Serial.println("\n\tthe hand test mode is on");
    //      handMode();

  };
}
void handMode() {
  while (1) {
    digitalWrite(blueBlink, HIGH);
    if (isNext() == 1|| getIremote()==OK|| getIremote()==up|| getIremote()==left|| getIremote()==right) {
      Serial.println("\tnext step! please place a clothe in the board");
      foldOneTime();
      delay(200);
    }
    else if (isAuto() == 1) { // if isStart() == 1 the arduino will run the auto mode
      Serial.println("\n\tthe auto test mode is on");
      autoMode();
    }
    else if (isStart() == 1) {
      endIt(); //close the board;
    };
    digitalWrite(blueBlink, LOW);
  };
}

void foldOneTime() {
  int isFinished = 0;
  digitalWrite(greenBlink, HIGH);

  while (isFinished == 0) {
    //shirt
    if (isL1() == 0 && isL2() == 0 && isR1() == 0 && isR2() == 0 ) { //all the four sensor is on
      Serial.println("fold a shirt on the board");
      digitalWrite(redBlink, HIGH);
      delay(500);
      sweep(L, Lmax, Lmin);
      sweep(L, Lmin, Lmax);
      sweep(R, Rmax, Rmin);
      sweep(R, Rmin, Rmax);
      sweep(F, Fmax, Fmin);
      sweep(F, Fmin, Fmax);
      sweep(B, Bmax, Bmin);
      sweep(B, Bmin, Bmax);
      digitalWrite(redBlink, LOW);
      isFinished = 1;
    }
    //pants on the left
    else if (pantLeft() == 1) {
      Serial.println("fold a pant on the left side of the board");
      digitalWrite(redBlink, HIGH);
      delay(500);
      sweep(L, Lmax, Lmin);
      sweep(L, Lmin, Lmax);
      sweep(F, Fmax, Fmin);
      sweep(F, Fmin, Fmax);
      sweep(B, Bmax, Bmin);
      sweep(B, Bmin, Bmax);
      isFinished = 1;
      digitalWrite(redBlink, LOW);
    }
    //pants on the right
    else if (pantRight() == 1) {
      Serial.println("fold a pant on the right side of the board");
      digitalWrite(redBlink, HIGH);
      delay(500);
      sweep(R, Rmax, Rmin);
      sweep(R, Rmin, Rmax);
      sweep(F, Fmax, Fmin);
      sweep(F, Fmin, Fmax);
      sweep(B, Bmax, Bmin);
      sweep(B, Bmin, Bmax);
      isFinished = 1;
      digitalWrite(redBlink, LOW);
    }
    else if (isNotAuto() == 1) { // if isStart() == 1 the arduino will run the auto mode
      Serial.println("\n\tthe hand test mode is on");
      digitalWrite(redBlink, LOW);
      digitalWrite(blueBlink, HIGH);
      handMode();
    }
    else if (isStart() == 1) {
      endIt(); //close the board;
    }
    else {
      Serial.println("the board is free");
    };
  };
  digitalWrite(greenBlink, LOW);
  delay(100);
}

int pantLeft() {
  if (isL1() == 0 && isL2() == 0 &&  isR2() == 1) {
    delay(500);
    if (isL1() == 0 && isL2() == 0 &&  isR2() == 1) {
      delay(500);
      if (isL1() == 0 && isL2() == 0 &&  isR2() == 1) {
        return 1;
      }
      else return 0;
    }
  }
}
int pantRight() {
  if (isL2() == 1 && isR1() == 0 && isR2() == 0) {
    delay(500);
    if (isL2() == 1 && isR1() == 0 && isR2() == 0) {
      delay(500);
      if (isL2() == 1 && isR1() == 0 && isR2() == 0) {
        return 1;
      }
      else return 0;
    }
  }
}

int isAuto() {
  return digitalRead(autoPin);
}
int isNotAuto() {
  return digitalRead(notAutoPin);
}
int isNext() {
  return digitalRead(nextPin);
}
int isStart() {
  return digitalRead(startPin);
}
int isL1() {
  return digitalRead(L1);
}
int isL2() {
  return digitalRead(L2);
}
int isR1() {
  return digitalRead(R1);
}
int isR2() {
  return digitalRead(R2);
}
void sweep(int servonum, int startAngle, int endAngle) {
#define ifQuickly  0  // if ifQuickly=0, slow sweep, =1, quick sweep
  Serial.print("servo ");
  Serial.print(servonum);
  int delaytime = 10; //6the bigger the delaytime, the slower the servo sweeps
#if ifQuickly == 0
  if (startAngle > endAngle) {
    for (uint16_t pulselen = startAngle; pulselen > endAngle; pulselen -= 3) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(delaytime);
    }
  }
  else if (startAngle <= endAngle) {
    for (uint16_t pulselen = startAngle; pulselen < endAngle; pulselen += 3) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(delaytime);
    }
  }
  Serial.print(" sloooowly sweep from ");
#else
  pwm.setPWM(servonum, 0, startAngle);
  delay(1000);
  pwm.setPWM(servonum, 0, endAngle);
  delay(1000);
  Serial.print(" fastly sweep from ");
#endif
  Serial.print(startAngle);
  Serial.print(" to ");
  Serial.print(endAngle);
  Serial.println(";");
}

unsigned long int getIremote() {
  unsigned long int recei = 0;

  for (int i = 0; i < 3; i++) {
    if (irrecv.decode(&results)) {
      //Serial.println(results.value);
      //Serial.println(results.value, HEX);//这是十六进制的编码显示
      unsigned long int recei0 = results.value;
      if (recei0 != 4294967295) {
        recei = results.value;
      }
      irrecv.resume(); // Receive the next value
      //Serial.print("\t\tThe results value is: ");
      //Serial.println(recei);
      return recei;
    }
  }
  delay(20);
  return 0;

}

void printStart() {
  Serial.println("------------- the clothes folder is trned on ------------");
  Serial.println("\tthe function was written by Hu Bingcheng ");
  Serial.println("\tversion 1.0");
  Serial.println("\tJuly, 17, 2017");
  Serial.println("---------- welcome to use the fantastic folder ----------\n\n");
}

