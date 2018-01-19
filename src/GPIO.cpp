/* 
* GPIO.cpp
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/

#include <avr/io.h>
#include "GPIO.h"


// default constructor
GPIO::GPIO()
{
} //GPIO

// default destructor
GPIO::~GPIO()
{
} //~GPIO

static GPIO & GPIO::Instance(void)
{
	static GPIO s;
	return s;
}

void pinMode(uint8_t pin, uint8_t mode)
{
	
	
}
void writePin(uint8_t pin, uint8_t data);
uint8_t readPin(uint8_t pin);

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
			return PORT_C;			
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 11:
		case 12:
		case 13:
			return PORT_D;
		case 9:
		case 10:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			return PORT_B;			
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
		case 12:
		case 10:		
			return 0x80;
	}
	return 0;
}