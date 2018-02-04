/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __TIMER16_H__
#define __TIMER16_H__

#include <inttypes.h>
#include "Timer.h"

class Timer16 : public Timer<uint16_t>
{
//variables
	public:
		static const uint8_t CO_FAST_PWM_OC1A = 0x80;
		static const uint8_t WG_FAST_PWM_10BIT = 0x0b;
		static const uint8_t WG_FAST_PWM_9BIT = 0x0a;
		static const uint8_t CS_1024PR = 0x05;
		static const uint8_t CS_1PR = 0x01;
//functions
	public:		
		Timer16();
		~Timer16();
		Timer16(uint8_t mode);

		void setCompareOutputMode(uint8_t mode);
		uint8_t getCompareOutputMode(void);
		void setWaveformGenerationMode(uint8_t mode);
		uint8_t getWaveformGenerationMode(void);
		void setClockSelection(uint8_t mode);
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
