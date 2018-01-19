/*
 * geiger.cpp
 *
 * Created: 18.01.2018 8:40:33
 * Author : a.tarletskiy
 */ 

#include <avr/io.h>
#include "inc/TWI.h"

int main(void)
{
	TWI twi();
	PCF8574 dev(twi);
    /* Replace with your application code */
    while (1) 
    {
		dev.acquire();
    }
}

