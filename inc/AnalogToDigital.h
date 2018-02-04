/* 
* AnalogToDigital.h
*
* Created: 26.01.2018 16:35:22
* Author: a.tarletskiy
*/


#ifndef __ANALOGTODIGITAL_H__
#define __ANALOGTODIGITAL_H__

#include <inttypes.h>

class AnalogToDigital
{
//variables
public:
	enum REFERENCE
	{
		AREF = 0x00,
		AVCC = 0x40,
		REF_INTERNAL_1_1V = 0xC0,
	};

	enum CHANNEL
	{	
		CH_0 = 0x00,
		CH_1 = 0x01,
		CH_2 = 0x02,
		CH_3 = 0x03,
		CH_4 = 0x04,
		CH_5 = 0x05,
		CH_6 = 0x06,
		CH_7 = 0x07,
		CH_T = 0x08,
		CH_1_1V = 0x0e,
		CH_GND = 0x0f,
	};

	enum PRESCALER
	{
		PR_2 = 0x00,
		PR_4 = 0x02,
		PR_8 = 0x03,
		PR_16 = 0x04,
		PR_32 = 0x05,
		PR_64 = 0x06,
		PR_128 = 0x07,
	};

protected:
private:

//functions
public:
	AnalogToDigital();
	AnalogToDigital(REFERENCE ref, uint8_t adj, PRESCALER prescaler);
	~AnalogToDigital();
	
	void startConversion(void);	
	uint16_t proc(void);
	void setChannel(CHANNEL ch);
	void adcEnable(bool en);
	void setPrescale(PRESCALER pr);
protected:
private:
	AnalogToDigital( const AnalogToDigital &c );
	AnalogToDigital& operator=( const AnalogToDigital &c );

}; //AnalogToDigital

#endif //__ANALOGTODIGITAL_H__
