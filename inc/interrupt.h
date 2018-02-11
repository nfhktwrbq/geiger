
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <avr/interrupt.h>
#include "global.h"

static volatile uint32_t sTimer = 0;
static volatile uint32_t sCounter = 0;

void initExternalInterrupts()
{
	SREG |= 0x80;
	DDRD &= 0x11111011;
	EICRA = 0x02;
	EIMSK = 0x01;
}

inline uint32_t times()
{
	return sTimer;
}

inline uint32_t counts()
{
	return sTimer;
}

ISR (INT0_vect)
{
    sCounter++;
}

ISR (TIMER2_OVF_vect)
{
}

ISR (TIMER1_OVF_vect)
{
}

ISR (TIMER0_OVF_vect)
{
	sTimer++;
}


#endif
