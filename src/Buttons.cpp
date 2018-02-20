#include "Buttons.h"

Buttons::Buttons(GPIO * pio) : pio(pio)
{
	pio->pinMode(BUTTON_LEFT, GPIO::INPUT);
	pio->pinMode(BUTTON_CENTER, GPIO::INPUT);
	pio->pinMode(BUTTON_RIGHT, GPIO::INPUT);
}

Buttons::~Buttons()
{

}

bool Buttons::getButtonPress(BUTTON button)
{
	return pio->readPin(button);
}