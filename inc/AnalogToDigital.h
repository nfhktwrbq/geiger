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
	static const uint8_t AREF = 0x00;
	static const uint8_t AVCC = 0x40;
	static const uint8_t REF_INTERNAL_1_1V = 0xC0;
	
	static const uint8_t CH_0 = 0x00;
	static const uint8_t CH_1 = 0x01;
	static const uint8_t CH_2 = 0x02;
	static const uint8_t CH_3 = 0x03;
	static const uint8_t CH_4 = 0x04;
	static const uint8_t CH_5 = 0x05;
	static const uint8_t CH_6 = 0x06;
	static const uint8_t CH_7 = 0x07;
	static const uint8_t CH_T = 0x08;
	static const uint8_t CH_1_1V = 0x0e;
	static const uint8_t CH_GND = 0x0f;
	
	static const uint8_t PR_2 = 0x00;
	static const uint8_t PR_4 = 0x02;
	static const uint8_t PR_8 = 0x03;
	static const uint8_t PR_16 = 0x04;
	static const uint8_t PR_32 = 0x05;
	static const uint8_t PR_64 = 0x06;
	static const uint8_t PR_128 = 0x07;
	
protected:
private:

//functions
public:
	AnalogToDigital();
	AnalogToDigital(uint8_t ref, uint8_t adj, uint8_t prescaler);
	~AnalogToDigital();
	
	void startConversion(void);	
	uint16_t proc(void);
	void setChannel(uint8_t ch);
	void adcEnable(bool en);
	void setPrescale(uint8_t pr);
protected:
private:
	AnalogToDigital( const AnalogToDigital &c );
	AnalogToDigital& operator=( const AnalogToDigital &c );

}; //AnalogToDigital

#endif //__ANALOGTODIGITAL_H__
