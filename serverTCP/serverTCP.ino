   


#include <ESP8266WiFi.h>
//#include "arduino.h"

WiFiServer server(8266);                //端口号，范围  0-65535
WiFiClient serverClients;

const char WiFiAPPSW[] = "12345678";    //设置AP模式下模块所发出的WIFI的密码
//#define MAX_SRV_CLIENTS 1               //最大同时连接数，即可接入的设备数量的最大值，
                  
char data[20];
int ind = 0;
uint8_t teapotPacket[15] = { '$', 0x02, 0,3, 4,51, 6,7, 8,9,8, 0x00, 0x00, '\r', '\n' };                   //8266 tcpserver只能接入5个（此数据不确定，网上是这么说的）


void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 3], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();

 //设置AP模式下的WIFI名称：12345678_ + MAC地址后六位  
  String AP_NameString = "12345678" + macID;
   
  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, AP_NameString.length() + 1, 0);
   
  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);
   
  WiFi.softAP(AP_NameChar, WiFiAPPSW);
 
  Serial.println();
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.softAPIP() );

  server.begin();
    
}

void setup() 
{
  Serial.begin(115200);
  Serial.println ("\nBegin now!!!");
  setupWiFi();
  
  bool available_init = 1;
  while(available_init){
    delay(10);
    if (server.hasClient()){
            if (!serverClients || !serverClients.connected()){
                if (serverClients) serverClients.stop();
                serverClients = server.available(); 
            } 
        WiFiClient serverClient = server.available();
        serverClient.stop();
        
    }
    if(serverClients.available()){
          available_init = 0;
    }
  }
  
  Serial.println ("\nreceived the start signal");
}
 
void loop() 
{
    //uint8_t i;
    //检测服务器端是否有活动的客户端连接
    
    if (server.hasClient()){
            if (!serverClients || !serverClients.connected()){
                if (serverClients) serverClients.stop();
                serverClients = server.available(); 
            } 
        WiFiClient serverClient = server.available();
        serverClient.stop();
    }

    
    //检查客户端的数据

        if (serverClients && serverClients.connected())
        {
            if (serverClients.available())
            {
                Serial.println("Connected to client !!! ");
                 //从Telnet客户端获取数据
                while (serverClients.available()) {
                    data[ind] = serverClients.read(); //读取client端发送的字符
                    ind++;
                         
                }
            for(int j=0;j < ind; j++)
            {
              Serial.print(data[j]);
            }
            Serial.println();
            ind = 0;
            serverClients.print("OK! Got your request.");        //在client端回复    
            unsigned long nowtime=millis();
            while(millis()-nowtime<5000){
                 teapotPacket[2] ++;
                 teapotPacket[11]++;
                 for(int i = 0; i<15; i++){
                  serverClients.write(teapotPacket[i]);
                  Serial.print(teapotPacket[i]);
                  
                 }
                 delay(5);
                 Serial.println();
            }
            }     
        
    }
}



