/*LED State will show different color at the LED light
 * 使用方法: 引用  LED_State(x); 其中x=1,2,3...
 * LED_State(1); 彩虹循环 !!! 注意,彩虹循环耗时1s, 不可与其他状态同时进行
 * LED_State(2); 红色常亮
 * LED_State(3); 绿色常亮
 * LED_State(3); 蓝色长亮
 * LED_State(x);
 */


#include "Arduino.h" 
#include <Adafruit_NeoPixel.h>
#define PIN 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

void LED_setup(){
  strip.begin();
  strip.show();
}
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void LED_State(int state){
  if(state == 1){
    rainbowCycle(5);
  }
  else if(state == 2){
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
  }
  else if(state == 3){
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
  }
  else if(state == 4){
    strip.setPixelColor(0, strip.Color(0, 0, 255));
    strip.show();
  }
}


void printStart() {
  Serial.println("\n------------- the balance car is trned on ------------");
  Serial.println("\tthe function was written by Hu Bingcheng ");
  Serial.println("\tversion 1.0");
  Serial.println("\t\t!!!");
  Serial.println("--------------------------- welcome ----------------------\n\n");
}
