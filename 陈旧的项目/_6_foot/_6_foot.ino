
const int dir2PinA = 2;
const int dir1PinA = 4;
const int EndPin = 6;
const int startPin = 7;
int delaytime = 300;
unsigned long AA;
unsigned long BB;
unsigned long CC;

void setup() {
  Serial.begin(9600);
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(EndPin, INPUT);
  pinMode(startPin, INPUT_PULLUP);
  AA=millis();
}

void loop() {
  BB=millis();
  CC=BB-AA;
  int IfStart = digitalRead(startPin);
  if (IfStart == 0|| CC>100000) {//=0是低电平, 表示按钮按下
    delay(1000);
    while (digitalRead(EndPin) == 1) {
      Serial.println("not end");
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      delay(300);
    };
    Serial.println("!!!!!!!!!!end");
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
    delay(delaytime);
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, LOW);
    while (1);
  };
}

