#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
unsigned long AA;
unsigned long BB;
unsigned long CC;
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(5, INPUT_PULLUP);
  AA=millis();
}

void loop() {
  BB=millis();
  CC=BB-AA;
  int sensorVal = digitalRead(5);
  if (sensorVal == HIGH && CC<120000) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
    ween(80,40);
    delay(4000);
    while(1);
  }
}

void ween(int a1, int a2){
  if(a1>a2){
  for (pos = a2; pos <= a1; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = a1; pos >= a2; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = a2; pos <= a1; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  }
}

