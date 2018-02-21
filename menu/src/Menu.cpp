/* 
* Menu.cpp
*
* Created: 15.02.2018 13:50:06
* Author: a.tarletskiy
*/


#include "Menu.h"


Menu::Menu(LiquidSystem * menuSystem, Buttons * buttons) : menuSystem(menuSystem), buttons(buttons)  
{
} //Menu

// default destructor
Menu::~Menu()
{
} //~Menu

void Menu::proc(void)
{
	// if (right.check() == LOW) 
	// {
	// 	menuSystem.next_screen();
	// }
	// if (left.check() == LOW) 
	// {
	// 	menuSystem.previous_screen();
	// }
	// if (up.check() == LOW) 
	// {
	// 	menuSystem.call_function(increase);
	// }
	// if (down.check() == LOW) 
	// {
	// 	menuSystem.call_function(decrease);
	// }
	// if (enter.check() == LOW) 
	// {
	// 	menuSystem.switch_focus();
	// }
}
