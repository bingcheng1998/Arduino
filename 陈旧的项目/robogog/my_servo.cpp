
//
// Created by zyf on 2017/3/18.
//

#include "my_servo.h"
#include"Arduino.h"

Adafruit_PWMServoDriver MyServo::pwmServoDriver = Adafruit_PWMServoDriver(0x40);

std::queue<MyServo::MyServoTask> MyServo::taskQueue = std::queue<MyServo::MyServoTask>();

enum SERVO_NAME{
    R_F_1, R_F_2, R_B_1, R_B_2, L_F_1, L_F_2, L_B_1, L_B_2, net, head, kidneyX, kidneyY, tail
};
MyServo servo[13] = {MyServo(1), MyServo(2), MyServo(3), MyServo(4), MyServo(5),MyServo(6),
MyServo(7),MyServo(8),MyServo(9),MyServo(10),MyServo(11),MyServo(12),MyServo(13),};

int MyServo::taskQueueDelay = 0;

void MyServo::setup()
{
  pwmServoDriver.begin();
  pwmServoDriver.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  servo[R_F_1].init(240, 428, 300);//(最小值,最大值,初始值)
  servo[R_F_2].init(150, 550, 260);//530...150
  servo[R_B_1].init(170, 566, 222);//226...182
  servo[R_B_2].init(136, 600, 580);//550'''294
  servo[L_F_1].init(150, 260, 260);
  servo[L_F_2].init(150, 260, 260);
  servo[L_B_1].init(150, 260, 260);
  servo[L_B_2].init(150, 260, 260);
  servo[net].init(150, 260, 260);
  servo[head].init(150, 260, 260);
  servo[kidneyX].init(150, 260, 260);
  servo[kidneyY].init(150, 260, 260);
  servo[tail].init(150, 260, 260);
}

void MyServo::loop()
{
    if (taskQueue.empty()) return;
    if (taskQueueDelay > 0)
    {
        taskQueueDelay--;
        return;
    }
    auto task = taskQueue.front();
    taskQueue.pop();
    //std::cout<<task.pulse<<"\t"<<task.delay_time<<std::endl;
    task.servo->setPulse(task.pulse, task.delay_time);
    taskQueueDelay = 2;
}

MyServo::MyServo(uint8_t num)
{
    m_num = num;
}

void MyServo::init(uint16_t minPulse, uint16_t maxPulse, uint16_t initialPulse)
{
    m_minPulse = minPulse;
    m_maxPulse = maxPulse;
    m_currentPulse = initialPulse;
    pwmServoDriver.setPWM(m_num, 0, m_currentPulse);
}

void MyServo::setPulse(uint16_t pulse, int delay_time=2)
{
    if (pulse > m_currentPulse)
    {
        for (; m_currentPulse < min(m_maxPulse, pulse); m_currentPulse++){
            pwmServoDriver.setPWM(m_num, 0, m_currentPulse);
            delay(delay_time);
        }
    }
    else
        for (; m_currentPulse > max(m_minPulse, pulse); m_currentPulse--){
            pwmServoDriver.setPWM(m_num, 0, m_currentPulse);
            delay(delay_time);
        }
    //Serial.println(m_num);
    //Serial.println(m_currentPulse);
}

void MyServo::addTaskPulse(uint16_t pulse, int delay_time)
{
    MyServoTask task;
    task.servo = this;
    task.pulse = pulse;
    task.delay_time = delay_time;
    taskQueue.push(task);
    //std::cout<<m_num<<"\t"<<pulse<<"\t"<<delay_time<<std::endl;
}

void MyServo::clearTask()
{
    taskQueue = std::queue<MyServoTask>();
}

bool MyServo::isTaskEmpty()
{
    return taskQueue.empty();
}

void MyServo::change(int16_t a)
{
    setPulse(m_currentPulse + a);
}

