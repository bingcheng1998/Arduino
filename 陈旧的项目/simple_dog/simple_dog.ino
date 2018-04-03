#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 
#define SERVOMAX  600
uint8_t servonum = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);
  yield();
}
void loop() {
int pos1[13]={340,340,340,340,340,340,340,340,340,340,340,340,340};
int pos2[13]={300,300,300,300,300,300,300,300,300,300,300,300,300};
posture(pos1);
posture(pos2);
//Position(340,340,340,340,340,340,340,340,340,340,340,340,340);
//Position(300,300,300,300,300,300,300,300,300,300,300,300,300);
}

void posture(int pos[13]){
  Serial.println(pos[0]+pos[1]+pos[2]+pos[3]+pos[4]);
  Position(pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6],pos[7],pos[8],pos[9],pos[10],pos[11],pos[12]);
  
}


void Position(int a, int b, int c, int d, int e, int f, int g,int h, int i, int j, int k, int l, int m){
  pwm.setPWM(0, 0, a);
  pwm.setPWM(1, 0, b);
  pwm.setPWM(2, 0, c);
  pwm.setPWM(3, 0, d);
  pwm.setPWM(4, 0, e);
  pwm.setPWM(5, 0, f);
  pwm.setPWM(6, 0, g);
  pwm.setPWM(7, 0, h);
  pwm.setPWM(8, 0, i);
  pwm.setPWM(9, 0, j);
  pwm.setPWM(10, 0, k);
  pwm.setPWM(11, 0, l);
  pwm.setPWM(12, 0, m);
  delay(500);
}

