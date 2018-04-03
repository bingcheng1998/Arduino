#include <TimerOne.h> //申明库文件
//把TCS3200颜色传感器各控制引脚连到Arduino数字端口
#define S0    3   //物体表面的反射光越强，TCS3002D内置振荡器产生的方波频率越高，
#define S1    4  //S0和S1的组合决定输出信号频率比例因子，比例因子为2%
//比率因子为TCS3200传感器OUT引脚输出信号频率与其内置振荡器频率之比
#define S2     5   //S2和S3的组合决定让红、绿、蓝，哪种光线通过滤波器
#define S3     6
#define OUT    2  //TCS3200颜色传感器输出信号连接到Arduino中断0引脚，并引发脉冲信号中断
//在中断函数中记录TCS3200输出信号的脉冲个数
#define LED    7  //控制TCS3200颜色传感器是否点亮LED灯
float g_SF[3];     //从TCS3200输出信号的脉冲数转换为RGB标准值的RGB比例因子
volatile int g_count = 0;  // 计算与反射光强相对应TCS3200颜色传感器输出信号的脉冲数
// 数组用于存储在1s内TCS3200输出信号的脉冲数，它乘以RGB比例因子就是RGB标准值
int   g_array[3];
int   g_flag = 0;   // 滤波器模式选择顺序标志
int rr = 1;


int redPin = 11;
int greenPin = 10;
int bluePin = 9;//11;

// 初始化TSC3200各控制引脚的输入输出模式
//设置TCS3002D的内置振荡器方波频率与其输出信号频率的比例因子为2%
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
}

//选择滤波器模式，决定让红、绿、蓝，哪种光线通过滤波器
void TSC_FilterColor(int Level01, int Level02)
{
  if (Level01 != 0)
    Level01 = HIGH;
  if (Level02 != 0)
    Level02 = HIGH;
  digitalWrite(S2, Level01);
  digitalWrite(S3, Level02);
}

//中断函数，计算TCS3200输出信号的脉冲数
void TSC_Count()
{
  g_count ++ ;
}

//定时器中断函数，每1s中断后，把该时间内的红、绿、蓝三种光线通过滤波器时，
//TCS3200输出信号脉冲个数分别存储到数组g_array[3]的相应元素变量中
void TSC_Callback()
{
  switch (g_flag)
  {
    case 0:
      Serial.println("->WB Start");
      TSC_WB(LOW, LOW);   //选择让红色光线通过滤波器的模式
      break;
    case 1:
      Serial.print("->Frequency R=");
      Serial.println(g_count);   //打印1s内的红光通过滤波器时，TCS3200输出的脉冲个数
      g_array[0] = g_count;    //存储1s内的红光通过滤波器时，TCS3200输出的脉冲个数
      TSC_WB(HIGH, HIGH);  //选择让绿色光线通过滤波器的模式
      break;
    case 2:
      Serial.print("->Frequency G=");
      Serial.println(g_count);   //打印1s内的绿光通过滤波器时，TCS3200输出的脉冲个数
      g_array[1] = g_count;    //存储1s内的绿光通过滤波器时，TCS3200输出的脉冲个数
      TSC_WB(LOW, HIGH);  //选择让蓝色光线通过滤波器的模式
      break;

    case 3:
      Serial.print("->Frequency B=");
      Serial.println(g_count);   //打印1s内的蓝光通过滤波器时，TCS3200输出的脉冲个数
      Serial.println("->WB End");
      g_array[2] = g_count;     //存储1s内的蓝光通过滤波器时，TCS3200输出的脉冲个数
      TSC_WB(HIGH, LOW);   //选择无滤波器的模式
      break;
    case 4:
    noInterrupts();
      colorRGB(constrain(int(g_array[0] * g_SF[0]), 0, 255), constrain(int(g_array[1] * g_SF[1]), 0, 255), constrain(int(g_array[2] * g_SF[2]), 0, 255));
      Timer1.setPeriod(1000000 / rr);   //设置输出信号脉冲计数时长0.1s
      interrupts();
      break;
    default:
      g_count = 0;     //计数值清零
      g_flag = 0;
      break;
  }
}
//设置反射光中红、绿、蓝三色光分别通过滤波器时如何处理数据的标志
//该函数被TSC_Callback( )调用
void TSC_WB(int Level0, int Level1)
{
  g_count = 0;   //计数值清零
  g_flag ++;     //输出信号计数标志
  TSC_FilterColor(Level0, Level1); //滤波器模式
  Timer1.setPeriod(1000000 / rr);   //设置输出信号脉冲计数时长0.1s
  //delay(1000/rr);
}
//初始化
void setup()
{

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);


  TSC_Init();
  Serial.begin(9600); //启动串行通信
  Timer1.initialize(1000000 / rr); // defaulte is 1s
  Timer1.attachInterrupt(TSC_Callback); //设置定时器1的中断，中断调用函数为TSC_Callback()
  //设置TCS3200输出信号的上跳沿触发中断，中断调用函数为TSC_Count()
  attachInterrupt(0, TSC_Count, RISING);//0在UNO上代表D2
  //digitalWrite(LED, HIGH);//点亮LED灯
  TSC_Callback();
  delay(5000 / rr); //延时0.4s，以等待被测物体红、绿、蓝三色在1s内的TCS3200输出信号脉冲计数
  //noInterrupts();
  //Timer1.stop();
  //通过白平衡测试，计算得到白色物体RGB值255与1s内三色光脉冲数的RGB比例因子
  g_SF[0] = 255.0 / g_array[0];    //红色光比例因子
  g_SF[1] = 255.0 / g_array[1] ;   //绿色光比例因子
  g_SF[2] = 255.0 / g_array[2] ;   //蓝色光比例因子
  //打印白平衡后的红、绿、蓝三色的RGB比例因子
  Serial.println(g_SF[0], 5);
  Serial.println(g_SF[1], 5);
  Serial.println(g_SF[2], 5);
  //红、绿、蓝三色光分别对应的1s内TCS3200输出脉冲数乘以相应的比例因子就是RGB标准值
  //打印被测物体的RGB值
  for (int i = 0; i < 3; i++) {
    Serial.print(constrain(int(g_array[i] * g_SF[i]), 0, 255));
    Serial.print(",");
  };
  Serial.println();
}
//主程序
void loop()
{
  g_flag = 0;
  //每获得一次被测物体RGB颜色值需时0.4s
  //interrupts();
  //Timer1.resume();
  TSC_Callback();
  delay(5000 / rr);
  //noInterrupts();
  //Timer1.stop();
  //Timer1.detachInterrupt();
  //打印出被测物体RGB颜色值
  for (int i = 0; i < 3; i++) {
    Serial.print(constrain(int(g_array[i] * g_SF[i]), 0, 255));
    Serial.print(",");
  };
  //colorRGB(constrain(int(g_array[0] * g_SF[0]),0,255),constrain(int(g_array[1] * g_SF[1]),0,255),constrain(int(g_array[2] * g_SF[2]),0,255));
  //delay(1000);
  Serial.println();
  //Timer1.resume();
  //Timer1.attachInterrupt(TSC_Callback);
}

void colorRGB(int red, int green, int blue) {
  analogWrite(redPin, constrain(red, 0, 255));
  analogWrite(greenPin, constrain(green, 0, 255));
  analogWrite(bluePin, constrain(blue, 0, 255));
}
