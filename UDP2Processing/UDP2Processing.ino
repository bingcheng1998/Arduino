#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;
unsigned int localPort = 8266;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "I received n";

const char WiFiAPPSW[] = "12345678";    //设置AP模式下模块所发出的WIFI的密码
//#define MAX_SRV_CLIENTS 1               //最大同时连接数，即可接入的设备数量的最大值，

//char data[20];
//int ind = 0;
uint8_t teapotPacket[15] = { '$', 0x02, 0, 9, 9, 9, 6, 7, 8, 9, 8, 0x00, 0x00, '\r', '\n' };              //8266 tcpserver只能接入5个（此数据不确定，网上是这么说的）

IPAddress remoteIp;
int remotePORT;

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

  for (int i = 0; i < AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSW);

  Serial.println();
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.softAPIP() );
}

void setupUdp() {
  bool udpSetup = 0;
  Serial.println("UDP connecting...");
  while (!udpSetup) {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      remoteIp = Udp.remoteIP();
      Serial.print(remoteIp);
      Serial.print(", port ");
      remotePORT = Udp.remotePort();
      Serial.println(remotePORT);

      // read the packet into packetBufffer
      int len = Udp.read(packetBuffer, 255);
      if (len > 0) {
        packetBuffer[len] = 0;
      }
      Serial.println("Contents:");
      Serial.println(packetBuffer);
      //      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      //      Udp.write(ReplyBuffer);
      //      Udp.endPacket();
      udpSetup = !udpSetup;
    }

  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println ("\nBegin now!!!");
  setupWiFi();
  Udp.begin(localPort);
  setupUdp();
  Serial.println("UDP connected!!!");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.print("Contents:\t");
    Serial.println(packetBuffer);
    ReplyBuffer[12] = packetBuffer[0];
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(remoteIp, remotePORT);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
    unsigned long time0 = millis();
    teapotPacket[2]==0;
    while (millis() - time0 < 1000) {
      teapotPacket[2] ++;
      teapotPacket[11]++;
      Udp.beginPacket(remoteIp, remotePORT);
      Udp.write(ReplyBuffer);
      Udp.endPacket();
      Udp.beginPacket(remoteIp, remotePORT);
      for (int i = 0; i < 15; i++) {
        
        Udp.write(teapotPacket[i]);
        
        Serial.print(teapotPacket[i]);

      }
      Udp.endPacket();
      delay(5);
      Serial.println();
    }
  }
}



