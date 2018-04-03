/*
   ESP8266 TCPcleint 连接到NET WORK ，实现远程遥控LED
   基于yeelink 免费物联平台 https://www.yeelink.net]www.yeelink.net
   by yfrobot
   [url=http://www.yfrobot.com]http://www.yfrobot.com[/url]

  制冷：25℃  api.yeelink.net/v1.0/device/360514/sensor/411336/datapoints
  制冷：26℃  api.yeelink.net/v1.0/device/360514/sensor/411338/datapoints
*/

#include <ESP8266WiFi.h>

#include "Yeelink.h"

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
Yeelink Yee1(sensorId1);

void setup() {
  WiFi.mode(WIFI_AP_STA);                 //set work mode:  WIFI_AP /WIFI_STA /WIFI_AP_STA
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2000);
  int k = Yee1.getSensorState(sensor1);
//
//  int StateNumber1 = getSensorState(sensorId1);
//  
//  int StateNumber2 = getSensorState(sensorId2);
//  
  Serial.println("\nNext Term ...\n");
}



