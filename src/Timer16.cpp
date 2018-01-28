/* 
* GPIO.cpp
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/

#include <avr/io.h>
#include "Timer16.h"


// default constructor
Timer16::Timer16()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1C = 0;
	ICR1 = 0;
	TIMSK1 = 0;
	TIFR1 = 0;
} //GPIO

// default destructor
Timer16::~Timer16()
{
} //~GPIO

Timer16::Timer16(uint8_t mode)
{
	
} //GPIO

void Timer16::setCompareOutputMode(uint8_t mode)
{
	TCCR1A &= 0x0f;
	TCCR1A |= (mode & 0xf0);
}

void Timer16::setWaveformGenerationMode(uint8_t mode)
{
	TCCR1A &= 0xfc;
	TCCR1B &= 0xe7;
	TCCR1A |= (mode & 0x03);
	TCCR1B |= (mode & 0x18);	
}

void Timer16::setClockSelection(uint8_t mode)
{
	TCCR1B &= 0xf8;
	TCCR1B |= (mode & 0x07);	
}

void Timer16::setInputCaptureNoiseCanceler(uint8_t mode)
{
	TCCR1B &= 0x7f;
	TCCR1B |= (mode & 0x80);	
}

void Timer16::setCaptureEdge(uint8_t mode)
{
	TCCR1B &= 0xbf;
	TCCR1B |= (mode & 0x40);	
}

void Timer16::setForceCapture(uint8_t mode)
{
	TCCR1C &= 0x3f;
	TCCR1C |= (mode & 0xc0);	
}

uint16_t Timer16::getTimerCounter(void)
{
	return TCNT1;
}

void Timer16::setTimerCounter(uint16_t tc)
{
	TCNT1 = tc;
}

uint16_t Timer16::getOutputCompareA(void)
{
	return OCR1A;
}

void Timer16::setOutputCompareA(uint16_t oc)
{
	OCR1A = oc;
}

uint16_t Timer16::getOutputCompareB(void)
{
	return OCR1B;
}

void Timer16::setOutputCompareB(uint16_t oc)
{
	OCR1B = oc;
}

uint16_t Timer16::getInputCapture(void)
{
	return ICR1;
}

void Timer16::setInputCapture(uint16_t ic)
{
	ICR1 = ic;
}

void Timer16::enableInterrupt(bool en)
{
	if(en)
	{
		TIMSK1 |= 0x20;
	}
	else
	{
		TIMSK1 &= 0xdf;
	}
}

void Timer16::setInterrupt(uint8_t mode)
{
	TIMSK1 &= 0xf8;
	TIMSK1 |= (mode & 0x07);
}

void Timer16::setInterruptFlag(uint8_t flag)
{	
	TIFR1 = flag;
}

uint8_t Timer16::getInterruptFlag(void)
{
	return TIFR1;
}
