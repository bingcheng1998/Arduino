#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;

byte e[8]=     {0x7C,0x7C,0x60,0x7C,0x7C,0x60,0x7C,0x7C};
byte d[8]=     {0x78,0x7C,0x66,0x66,0x66,0x66,0x7C,0x78};
byte u[8]=     {0x66,0x66,0x66,0x66,0x66,0x66,0x7E,0x7E};
byte c[8]=     {0x7E,0x7E,0x60,0x60,0x60,0x60,0x7E,0x7E};
byte eight[8]= {0x7E,0x7E,0x66,0x7E,0x7E,0x66,0x7E,0x7E};
byte s[8]=     {0x7E,0x7C,0x60,0x7C,0x3E,0x06,0x3E,0x7E};
byte dot[8]=   {0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18};
byte o[8]=     {0x7E,0x7E,0x66,0x66,0x66,0x66,0x7E,0x7E};
byte m[8]=     {0xE7,0xFF,0xFF,0xDB,0xDB,0xDB,0xC3,0xC3};
byte JI[8]=    {0xF7,0x22,0x22,0x22,0x22,0x22,0xA2,0x47};
byte _10[8]=   {0x46,0xC9,0x49,0x49,0x49,0x49,0x49,0xE6};
byte _9[8]=    {0x18,0x24,0x24,0x1C,0x04,0x24,0x18,0x00};
byte  _8[8]=   {0x18,0x24,0x24,0x18,0x24,0x24,0x24,0x18};
byte _7[8]=   {0x7C,0x44,0x08,0x10,0x10,0x10,0x10,0x10};
byte  _6[8]=  {0x18,0x24,0x20,0x38,0x24,0x24,0x24,0x18};
byte  _5[8]=  {0x20,0x3C,0x20,0x38,0x04,0x04,0x24,0x18};
byte  _4[8]=  {0x04,0x0C,0x14,0x24,0x3E,0x04,0x04,0x00};
byte  _3[8]=  {0x3C,0x24,0x08,0x38,0x04,0x04,0x24,0x18};
byte  _2[8]=  {0x18,0x24,0x24,0x08,0x10,0x20,0x3C,0x00};
byte  _1[8]=  {0x08,0x18,0x08,0x08,0x08,0x08,0x1C,0x00};
byte  _I[8]=  {0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x3C};
byte  B_love[8]=  {0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18,0x00};
byte  S_love[8]=  {0x00,0x24,0x7E,0x7E,0x3C,0x18,0x00,0x00};
//byte  [8]=  {};
//byte  [8]=  {};





LedControl lc=LedControl(DIN,CLK,CS,0);

void setup(){
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
}

void loop(){ 

//    byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
//    byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
//    byte frown[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};
//    
//
//    printByte(smile);
//     
//    delay(1000);
//
//    printByte(neutral);
//    
//    delay(1000);
//
//    printByte(frown);    
//
//    delay(1000);

printByte(_I);
delay(1000);
printByte(B_love);
delay(300);
printByte(S_love);
delay(300);
printByte(B_love);
delay(300);
printByte(JI);
delay(1000);


   printByte(_10);
   delay(1000);
    printByte(_9);
    delay(1000);
    printByte(_8);
    delay(1000);
    printByte(_7);
    delay(1000);
    printByte(_6);
    delay(1000);
    printByte(_5);
delay(1000);
printByte(_4);
delay(1000); 
printByte(_3);
delay(1000);
printByte(_2);
delay(1000);

printByte(_1);
delay(1000);
printByte(JI);
    delay(1000);
    //printEduc8s();
   
    lc.clearDisplay(0);
    
    //delay(1000);

    
}

void printEduc8s()
{
  printByte(e);
  delay(1000);
  printByte(d);
  delay(1000);
  printByte(u);
  delay(1000);
  printByte(c);
  delay(1000);
  printByte(eight);
  delay(1000);
  printByte(s);
  delay(1000);
  printByte(dot);
  delay(1000);
  printByte(c);
  delay(1000);
  printByte(o);
  delay(1000);
  printByte(m);
  delay(1000);
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

