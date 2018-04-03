/*
   ESP8266 TCPcleint 连接到NET WORK ，实现远程遥控LED
   基于yeelink 免费物联平台 https://www.yeelink.net]www.yeelink.net
   by yfrobot
   [url=http://www.yfrobot.com]http://www.yfrobot.com[/url]
\"timestamp\":\"2017-03-05T16:13:04\",
  制冷：25℃  api.yeelink.net/v1.0/device/360514/sensor/411336/datapoints
  制冷：26℃  api.yeelink.net/v1.0/device/360514/sensor/411338/datapoints
  上传数据   api.yeelink.net/v1.0/device/360514/sensor/411340/datapoints

*/

#include <ESP8266WiFi.h>


//#define ledPin 4                          // 定义ledPin连接到GPIO4
const char* ssid     = "D22-201";         // XXXXXX -- 使用时请修改为当前你的 wifi ssid
const char* password = "963852741";     // XXXXXX -- 使用时请修改为当前你的 wifi 密码

//const char* ssid     = "hbc1998";         // XXXXXX -- 使用时请修改为当前你的 wifi ssid
//const char* password = "hbc981118hbc";     // XXXXXX -- 使用时请修改为当前你的 wifi 密码


const char* host = "api.yeelink.net";
const char* APIKEY = "6406e78563f20e66ddbb754a79919d31";    //API KEY
int deviceId = 360514;
int sensorId1 = 411336;
int sensorId2 = 411338;
int sensorId3 = 411375;

WiFiClient client;
const int tcpPort = 80;
char data[512] ;
int x = 0;
int dat = 0;

void setup() {
  WiFi.mode(WIFI_AP_STA);                 //set work mode:  WIFI_AP /WIFI_STA /WIFI_AP_STA
  Serial.begin(115200);
  //pinMode(ledPin, OUTPUT);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
float num = 19.23;
void loop() {
  delay(2000);

  int StateNumber1 = getSensorState(sensorId1);
   postData(sensorId3, num) ;
   delay(11000);
  //int StateNumber2 = getSensorState(sensorId2);
num=num+8.12;
  Serial.println("------------------------- Next Term -------------------------");
}


void postData(int sId, float val) {
  // We now create a URI for the request
  int dId = deviceId;
  String url = "/v1.0/device/";
  url += String(dId);
  url += "/sensor/";
  url += String(sId);
  url += "/datapoints";
  String str = String(val);
  String data = "{\"value\":" + str + "}";
 
  // This will send the request to the server
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Accept: */*\r\n" +
               "U-ApiKey:" + APIKEY + "\r\n" +
               "Content-Length: " + String(str.length()+10) + "\r\n" +                       //发送数据长度
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Connection: close\r\n\r\n" + 
               data
              );
  Serial.println(str);
  Serial.println(String(str.length()));
}
//
//int postTemprature(int sensorId, int temp){
//  if (!client.connect(host, tcpPort)) {
//    Serial.println("connection failed");
//    return 4;
//  }
//
//  String url = "/v1.0/device/";
//  url += String(deviceId);
//  url += "/sensor/";
//  url += String(sensorId);
//  url += "/datapoints";
//  Serial.print(String("POST ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "U-ApiKey:" + APIKEY + "\r\n" +
//               "Content-Length: " + 60 + "\r\n" +
//               "Content-Type: " + "application/x-www-form-urlencoded" +"\r\n"+
//               "Connection: close"+"\r\n\r\n"+
//               "{\"value\":"+76.34 +"}"+ "\r\n\r\n");
//
//  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "U-ApiKey:" + APIKEY + "\r\n" +
//               //"Content-Length: " + 52 + "\r\n" +
//               "Content-Type: " + "application/x-www-form-urlencoded" +"\r\n"+
//               "Connection: close"+"\r\n"+
//               "{\"timestamp\":\"2017-03-05T16:13:04\",\"value\":"+176.34 +"}"+ "\r\n\r\n");
//  //GetJSON();
//}

int getSensorState(int sensorId) {
  int StateForThisTerm = 2;
  if (!client.connect(host, tcpPort)) {
    Serial.println("connection failed");
    return 4;
  }

  String url = "/v1.0/device/";
  url += String(deviceId);
  url += "/sensor/";
  url += String(sensorId);
  url += "/datapoints";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "U-ApiKey:" + APIKEY + "\r\n"
               "Connection: close\r\n\r\n");


  StateForThisTerm = GetJSON();


  Serial.print("\tsensorId: ");
  Serial.print(sensorId);
  Serial.print("\t");
  Serial.print("State:");
  Serial.println(StateForThisTerm);
  return StateForThisTerm;
}



int GetJSON() {
  int State = 2;
  byte JsonBack = 0;
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 2000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      JsonBack = 1;
      return 3;
    }
  }

  while (client.available() && JsonBack == 0) {
    int e = client.read();
    if (e == '{'   &&    x == 0) {
      x = 1;
      Serial.println();
      Serial.print("   The returned JSON value is:\n\t{");
    }
    else if (x == 1) {
      data[dat] = e;

      Serial.print(data[dat]);
      if (e == '}') {
        State = data[dat - 1];
        //Serial.print("\n  dat = ");
        //Serial.println(dat);
        x = 0;
        dat = 0;
        break;
      }
      dat++;
    }
  }
  JsonBack = 1;
  Serial.println();
  return State - 48;
}



