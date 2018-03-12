/* 
* Menu.h
*
* Created: 15.02.2018 13:50:07
* Author: a.tarletskiy
*/


#ifndef __MENU_H__
#define __MENU_H__

#include "Buttons.h"

class Menu
{
//variables
public:
	
protected:
private:
	
	Buttons * buttons;
	char * searchString;
	char * expoString;

//functions
public:
	Menu(Counter * counter, Buttons * buttons);
	~Menu();
	void proc();
	void setExpoString(char * str);
	void setSearchString(char * str);
	
protected:
private:
	Menu( const Menu &c );
	Menu& operator=( const Menu &c );

}; //Menu

#endif //__MENU_H__
