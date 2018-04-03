

#include "Yeelink.h"
#include "Arduino.h" 
#include <ESP8266WiFi.h>

Yeelink::Yeelink(){};
~Yeelink(){};

Yeelink::getSensorState(int sensorId){
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

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 2000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return 3;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    int e = client.read();
    if (e == '{'   &&    x == 0) {
      x = 1;
    } else if (x == 1) {
      data[dat] = e;
      //      Serial.print(e);
      if (e == '}') {
        digitalWrite(ledPin, data[dat - 1] - '0');
        //Serial.print("button value :");
        StateForThisTerm = data[dat - 1];
        //Serial.print(StateForThisTerm);
        x = 0;
        dat = 0;
        break;
      }
      dat++;
    }
  }
  Serial.print(sensorId);
  Serial.print("\t");
  Serial.println(StateForThisTerm-48);
  return StateForThisTerm-48;
}
//
//int getSensorState(int sensorId) {
//  int StateForThisTerm = 2;
//  if (!client.connect(host, tcpPort)) {
//    Serial.println("connection failed");
//    return 4;
//  }
//  String url = "/v1.0/device/";
//  url += String(deviceId);
//  url += "/sensor/";
//  url += String(sensorId);
//  url += "/datapoints";
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "U-ApiKey:" + APIKEY + "\r\n"
//               "Connection: close\r\n\r\n");
//
//  unsigned long timeout = millis();
//  while (client.available() == 0) {
//    if (millis() - timeout > 2000) {
//      Serial.println(">>> Client Timeout !");
//      client.stop();
//      return 3;
//    }
//  }
//
//  // Read all the lines of the reply from server and print them to Serial
//  while (client.available()) {
//    int e = client.read();
//    if (e == '{'   &&    x == 0) {
//      x = 1;
//    } else if (x == 1) {
//      data[dat] = e;
//      //      Serial.print(e);
//      if (e == '}') {
//        digitalWrite(ledPin, data[dat - 1] - '0');
//        //Serial.print("button value :");
//        StateForThisTerm = data[dat - 1];
//        //Serial.print(StateForThisTerm);
//        x = 0;
//        dat = 0;
//        break;
//      }
//      dat++;
//    }
//  }
//  Serial.print(sensorId);
//  Serial.print("\t");
//  Serial.println(StateForThisTerm-48);
//  return StateForThisTerm-48;
//}
