/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __TIMER8_0_H__
#define __TIMER8_0_H__

#include <inttypes.h>
#include "global.h"
#include "Timer.h"

class Timer8_0 : public Timer<uint8_t, COMPARE_OUTPUT_8, WAVE_FORM_GENERATION_8, CLOCK_SELECTION_8>
{
//variables
	public:
		
//functions
	public:		
		Timer8_0();
		~Timer8_0();
		Timer8_0(uint8_t mode);

		void setCompareOutputMode(COMPARE_OUTPUT_8 mode);
		uint8_t getCompareOutputMode(void);
		void setWaveformGenerationMode(WAVE_FORM_GENERATION_8 mode);
		uint8_t getWaveformGenerationMode(void);
		void setClockSelection(CLOCK_SELECTION_8 mode);
		void setCaptureEdge(uint8_t mode);
		void setForceCapture(uint8_t mode);
		uint8_t getTimerCounter(void);
		void setTimerCounter(uint8_t tc);
		uint8_t getOutputCompareA(void);
		void setOutputCompareA(uint8_t oc);
		uint8_t getOutputCompareB(void);
		void setOutputCompareB(uint8_t oc);
		void enableInterrupt(bool en);
		void setInterrupt(uint8_t mode);
		void setInterruptFlag(uint8_t flag);
		uint8_t getInterruptFlag(void);
	private:
		Timer8_0( const Timer8_0 &c );
		Timer8_0& operator=( const Timer8_0 &c );

}; //Timer

#endif //__TIMER_H__
