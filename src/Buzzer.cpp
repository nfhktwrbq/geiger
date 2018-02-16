/* 
* Buzzer.cpp
*
* Created: 15.02.2018 13:50:06
* Author: a.tarletskiy
*/


#include "Buzzer.h"


Buzzer::Buzzer(GPIO * pio) : pio(pio)
{
	pio->pinMode(BUZZER_PIN, GPIO::OUTPUT);
	pio->writePin(BUZZER_PIN, GPIO::LOW);
} //Buzzer

// default destructor
Buzzer::~Buzzer()
{
} //~Buzzer

void Buzzer::init(void)
{
	pio->pinMode(BUZZER_PIN, GPIO::OUTPUT);
	pio->writePin(BUZZER_PIN, GPIO::LOW);
}

void Buzzer::on(void)
{
	pio->writePin(BUZZER_PIN, GPIO::HIGH);
}

void Buzzer::off(void)
{
	pio->writePin(BUZZER_PIN, GPIO::LOW);
}

bool Buzzer::isOn(void)
{
	return pio->readPin(BUZZER_PIN);
}

void Buzzer::enable(bool enbl)
{
	en =  enbl;
}

bool Buzzer::isEnable(void)
{
	return en;
}