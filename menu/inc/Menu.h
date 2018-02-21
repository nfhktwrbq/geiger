/* 
* Menu.h
*
* Created: 15.02.2018 13:50:07
* Author: a.tarletskiy
*/


#ifndef __MENU_H__
#define __MENU_H__

#include "LiquidMenu.h"
#include "Buttons.h"

class Menu
{
//variables
public:
	
protected:
private:
	LiquidSystem * menuSystem;
	Buttons * buttons;
//functions
public:
	Menu(LiquidSystem * menuSystem, Buttons * buttons);
	~Menu();
	void proc();
	
	
protected:
private:
	Menu( const Menu &c );
	Menu& operator=( const Menu &c );

}; //Menu

#endif //__MENU_H__
