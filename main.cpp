/*
 * geiger.cpp
 *
 * Created: 18.01.2018 8:40:33
 * Author : a.tarletskiy
 */ 

#include <util/delay.h>
#include <inttypes.h>

#include "GPIO.h"
#include "Timer.h"
#include "HD44780.h"
#include "portability.h"
#include "AnalogToDigital.h"
#include "gvars.h"
#include "global.h"
#include "PulseWidthModulation.h"
#include "HighSuply.h"
#include "LiquidMenu.h"
#include "MT10S.h"
#include "Counter.h"
#include "Buttons.h"


#define TEST_PIN 14

void qqq(void);

GPIO * pio = &GPIO::Instance();

	MT10S lcd(pio, 16, 17, 18, 19, 23, 24);
	
	Buttons buttons(pio);

	Timer8 timer8_0(&TCCR0A, &TCCR0B, &TCNT0, &OCR0A, &OCR0B, &TIMSK0, &TIFR0, &GTCCR, &GTCCR);	
	PulseWidthModulation8 pwmLCDLED(&timer8_0);

	// First we need to instantiate the LiquidCrystal object.	

	// ----- WELCOME SCREEN -----
	/// Instantiating a line with one string literal.
	LiquidLine welcome_line(1, 0, "PWM");
	/// Forming a screen from the above two lines.
	LiquidScreen welcome_screen(welcome_line);
	// --------------------------

	// ----- SCREEN 2 -----
	LiquidLine some_line(0, 0, "Some line");
	LiquidScreen some_screen(some_line);
	// --------------------

	// Now let's combine the screens into a menu.
	LiquidMenu my_menu(lcd, welcome_screen, some_screen);	
	
	
int main(void)
{
	lcd.init();
	pio->pinMode(11,GPIO::OUTPUT);

	

	timer8_0.setInterrupt(INT_OVERFLOW);
	pwmLCDLED.initPWM(CO_FAST_PWM_OCnB, WG_FAST_PWM_1, CS_1PR);	
	pwmLCDLED.setMaxPWMBorder(255);
	
	Timer16 timer16_1(&TCCR1A, &TCCR1B, &TCNT1, &OCR1A, &OCR1B, &TIMSK1, &TIFR1, &TCCR1C, &ICR1);
	timer16_1.setInterrupt(INT_OVERFLOW);	
	PulseWidthModulation16 pwmHV(&timer16_1);
	pwmHV.initPWM(CO_FAST_PWM_OCnA, WG_FAST_PWM_9BIT, CS_1PR);


	pwmHV.setMaxPWMBorder(80);

	
	Timer8 timer8_2(&TCCR2A, &TCCR2B, &TCNT2, &OCR2A, &OCR2B, &TIMSK2, &TIFR2, &ASSR, &GTCCR);	
		
	AnalogToDigital adc(AnalogToDigital::AREF,0,AnalogToDigital::PR_128);
    adc.setChannel(AnalogToDigital::CH_3);
	
	 
	Buzzer buzzer(pio);
	Buzzer buzzerStatus(pio);
	buzzer.enable(true);		
	
	if(!welcome_line.attach_function(1, qqq))
	{
	 	lcd.clear();
	 	lcd.setCursor(0,0);
	  	lcd.printf("FALSE");
	  	_delay_ms(1000);
	}else
	{
		lcd.clear();
	 	lcd.setCursor(0,0);
	  	lcd.printf("F=%d",qqq);
	  	_delay_ms(1000);
	}
	welcome_line.attach_function(2, qqq);
some_line.attach_function(1, qqq);
some_line.attach_function(2, qqq);
	/// Instantiating a line with an integer variable.
	//uint8_t oneTwoThree = 123;
	//LiquidLine welcome_line2(2, 1, oneTwoThree);
	//LiquidLine welcome_line3(3, 2, "Third mwnu");

	_delay_ms(1000);
	 lcd.setCursor(0,0);
    lcd.printf("1 = %d", TCCR0A);
	_delay_ms(1000);

	_delay_ms(1000);
	 lcd.setCursor(0,0);
    lcd.printf("2 = %d", TCCR0B);
	_delay_ms(1000);
	HighSuply counterSupply(&pwmHV, &adc, AnalogToDigital::CH_3);
	// if(!counterSupply.setVoltage(400, 5, 250))
	// {
	// 	lcd.setCursor(0,0);
	// 	lcd.printf("V=%d", counterSupply.getVoltage());
	// 	while(1);
	// }


my_menu.add_screen(welcome_screen);
my_menu.add_screen(some_screen);



	Counter c(&counterSupply, &buzzer, &my_menu);
	counter = &c;
	counter->init();

	
   // timer16_1.setOutputCompareA(1);
    //uint32_t t=0;
    lcd.setCursor(0,0);
    lcd.printf("T=%d",  counter->getTimer());

    while (1) 
    {

    	if(buttons.getButtonPress(Buttons::BUTTON_LEFT))
    	{
    		my_menu--;
   //  		lcd.clear();
			// lcd.setCursor(0,0);
		 //    lcd.printf("= %d", OCR0B);
   //  		pwmLCDLED.changeOn(10);
    		while(buttons.getButtonPress(Buttons::BUTTON_LEFT));
    		
    		_delay_ms(10);
    	}
    	if(buttons.getButtonPress(Buttons::BUTTON_RIGHT))
    	{
    		my_menu++;
    	// 	lcd.clear();
    	// 	lcd.setCursor(0,0);
		  	// lcd.printf("= %d", OCR0B);
    	// 	pwmLCDLED.changeOn(-10);
    	 	while(buttons.getButtonPress(Buttons::BUTTON_RIGHT));
    		
    		_delay_ms(10);
    	}
    	if(buttons.getButtonPress(Buttons::BUTTON_CENTER))
    	{
    		my_menu.switch_focus(0);
    		if(!my_menu.call_function(1))
    		{
	    	 	lcd.clear();
	    	 	lcd.setCursor(0,0);
			  	lcd.printf("FALSE");
	    	}
    		//pwmLCDLED.changeOn(10);
    		while(buttons.getButtonPress(Buttons::BUTTON_CENTER));
    		my_menu.update();
    		_delay_ms(10);
    	}
  //   	if(counter->getTimer() - t > 100)
  //   	{
  //   		t = counter->getTimer();    	
		// 	lcd.setCursor(0,0);
	 //    	lcd.clear();
		// 	lcd.printf("%d %d", counterSupply.getVoltage(), counter->getCountSpeed());
		// 	_delay_ms(500);
		// }
		// counter->proc();
		

    }
}

void qqq(void){
	pwmLCDLED.changeOn(10);
	lcd.clear();
    	lcd.setCursor(0,0);
		 lcd.printf("qqqqqqqq");
}