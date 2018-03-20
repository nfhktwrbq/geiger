/* 
* MT10S.cpp
*
* Created: 09.02.2018 11:45:41
* Author: a.tarletskiy
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "MT10S.h"


// default constructor
MT10S::MT10S()
{
	cursorPos = 0;
} //MT10S

MT10S::MT10S(GPIO * pio, uint8_t pinD4, uint8_t pinD5, uint8_t pinD6, uint8_t pinD7, uint8_t pinRS, uint8_t pinE) :
HD44780::HD44780(pio, pinD4, pinD5, pinD6, pinD7, pinRS, pinE)
{
	cursorPos = 0;
} //MT10S

// default destructor
MT10S::~MT10S()
{
} //~MT10S

void MT10S::print(char ch)
{
	HD44780::print(ch);
	if(cursorPos == 0x07)
	{
		cursorPos = 0x40;
		HD44780::setCursor(0, 1);
	}
	else
	{
		cursorPos++;
	}
}

/*
void MT10S::clear()
{
	HD44780::clear();
	memset(lcdString, 0x20, LCD_STRING_LEN - 1);
	lcdString[LCD_STRING_LEN-1] = 0;
	setCursor(0, 0);
	for(uint8_t i = 0; i < 10; i++)
	{
		print(' ');
	}
}
void MT10S::print(const char * str)
{
	while(* str)
	{
		print(* str);
		str++;
	}
}

void MT10S::write(char ch)
{	
	MT10S::print(ch);
}

void MT10S::printf(const char * format, ...)
{	
	char str[MAX_STRING_LEN];
	
	va_list args;
	va_start(args, format);
	vsnprintf(str, MAX_STRING_LEN, format, args);
	va_end(args);
	print(str);
}
*/
void MT10S::setCursor(uint8_t col, uint8_t row)
{
	if(col > 7)
	{
		cursorPos = (col % 8) + 0x40;
	}
	else
	{
		cursorPos = col;
	}
	//stringPos = col;
	HD44780::setCursor(cursorPos, 0);	
}