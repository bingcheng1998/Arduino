#include <Wire.h>
byte A[11];

void setup()
{
  Serial.begin(57600);
  Serial1.begin(57600);
  Serial.println("initial ...000");
  Serial1.println("initial ...111");
  Serial1.write(0xff);
  Serial1.write(0xaa);
  Serial1.write(0x52);
  Serial1.flush();
  Serial.println("end");
}

static int counter=0;
char buffer[20];
void loop()
{
  if(counter==0&&A[0]==0x55)
  {
    int index=2;
    switch(A[1])
    {
      case 0x53:
      {
        
        float xa=(A[index]|(A[index+1]<<8))/32768.0*180;
        float ya=(A[index+2]|(A[index+3]<<8))/32768.0*180;
        float za=(A[index+4]|(A[index+5]<<8))/32768.0*180;
        //if(abs(temp-97.77)<3) break;
        //sprintf(buffer,"%lf,",xa);
        Serial.print("x=");
        Serial.println(xa);
        //sprintf(buffer,"%lf,",ya);
        Serial.print("y=");
        Serial.println(ya);
        //sprintf(buffer,"%lf",za);
        Serial.print("z=");
        Serial.println(za);
        A[0]=0;
        delay(50);
      }
        break;
      default:
      break;
    }
  }
}

void serialEvent1()
{
  while(Serial1.available())
  {
    A[counter]=Serial1.read();
    if(counter==0&&A[counter]!=0x55) return;
    counter=(counter+1)%11;
  }
}
void serialEvent()
{
  char buf[255];
  int i=0;
  while(Serial.available()) buf[i++]=Serial.read();
  buf[i]=0;
  if(strcmp("stop",buf)==0) Serial1.end();
  else if(strcmp("run",buf)==0) Serial1.begin(115200);
}
