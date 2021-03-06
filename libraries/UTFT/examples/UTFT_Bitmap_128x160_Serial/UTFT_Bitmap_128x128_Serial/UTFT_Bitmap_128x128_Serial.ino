// UTFT_Bitmap_128x128 (C)2012 Henning Karlsen
// https://shop73023976.taobao.com/?spm=2013.1.1000126.d21.f3HieB
// This program is a demo of the drawBitmap()-function.
//
// This demo was made to work on the 128x128 modules.
// Any other size displays may cause strange behaviour.
//
// This program requires the UTFT library.
//

#include <UTFT.h>
#include <avr/pgmspace.h>

UTFT myGLCD(QD_TFT180A,A2,A1,A5,A4,A3);  // Remember to change the model parameter to suit your display module!

extern unsigned int icon1[0x400];
extern unsigned int icon2[0x400];
extern unsigned int tux[0x1000];

void setup()
{
  myGLCD.InitLCD(PORTRAIT);
}

void loop()
{
// Draw a 4 by 4 grid of a 32x32 icon.
  myGLCD.fillScr(255, 255, 255);
  for (int x=0; x<4; x++)
    for (int y=0; y<5; y++)
      myGLCD.drawBitmap (x*32, y*32, 32, 32, icon1);

  delay(5000);
  
// Draw a 2 by 2 grid of a 64x64 icon.
  myGLCD.fillScr(255, 255, 255);
  for (int x=0; x<2; x++)
    for (int y=0; y<3; y++)
  myGLCD.drawBitmap (x*64, y*64, 64, 64, tux);

  delay(5000);

// Draw a 2 by 2 grid of a 32x32 icon.
  myGLCD.fillScr(255, 255, 255);
  for (int x=0; x<2; x++)
    for (int y=0; y<3; y++)
      myGLCD.drawBitmap (x*64, y*64, 32, 32, icon2, 2);

  delay(5000);
}

