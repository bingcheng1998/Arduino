//
//  Four_digital_tube.cpp
//  Four_digital_tube
//
//  Created by 胡炳城 on 2017/1/4.
//  Copyright © 2017年 胡炳城. All rights reserved.
//

#include "Four_digital_tube.h"
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int p = 8;
//设置阳极接口
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;
//设置变量
long n = 0;
int x = 100;
int del = 55;  //此处数值对时钟进行微调
 

void LED_4_setup()
{
    pinMode(d1, OUTPUT);
      pinMode(d2, OUTPUT);
      pinMode(d3, OUTPUT);
      pinMode(d4, OUTPUT);
      pinMode(a, OUTPUT);
      pinMode(b, OUTPUT);
      pinMode(c, OUTPUT);
      pinMode(d, OUTPUT);
      pinMode(e, OUTPUT);
      pinMode(f, OUTPUT);
      pinMode(g, OUTPUT);
      pinMode(p, OUTPUT);
}
 

void print2screen(double de){
    LED_4_setup();
    de*=10;
    int m=de;
    int cd1,cd2,cd3,cd4;
    cd1=m/1000;
    cd2=(m-cd1*1000)/100;
    cd3=(m-cd1*1000-cd2*100)*10/100;
    cd4=(m-cd1*1000-cd2*100-cd3*10)*100/100;
    //cd1=4,cd2=6,cd3=8,cd4=9;
    if(m>=1000){
        clearLEDs();
        pickDigit(1);
          pickNumber(cd1);
        //dispDec(1);
          delayMicroseconds(del);
        clearLEDs();
        pickDigit(2);
          pickNumber(cd2);
        //dispDec(1);
          delayMicroseconds(del);
        clearLEDs();
        pickDigit(3);
          pickNumber(cd3);
        dispDec(1);
          delayMicroseconds(del);
        clearLEDs();
        pickDigit(4);
          pickNumber(cd4);
        //dispDec(3);
          delayMicroseconds(del);
    }
    
    else if(m>=100){
        clearLEDs();
        pickDigit(2);
          pickNumber(cd2);
        //dispDec(1);
          delayMicroseconds(del);
        clearLEDs();
        pickDigit(3);
          pickNumber(cd3);
        dispDec(1);
          delayMicroseconds(del);
        clearLEDs();
        pickDigit(4);
          pickNumber(cd4);
        //dispDec(1);
          delayMicroseconds(del);
    }
    else if(m>=10){
        clearLEDs();
        pickDigit(3);
          pickNumber(cd3);
        dispDec(1);
          delayMicroseconds(del);
        clearLEDs();
        pickDigit(4);
          pickNumber(cd4);
        //dispDec(2);
          delayMicroseconds(del);
    }
    
    else{
        clearLEDs();
        pickDigit(3);
          pickNumber(0);
        dispDec(1);
          delayMicroseconds(del);
        clearLEDs();
        pickDigit(4);
          pickNumber(cd4);
        //dispDec(2);
          delayMicroseconds(del);
    }
}

void pickDigit(int x)  //定义pickDigit(x),其作用是开启dx端口
{
      digitalWrite(d1, LOW);
      digitalWrite(d2, LOW);
      digitalWrite(d3, LOW);
      digitalWrite(d4, LOW);
     
      switch(x)
      {
              case 1:
                digitalWrite(d1, HIGH);
                break;
              case 2:
                digitalWrite(d2, HIGH);
                break;
              case 3:
                digitalWrite(d3, HIGH);
                break;
              default:
                digitalWrite(d4, HIGH);
                break;
          }
}
 
void pickNumber(int x)   //定义pickNumber(x),其作用是显示数字x
{
      switch(x)
      {
              default:
                zero();
                break;
              case 1:
                one();
                break;
              case 2:
                two();
                break;
              case 3:
                three();
                break;
              case 4:
                four();
                break;
              case 5:
                five();
                break;
              case 6:
                six();
                break;
              case 7:
                seven();
                break;
              case 8:
                eight();
                break;
              case 9:
                nine();
                break;
          }
}
 
void dispDec(int x)  //设定开启小数点
{
      digitalWrite(p, LOW);
}
 
void clearLEDs()  //清屏
{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(p, HIGH);
}
 
void zero()  //定义数字0时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
}
 
void one()  //定义数字1时阴极那些管脚开关
{
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}
 
void two()  //定义数字2时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
}
 
void three()  //定义数字3时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
}
 
void four()  //定义数字4时阴极那些管脚开关
{
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}
 
void five()  //定义数字5时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}
 
void six()  //定义数字6时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}
 
void seven()  //定义数字7时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
}
 
void eight()  //定义数字8时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}
 
void nine()  //定义数字9时阴极那些管脚开关
{
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
}
