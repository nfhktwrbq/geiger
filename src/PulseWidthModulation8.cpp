#include <avr/io.h>
#include "PulseWidthModulation8.h"



PulseWidthModulation8::PulseWidthModulation8(Timer<uint8_t> * timer) : timer(timer)
{
	timer->getCompareOutputMode();
}


PulseWidthModulation8::~PulseWidthModulation8()
{
}

void PulseWidthModulation8::setTimer(Timer<uint8_t> * timer)
{
	PulseWidthModulation8::timer = timer;	
}

void PulseWidthModulation8::setPWM(uint8_t val)
{
	timer->setOutputCompareA(val);
}

uint8_t PulseWidthModulation8::getPWM(void)
{
	return timer->getOutputCompareA();
}

void PulseWidthModulation8::setMinPWMBorder(uint8_t border)
{
	minPWM = border;
}

void PulseWidthModulation8::setMaxPWMBorder(uint8_t border)
{
	maxPWM = border;
}

uint8_t PulseWidthModulation8::getMinPWMBorder(void)
{
	return minPWM;
}

uint8_t PulseWidthModulation8::getMaxPWMBorder(void)
{
	return maxPWM;
}
