/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
int value0, value1, value2;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
//  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:

  if(sensorValue0!=0 && sensorValue0!=1023){
    value0 = sensorValue0;
  };
  if(sensorValue1!=0 && sensorValue1!=1023){
    value1 = sensorValue1;
  };
  if(sensorValue2!=0 && sensorValue2!=1023){
    value2 = sensorValue2;
  }
  
//  Serial.print(value0);
//  Serial.print("\t");
//  Serial.print(value1);
//  Serial.print("\t");
  Serial.println(value2);
}
