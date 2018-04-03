//接收红外信息，解码获取对应数字，控制舵机旋转对应角度。

#include <IRremote.h>//红外库
int RECV_PIN = 11; //红外接收VOUT引脚定义
int SERVOPIN1 = 9; //舵机驱动引脚定义
int SERVOPIN2 = 10; //舵机驱动引脚定义
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量

//编码示例遥控数字1~9代表舵机20-180角度
long d20 = 0x00ff30CF;
long d40 = 0x00FF18E7;
long d60 = 0x00FF7A85;
long d80 = 0x00FF10EF;
long d100 = 0x00FF38C7;
long d120 = 0x00FF5AA5;
long d140 = 0x00FF42BD;
long d160 = 0x00FF4AB5;
long d180 = 0x00FF52AD;
IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明

void setup() {
  // put your setup code here, to run once:
  pinMode(RECV_PIN, INPUT); //红外VOUT端口模式，输入
  pinMode(SERVOPIN1, OUTPUT); //舵机端口模式，输出
  pinMode(SERVOPIN2, OUTPUT); //舵机端口模式，输出
  Serial.begin(9600);//波特率9600
  irrecv.enableIRIn();//开启红外接收
  Serial.println("system is read now!");
}

int on = 0;
unsigned long last = millis();
static int pos1=90;
static int pos2=90;
void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    if (millis() - last > 250) {
      on = !on;
      digitalWrite(13, on ? HIGH : LOW);
      dump(&results);
    }
    if (results.value == d20) {
      Serial.println("1 ++");
      pos1+=10;
      startRun1(pos1);
    }
    if (results.value == d40) {
      Serial.println("1 --");
      pos1-=10;
      startRun1(pos1);
    }

    if (results.value == d60)
    {
      Serial.println("2 ++");
      pos2+=10;
      startRun2(pos2);
    }
    if (results.value == d80)
    {
      Serial.println("2 --");
      pos2-=10;
      startRun2(pos2);
    }
    
    last = millis();
    irrecv.resume();
  }
  //delay(50);
}

void dump(decode_results *results)
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.println("Could not decode message");
  }
  else
  {
    if (results->decode_type == NEC) {
      Serial.print("Decoded NEC: ");
    }
    else if (results->decode_type == SONY) {
      Serial.print("Decoded SONY: ");
    }
    else if (results->decode_type == RC5) {
      Serial.print("Decoded RC5: ");
    }
    else if (results->decode_type == RC6) {
      Serial.print("Decoded RC6: ");
    }
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
  }
  //Serial.print("Raw (");
  //Serial.print(count, DEC);
  //Serial.print("): ");

//  for (int i = 0; i < count; i++)
//  {
//    if ((i % 2) == 1) {
//      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
//    }
 //   else {
 //     Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
 //   }
 //   Serial.print(" ");
 // }
 // Serial.println("");
}

void servopulse1(int servopin, int myangle) /*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
  pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(SERVOPIN1, HIGH); //将舵机接口电平置高

  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(SERVOPIN1, LOW); //将舵机接口电平置低

  delay(20 - pulsewidth / 1000); //延时周期内剩余时间
}
void servopulse2(int servopin, int myangle) /*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
  pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
 
  digitalWrite(SERVOPIN2, HIGH);
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
 
  digitalWrite(SERVOPIN2, LOW);
  delay(20 - pulsewidth / 1000); //延时周期内剩余时间
}

void startRun1(int degree) {
  if (degree > 0 && degree <= 180) //判断收到数据值是否符合范围
  {
    //直接获取旋转角度
    Serial.print("moving servo to ");
    Serial.print(degree, DEC);
    Serial.println();
    for (int i = 0; i <= 50; i++) //产生PWM个数，等效延时以保证能转到响应角度
    {
      servopulse1(SERVOPIN1, degree); //模拟产生PWM
    }
  }
}
void startRun2(int degree) {
  if (degree > 0 && degree <= 180) //判断收到数据值是否符合范围
  {
    //直接获取旋转角度
    Serial.print("moving servo to ");
    Serial.print(degree, DEC);
    Serial.println();
    for (int i = 0; i <= 50; i++) //产生PWM个数，等效延时以保证能转到响应角度
    {
      servopulse2(SERVOPIN2, degree); //模拟产生PWM
    }
  }
}
