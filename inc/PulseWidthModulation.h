/* 
* PulseWidthModulation.h
*
* Created: 06.02.2018 16:44:06
* Author: a.tarletskiy
*/


#ifndef __PULSEWIDTHMODULATION_H__
#define __PULSEWIDTHMODULATION_H__

#include "Timer.h"

template <class T, class U, typename CO, typename WG, typename CS>
class PulseWidthModulation
{
//variables
public:
protected:
private:
	T * timer;
//functions
public:
	PulseWidthModulation(T * timer) : timer(timer)
	{
		//maxPWM = 0xff;
		//minPWM = 0x00;
	} //PulseWidthModulation

	~PulseWidthModulation()
	{
	} //~PulseWidthModulation

	void initPWM(CO co, WG wg, CS cs)
	{
		timer->setCompareOutputMode(co);
		timer->setWaveformGenerationMode(wg);
		timer->setClockSelection(cs);
	}
	/*void PulseWidthModulation8::setTimer(Timer<uint8_t> * timer)
	{
		PulseWidthModulation8::timer = timer;
	}

	void PulseWidthModulation8::setPWM(uint8_t val)
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

#endif //__PULSEWIDTHMODULATION_H__
