/* 
* Buzzer.h
*
* Created: 15.02.2018 13:50:07
* Author: a.tarletskiy
*/


#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <inttypes.h>
#include "GPIO.h"

class Buzzer
{
//variables
public:
	static const uint8_t TIME_ON = 5;
	static const uint8_t PIN = 14;
	
protected:
private:
	uint8_t onTime = 5;
	GPIO * pio;
	bool en;
	
//functions
public:
	Buzzer(GPIO * pio);
	~Buzzer();
	
	void init(void);
	void on(uint8_t onTime = TIME_ON);
	void off(void);
	bool isOn(void);
	void enable(bool enbl);
	bool isEnable(void);
	void setOnTime(uint8_t onTime);
	uint8_t getOnTime(void);
protected:
private:
	Buzzer( const Buzzer &c );
	Buzzer& operator=( const Buzzer &c );

}; //Buzzer

#endif //__BUZZER_H__
