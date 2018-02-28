/* 
* HD44780.cpp
*
* Created: 24.01.2018 15:43:38
* Author: a.tarletskiy
*/

#include <util/delay.h>
#include <stdarg.h>
#include <stdio.h>
#include "HD44780.h"

// default constructor
HD44780::HD44780()
{
} //HD44780

HD44780::HD44780(GPIO * pio, uint8_t pinD4, uint8_t pinD5, uint8_t pinD6, uint8_t pinD7, uint8_t pinRS, uint8_t pinE) :
 pio(pio), pinD4(pinD4), pinD5(pinD5), pinD6(pinD6), pinD7(pinD7), pinRS(pinRS), pinE(pinE)
 {	
 }

// default destructor
HD44780::~HD44780()
{
} //~HD44780

void HD44780::init(void)
{
	_delay_ms(125);

	pio->pinMode(pinD4, pio->OUTPUT);
	pio->pinMode(pinD5, pio->OUTPUT);
	pio->pinMode(pinD6, pio->OUTPUT);
	pio->pinMode(pinD7, pio->OUTPUT);
	pio->pinMode(pinRS, pio->OUTPUT);
	pio->pinMode(pinE, pio->OUTPUT);
	


	setData(0x00);
	pio->writePin(pinRS, pio->LOW);
	pio->writePin(pinE, pio->LOW);

	_delay_ms(25);

	setData(0x03);
	strobe();	
	_delay_ms(10);

	strobe();
	_delay_us(45);

	strobe();
	_delay_us(45);	
	
	setData(0x02);
	strobe();
	_delay_us(45);
	
	sendCmd(0x28);
	sendCmd(0x08);
	sendCmd(0x0C);
	sendCmd(0x01);
	sendCmd(0x06);
}

void HD44780::sendCmd(uint8_t cmd)
{
	_delay_us(40);
	pio->writePin(pinRS, pio->LOW);
	pio->writePin(pinE, pio->LOW);
	setData(0x00);
	_delay_us(1);
	pio->writePin(pinE, pio->HIGH);
	_delay_us(1);
	setData(cmd >> 4);
	_delay_us(1);
	pio->writePin(pinE, pio->LOW);
	_delay_us(1);
	setData(0x00);

	_delay_us(1);
	pio->writePin(pinE, pio->HIGH);
	_delay_us(1);
	setData(cmd);
	_delay_us(1);
	pio->writePin(pinE, pio->LOW);
	_delay_us(1);
	setData(0x00);
}

void HD44780::print(char ch)
{
	_delay_us(40);
	pio->writePin(pinRS, pio->LOW);
	pio->writePin(pinE, pio->LOW);
	setData(0x00);
	pio->writePin(pinRS, pio->HIGH);
	_delay_us(1);
	pio->writePin(pinE, pio->HIGH);
	_delay_us(1);
	setData(ch >> 4);
	_delay_us(1);
	pio->writePin(pinE, pio->LOW);
	_delay_us(1);
	setData(0x00);
	pio->writePin(pinRS, pio->LOW);

	pio->writePin(pinRS, pio->HIGH);
	_delay_us(1);
	pio->writePin(pinE, pio->HIGH);
	_delay_us(1);
	setData(ch);
	_delay_us(1);
	pio->writePin(pinE, pio->LOW);
	_delay_us(1);
	setData(0x00);	
	pio->writePin(pinRS, pio->LOW);
}

void HD44780::write(char ch)
{
	print(ch);
}

void HD44780::print(char * str)
{
	while(* str)
	{
		this->print(* str);
		str++;		
	}
}

void HD44780::print(const char * str)
{
	printf("%s", str);
}

void HD44780::print(uint8_t val)
{
	printf("%u", val);
}

void HD44780::print(uint16_t val)
{
	printf("%u", val);
}

void HD44780::print(uint32_t val)
{
	printf("%u", val);
}

void HD44780::print(int16_t val)
{
	printf("%d", val);
}

void HD44780::print(int32_t val)
{
	printf("%d", val);
}

void HD44780::print(float val)
{
	printf("%f", val);
}

void HD44780::print(double val)
{
	printf("%f", val);
}

void HD44780::printf(const char * format, ...)
{	
	char str[MAX_STRING_LEN];
	
	va_list args;
	va_start(args, format);
	vsnprintf(str, MAX_STRING_LEN, format, args);
	va_end(args);
	print(str);
}

void HD44780::setCursor(uint8_t col, uint8_t row)
{
	uint8_t adr;
	if(!row)
	{
		adr = 0x80;
	}
	else
	{
		adr = 0xC0;
	}
	adr |= col;
	sendCmd(adr);	
}

void HD44780::createChar(uint8_t location, uint8_t * chArr)
{
	location &= 0x7;            // we only have 8 locations 0-7
	
	sendCmd(0x40 | (location << 3));
	_delay_us(30);
	
	for (uint8_t i = 0; i < 8; i++)
	{
		write(chArr[i]);      // call the virtual write method
		_delay_us(40);
	}
}

void HD44780::clear()
{
	sendCmd(0x01);
	_delay_ms(2);	
}

void HD44780::home()
{
	sendCmd(0x02);
	_delay_us(50);	
}

void HD44780::setData(uint8_t data)
{
	pio->writePin(pinD4, data & 0x01);
	pio->writePin(pinD5, data & 0x02);
	pio->writePin(pinD6, data & 0x04);
	pio->writePin(pinD7, data & 0x08);
	//pio->writePin(pinRS, data & 0x10);
	//pio->writePin(pinE, data & 0x20);
}

void HD44780::strobe(void)
{
	pio->writePin(pinE, pio->LOW);
	pio->writePin(pinE, pio->HIGH);
	_delay_us(40);
	pio->writePin(pinE, pio->LOW);
	_delay_us(40);
}