#include "Gesture.h"

void setup() {
  Serial.begin(9600);
  Serial.println();
  GestureSetup();
}

void loop() {
  
  // Read the proximity value
  if ( !apds.readProximity(proximity_data) ) {
    Serial.println("Error reading proximity value");
  } else {
    Serial.print("Proximity: ");
    Serial.println(proximity_data);
  }
  
  // Wait 250 ms before next reading
  delay(10);
}
