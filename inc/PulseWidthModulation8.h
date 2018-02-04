/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __PULSE_WIDTH_MODULATION_H__
#define __PULSE_WIDTH_MODULATION_H__

#include <inttypes.h>
#include "Timer.h"

class PulseWidthModulation8
{
//variables
	private:
		Timer<uint8_t> * timer;
		uint8_t minPWM;
		uint8_t maxPWM;
		uint8_t channel;
//functions
	public:
		PulseWidthModulation8(Timer<uint8_t> * timer);
		~PulseWidthModulation8();
		void setTimer(Timer<uint8_t> * timer);
		void setPWM(uint8_t val);
		uint8_t getPWM(void);
		void setMinPWMBorder(uint8_t border);
		void setMaxPWMBorder(uint8_t border);
		uint8_t getMinPWMBorder(void);
		uint8_t getMaxPWMBorder(void);
	private:
		PulseWidthModulation8( const PulseWidthModulation8 &c );
		PulseWidthModulation8& operator=( const PulseWidthModulation8 &c );
		
}; //PULSE_WIDTH_MODULATION

#endif //__PULSE_WIDTH_MODULATION_H__
