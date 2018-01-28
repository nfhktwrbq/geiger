/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __TIMER_H__
#define __TIMER_H__

#include <inttypes.h>

class Timer
{
//variables
//functions
	public:
		
		virtual void setCompareOutputMode(uint8_t mode) = 0;

		virtual void setWaveformGenerationMode(uint8_t mode) = 0;

		virtual void setClockSelection(uint8_t mode) = 0;
		
		virtual uint16_t getTimerCounter(void) = 0;

		virtual void setTimerCounter(uint16_t tc) = 0;

		virtual uint16_t getOutputCompareA(void) = 0;

		virtual void setOutputCompareA(uint16_t oc) = 0;

		virtual uint16_t getOutputCompareB(void) = 0;

		virtual void setOutputCompareB(uint16_t oc) = 0;

		virtual void enableInterrupt(bool en) = 0;

		virtual void setInterrupt(uint8_t mode) = 0;

		virtual void setInterruptFlag(uint8_t flag) = 0;

		virtual uint8_t getInterruptFlag(void) = 0;

}; //Timer

#endif //__TIMER_H__
