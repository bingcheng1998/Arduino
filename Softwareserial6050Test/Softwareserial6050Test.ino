#include <SoftwareSerial.h>

unsigned char Re_buf[11],counter=0;
unsigned char sign=0;
float a[3],w[3],angle[3],T;

SoftwareSerial mySerial(8, 9); 

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
while (!Serial) {
  }
  Serial.println("SoftwareSerial start at RX-8, TX-9");
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    mySerial.listen();
    while (mySerial.available()>0) {

    //char inChar = (char)Serial.read(); Serial.print(inChar); //Output Original Data, use this code

    Re_buf[counter] = (unsigned char) mySerial.read();
    if (counter == 0 && Re_buf[0] != 0x55) return; //第0号数据不是帧头
    counter++;
    if (counter == 11)          //接收到11个数据
    {
      counter = 0;             //重新赋值，准备下一帧数据的接收
      sign = 1;
    }

  }



  if (sign)
  {
    sign = 0;
    if (Re_buf[0] == 0x55)   //检查帧头
    {
      switch (Re_buf [1])
      {
        case 0x51:
          a[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 16;
          a[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 16;
          a[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 16;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
        case 0x52:
          w[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 2000;
          w[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 2000;
          w[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 2000;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          break;
        case 0x53:
          angle[0] = (short(Re_buf [3] << 8 | Re_buf [2])) / 32768.0 * 180;
          angle[1] = (short(Re_buf [5] << 8 | Re_buf [4])) / 32768.0 * 180;
          angle[2] = (short(Re_buf [7] << 8 | Re_buf [6])) / 32768.0 * 180;
          T = (short(Re_buf [9] << 8 | Re_buf [8])) / 340.0 + 36.25;
          Serial.print("a:\t");
          Serial.print(a[0]); Serial.print("\t");
          Serial.print(a[1]); Serial.print("\t");
          Serial.print(a[2]); Serial.print("\t");
          Serial.print("w:\t");
          Serial.print(w[0]); Serial.print("\t");
          Serial.print(w[1]); Serial.print("\t");
          Serial.print(a[2]); Serial.print("\t");
          Serial.print("angle:\t");
          Serial.print(angle[0]); Serial.print("\t");
          Serial.print(angle[1]); Serial.print("\t");
          Serial.print(angle[2]); Serial.print("\t");
          Serial.print("T:\t");
          Serial.println(T);
          break;
      }
    }
  }
}

