
const int dir1PinA = 3;
const int dir2PinA = 5;
const int StartPin = 7;
const int delaytime = 2000;
unsigned long AA;
unsigned long BB;
unsigned long CC;

void setup() {
  Serial.begin(9600);
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(StartPin, INPUT);
  AA=millis();
}

void loop() {
  int i;
  BB=millis();
  CC=BB-AA;
  if (IfStart() != 1|| CC>140000) {
    
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      i++;
   Serial.println(i);
   delay(10000);
   
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, LOW);
   while(1);
  };
}

int IfStart() {
  return digitalRead(StartPin);
}

