/***************************************************************

Name:		Gizwits + ArduinoUnoWiFi library 
Author:		bing@arduino.org.cn
Version:	V03030000
Init:		2016-09-06
Modify:		2017-08-01

****************************************************************/

#ifndef _GIZWITS_H
#define _GIZWITS_H

extern "C"
{
  #include "gizwits_product.h"
}

extern dataPoint_t currentDataPoint;
extern wifiStatueFlags_t wifiStatueFlags;

/*  Gizwits class */
class Gizwits
{
public:

	Gizwits();
	~Gizwits();

	void begin(void);
	void process(void);

	void read(EVENT_TYPE_T eventType, bool* value);
	void read(EVENT_TYPE_T eventType, uint32_t* value);
	void read(EVENT_TYPE_T eventType, int32_t* value);
	void read(EVENT_TYPE_T eventType, float* value);
	void readBinary(EVENT_TYPE_T eventType, uint8_t* data);
	
	void write(VALUE_TYPE_T valueType, bool value);
	void write(VALUE_TYPE_T valueType, uint32_t value);
	void write(VALUE_TYPE_T valueType, int32_t value);
	void write(VALUE_TYPE_T valueType, float value);
	void writeBinary(VALUE_TYPE_T valueType, uint8_t* data,uint32_t dataLen);
	
	bool hasBeenSet(EVENT_TYPE_T eventType);
	bool wifiHasBeenSet(EVENT_TYPE_T eventType);
	void setBindMode(uint8_t mode);

};

#endif