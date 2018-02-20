#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include "GPIO.h"

class Buttons
{
public:
	enum BUTTON
	{
		BUTTON_LEFT = 13,
		BUTTON_CENTER = 12,
		BUTTON_RIGHT = 6,
	};

	Buttons(GPIO * pio);
	~Buttons();
	bool getButtonPress(BUTTON button);

private:
	GPIO * pio;

private:
	Buttons( const Buttons &c );
	Buttons& operator=( const Buttons &c );
};

#endif