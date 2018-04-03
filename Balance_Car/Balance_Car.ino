/* 本程序为蓝牙控制的平衡小车的控制程序
   包含LED模块, 六轴陀螺仪模块, 蓝牙模块, 手势传感器模块
   本程序开始于2017年7月25日
*/
#include "LED.h"
#include <SoftwareSerial.h>
#include <Kalman.h>
#include <Wire.h>
///include <Math.h>
#include "MPU6050.h"
#include "background.h"
#include "Gesture.h"
#include "Wheel.h"
SoftwareSerial BlueTooth(/*接模块上的TX*/4, /*接模块上的RX*/7);
char val;
void setup() {
  Serial.begin(9600);
  BlueTooth.begin(9600);
  LED_setup();
  GestureSetup();
  WheelSetup();
  Serial.println("\n");
  showfigure(0);
  delay(1000);
  printStart();
  WriteMPUReg(0x6B, 0); //启动MPU6050设备
  Calibration(); //执行校准
  nLastTime = micros(); //记录当前时间
  showfigure(0);
}

void loop() {
  int readouts[nValCnt];
  ReadAccGyr(readouts); //读出测量值

  float realVals[7];
  Rectify(readouts, realVals); //根据校准的偏移量进行纠正

  //计算加速度向量的模长，均以g为单位
  float fNorm = sqrt(realVals[0] * realVals[0] + realVals[1] * realVals[1] + realVals[2] * realVals[2]);
  float fRoll = GetRoll(realVals, fNorm); //计算Roll角
  if (realVals[1] > 0) {
    fRoll = -fRoll;
  }
  float fPitch = GetPitch(realVals, fNorm); //计算Pitch角
  if (realVals[0] < 0) {
    fPitch = -fPitch;
  }

  //计算两次测量的时间间隔dt，以秒为单位
  unsigned long nCurTime = micros();
  float dt = (double)(nCurTime - nLastTime) / 1000000.0;
  //对Roll角和Pitch角进行卡尔曼滤波
  float fNewRoll = kalmanRoll.getAngle(fRoll, realVals[4], dt);
  float fNewPitch = kalmanPitch.getAngle(fPitch, realVals[5], dt);
  //跟据滤波值计算角度速
  float fRollRate = (fNewRoll - fLastRoll) / dt;
  float fPitchRate = (fNewPitch - fLastPitch) / dt;

  //更新Roll角和Pitch角
  fLastRoll = fNewRoll;
  fLastPitch = fNewPitch;
  //更新本次测的时间
  nLastTime = nCurTime;

  //向串口打印输出Roll角和Pitch角，运行时在Arduino的串口监视器中查看

  Serial.print("Roll:");
  Serial.print(fNewRoll); Serial.print('(');
  Serial.print(fRollRate); Serial.print("),\tPitch:");
  Serial.print(fNewPitch); Serial.print('(');
  Serial.print(fPitchRate); Serial.print(")\n");
  delay(10);

  //-------------------------------------------


  if (BlueTooth.available()) {
    val = BlueTooth.read();
    Serial.print("BlueTooth receive the char: ");
    Serial.print(val);
    Serial.println(".");
    if (val == 'q') {
      showfigure(1);
    }
    if (val == 'h') {
      showfigure(2);
    }
    if (val == 'a') {
      showfigure(0);
      LED_State(1);
    }
    if (val == 'b') {
      LED_State(2);
      
for(int i=0; i<255;i++){
  TurnLeft(i);
  delay(10);
}
for(int i=255; i>0;i--){
  TurnLeft(i);
  delay(10);
}
    } 

    //delay(250);
  }

  if (apds.readProximity(proximity_data)&&proximity_data>0) {
    Serial.print("Proximity: ");
    Serial.println(proximity_data);
    if (proximity_data > 100) {
      LED_State(1);
    }
  }
}

