#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <avr/interrupt.h>
#include <inttypes.h>
#include "HighSuply.h"
#include "Buzzer.h"
#include "Timer.h"
#include "GPIO.h"
#include "MT10S.h"
#include "LiquidMenu.h"

ISR(INT0_vect);
ISR(TIMER2_OVF_vect);
ISR(TIMER1_OVF_vect);
ISR(TIMER0_OVF_vect);

class Counter
{
	public:
		static const uint32_t SECOND = F_CPU / 512;
	private:
		uint32_t countSpeed;
		static const uint32_t HIGH_SUPLY_ADJUST_PERIOD = SECOND * 10;
		volatile uint32_t timer = 0;
		volatile uint32_t counter = 0;
		HighSuply * highSuply;
		Buzzer * buzzer;	
		bool enableAdjust;	
		//lcd.init();
		
	public:
		Counter();
		Counter(HighSuply * highSuply, Buzzer * buzzer);
		~Counter();
		
		void init(void);
		bool initHighVoltage(void);
		void proc(void);
		uint32_t getCounter(void);
		void setCounter(uint32_t);
		uint32_t getTimer(void);
		void setTimer(uint32_t);
		uint32_t getCountSpeed(void);
		void setBuzzer(Buzzer * buzzer);
		void enableHighVoltageAdjust(bool en);
	private:
		
		void procCounter(void);
		void procHighSuply(void);
		void initExternalInterrupts(void);
		void interruptHandlerINT0(void);
		void interruptHandlerTIMER2_Overflow(void);
		void interruptHandlerTIMER1_Overflow(void);
		void interruptHandlerTIMER0_Overflow(void);


		
		friend void INT0_vect(void);
		friend void TIMER2_OVF_vect(void);
		friend void TIMER1_OVF_vect(void);
		friend void TIMER0_OVF_vect(void);
};

extern Counter * counter;

#endif