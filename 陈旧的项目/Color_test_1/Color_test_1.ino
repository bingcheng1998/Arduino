#include <TimerOne.h>
#define S0     3   // Please notice the Pin's define
#define S1     4
#define S2     5
#define S3     6
#define OUT    2

int redPin = 11;
int greenPin = 10;
int bluePin = 9;//11;

int   g_count = 0;    // count the frequecy
int   g_array[3];     // store the RGB value
int   g_flag = 0;     // filter of RGB queue
float g_SF[3];        // save the RGB Scale factor

// Init TSC230 and setting Frequency.
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  digitalWrite(S0, LOW);  // OUTPUT FREQUENCY SCALING 2%
  digitalWrite(S1, HIGH);
}

// Select the filter color
void TSC_FilterColor(int Level01, int Level02)
{
  if (Level01 != 0)
    Level01 = HIGH;

  if (Level02 != 0)
    Level02 = HIGH;

  digitalWrite(S2, Level01);
  digitalWrite(S3, Level02);
}

void TSC_Count()
{
  g_count ++ ;
}

void TSC_Callback()
{
  switch (g_flag)
  {
    case 0:
      TSC_WB(LOW, LOW);              //Filter without Red
      break;
    case 1:
      g_array[0] = g_count;
      TSC_WB(HIGH, HIGH);            //Filter without Green
      break;
    case 2:
      g_array[1] = g_count;
      TSC_WB(LOW, HIGH);             //Filter without Blue
      break;

    case 3:
      g_array[2] = g_count;
      TSC_WB(HIGH, LOW);             //Clear(no filter)
      break;
    default:
      g_count = 0;
      break;
  }
}

void TSC_WB(int Level0, int Level1)      //White Balance
{
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
  Timer1.setPeriod(1000000);             // set 1s period
}

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  TSC_Init();
  Serial.begin(9600);
  Timer1.initialize();             // defaulte is 1s
  Timer1.attachInterrupt(TSC_Callback);
  attachInterrupt(0, TSC_Count, RISING);

  delay(4000);

  for (int i = 0; i < 3; i++){

  g_SF[0] = 255.0 / g_array[0];    //R Scale factor
  g_SF[1] = 255.0 / g_array[1] ;   //G Scale factor
  g_SF[2] = 255.0 / g_array[2] ;   //B Scale factor
  };
}

void loop()
{
  g_flag = 0;
  int color[3]={0,0,0};
  Serial.print("[");
  noInterrupts();
  for (int i = 0; i < 2; i++) {
    color[i] =  int(g_array[i] * g_SF[i]);
    Serial.print(g_array[i] * g_SF[i]);
    Serial.print(",");
  }
  color[2] = int(g_array[2] * g_SF[2]);
  Serial.print(g_array[2] * g_SF[2]);
  Serial.println("]");
  
  colorRGB(color[0],  color[1], color[2]);
  delayMicroseconds(1000);
  interrupts();
  colorRGB(0,0,0);
  delay(4000);
}

void colorRGB(int red, int green, int blue) {
  analogWrite(redPin, constrain(red, 0, 255));
  analogWrite(greenPin, constrain(green, 0, 255));
  analogWrite(bluePin, constrain(blue, 0, 255));
}
