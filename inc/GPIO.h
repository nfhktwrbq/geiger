/* 
* GPIO.h
*
* Created: 19.01.2018 14:24:56
* Author: a.tarletskiy
*/


#ifndef __GPIO_H__
#define __GPIO_H__


class GPIO
{
//variables
public:
protected:
private:

//functions
public:
	static GPIO & Instance(void);
	void pinMode(uint8_t pin, uint8_t mode);
	void writePin(uint8_t pin, uint8_t data);
	uint8_t readPin(uint8_t pin);
	enum
	{
		INPUT,
		OUTPUT,
		HIGH,
		LOW
	} __attribute__((packed));
protected:
private:
	GPIO();
	~GPIO();
	GPIO( const GPIO &c );
	GPIO& operator=( const GPIO &c );
	uint8_t * pinToPort(uint8_t pin);
	uint8_t pinToBit(uint8_t pin);
	enum
	{
		PORT_B = 1,
		PORT_C,
		PORT_D,
		DDR,
		PIN
	} __attribute__((packed));
}; //GPIO

#endif //__GPIO_H__
