#include "robodog.h"
#include"Arduino.h"
#include "colorLED.h"
int type = 1;
void next_type();
void robodog::setup() { //开机选择模式
  colorLED L1;
  L1.green();
  if (Serial.available()) {
    switch (Serial.read()) {
      case 's'://选择
        next_type();
        switch (type) {
          case 1:
            L1.green();
            //robodog::auto();
            break;
          case 2:
            L1.red();
            //robodog::bluetooth();
            break;
          case 3:
            L1.blue();
            break;
          default:;
        };
        break;
      case 't'://开始
        switch (type) {
          case 1:
            //colorLED::green();
            //robodogautogod();
            break;
          case 2:
            //colorLED::red();
            //bluetooth();
            break;
          case 3:
            //colorLED::blue();
            break;
          default:;
        };
        break;
      default:;
    };
  }
}

void next_type() {
  type++;
  if (type > 3) type = 1;
}

void robodog::change_one(int servo_num, int chang_number){};
void robodog::go_straight(int victor = 5){};
void robodog::go_back(int victor = 5){};
void robodog::turn_right(int victor = 5){};
void robodog::turn_left(int victor = 5){};
void robodog::autodog(){};//自动模式
void robodog::bluetooth(){};//蓝牙操控

