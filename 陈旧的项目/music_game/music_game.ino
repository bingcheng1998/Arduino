#include <TimerOne.h>
/*
   作者:胡炳城
   作品:手势距离控制的电子琴
   起始日期:2017、5、11
   项目地址:
*/

const int V_TrigPin = 2;
const int V_EchoPin = 3;
const int P_TrigPin = 4;
const int P_EchoPin = 5;
const int volume_Pin = 1;
const int pitch_Pin = 0;
const int volumeControll = 9; //通过改变电压来刺激三极管以控制音量
const int pitchControll = 10; //连续改变电压来控制音色

void setup(void)
{
  pinMode(V_TrigPin, OUTPUT);
  pinMode(V_EchoPin, INPUT);
  pinMode(P_TrigPin, OUTPUT);
  pinMode(P_EchoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Ultrasonic sensor:");
  Timer1.initialize(150000);//每0.15秒进行一次中断程序GetVP
  Timer1.attachInterrupt(GetVP); // 获取音量与音调
}


volatile unsigned int volume = 0; // 这是电子琴的音量
volatile unsigned int pitch = 120; // 这是电子琴的音调

float GetDis(int VorP) {
  float distance;
  int TrigPin, EchoPin;
  if (VorP == 1) {
    TrigPin = V_TrigPin;
    EchoPin = V_EchoPin;
  }
  else {
    TrigPin = P_TrigPin;
    EchoPin = P_EchoPin;
  };
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  // 检测脉冲宽度，并计算出距离
  distance = pulseIn(EchoPin, HIGH) / 58.00;
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(10);
}

void GetVP(void)
{
volume = constrain(50-GetDis(volume_Pin),0,50);
pitch = constrain(50-GetDis(pitch_Pin),0,50);
}

void loop(void)
{
  unsigned int volumeCopy;
  unsigned int pitchCopy;

  noInterrupts();
  volumeCopy = volume;
  pitchCopy = pitch;
  interrupts();
  
  int thisPitch = map(pitchCopy, 10, 50, 120, 1500);
  int thisVolume = map(volumeCopy, 0, 50, 0, 255);//这些地方要改,因为用到三极管,只要小电压就可以撬动
  // 9号数字引脚上接扬声器
  //改变音量
  analogWrite(volumeControll, constrain(thisVolume, 0, 255));
  //改变音调,模拟钢琴音色
  analogWrite(pitchControll, 100);
  tone(9, thisPitch, 1); //时长单位ms
  analogWrite(pitchControll, 10);
  tone(9, thisPitch, 2);
  analogWrite(pitchControll, 225);
  tone(9, thisPitch, 1);
  analogWrite(pitchControll, 140);
  tone(9, thisPitch, 3);
  analogWrite(pitchControll, 60);//这些地方要改,因为用到三极管,只要小电压就可以撬动
  tone(9, thisPitch, 3);
}
