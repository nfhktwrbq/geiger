/* 
* Settings.h
*
* Created: 21.02.2018 11:59:56
* Author: a.tarletskiy
*/


#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <avr/eeprom.h>





class Settings
{
//variables
public:
	enum SETTING
	{
		LCD_LED_BRIGHT = 0,
		EXPO_TIME,	
		EXPO_UNIT,
		SEARCH_UNIT,
		BUZZER,
		SETTINGS_NUM,
	};
protected:
private:	
	static const uint8_t settingsDefault[SETTINGS_NUM];	
	uint8_t settings[SETTINGS_NUM + 1];
	bool _isEdit;
//functions
public:
	Settings();
	~Settings();
	bool init(void);
	void set(SETTING setting, uint8_t value);
	uint8_t get(SETTING setting);
	void save(void);
	bool isEdit(void);
protected:
private:
	Settings( const Settings &c );
	Settings& operator=( const Settings &c );
	
	uint8_t crc8(const uint8_t *pcBlock, uint16_t len);

}; //Settings

#endif //__SETTINGS_H__
