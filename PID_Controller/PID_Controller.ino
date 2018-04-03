float Kp = 0.5, Ki = 0.5, Kd = 0.5 ;
float Pout, Iout, Dout, Output ;
float now, lasttime = 0, timechange;
float Input, lastinput, Setpoint = 127.0;
float error, errorsum = 0, Derror;
int settime = 1000;
void setup() {
  Serial.begin(9600);
}


void loop () {
  now = millis(); //得到当前毫秒值

  timechange = (now - lasttime); //计算差异
  if ( timechange >= settime) { //当时间到达设定值时运行
    Input = (analogRead(0) / 4.0); //读取工nput值并规范化输出
    error = Setpoint - Input; //计算误差
    errorsum = errorsum + error ;//将当前误差加到运行总误差
    Derror = (Input - lastinput); //计算输入斜率
    Pout = Kp * error; //计算PID增益
    Iout = Ki * errorsum;
    Dout = Kd * Derror;
    if (Iout > 255) //检查积分是否饱和并纠正
      Iout = 255 ;
    if (Iout < 0)
      Iout = 0;
    Output = Pout + Iout + Dout; //定义输出变量
    if ( Output > 255) //输出的完整性检查,使其保持在输出变量范围内
      Output = 255;
    if ( Output < 0)
      Output = 0;
    lastinput = Input; //保存输入及时间留作下次循环之用
    lasttime = now;
    analogWrite(3, Output);//将输出写至pWM引脚3
    Serial.print( Setpoint);//将一些信息输出至串行监控器
    Serial.print (" : ");
    Serial.print (Input);
    Serial.print (" : ");
    Serial.println (Output);
  }
}

