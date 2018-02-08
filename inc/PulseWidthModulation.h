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
	typename T::COMPARE_OUTPUT_TYPE channel;
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
		channel = co;
	}
	void setTimer(T * timer)
	{
		this->timer = timer;
	}

	void setPWM(typename T::U_TYPE val)
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

	typename T::U_TYPE getPWM(void)
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

	void setMinPWMBorder(typename T::U_TYPE border)
	{
		minPWM = border;
	}

	void setMaxPWMBorder(typename T::U_TYPE border)
	{
		maxPWM = border;
	}

	typename T::U_TYPE getMinPWMBorder(void)
	{
		return minPWM;
	}

	typename T::U_TYPE getMaxPWMBorder(void)
	{
		return maxPWM;
	}

	void setPWMChannel(typename T::COMPARE_OUTPUT_TYPE ch)
	{
		channel = ch;
	}
	
	void changeOn(int8_t i = 1)
	{
		setPWM(getPWM()+i);
	}
	
	
	
protected:
private:
	PulseWidthModulation( const PulseWidthModulation &c );
	PulseWidthModulation& operator=( const PulseWidthModulation &c );

}; //PulseWidthModulation

typedef PulseWidthModulation<Timer8> PulseWidthModulation8;
typedef PulseWidthModulation<Timer16> PulseWidthModulation16;

#endif //__PULSEWIDTHMODULATION_H__
