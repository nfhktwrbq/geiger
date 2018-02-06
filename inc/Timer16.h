/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __TIMER16_H__
#define __TIMER16_H__

#include <inttypes.h>
#include "global.h"
#include "Timer.h"

class Timer16 : public Timer<uint16_t, COMPARE_OUTPUT_16, WAVE_FORM_GENERATION_16, CLOCK_SELECTION_16>
{
//variables
	public:
	
//functions
	public:		
		Timer16();
		~Timer16();
		Timer16(uint8_t mode);

		void setCompareOutputMode(COMPARE_OUTPUT_16 mode);
		uint8_t getCompareOutputMode(void);
		void setWaveformGenerationMode(WAVE_FORM_GENERATION_16 mode);
		uint8_t getWaveformGenerationMode(void);
		void setClockSelection(CLOCK_SELECTION_16 mode);
		void setInputCaptureNoiseCanceler(uint8_t mode);
		void setCaptureEdge(uint8_t mode);
		void setForceCapture(uint8_t mode);
		uint16_t getTimerCounter(void);
		void setTimerCounter(uint16_t tc);
		uint16_t getOutputCompareA(void);
		void setOutputCompareA(uint16_t oc);
		uint16_t getOutputCompareB(void);
		void setOutputCompareB(uint16_t oc);
		uint16_t getInputCapture(void);
		void setInputCapture(uint16_t ic);
		void enableInterrupt(bool en);
		void setInterrupt(uint8_t mode);
		void setInterruptFlag(uint8_t flag);
		uint8_t getInterruptFlag(void);
	private:
		Timer16( const Timer16 &c );
		Timer16& operator=( const Timer16 &c );

}; //Timer

#endif //__TIMER_H__
