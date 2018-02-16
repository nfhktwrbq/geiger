/* 
* HighSuply.cpp
*
* Created: 08.02.2018 16:39:54
* Author: a.tarletskiy
*/

#include <util/delay.h>
#include "HighSuply.h"

// default constructor
HighSuply::HighSuply()
{
} //HighSuply

HighSuply::HighSuply(PulseWidthModulation16 * pwm, AnalogToDigital * adc, uint8_t adcChannel) : adc(adc), pwm(pwm), adcChannel(adcChannel)
{
} //HighSuply

// default destructor
HighSuply::~HighSuply()
{
} //~HighSuply

uint16_t HighSuply::getVoltage()
{
	return adc->proc() * VOLTAGE_NUMERATOR / VOLTAGE_DENOMINATOR;
}

bool HighSuply::fastHsAdjust(void)
{
	if(targetVoltage > MAX_HV) return false;
	if((getVoltage() > (targetVoltage + gate)) && pwm->getPWM() > 0)
	{
		pwm->changeOn(-1);
		return true;
	}
	if((getVoltage() < (targetVoltage - gate)) && (pwm->getPWM() < pwm->getMaxPWMBorder()))
	{
		pwm->changeOn(1);
		return true;
	}
	return true;	
}

bool  HighSuply::setVoltage(uint16_t HV, uint16_t gate, uint16_t delay)
{
	uint16_t new_HV = 0;
	uint16_t prev_HV = 0;
	uint16_t timeout = 0;
	if(HV>MAX_HV) return false;
	new_HV = getVoltage();
	prev_HV = new_HV;
	while(new_HV < (HV - gate) || new_HV > (HV + gate))
	{
		timeout++;
		for(uint8_t i = 0; i < delay; i++)
		{
			_delay_ms(2);
		}
		new_HV = getVoltage();
		if(new_HV > (HV + gate))
		{
			if(pwm->getPWM() > 0)
			{
				if((new_HV - HV) > 100 && pwm->getPWM() > 7)
				{
					pwm->changeOn(-7);
					OCR1A -= 7;
				}
				else
				{
					pwm->changeOn(-1);
				}
			}
			if(timeout > 10)
			{
				if((new_HV + TIMEOUT_GATE) > prev_HV)
				{
					return false;
				}
				else
				{
					timeout = 0;
					prev_HV = new_HV;
				}
			}
		}
		if(new_HV<(HV-gate))
		{
			if(OCR1A < pwm->getMaxPWMBorder())
			{
				if((HV-new_HV) > 100 && OCR1A < pwm->getMaxPWMBorder() - 7)
				{
					pwm->changeOn(7);
				}
				else
				{
					pwm->changeOn(1);
				}
			}

			if(timeout > 10)
			{
				if((new_HV - TIMEOUT_GATE) < prev_HV)
				{
					return false;
				}
				else
				{
					timeout = 0;
					prev_HV = new_HV;
				}
			}
		}
	}	
	return true;
}

void HighSuply::setTargetVoltage(uint16_t val)
{
	targetVoltage = val;
}

uint16_t HighSuply::getTargetVoltage(void)
{
	return targetVoltage;
}

void HighSuply::setGate(uint16_t val)
{
	gate = val;
}

uint16_t HighSuply::getGate(void)
{
	return gate;
}


