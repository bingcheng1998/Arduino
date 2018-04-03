
#include <Servo.h>
#include "Adafruit_PWMServoDriver.h"
#include <math.h>
#include <ArduinoSTL.h>
#include <queue>

#define max(a, b) (((a)>(b))?(a):(b))
#define min(a, b) (((a)<(b))?(a):(b))

class MyServo
{
public:
    struct MyServoTask
    {
        MyServo *servo;
        int delay_time;
        int pulse;
    };
    
    static Adafruit_PWMServoDriver pwmServoDriver;

    static void setup();

    static void loop();
    
    static std::queue<MyServoTask> taskQueue;

    static int taskQueueDelay;
    
    MyServo(uint8_t num);

    /**
     *
     * @param minPulse
     * @param maxPulse
     * @param initialPulse
     */
    void init(uint16_t minPulse, uint16_t maxPulse, uint16_t initialPulse);

    void setPulse(uint16_t pulse, int delay_time=2);

    void addTaskPulse(uint16_t pulse, int delay_time=2);

    static void clearTask();

    static bool isTaskEmpty();
     
    void change(int16_t a);

private:

    // 舵机驱动板上的编号
    uint8_t m_num;
    // 最小/最大范围
    uint16_t m_minPulse, m_maxPulse;
    // 当前值
    uint16_t m_currentPulse;
};

