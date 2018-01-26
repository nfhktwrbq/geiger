/*
 * geiger.cpp
 *
 * Created: 18.01.2018 8:40:33
 * Author : a.tarletskiy
 */ 


#include "GPIO.h"
#include "HD44780.h"
#include "portability.h"
#include "AnalogToDigital.h"

int main(void)
{
	GPIO * pio = &GPIO::Instance();
	HD44780 lcd(pio, 2, 3, 4, 5, 27, 28);
	AnalogToDigital adc(0,0,0);
    
	pio->pinMode(26, pio->OUTPUT);
	lcd.init();
	lcd.printf("Volt = %d", /*adc.proc()*/3);
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

