
#include <ESP8266WiFi.h>
WiFiUDP Udp;
unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back


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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println ("\nBegin now!!!");
  setupWiFi();
  
  }
  
  Serial.println ("\nreceived the start signal");
Udp.begin(localPort);

}

void loop() {
  // put your main code here, to run repeatedly:
int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}
