/*
   showfigure(int num) 函数可以绘制图形, num为图形选项
   num=0 平衡小车启动中
   num=1 前   (^_^)
   num=2 后   (@_@)
   num=
   num=
*/

#include "Arduino.h"
#include "Char_list.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif



//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* reset=*/ 8);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display


uint8_t draw_state = 0;



void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void draw(void) {
  u8g2_prepare();
  switch (draw_state) {
    case 0:
      u8g2.drawXBMP ( 0 , 0 , 2 , 16 , bitmap_ping);
      u8g2.drawXBMP ( 17 , 0 , 2 , 16 , bitmap_heng );
      u8g2.drawXBMP ( 34 , 0 , 2 , 16 , bitmap_xiao );
      u8g2.drawXBMP ( 51 , 0 , 2 , 16 , bitmap_che );
      u8g2.drawXBMP ( 68 , 0 , 2 , 16 , bitmap_qi );
      u8g2.drawXBMP ( 85 , 0 , 2 , 16 , bitmap_dong );
      u8g2.drawXBMP ( 102 , 0 , 2 , 16 , bitmap_zhong ); break;
    case 1:
      u8g2.drawXBMP ( 50 , 0 , 2 , 16 , bitmap_qian);
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.drawStr(26, 40, "(^_^)"); break;
    case 2:
      u8g2.drawXBMP ( 50 , 0 , 2 , 16 , bitmap_hou);
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.drawStr(20, 40, "(@_@)"); break;
  }
}


void showfigure(int num) {
  
  draw_state = num;
  
//  u8g2.firstPage();
//  do {
//    draw();
//  } while ( u8g2.nextPage() );

  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();
  
}

