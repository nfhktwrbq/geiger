#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <avr/interrupt.h>
#include <inttypes.h>
#include "HighSuply.h"

ISR(INT0_vect);
ISR(TIMER2_OVF_vect);
ISR(TIMER1_OVF_vect);
ISR(TIMER0_OVF_vect);

class Counter
{
	private:
		uint32_t countSpeed;
		static const uint32_t SECOND = 62500;
		static const uint32_t HIGH_SUPLY_ADJUST_PERIOD = SECOND * 10;
		HighSuply * highSuply;
		volatile uint32_t timer = 0;
		volatile uint32_t counter = 0;
	public:
		Counter();
		Counter(HighSuply * highSuply);
		~Counter();
		
		
		void proc(void);
		uint32_t getCounter(void);
		void setCounter(uint32_t);
		uint32_t getTimer(void);
		void setTimer(uint32_t);
	private:
		uint32_t getCountSpeed(void);
		void procCounter(void);
		void procHighSuply(void);
		void initExternalInterrupts();
		
		friend void INT0_vect(void);
		friend void TIMER2_OVF_vect(void);
		friend void TIMER1_OVF_vect(void);
		friend void TIMER0_OVF_vect(void);
};

extern Counter counter;

#endif