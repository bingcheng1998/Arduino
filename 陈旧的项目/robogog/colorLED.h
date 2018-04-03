#ifndef _COLORLED_H
#define _COLORLED_H
#include"Arduino.h"

class colorLED {
  public:
    void red();
    void red_blink();
    void green();
    void green_blink();
    void blue();
    void blue_blink();
    void color();
    void randcolor();
    static void setup();
};
#endif
