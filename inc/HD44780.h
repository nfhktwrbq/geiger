/* 
* HD44780.h
*
* Created: 24.01.2018 15:43:38
* Author: a.tarletskiy
*/


#ifndef __HD44780_H__
#define __HD44780_H__

#include <stddef.h>
#include "GPIO.h"

class HD44780
{
//variables
public:
protected:
	const static size_t MAX_STRING_LEN = 40;
private:
	GPIO * pio;
	uint8_t pinD4;
	uint8_t pinD5;
	uint8_t pinD6;
	uint8_t pinD7;
	uint8_t pinRS;
	uint8_t pinE;
	
	

//functions
public:
	HD44780();
	HD44780(GPIO * pio, uint8_t pinD4, uint8_t pinD5, uint8_t pinD6, uint8_t pinD7, uint8_t pinRS, uint8_t pinE);
	virtual ~HD44780();
	
	virtual void sendCmd(uint8_t cmd);
	virtual void init(void);
	virtual void print(char ch);
	virtual void print(uint8_t val);
	virtual void print(uint16_t val);
	virtual void print(uint32_t val);
	virtual void print(int16_t val);
	virtual void print(int32_t val);
	virtual void print(float val);
	virtual void print(double val);

	virtual void write(char ch);
	virtual void print(const char * str);
	virtual void print(char * str);
	virtual void printf(const char * format, ...);
	virtual void setCursor(uint8_t col, uint8_t row);
	virtual void createChar(uint8_t location, uint8_t * chArr);
	virtual void clear();
	virtual void home();
	virtual uint8_t getCursorPosition(void);
	virtual uint8_t getSymbolsPerString(void);

protected:
private:
	HD44780( const HD44780 &c );
	HD44780& operator=( const HD44780 &c );
	
	virtual void setData(uint8_t data);
	virtual void strobe(void);

}; //HD44780

#endif //__HD44780_H__
