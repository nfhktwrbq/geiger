
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <avr/interrupt.h>
#include "global.h"


ISR (INT0_vect)
{
        count++;
}

ISR (TIMER2_OVF_vect)
{
}

ISR (TIMER0_OVF_vect)
{
}


#endif
