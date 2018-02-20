/* 
* Buzzer.cpp
*
* Created: 15.02.2018 13:50:06
* Author: a.tarletskiy
*/


#include "Buzzer.h"


Buzzer::Buzzer(GPIO * pio) : pio(pio)
{
	pio->pinMode(PIN, GPIO::OUTPUT);
	pio->writePin(PIN, GPIO::LOW);
	onTime = TIME_ON;
} //Buzzer

// default destructor
Buzzer::~Buzzer()
{
} //~Buzzer

void Buzzer::init(void)
{
	pio->pinMode(PIN, GPIO::OUTPUT);
	pio->writePin(PIN, GPIO::LOW);
}

void Buzzer::on(uint8_t onTime)//default = BUZZER_ON_TIME
{
	this->onTime = onTime;
	pio->writePin(PIN, GPIO::HIGH);
}

void Buzzer::off(void)
{
	pio->writePin(PIN, GPIO::LOW);
}

bool Buzzer::isOn(void)
{
	return pio->readPin(PIN);
}

void Buzzer::enable(bool enbl)
{
	en =  enbl;
}

bool Buzzer::isEnable(void)
{
	return en;
}

void Buzzer::setOnTime(uint8_t onTime)
{
	this->onTime = onTime;
}

uint8_t Buzzer::getOnTime(void)
{
	return onTime;
}