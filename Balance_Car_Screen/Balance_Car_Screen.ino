

#include "background.h"

void setup() {
#if defined(ARDUINO)
  //pinMode(13, OUTPUT);           
  //digitalWrite(13, HIGH);  
  u8g2.begin();
#endif
}


void loop() {
showfigure(0);
delay(1000);
showfigure(1);
delay(1000);
showfigure(2);
delay(1000);
}


