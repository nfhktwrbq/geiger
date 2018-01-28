/* 
* GPIO.cpp
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/

#include <avr/io.h>
#include "Timer8_0.h"


// default constructor
Timer8_0::Timer8_0()
{
	TCCR0A = 0;
	TCCR0B = 0;
	OCR0A = 0;
	OCR0B = 0;
	TIMSK0 = 0;
	TIFR0 = 0;
} //GPIO

// default destructor
Timer8_0::~Timer8_0()
{
} //~GPIO

Timer8_0::Timer8_0(uint8_t mode)
{
	
} //GPIO

void Timer8_0::setCompareOutputMode(uint8_t mode)
{
	TCCR0A &= 0x0f;
	TCCR0A |= (mode & 0xf0);
}

void Timer8_0::setWaveformGenerationMode(uint8_t mode)
{
	TCCR0A &= 0xfc;
	TCCR0B &= 0xf7;
	TCCR0A |= (mode & 0x03);
	TCCR0B |= (mode & 0x08);	
}

void Timer8_0::setClockSelection(uint8_t mode)
{
	TCCR0B &= 0xf8;
	TCCR0B |= (mode & 0x07);	
}

void Timer8_0::setForceCapture(uint8_t mode)
{
	TCCR0B &= 0x3f;
	TCCR0B |= (mode & 0xc0);	
}

uint16_t Timer8_0::getTimerCounter(void)
{
	return (uint16_t)TCNT0;
}

void Timer8_0::setTimerCounter(uint16_t tc)
{
	TCNT0 = (uint8_t)tc;
}

uint16_t Timer8_0::getOutputCompareA(void)
{
	return (uint16_t)OCR0A;
}

void Timer8_0::setOutputCompareA(uint16_t oc)
{
	OCR0A = (uint8_t)oc;
}

uint16_t Timer8_0::getOutputCompareB(void)
{
	return (uint16_t)OCR0B;
}

void Timer8_0::setOutputCompareB(uint16_t oc)
{
	OCR0B = (uint8_t)oc;
}

void Timer8_0::enableInterrupt(bool en)
{
}

void Timer8_0::setInterrupt(uint8_t mode)
{
	TIMSK0 &= 0xf8;
	TIMSK0 |= (mode & 0x07);
}

void Timer8_0::setInterruptFlag(uint8_t flag)
{	
	TIFR0 = flag;
}

uint8_t Timer8_0::getInterruptFlag(void)
{
	return TIFR0;
}
