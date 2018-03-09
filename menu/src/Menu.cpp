/* 
* Menu->cpp
*
* Created: 15->02->2018 13:50:06
* Author: a->tarletskiy
*/


#include "Menu.h"


Menu::Menu(Counter * counter, LiquidSystem * menuSystem, LiquidMenu * workMenu, LiquidMenu * settingsMenu, Buttons * buttons) : menuSystem(menuSystem), buttons(buttons)  
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
		 menuSystem->previous_screen();
	}
	if(buttons->getButtonClick(Buttons::BUTTON_RIGHT))
	{
		 menuSystem->next_screen();
	}
	if(buttons->getButtonClick(Buttons::BUTTON_CENTER))
	{
		 menuSystem->call_function(1);
	}
	if(buttons->getButtonLongPress(Buttons::BUTTON_LEFT))
	{
		 menuSystem->change_menu(*workMenu);
	}
	if(buttons->getButtonLongPress(Buttons::BUTTON_RIGHT))
	{
		 menuSystem->change_menu(*settingsMenu);
	}
	if(buttons->getButtonLongPress(Buttons::BUTTON_CENTER))
	{

	}
}
