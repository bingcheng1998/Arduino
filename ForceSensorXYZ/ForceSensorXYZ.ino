#include <HX711_ADC.h>

//HX711 constructor (dout pin, sck pin)
HX711_ADC LoadCell(4, 5);
HX711_ADC LoadCell1(6,7);
HX711_ADC LoadCell2(8,9);

long t;
 int times;

void setup() {
  Serial.begin(9600);
  LoadCell.begin();
  long stabilisingtime = 2000; // 自动拟合采样时间
  LoadCell.start(stabilisingtime);
  LoadCell.setCalFactor(696.0); 
  LoadCell1.begin();
  LoadCell1.start(stabilisingtime);
  LoadCell1.setCalFactor(696.0); 
  LoadCell2.begin();
  LoadCell2.start(stabilisingtime);
  LoadCell2.setCalFactor(696.0); 
 t = millis();

}

void loop() {
  //update() should be called at least as often as HX711 sample rate; >10Hz@10SPS, >80Hz@80SPS
  //longer delay in scetch will reduce effective sample rate (be carefull with delay() in loop)
  LoadCell.update();
   LoadCell1.update();
   LoadCell2.update();

  //get smoothed value from data set + current calibration factor
  if (millis()-t<1000) {
    float i = LoadCell.getData();
     float j  = LoadCell1.getData();
      float k  = LoadCell2.getData();
    Serial.print(10010.1); //发送报头, 防止错误
    Serial.print("\t");
    Serial.print(-i);
    Serial.print("\t");
    Serial.print(-j);
    Serial.print("\t");
    Serial.print(k);
    Serial.print("\t\n");
    times++;
    Serial.println(times);
  }
}
