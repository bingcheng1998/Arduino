#include <IRremote.h>
  
int RECV_PIN = 11;      //定义红外接收模块输出口接arduino数字引脚11
  
IRrecv irrecv(RECV_PIN);
  
decode_results results;
  
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //初始化红外遥控
}
  
void loop() {
  if (irrecv.decode(&results)) {
 if(results.value==16753245)      //确认接收到的第一排按键1的编码，此码是预先读出来的按键编码。
  {
   Serial.println("#0p500t1a2");   //0号舵机每周期步进1us，步进加速值2us运动到负90度位置；如：1s时候速度为3us，2s时候为5us； 
  }
  else if(results.value==16736925)   //确认接收到的第一排按键2的编码
  {
    Serial.println("#0p2500t1a2");  //0号舵机每周期步进1us，步进加速值2us有负90度位置运动到正90度位置； 
  }
    irrecv.resume(); // 接收下一个值
  }
}
