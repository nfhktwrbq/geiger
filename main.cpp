/*
 * geiger.cpp
 *
 * Created: 18.01.2018 8:40:33
 * Author : a.tarletskiy
 */ 


#include "GPIO.h"
#include "portability.h"

int main(void)
{
	GPIO * pio = &GPIO::Instance();
    
	pio->pinMode(2, pio->OUTPUT);
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

