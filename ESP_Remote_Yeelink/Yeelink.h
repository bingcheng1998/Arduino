#ifndef Yeelink_h
#define Yeelink_h

#include "Arduino.h" 

#include <ESP8266WiFi.h>

#define ledPin 4                          // 定义ledPin连接到GPIO4
const char* ssid     = "D22-201";         // XXXXXX -- 使用时请修改为当前你的 wifi ssid
const char* password = "963852741";     // XXXXXX -- 使用时请修改为当前你的 wifi 密码
const char* host = "www.yeelink.net";
const char* APIKEY = "f7b461456474ecfa49dd877d22a9f7a5";    //API KEY
int deviceId = 360514;
int sensorId1 = 411336;
int sensorId2 = 411338;

WiFiClient client;
const int tcpPort = 80;
char data[512] ;
int x = 0;
int dat = 0;

//int getSensorState(int sensorId);

class Yeelink
{
     private:
          //byte pin;        //控制led使用的引脚
     
     
     public:
          Yeelink();
          
          getSensorState(int sensorId);

          ~Yeelink();


//          
//          LED(byte p , bool state=LOW );   //构造函数
//          
//          ~LED();          //析构函数
//
//          byte getPin();   //获取控制的引脚
//          
//          void on();      //打开LED
//
//          void off();     //关闭LED
//
//          bool getState();  //获取LED状态
//          void disattach(); //释放引脚与LED的绑定，使得引脚可以控制其他的东西

};




# endif
