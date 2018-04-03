#include <IRremote.h>

int RECV_PIN = 2; //define input pin on Arduino


IRrecv irrecv(RECV_PIN);
decode_results results;


void setup(){
    Serial.begin(9600);
    delay(1000);
    irrecv.enableIRIn(); 
}

void loop() {
  static int Now_Command;//这个是当前命令值

   if (irrecv.decode(&results)) {
      Serial.println(results.value);
      
      
      irrecv.resume(); // Receive the next value
   }
   
}

void Do_Command(int Command){
  
}

