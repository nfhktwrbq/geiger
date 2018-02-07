/*
 * geiger.cpp
 *
 * Created: 18.01.2018 8:40:33
 * Author : a.tarletskiy
 */ 


#include "GPIO.h"
#include "Timer.h"
#include "HD44780.h"
#include "portability.h"
#include "AnalogToDigital.h"
#include "gvars.h"
#include "global.h"
#include "PulseWidthModulation.h"


#include "interrupt.h"
#include "util/delay.h"

#define TEST_PIN 14

int main(void)
{
	GPIO * pio = &GPIO::Instance();


//	t16.setCompareOutputMode(Timer16::CO_FAST_PWM_OCnA);
//	t16.setWaveformGenerationMode(Timer16::WG_FAST_PWM_9BIT);
//	t16.setClockSelection(Timer16::CS_1PR);
	//t16.setInputCaptureNoiseCanceler(uint8_t mode);
	//t16.setCaptureEdge(uint8_t mode);
	//t16.setForceCapture(uint8_t mode);
	//t16.getTimerCounter(void);
//	t16.setTimerCounter(0);
	//t16.getOutputCompareA(void);
//	t16.setOutputCompareA(0x0000);
	//t16.getOutputCompareB(void);
	//t16.setOutputCompareB(uint16_t oc);
	//t16.getInputCapture(void);
	//t16.setInputCapture(uint16_t ic);
//	t16.enableInterrupt(false);
	//t16.setInterruptFlag(uint8_t flag);
	//t16.getInterruptFlag(void);

	
	
	

	pio->pinMode(6, pio->INPUT);
	pio->pinMode(15, pio->OUTPUT);
	pio->pinMode(TEST_PIN, pio->OUTPUT);
	pio->writePin(15, pio->LOW);
	HD44780 lcd(pio, 16, 17, 18, 19, 23, 24);
	AnalogToDigital adc(AnalogToDigital::AREF,0,AnalogToDigital::PR_128);
    adc.setChannel(AnalogToDigital::CH_3);
	
	Timer8 timer8_0(&TCCR0A, &TCCR0B, &TCNT0, &OCR0A, &OCR0B, &TIMSK0, &TIFR0, &GTCCR, &GTCCR);
	Timer8 timer8_2(&TCCR2A, &TCCR2B, &TCNT2, &OCR2A, &OCR2B, &TIMSK2, &TIFR2, &ASSR, &GTCCR);
	Timer16 timer16_1(&TCCR1A, &TCCR1B, &TCNT1, &OCR1A, &OCR1B, &TIMSK1, &TIFR1, &TCCR1C, &ICR1);
	
	PulseWidthModulation8 pwm8(&timer8_0);
	PulseWidthModulation16 pwmHV(&timer16_1);
	
	pwm8.initPWM(CO_FAST_PWM_OCnA, WG_FAST_PWM_9BIT, CS_1PR);
	
	lcd.init();
	lcd.sendCmd(0x02);
	_delay_ms(500);
	lcd.print("Hello");

	_delay_ms(4000);
	lcd.setXY(0,0);
	lcd.print("        ");
	lcd.setXY(0,0);
	//lcd.printf("T=%d", t16.getTimerCounter());
    _delay_ms(4000);
    uint16_t i = 0;
    while (1) 
    {
		lcd.setXY(0,0);
    	
		lcd.printf("T=%d", adc.proc());

		if(pio->readPin(6))
		{
			//t16.setOutputCompareA(i);
			i++;
		}
		_delay_ms(500);
		pio->writePin(TEST_PIN, pio->LOW);
		_delay_ms(50);
		pio->writePin(TEST_PIN, pio->LOW);

    }
}

