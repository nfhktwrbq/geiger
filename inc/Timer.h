/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __TIMER_H__
#define __TIMER_H__

#include <inttypes.h>
template <typename T>
class Timer
{
//variables
//functions
	public:
		
		virtual void setCompareOutputMode(uint8_t mode) = 0;

		virtual uint8_t getCompareOutputMode(void) = 0;

		virtual void setWaveformGenerationMode(uint8_t mode) = 0;

		virtual uint8_t getWaveformGenerationMode(void) = 0;

		virtual void setClockSelection(uint8_t mode) = 0;
		
		virtual T getTimerCounter(void) = 0;

		virtual void setTimerCounter(T tc) = 0;

		virtual T getOutputCompareA(void) = 0;

		virtual void setOutputCompareA(T oc) = 0;

		virtual T getOutputCompareB(void) = 0;

		virtual void setOutputCompareB(T oc) = 0;

		virtual void enableInterrupt(bool en) = 0;

		virtual void setInterrupt(uint8_t mode) = 0;

		virtual void setInterruptFlag(uint8_t flag) = 0;

		virtual uint8_t getInterruptFlag(void) = 0;

}; //Timer

#endif //__TIMER_H__
