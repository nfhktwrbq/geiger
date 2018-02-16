/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __GPIO_H__
#define __GPIO_H__

#include <inttypes.h>

class GPIO
{
//variables

//functions
public:
	static GPIO & Instance(void);
	void pinMode(uint8_t pin, uint8_t mode);
	void writePin(uint8_t pin, uint8_t data);
	uint8_t readPin(uint8_t pin);
	enum
	{
		LOW = 0,
		INPUT,
		OUTPUT,
		HIGH,		
	};
protected:
private:
	GPIO();
	~GPIO();
	GPIO( const GPIO &c );
	GPIO& operator=( const GPIO &c );
	uint8_t pinToPort(uint8_t pin);
	uint8_t pinToBit(uint8_t pin);
	enum
	{
		PORT_B = 1,
		PORT_C = 2,
		PORT_D = 3,
		DDR,
		PIN,
	};
}; //GPIO

#endif //__GPIO_H__
