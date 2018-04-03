#include <IRremote.h>

#define left  16720605
#define right 16761405
#define up    16736925
#define down  16754775
#define OK 16712445
#define _1 16738455
#define _2 16750695
#define _3 16756815
#define _4 16724175
#define _5 16718055
#define _6 16743045
#define _7 16716015
#define _8 16726215
#define _9 16734885
#define _* 16728765
#define _0 16730805
#define _# 16732845

int RECV_PIN = A3; //define input pin on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  Serial.print(getIremote());

  if (getIremote() == left) {
    Serial.print("LEFT");
  }

}


unsigned long int getIremote() {
  unsigned long int recei = 0;

  for (int i = 0; i < 3; i++) {
    if (irrecv.decode(&results)) {
      //Serial.println(results.value);
      //Serial.println(results.value, HEX);//这是十六进制的编码显示
      unsigned long int recei0 = results.value;
      if (recei0 != 4294967295) {
        recei = results.value;
      }
      irrecv.resume(); // Receive the next value
      //Serial.print("\t\tThe results value is: ");
      //Serial.println(recei);
      return recei;
    }
  }
  delay(20);
  return 0;

}

