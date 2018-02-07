/* 
* PulseWidthModulation.h
*
* Created: 06.02.2018 16:44:06
* Author: a.tarletskiy
*/


#ifndef __PULSEWIDTHMODULATION_H__
#define __PULSEWIDTHMODULATION_H__

#include <string.h>
#include "Timer.h"

template <typename T>
class PulseWidthModulation
{
//variables
public:
protected:
private:
	T * timer;
	typename T::U_TYPE maxPWM;
	typename T::U_TYPE minPWM;
//functions
public:
	PulseWidthModulation(T * timer) : timer(timer)
	{
		memset(&maxPWM, 0xff, sizeof(typename T::U_TYPE));		
		minPWM = 0;
	} //PulseWidthModulation

	~PulseWidthModulation()
	{
	} //~PulseWidthModulation

	void initPWM(typename T::COMPARE_OUTPUT_TYPE co, typename T::WAVE_FORM_GENERATION_TYPE wg, typename T::CLOCK_SELECTION_TYPE cs)
	{
		timer->setCompareOutputMode(co);
		timer->setWaveformGenerationMode(wg);
		timer->setClockSelection(cs);
	}
	void setTimer(T * timer)
	{
		this->timer = timer;
	}
/*
	void setPWM(uint8_t val)
	{
		if(val > maxPWM || val < minPWM)
		{
			return;
		}
		
		if(channel)
		{
			timer->setOutputCompareA(val);
		}
		else
		{
			timer->setOutputCompareB(val);
		}
	}

	uint8_t PulseWidthModulation8::getPWM(void)
	{
		if(channel)
		{
			return timer->getOutputCompareA();
		}
		else
		{
			return timer->getOutputCompareB();
		}
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

	void PulseWidthModulation8::setPWMChannel(CHANNEL ch)
	{
		channel = ch;
	}
	*/
protected:
private:
	PulseWidthModulation( const PulseWidthModulation &c );
	PulseWidthModulation& operator=( const PulseWidthModulation &c );

}; //PulseWidthModulation

typedef PulseWidthModulation<Timer8> PulseWidthModulation8;
typedef PulseWidthModulation<Timer16> PulseWidthModulation16;

#endif //__PULSEWIDTHMODULATION_H__
