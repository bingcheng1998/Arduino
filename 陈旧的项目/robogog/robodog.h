#include "my_servo.h"
#include "colorLED.h"
#include "Arduino.h"
class robodog{
  public:
  void change_one(int servo_num, int chang_number);
  void go_straight(int victor=5);
  void go_back(int victor=5);
  void turn_right(int victor=5);
  void turn_left(int victor=5);
  static void setup();
  void autodog();//自动模式
  void bluetooth();//蓝牙操控

  private:
  
};

