#include "Arduino.h"

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
  analogWrite(Left1, Speed);
  analogWrite(Left2, 0);
  analogWrite(Right1, Speed-cali);
  analogWrite(Right2, 0);
}
void GoBack(int Speed){
  analogWrite(Left1, 0);
  analogWrite(Left2, Speed);
  analogWrite(Right1, 0);
  analogWrite(Right2, Speed-cali);
}
void GoLeft(int Speed){
  analogWrite(Left1, Speed-per);
  analogWrite(Left2, 0);
  analogWrite(Right1, Speed-cali);
  analogWrite(Right2, 0);
}
void GoRight(int Speed){
  analogWrite(Left1, Speed);
  analogWrite(Left2, 0);
  analogWrite(Right1, Speed-cali-per);
  analogWrite(Right2, 0);
}
void TurnLeft(int Speed){
  analogWrite(Left1, 0);
  analogWrite(Left2, Speed);
  analogWrite(Right1, Speed-cali);
  analogWrite(Right2, 0);
}
void TurnRight(int Speed){
  analogWrite(Left1, Speed);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, Speed-cali);
}
void Stop(){
  analogWrite(Left1, 0);
  analogWrite(Left2, 0);
  analogWrite(Right1, 0);
  analogWrite(Right2, 0);
}

