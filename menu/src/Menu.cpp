/* 
* Menu->cpp
*
* Created: 15->02->2018 13:50:06
* Author: a->tarletskiy
*/


#include "Menu.h"


Menu::Menu(Counter * counter,  Buttons * buttons) : buttons(buttons)  
{
} //Menu

// default destructor
Menu::~Menu()
{
} //~Menu

void Menu::proc(void)
{
	buttons->proc();
	if(buttons->getButtonClick(Buttons::BUTTON_LEFT))
	{
		
	}
	if(buttons->getButtonClick(Buttons::BUTTON_RIGHT))
	{
		 
	}
	if(buttons->getButtonClick(Buttons::BUTTON_CENTER))
	{
		 
	}
	if(buttons->getButtonLongPress(Buttons::BUTTON_LEFT))
	{
		 
	}
	if(buttons->getButtonLongPress(Buttons::BUTTON_RIGHT))
	{
		 
	}
	if(buttons->getButtonLongPress(Buttons::BUTTON_CENTER))
	{

	}
}
