/* 
* MT10S.h
*
* Created: 09.02.2018 11:45:41
* Author: a.tarletskiy
*/


#ifndef __MT10S_H__
#define __MT10S_H__


#include "HD44780.h"


class MT10S : public HD44780
{
//variables
public:
protected:
private:
	static const uint8_t LCD_STRING_LEN = 11;
	uint8_t cursorPos;

//functions
public:
	using HD44780::print;
	virtual void print(char ch);
	virtual void setCursor(uint8_t col, uint8_t row);
	virtual uint8_t getCursorPosition(void);
	virtual uint8_t getSymbolsPerString(void);
	MT10S();
	MT10S(GPIO * pio, uint8_t pinD4, uint8_t pinD5, uint8_t pinD6, uint8_t pinD7, uint8_t pinRS, uint8_t pinE);
	~MT10S();
protected:
private:
	MT10S( const MT10S &c );
	MT10S& operator=( const MT10S &c );

}; //MT10S

#endif //__MT10S_H__
