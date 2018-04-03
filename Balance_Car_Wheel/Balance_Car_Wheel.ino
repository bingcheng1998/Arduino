
const int Left1 = 6;
const int Left2 = 9; 
const int Right1 = 10; 
const int Right2 = 11;

const int cali=0;//偏差校准,使机器走直线。speed Right 减去以这个数,简单调节
const int per=0;//转弯时角度差量



void WheelSetup(){
  pinMode(Left1, OUTPUT);
  pinMode(Left2, OUTPUT);
  pinMode(Right1, OUTPUT);
  pinMode(Right2, OUTPUT);
}

void GoForward(int Speed){
  analogWrite(Left1, constrain(Speed, 0, 255));
  analogWrite(Left2, 0);
  analogWrite(Right1, constrain(Speed, 0, 255)-cali);
  analogWrite(Right2, 0);
}
void GoBack(int Speed){
  analogWrite(Left1, 0);
  analogWrite(Left2, constrain(Speed, 0, 255));
  analogWrite(Right1, 0);
  analogWrite(Right2, constrain(Speed, 0, 255)-cali);
}
void GoLeft(int Speed){
  analogWrite(Left1, constrain(Speed, 0, 255)-per);
  analogWrite(Left2, 0);
  analogWrite(Right1, constrain(Speed, 0, 255)-cali);
  analogWrite(Right2, 0);
}
void GoRight(int Speed){
  analogWrite(Left1, constrain(Speed, 0, 255));
  analogWrite(Left2, 0);
  analogWrite(Right1, constrain(Speed, 0, 255)-cali-per);
  analogWrite(Right2, 0);
}
void TurnLeft(int Speed){
  analogWrite(Left1, 0);
  analogWrite(Left2, constrain(Speed, 0, 255));
  analogWrite(Right1, constrain(Speed, 0, 255)-cali);
  analogWrite(Right2, 0);
}
void TurnRight(int Speed){
  analogWrite(Left1, constrain(Speed, 0, 255));
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, constrain(Speed, 0, 255)-cali);
}
void Stop(){
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
}

void PidWheel(float Angle, float AngleSpeed){
  
}

void setup() {
WheelSetup();
}

void loop() {
  int speed1 = 100;
GoForward(speed1);
delay(500);
GoBack(speed1);
delay(500);
GoRight(speed1);
delay(500);
TurnLeft(speed1);
delay(500);
//for(int i=0; i<255;i++){
//  GoForward(i);
//  delay(10);
//}
for(int i=0; i<255;i++){
  TurnLeft(i);
  delay(10);
}
for(int i=255; i>0;i--){
  TurnLeft(i);
  delay(10);
}
}
