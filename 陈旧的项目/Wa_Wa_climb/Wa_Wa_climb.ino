#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo PicDown;
Servo mouth;

unsigned long starttime;
    unsigned long stoptime;
    unsigned long looptime;
unsigned long AA;
unsigned long BB;
unsigned long CC;
int pos = 0;
int val = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("climb start");
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
  PicDown.attach(3);
  mouth.attach(8);
  pinMode(7, INPUT);
  pinMode(5, INPUT_PULLUP);
  PicDown.write(100);
  mouth.write(30); 
  AA=millis();
}

void loop() {
  BB=millis();
  CC=BB-AA;
  int Black = digitalRead(7);
  if (Black == HIGH || CC>350000) {
    digitalWrite(13, HIGH);
    Serial.println("drag is coming!");
    starttime=millis();
    ween(144, 30);
    delay(4000);
    digitalWrite(13, LOW);
  }
}

void ween(int a1, int a2) {
  int Pong = digitalRead(5);
  int t;
  while (Pong == 1) {
    Serial.println("wawa time");
    Serial.println(t);
    t++;
    next();
    if (a1 > a2) {
      for (pos = a2; pos <= a1; pos += 10) { // goes from 0 degrees to 180 degrees
        next();
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(100);                       // waits 15ms for the servo to reach the position
      };
      for (pos = a1; pos >= a2; pos -= 10) { // goes from 180 degrees to 0 degrees
        next();
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(100);                       // waits 15ms for the servo to reach the position
      };
    };
  };

}

int IsPulldown(){
  if (digitalRead(5) == 1) return 0;
  else return 0;
}


void next(){
  stoptime=millis();
  //Serial.println("get digitalRead(5)");
  //Serial.println(digitalRead(5));
  looptime = stoptime - starttime;
  if (digitalRead(5) == 0 || looptime>140000){


myservo.write(30);
delay(1000);
    
  HuaDown();
  MouthOpen();
  while(1);
  };
  
}

void HuaDown(){
  Serial.println("the picture is down");
  PicDown.write(0);
  delay(1300);
  PicDown.write(100);
  delay(1300);
}

void MouthOpen(){
  Serial.println("the mouth is going to open");
  for(int i=0; i<3; i++){
    for (pos = 30; pos <= 170; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    mouth.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 170; pos >= 30; pos -= 1) { // goes from 180 degrees to 0 degrees
    mouth.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  }
}

