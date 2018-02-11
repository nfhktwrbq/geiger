#include "Counter.h"
#include "interrupt.h"

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
	static uint32_t timer = 0;
	static uint32_t prevCount = 0;
	
	if (times() - timer > SECOND)
	{
		timer = times();
		countSpeed = counts() - prevCount;
		prevCount = counts();
	} 
}

void Counter::procHighSuply(void)
{
	static uint32_t timer = 0; 	

	if (times() - timer > HIGH_SUPLY_ADJUST_PERIOD)
	{
		timer = times();
		highSuply->fastHsAdjust();
	} 
}