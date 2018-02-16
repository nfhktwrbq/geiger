/* 
* AnalogToDigital.cpp
*
* Created: 26.01.2018 16:35:22
* Author: a.tarletskiy
*/

#include <avr/io.h>
#include "AnalogToDigital.h"

// default constructor
AnalogToDigital::AnalogToDigital()
{
} //AnalogToDigital

// default destructor
AnalogToDigital::~AnalogToDigital()
{
} //~AnalogToDigital

AnalogToDigital::AnalogToDigital(REFERENCE ref, uint8_t adj, PRESCALER prescaler)
{	
	ADMUX = 0;
	ADMUX |= (0xe0 & ref) | (0x10 & adj);
	ADCSRA = 0;
	ADCSRA |= 0x80 | (0x03 & prescaler);
	ADCSRB = 0;
}

void AnalogToDigital::startConversion(void)
{
	ADCSRA |= 0x40;
}

uint16_t AnalogToDigital::proc(void)
{
	startConversion();
	return ADC;
}

void AnalogToDigital::setChannel(CHANNEL ch)
{
	ADMUX &= 0xf0;
	ADMUX |= (0x0f & ch);
	if(ch <= 7)
	{
		DIDR0 = 0;
		DIDR0 |= (1 << ch);
	}
}

void AnalogToDigital::adcEnable(bool en)
{
	if(en)
	{
		ADCSRA |= 0x80;
	}
	else
	{
		ADCSRA &= 0x7f;
	}
}

void AnalogToDigital::setPrescale(PRESCALER pr)
{
	ADCSRA &= 0x7c;
	ADCSRA |= 0x80 | (0x03 & pr);
}
