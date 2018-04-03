#include "robodog.h"
#include "colorLED.h"
//#include "my_servo.h"
#include"Arduino.h"
#include <MsTimer2.h> //中断库

robodog smalldog;
colorLED head;
void fixdog();//这个程序是在中断时运行
void setup() {
  Serial.begin(57600); //初始化串口
  colorLED::setup();
  MyServo::setup();
  //robodog::setup();
  MsTimer2::set(1000, fixdog); //设置中断，每1000ms进入一次中断服务程序 onTimer()
  MsTimer2::start(); //开始计时
}

void loop() {//蓝牙选择
    if (Serial.available()){
    switch (Serial.read()){
      case 'u'://前
        smalldog.go_straight();
        break;
      case 'd'://后
        smalldog.go_back();
        break;
      case 'l'://左
        smalldog.turn_left();
        break;
      case 'r'://右
        smalldog.turn_right();
        break;
//      case 's'://选择 
//        break;
//      case 't'://开始
//        break;
      case 'q'://方块
        
        break;
      case 't'://三角
        
        break;
      case 'n'://插形
        
        break;
      case 'o'://圆形
        
        break;
      default:;
    };
  };
}

//fixdog() 是在中断时运行,计划接收蓝牙信号,接收陀螺仪信号,然后平衡四只足。
void fixdog(){

}
