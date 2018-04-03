//=========================================================   
//===                  PID_CONTROLLER                   ===
//=========================================================
//串级PID: 主调：角度
//         副调：速度
//先控制角度，后控制速度  constrain(Speed, 0, 255)
//=========================================================
int Pwm_out = 0;
int Turn_Need = 0;
int Speed_Need = 0;
int speed_output_R , speed_output_L;
float speeds , speeds_filter, positions;
float diff_speeds,diff_speeds_all;
//========================
float Kap = 24.5;       //
float Kad = 10;         //
float Ksp = 2.8;        //
float Ksi = 0.11;       //
//========================
void PID_PWM()
{ 
  speeds=(count_left + count_right)*0.5;

  diff_speeds = count_left - count_right;
  diff_speeds_all += diff_speeds;
  
  speeds_filter *=0.85;  //一阶互补滤波
  speeds_filter +=speeds*0.15;
  
  positions += speeds_filter;
  positions += Speed_Need;
  positions = constrain(positions, -2300, 2300);//抗积分饱和 
  
  Pwm_out = Kap*Angle[0] + Kad*w[0] + Ksp*speeds_filter + Ksi*positions ;  //PID控制器
  if(Turn_Need == 0)
  {
    speed_output_R = int(Pwm_out - diff_speeds_all);
    speed_output_L = int(Pwm_out + diff_speeds_all);
  }
  speed_output_R = int(Pwm_out + Turn_Need);
  speed_output_L = int(Pwm_out - Turn_Need);
  Motor(speed_output_L , speed_output_R);
  count_left = 0;
  count_right = 0;

//  Serial.print(Angle[0]);      //主调被调量
//  Serial.print(',');
//  Serial.print(speeds_filter);//副调被调量
//  Serial.print(',');
//  Serial.println(Pwm_out);  //输出量
}

