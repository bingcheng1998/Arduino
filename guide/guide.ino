//设置控制各段的数字IO 脚
int a = 7; //定义数字接口7 连接a 段数码管
int b = 6; // 定义数字接口6 连接b 段数码管
int c = 5; // 定义数字接口5 连接c 段数码管
int d = 11; // 定义数字接口11 连接d 段数码管
int e = 10; // 定义数字接口10 连接e 段数码管
int f = 8; // 定义数字接口8 连接f 段数码管
int g = 9; // 定义数字接口9 连接g 段数码管
int dp = 4; // 定义数字接口4 连接dp 段数码管
void digital_1(void) //显示数字1
{
  unsigned char j;
  digitalWrite(c, HIGH); //给数字接口5 引脚高电平，点亮c 段
  digitalWrite(b, HIGH); //点亮b 段
  for (j = 7; j <= 11; j++) //熄灭其余段
    digitalWrite(j, LOW);
  digitalWrite(dp, LOW); //熄灭小数点DP 段
}
void digital_2(void) //显示数字2
{
  unsigned char j;
  digitalWrite(b, HIGH);
  digitalWrite(a, HIGH);
  for (j = 9; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(c, LOW);
  digitalWrite(f, LOW);
}
void digital_3(void) //显示数字3
{
  unsigned char j;
  digitalWrite(g, HIGH);
  digitalWrite(d, HIGH);
  for (j = 5; j <= 7; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(f, LOW);
  digitalWrite(e, LOW);
}
void digital_4(void) //显示数字4
{
  digitalWrite(c, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(a, LOW);
  digitalWrite(e, LOW);
  digitalWrite(d, LOW);
}
void digital_5(void) //显示数字5
{
  unsigned char j;
  for (j = 7; j <= 9; j++)
    digitalWrite(j, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(b, LOW);
  digitalWrite(e, LOW);
}
void digital_6(void) //显示数字6
{
  unsigned char j;
  for (j = 7; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(dp, LOW);
  digitalWrite(b, LOW);
}
void digital_7(void) //显示数字7
{
  unsigned char j;
  for (j = 5; j <= 7; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
  for (j = 8; j <= 11; j++)
    digitalWrite(j, LOW);
}
void digital_8(void) //显示数字8
{
  unsigned char j;
  for (j = 5; j <= 11; j++)
    digitalWrite(j, HIGH);
  digitalWrite(dp, LOW);
}
void setup()
{
  int i;//定义变量
  for (i = 4; i <= 11; i++)
    pinMode(i, OUTPUT); //设置4～11 引脚为输出模式
}
void loop()
{
  while (1)
  {
    digital_1();//显示数字1
    delay(2000);//延时2s
    digital_2();//显示数字2
    delay(1000); //延时1s
    digital_3();//显示数字3
    delay(1000); //延时1s
    digital_4();//显示数字4
    delay(1000); //延时1s
    digital_5();//显示数字5
    delay(1000); //延时1s
    digital_6();//显示数字6
    delay(1000); //延时1s
    digital_7();//显示数字7
    delay(1000); //延时1s
    digital_8();//显示数字8
    delay(1000); //延时1s
  }
}
