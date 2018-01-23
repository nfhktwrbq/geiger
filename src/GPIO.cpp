/* 
* GPIO.cpp
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"


// default constructor
GPIO::GPIO()
{
} //GPIO

// default destructor
GPIO::~GPIO()
{
} //~GPIO

GPIO & GPIO::Instance(void)
{
	static GPIO s;
	return s;
}

void GPIO::pinMode(uint8_t pin, uint8_t mode)
{
	volatile uint8_t * reg;
	uint8_t bit;
	uint8_t oldSreg;

	bit = pinToBit(pin);

	switch(pinToPort(pin))
	{
		case PORT_B:
			reg = &DDRB;
		break;
		case PORT_C:
			reg = &DDRC;
		break;
		case PORT_D:
			reg = &DDRD;
		break;
		default:
		return;
	}
	
	if(mode == INPUT)
	{
		oldSreg = SREG;
		cli();
		*reg &= ~bit;
		SREG = oldSreg;
	}
	else
	{
		oldSreg = SREG;
		cli();
		*reg |= bit;
		SREG = oldSreg;
	}
}

void GPIO::writePin(uint8_t pin, uint8_t data)
{
	volatile uint8_t * reg;
	uint8_t bit;
	uint8_t oldSreg;

	bit = pinToBit(pin);

	switch(pinToPort(pin))
	{
		case PORT_B:
			reg = &PORTB;
		break;
		case PORT_C:
			reg = &PORTC;
		break;
		case PORT_D:
			reg = &PORTD;
		break;
		default:
		return;
	}
	
	if(data == LOW)
	{
		oldSreg = SREG;
		cli();
		*reg &= ~bit;
		SREG = oldSreg;
	}
	else
	{
		oldSreg = SREG;
		cli();
		*reg |= bit;
		SREG = oldSreg;
	}	
}

uint8_t GPIO::readPin(uint8_t pin)
{
	volatile uint8_t * reg;
	uint8_t bit;
	uint8_t oldSreg;
	volatile uint8_t res;

	bit = pinToBit(pin);

	switch(pinToPort(pin))
	{
		case PORT_B:
			reg = &PINB;
		break;
		case PORT_C:
			reg = &PINC;
		break;
		case PORT_D:
			reg = &PIND;
		break;
		default:
		return 0;
	}
		
	oldSreg = SREG;
	cli();
	res = *reg & bit;
	SREG = oldSreg;

	return res;	
}

uint8_t GPIO::pinToPort(uint8_t pin)
{
	switch(pin)
	{
		case 1:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
			return (int)PORT_C;			
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 11:
		case 12:
		case 13:
			return (int)PORT_D;
		case 9:
		case 10:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			return (int)PORT_B;			
	}
	return 0;
}

uint8_t GPIO::pinToBit(uint8_t pin)
{
	switch(pin)
	{
		case 2:
		case 14:
		case 23:
			return 0x01;
		case 3:
		case 15:
		case 24:
			return 0x02;
		case 4:
		case 16:
		case 25:
			return 0x04;
		case 5:
		case 17:
		case 26:
			return 0x08;
		case 6:
		case 18:
		case 27:
			return 0x10;
		case 11:
		case 19:
		case 28:
			return 0x20;
		case 12:
		case 9:
		case 1:
			return 0x40;
		case 13:
		case 10:		
			return 0x80;
	}
	return 0;
}