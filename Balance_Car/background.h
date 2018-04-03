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

//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0); //慢速
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // 快速
uint8_t draw_state = 0;


//void u8g_prepare(void) {
//  u8g.setFont(u8g_font_6x10);
//  u8g.setFontRefHeightExtendedText();
//  u8g.setDefaultForegroundColor();
//  u8g.setFontPosTop();
//}
void draw(void) {
  //u8g_prepare();
  switch (draw_state) {
    case 0:
      u8g.drawBitmapP ( 0 , 0 , 2 , 16 , bitmap_ping);
      u8g.drawBitmapP ( 17 , 0 , 2 , 16 , bitmap_heng );
      u8g.drawBitmapP ( 34 , 0 , 2 , 16 , bitmap_xiao );
      u8g.drawBitmapP ( 51 , 0 , 2 , 16 , bitmap_che );
      u8g.drawBitmapP ( 68 , 0 , 2 , 16 , bitmap_qi );
      u8g.drawBitmapP ( 85 , 0 , 2 , 16 , bitmap_dong );
      u8g.drawBitmapP ( 102 , 0 , 2 , 16 , bitmap_zhong ); break;
    case 1:
      u8g.drawBitmapP ( 50 , 0 , 2 , 16 , bitmap_qian);
      u8g.setFont(u8g_font_osb21);
      u8g.drawStr(26, 40, "(^_^)"); break;
    case 2:
      u8g.drawBitmapP ( 50 , 0 , 2 , 16 , bitmap_hou);
      u8g.setFont(u8g_font_osb21);
      u8g.drawStr(20, 40, "(@_@)"); break;
    case 3:
      u8g.setPrintPos(20, 30);
      u8g.print("Welcome!!!! "); break;
  }
}

void showfigure(int num) {
  draw_state = num;
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}

