/* 
* HighSuply.h
*
* Created: 08.02.2018 16:39:54
* Author: a.tarletskiy
*/


#ifndef __HIGHSUPLY_H__
#define __HIGHSUPLY_H__
#include <inttypes.h>
#include "PulseWidthModulation.h"
#include "AnalogToDigital.h"

class HighSuply
{
//variables
public:
protected:
private:
	static const uint16_t MAX_HV = 450;
	AnalogToDigital * adc;
	PulseWidthModulation16 * pwm;
	uint8_t adcChannel;
	uint16_t targetVoltage;
	uint16_t gate;
	static const uint8_t VOLTAGE_NUMERATOR = 1;
	static const uint8_t VOLTAGE_DENOMINATOR = 2;
	static const uint8_t TIMEOUT_GATE = 10;
	
//functions
public:
	HighSuply();
	HighSuply(PulseWidthModulation16 * pwm, AnalogToDigital * adc, uint8_t adcChannel);
	~HighSuply();
	uint16_t getVoltage();
	bool fastHsAdjust(void);
	bool setVoltage(uint16_t HV, uint16_t gate, uint16_t delay);
	void setTargetVoltage(uint16_t val);
	uint16_t getTargetVoltage(void);
	void setGate(uint16_t val);
	uint16_t getGate(void);
protected:
private:
	HighSuply( const HighSuply &c );
	HighSuply& operator=( const HighSuply &c );

}; //HighSuply

#endif //__HIGHSUPLY_H__
