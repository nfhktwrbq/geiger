/* 
* GPIO.cpp
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/

#include <avr/io.h>
#include "Timer8_2.h"


// default constructor
Timer8_2::Timer8_2()
{
	TCCR2A = 0;
	TCCR2B = 0;
	OCR2A = 0;
	OCR2B = 0;
	TIMSK2 = 0;
	TIFR2 = 0;
} //GPIO

// default destructor
Timer8_2::~Timer8_2()
{
} //~GPIO

Timer8_2::Timer8_2(uint8_t mode)
{
	
} //GPIO

void Timer8_2::setCompareOutputMode(uint8_t mode)
{
	TCCR2A &= 0x0f;
	TCCR2A |= (mode & 0xf0);
}

uint8_t Timer8_2::getCompareOutputMode(void)
{
	return TCCR2A;
}

void Timer8_2::setWaveformGenerationMode(uint8_t mode)
{
	TCCR2A &= 0xfc;
	TCCR2B &= 0xf7;
	TCCR2A |= (mode & 0x03);
	TCCR2B |= (mode & 0x08);	
}

uint8_t Timer8_2::getWaveformGenerationMode(void)
{
	return 0;
}

void Timer8_2::setClockSelection(uint8_t mode)
{
	TCCR2B &= 0xf8;
	TCCR2B |= (mode & 0x07);	
}

void Timer8_2::setForceCapture(uint8_t mode)
{
	TCCR2B &= 0x3f;
	TCCR2B |= (mode & 0xc0);	
}

uint8_t Timer8_2::getTimerCounter(void)
{
	return TCNT2;
}

void Timer8_2::setTimerCounter(uint8_t tc)
{
	TCNT2 = tc;
}

uint8_t Timer8_2::getOutputCompareA(void)
{
	return OCR2A;
}

void Timer8_2::setOutputCompareA(uint8_t oc)
{
	OCR2A = oc;
}

uint8_t Timer8_2::getOutputCompareB(void)
{
	return OCR2B;
}

void Timer8_2::setOutputCompareB(uint8_t oc)
{
	OCR2B = oc;
}

void Timer8_2::enableInterrupt(bool en)
{
}

void Timer8_2::setInterrupt(uint8_t mode)
{
	TIMSK2 &= 0xf8;
	TIMSK2 |= (mode & 0x07);
}

void Timer8_2::setInterruptFlag(uint8_t flag)
{	
	TIFR2 = flag;
}

uint8_t Timer8_2::getInterruptFlag(void)
{
	return TIFR2;
}
