
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Counter.h"


Counter::Counter()
{
	enableAdjust = true;
}

Counter::Counter(HighSuply * highSuply, Buzzer * buzzer) : highSuply(highSuply), buzzer(buzzer)
{
	highSuply->setTargetVoltage(400);
	highSuply->setGate(5);
	enableAdjust = true;
}

Counter::~Counter()
{
}

void Counter::init(void)
{
	initExternalInterrupts();	
}

bool Counter::initHighVoltage(void)
{
	if(!highSuply->setVoltage( highSuply->getTargetVoltage(), 5, 250 ) )
	{
		enableHighVoltageAdjust(false);
		return false;
	}	
	return true;
}

uint32_t Counter::getCountSpeed(void)
{
	return countSpeed;
}

void Counter::proc(void)
{
	procCounter();
	if(enableAdjust)
	{
		procHighSuply();	
	}	
}

void Counter::procCounter(void)
{
	static uint32_t sTimer = 0;	
	static uint32_t sCounter = 0;
	
	if (timer - sTimer > SECOND)
	{
		sTimer = timer;
		countSpeed = counter - sCounter;
		sCounter = counter;
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
	
	DDRD &= 0b11111011;
	EICRA = 0x02;
	EIMSK = 0x01;
	SREG |= 0x80;
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

void Counter::setBuzzer(Buzzer * buzzer)
{
	this->buzzer = buzzer;
}

void Counter::enableHighVoltageAdjust(bool en)
{
	this->enableAdjust = en;
}

void Counter::interruptHandlerINT0(void)
{
	counter++;
	if(buzzer->isEnable())
	{
		buzzer->on();
	}		
}

void Counter::interruptHandlerTIMER2_Overflow(void)
{
	
}

void Counter::interruptHandlerTIMER1_Overflow(void)
{
	static uint8_t tmp = 0;
	this->timer++;
	if(buzzer->isOn())
	{
		if(tmp < Buzzer::TIME_ON)
		{
			tmp++;
		}
		else
		{
			buzzer->off();
		}
	}
}

void Counter::interruptHandlerTIMER0_Overflow(void)
{
	
}



ISR (INT0_vect)
{
	counter->interruptHandlerINT0();
}

ISR (TIMER2_OVF_vect)
{
	counter->interruptHandlerTIMER2_Overflow();
}

ISR (TIMER1_OVF_vect)
{
	counter->interruptHandlerTIMER1_Overflow();
}

ISR (TIMER0_OVF_vect)
{
	counter->interruptHandlerTIMER0_Overflow();
}

Counter * counter;
