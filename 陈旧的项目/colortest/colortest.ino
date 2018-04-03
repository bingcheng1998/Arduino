#include <Adafruit_NeoPixel.h>

#define PIN 6
const int colorful = 5;
const int redBlink = 4;
const int greenBlink = 3;
const int blueBlink = 7;
int times=5;
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(colorful, LOW);
  pinMode(redBlink, LOW);
  pinMode(greenBlink, LOW);
  pinMode(blueBlink, LOW);
  
  Serial.println("\n");
  printStart();
  delay(1000);
}


int isColorful() {
  return digitalRead(colorful);
}
int isRedBlink() {
  return digitalRead(redBlink);
}
int isGreenBlink() {
  return digitalRead(greenBlink);
}
int isBlueBlink() {
  //Serial.print("digitalRead(blueBlink)\t");
  //Serial.println(digitalRead(blueBlink));
  return digitalRead(blueBlink);
  //delay(1000);
  //return 0;
}

void loop() {
  // Some example procedures showing how to display to the pixels:
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127,   0,   0), 50); // Red
  //heaterChase(strip.Color(  0,   0, 127), 50); // Blue

  //rainbow(5);
  
  if(isColorful() == 1){
    Serial.println("\nrainbow is on");
    rainbowCycle(4);
    //delay(1000);
    colorWipe(strip.Color(0, 0, 0), 1);
  }
  else if(isRedBlink() == 1){
    Serial.println("\nRedBlink is on");
    
    for(int i=0; i<times; i++){
      colorWipe(strip.Color(200, 0, 0), 50);
    //delay(1000);
    colorWipe(strip.Color(0, 0, 0), 1);
    }
  }
  else if(isGreenBlink() == 1){
    Serial.println("\nGreenBlink is on");
    for(int i=0; i<times; i++){
      colorWipe(strip.Color(0, 200, 0), 50);
      //delay(1000);
  colorWipe(strip.Color(0, 0, 0), 1);
    }
  }
  else if(isBlueBlink() == 1){
    Serial.println("\nBlueBlink is on");
    for(int i=0; i<times; i++){
      colorWipe(strip.Color(0, 0, 200), 50);
      //delay(1000);
  colorWipe(strip.Color(0, 0, 0), 1);
    }
    
  }
  else;
  
  //rainbowCycle(2);
  //theaterChaseRainbow(50);

    colorWipe(strip.Color(0, 0, 0), 1);

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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


void printStart() {
  Serial.println("\n------------- the color binker is trned on ------------");
  Serial.println("\tthe function was written by Hu Bingcheng ");
  Serial.println("\tversion 1.0");
  Serial.println("\tJuly, 17, 2017");
  Serial.println("---------- welcome to use the color binker ------------\n\n");
}
