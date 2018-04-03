
#include <SoftwareSerial.h> 
/*
 * #在框中输入AT命令测试

AT+ORGL                          恢复出厂设置

AT+NAME=XXX                修改蓝牙模块名称为XXX
AT+ROLE=0                     蓝牙模式为从模式
AT+CMODE=1                 蓝牙连接模式为任意地址连接模式，也就是说该模块可以被任意蓝牙设备连接
AT+PSWD=1234             蓝牙配对密码为1234
AT+UART=9600,0,0        蓝牙通信串口波特率为9600，停止位1位，无校验位
 * 
 * 
 */
SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
pinMode(9, OUTPUT); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
digitalWrite(9, HIGH);
Serial.begin(38400);
Serial.println("Enter AT commands:");
BTSerial.begin(38400); // HC-05 default speed in AT command more
delay(200);
BTSerial.write("AT");
}

void loop()
{

// Keep reading from HC-05 and send to Arduino Serial Monitor
if (BTSerial.available())
Serial.write(BTSerial.read());

// Keep reading from Arduino Serial Monitor and send to HC-05
if (Serial.available())
BTSerial.write(Serial.read());
}

