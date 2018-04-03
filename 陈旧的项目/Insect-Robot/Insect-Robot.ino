/*虫虫机器人*
   开写日期: 2017、4、27
   最后一次修改日期:
   作者: 胡炳城
*/

#include <Servo.h>
#include <IRremote.h>

//定义遥控面板(用的是黑色遥控器,上方有十字操作阵),
//如果款式不同,请自己修改
#define left  16720605
#define right 16761405
#define up    16736925
#define down  16754775
#define OK 16712445
#define _1 16738455
#define _2 16750695
#define _3 16756815
#define _4 16724175
#define _5 16718055
#define _6 16743045
#define _7 16716015
#define _8 16726215
#define _9 16734885
#define _* 16728765
#define _0 16730805
#define _J 16732845
#define delayer 4294967295

const int RECV_PIN = 2;
const int myhand_PIN = 14;
const int myleg_PIN = 15;
const int redPin = 5;//此接口为可调压接口
const int greenPin = 3;//此接口为可调压接口
const int bluePin = 7;
const int TrigPin = A0;
const int EchoPin = A1;
const float Back_DIS = 23.0;//折返的距离,单位cm,loop2使用
const float Most_DIS = 40.0;//loop4中颜色变化的基础值,大于此距离,显示为红色,越靠近颜色越蓝

static void (*restartArduino)(void) = 0x0000; // ***复位本CPU函数指针

Servo myhand;//前腿
Servo myleg;//后腿
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // 开启红外接收头
  myhand.attach(myhand_PIN);
  myleg.attach(myleg_PIN);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  colorRGB(90, 190, 134);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if (results.value == _1) { //手动模式
      Blink_RGB(100, 40, 225, 6);
      loop1();
    }
    else if (results.value == _2) { //自动模式
      Blink_RGB(20, 225, 50, 6);
      loop2();
    }
    else if (results.value == _3) { //待定
      Blink_RGB(225, 40, 50, 6);
      loop3();
    }
    else if (results.value == _4) { //待定
      Blink_RGB(0, 140, 50, 6);
      loop4();
    }
    else if (results.value == _5) { //待定
      Blink_RGB(100, 100, 100, 6);
      loop5();
    }
    //delay(50);
    irrecv.resume();
  };
}

void loop1() {
  colorRGB(random(50, 255), random(50, 255), random(50, 255));
  for (;;) {
    if (irrecv.decode(&results)) {
      Serial.println(results.value);
      if (results.value == up) { //前进
        colorRGB(random(50, 255), random(50, 255), random(50, 255));
        GoAhead();
        stop();
      }
      else if (results.value == down) { //
        colorRGB(random(50, 255), random(50, 255), random(50, 255));
        GoBack();
        stop();
      }
      else if (results.value == left) { //
        colorRGB(random(50, 255), random(50, 255), random(50, 255));
        TurnLeft();
        stop();
      }
      else if (results.value == right) { //
        colorRGB(random(50, 255), random(50, 255), random(50, 255));
        TurnRight();
        stop();
      }
      else if (results.value == _J) { //前进
        restartArduino(); //复位
      };
      irrecv.resume(); // 必不可少,接收下一个值
    };
  };
}

void loop2() {
  for (;;) {
    if (irrecv.decode(&results)) {
      Serial.println(results.value);
      if (results.value == delayer) {
        restartArduino(); //复位
      };
      irrecv.resume();
    };
    colorRGB(random(50, 255), random(50, 255), random(50, 255));
    GoAhead();
    if (isClose() == 1) {
      colorRGB(225, 0, 0);
      stop();
      GoBack();
      TurnLeft();
      Serial.println("I am close to the wall");
    };
  };
}

void loop3() {
  for (;;) {
    colorRGB(random(50, 255), random(50, 255), random(50, 255));
    delay(1000);
    if (irrecv.decode(&results)) {
      Serial.println(results.value);
      if (results.value == _J) { //
        restartArduino(); //复位
      };
      irrecv.resume();
    };
  };
}

void loop4() {
  for (;;) {
    int REDcolor = (int)constrain(DisSonar() * 225 / Most_DIS, 0, 255);
    Serial.println(REDcolor);
    //Serial.println(((225-REDcolor)/10));
    //Serial.println((225-REDcolor));
    Serial.println();
    colorRGB(REDcolor, (225 - REDcolor), 0);
    delay(50);
    if (irrecv.decode(&results)) {
      Serial.println(results.value);
      if (results.value == _J) {
        restartArduino(); //复位
      };
      irrecv.resume();
    };
  }
}

void loop5() {
  for (;;) {
    for (int i = 0; i < 254; i++) {
      colorRGB(i, 0, 0);
      delay(20);
    };
    for (int i = 0; i < 254; i++) {
      colorRGB(0, i, 0);
      delay(20);
    };
    if (irrecv.decode(&results)) {
      Serial.println(results.value);
      if (results.value == _J) {
        restartArduino(); //复位
      };
      irrecv.resume();
    };
  }
}
void runahead(int hand1, int hand2, int leg1, int leg2, int times){
  for (int i = 0; i < times; i++) {
    myleg.write(leg1);
    myhand.write(hand2-15);
    delay(200);
    myhand.write(hand1);
    delay(100);
    myleg.write(leg2);
    myhand.write(hand1-15);
    delay(200);
    myhand.write(hand2);
    delay(100);
  };
}

void GoAhead() {
  // running(70, 110, 130, 50, 5);
  for (int i = 0; i < 5; i++) {
    myleg.write(120);
    myhand.write(70);
    delay(200);
    myhand.write(120);
    delay(100);
    myleg.write(60);
    myhand.write(110);
    delay(200);
    myhand.write(80);
    delay(100);
  };
  //runahead(110, 70, 120, 60, 5);
}
void GoBack() {
  running(60, 120, 60, 120, 5);
}
void TurnLeft() {
  running(60, 120, 130, 70, 5);
}
void TurnRight() {
  running(60, 120, 110, 50, 5);
}
void stop() {
  Wservo(90, 90);
}

void Wservo(int hand, int leg) { //写舵机角度
  myhand.write(hand);
  myleg.write(leg);
  delay(300);
}

void running(int hand1, int hand2, int leg1, int leg2, int times) {
  for (int i = 0; i < times; i++) {
    Wservo(hand1, leg1);
    Wservo(hand2, leg2);
  };
}

void colorRGB(int red, int green, int blue) {
  analogWrite(redPin, constrain(red, 0, 255));
  analogWrite(greenPin, constrain(green, 0, 255));
  analogWrite(bluePin, constrain(blue, 0, 255));
}
void Blink_RGB(int red, int green, int blue, int times) {
  for (int i = 0; i < times; i++) {
    analogWrite(redPin, constrain(red, 0, 255));
    analogWrite(greenPin, constrain(green, 0, 255));
    analogWrite(bluePin, constrain(blue, 0, 255));
    delay(80);
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(80);
  };
}

bool isClose() {
  float distance = DisSonar();
  if (Back_DIS > distance) {
    return 1;
  }
  else return 0;
}

float DisSonar() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  float distance;
  distance = pulseIn(EchoPin, HIGH) / 58.00;
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  return distance;
}

