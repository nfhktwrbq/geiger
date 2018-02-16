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
	static const uint8_t BUZZER_TIME_ON = 5;
	static const uint8_t BUZZER_PIN = 14;
protected:
private:
	GPIO * pio;
	bool en;
	
//functions
public:
	Buzzer(GPIO * pio);
	~Buzzer();
	
	void init(void);
	void on(void);
	void off(void);
	bool isOn(void);
	void enable(bool enbl);
	bool isEnable(void);
protected:
private:
	Buzzer( const Buzzer &c );
	Buzzer& operator=( const Buzzer &c );

}; //Buzzer

#endif //__BUZZER_H__
