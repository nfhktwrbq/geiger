#include "Buttons.h"

const uint32_t Buttons::LONG_PRESS_TIME = LONG_PRESS_TIMEOUT;

Buttons::Buttons(GPIO * pio, Counter * counter) : pio(pio), counter(counter)
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

bool Buttons::getButtonLongPress(BUTTON button)
{
	return getButtonState(button, longPressState);
}

bool Buttons::getButtonClick(BUTTON button)
{
	return getButtonState(button, clickState);
}

bool Buttons::getButtonState(BUTTON button, uint8_t &stateType)
{
	bool state = stateType & getBit(button);
	stateType &= ~getBit(button);
	return state;
}

void Buttons::proc(void)
{
	static uint32_t timerButtonLeft = 0;
	static uint32_t timerButtonCenter = 0;
	static uint32_t timerButtonRight = 0;

	static uint8_t pressButtonLeft = false;
	static uint8_t pressButtonCenter = false;		
	static uint8_t pressButtonRight = false;

	buttonProc(BUTTON_LEFT, timerButtonLeft, pressButtonLeft);
	buttonProc(BUTTON_CENTER, timerButtonCenter, pressButtonCenter);	
	buttonProc(BUTTON_RIGHT, timerButtonRight, pressButtonRight);
}

void Buttons::buttonProc(BUTTON button, uint32_t & timer, uint8_t & state)
{
	switch(state)
	{
		case 0:
			if(getButtonPress(button) )
			{
				state = 1;
			}
			else
			{
				timer = counter->getTimer();
			}
		break;
		case 1:
			if(getButtonPress(button))
			{
				if(counter->getTimer() - timer > LONG_PRESS_TIME)
				{
					state = 2;
				}
			}
			else
			{
				clickState |= getBit(button);	
				timer = counter->getTimer();	
				state = 0;
			}
		break;
		case 2:
			longPressState |= getBit(button);
			timer = counter->getTimer();
			state = 3;
		break;
		case 3:
			if(getButtonPress(button))
			{
				timer = counter->getTimer();
				state = 4; 
			}
			else
			{
				state = 0;
			}
		break;
		case 4:
			if(getButtonPress(button))
			{
				if(counter->getTimer() - timer > LONG_PRESS_TIME)
				{
					longPressState |= getBit(button);
					state = 3;
				}
			}
			else
			{
				state = 0;
			}
		break;
		default:
			timer = counter->getTimer();
		break;
	}
}

uint8_t Buttons::getBit(BUTTON button)
{
	switch(button)
	{
		case BUTTON_LEFT:
			return 0x01;
		break;
		case BUTTON_CENTER:
			return 0x02;
		break;
		case BUTTON_RIGHT:
			return 0x04;
		break;
		default:
			return 0x00;
		break;
	}
}