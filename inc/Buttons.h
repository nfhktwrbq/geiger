#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include "GPIO.h"
#include "Counter.h"
#include "global.h"

class Buttons
{
public:
	enum BUTTON
	{
		BUTTON_LEFT = 13,
		BUTTON_CENTER = 12,
		BUTTON_RIGHT = 6,
	};

private:
	GPIO * pio;
	Counter * counter;
	uint8_t longPressState;
	uint8_t clickState;
	static const uint32_t LONG_PRESS_TIME;

public:
	Buttons(GPIO * pio, Counter * counter);
	~Buttons();
	bool getButtonPress(BUTTON button);
	bool getButtonLongPress(BUTTON button);
	bool getButtonClick(BUTTON button);
	void proc(void);

private:
	Buttons( const Buttons &c );
	Buttons& operator=( const Buttons &c );
	
	bool getButtonState(BUTTON button, uint8_t &stateType);
	void buttonProc(BUTTON button, uint32_t & timer, uint8_t & state);
	uint8_t getBit(BUTTON button);
};

#endif