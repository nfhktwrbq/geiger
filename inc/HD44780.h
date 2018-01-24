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
	

/*void lcd_WrCmd();
void lcd_WrChr(uint8_t Data);
void lcd_setXY(bool Row, char Col);
void lcd_WrInt(uint16_t num, char q, uint8_t fill);
uint8_t lcd_readChr(void);
void lcd_WrTemp(uint16_t tp);
void lcd_WrLong(uint32_t num, bool q);
void lcd_clear(void);
bool lcd_busy(void);
void lcd_WrStr(const char *data, uint8_t len = MAX_LEN);
void lcd_message(uint8_t position1, const char * firsrStringMesage, uint8_t position2, const char * secondStringMessage);
void lcd_message(uint8_t stringNumber, uint8_t position1, const char * stringMesage);
void lcd_iMessage(uint8_t stringNumber, uint8_t position1, uint32_t data);
void lcd_off(void);*/


protected:
private:
	GPIO * pio;
	uint8_t pinD4;
	uint8_t pinD5;
	uint8_t pinD6;
	uint8_t pinD7;
	uint8_t pinRS;
	uint8_t pinE;
	
	const static size_t MAX_STRING_LEN = 40;

//functions
public:
	HD44780();
	HD44780(GPIO * pio, uint8_t pinD4, uint8_t pinD5, uint8_t pinD6, uint8_t pinD7, uint8_t pinRS, uint8_t pinE);
	~HD44780();
	
	void sendCmd(uint8_t cmd);
	void init(void);
	void print(char ch);
	void print(char * str);
	void printf(const char * format, ...);
	void setXY(uint8_t x, uint8_t y);
	void clear();
	
protected:
private:
	HD44780( const HD44780 &c );
	HD44780& operator=( const HD44780 &c );
	
	void setData(uint8_t data);
	void strobe(void);

}; //HD44780

#endif //__HD44780_H__
