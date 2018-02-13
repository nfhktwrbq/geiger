
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Counter.h"


Counter::Counter()
{
}

Counter::Counter(HighSuply * highSuply) : highSuply(highSuply)
{
	highSuply->setTargetVoltage(400);
	highSuply->setGate(5);
}

Counter::~Counter()
{
}

uint32_t Counter::getCountSpeed(void)
{
	return countSpeed;
}

void Counter::proc(void)
{
	procCounter();
	procHighSuply();
}

void Counter::procCounter(void)
{
	static uint32_t sTimer = 0;	
	
	if (timer - sTimer > SECOND)
	{
		sTimer = timer;
		countSpeed = counter;
		counter = 0;
	} 
}

void Counter::procHighSuply(void)
{
	static uint32_t sTimer = 0; 	

	if (timer - sTimer > HIGH_SUPLY_ADJUST_PERIOD)
	{
		sTimer = timer;
		highSuply->fastHsAdjust();
	} 
}

void Counter::initExternalInterrupts()
{
	SREG |= 0x80;
	DDRD &= 0x11111011;
	EICRA = 0x02;
	EIMSK = 0x01;
}

uint32_t Counter::getCounter(void)
{
	return counter;
}

void Counter::setCounter(uint32_t counter)
{
	this->counter = counter;
}

uint32_t Counter::getTimer(void)
{
	return timer;
}

void Counter::setTimer(uint32_t timer)
{
	this->timer = timer;
}

ISR (INT0_vect)
{
	counter.setCounter(counter.getCounter() + 1);
}

ISR (TIMER2_OVF_vect)
{
}

ISR (TIMER1_OVF_vect)
{
}

ISR (TIMER0_OVF_vect)
{
	counter.setTimer(counter.getTimer() + 1);
}

Counter counter;
