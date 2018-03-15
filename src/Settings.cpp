/* 
* Settings.cpp
*
* Created: 21.02.2018 11:59:55
* Author: a.tarletskiy
*/


#include "Settings.h"

uint8_t settingsEE[Settings::SETTINGS_NUM + 1] EEMEM;

const uint8_t Settings::settingsDefault[SETTINGS_NUM] =
{
	0x00, // 0
	0x00, // 1
	0x00, // 2
	0x00, // 3
	0x00, // 4
};

// default constructor
Settings::Settings()
{
	_isEdit = false;
} //Settings

// default destructor
Settings::~Settings()
{
} //~Settings

bool Settings::init(void)
{
	for(uint8_t i = 0; i < SETTINGS_NUM + 1; i++)
	{
		settings[i] = eeprom_read_byte(&settingsEE[i]);		
	}
	if(settings[SETTINGS_NUM] != crc8(settings, SETTINGS_NUM))	
	{
		for(uint8_t i = 0; i < SETTINGS_NUM; i++)
		{
			eeprom_update_byte(&settingsEE[i], settingsDefault[i]);
			settings[i] = settingsDefault[i];
		}
		eeprom_update_byte(&settingsEE[SETTINGS_NUM], crc8(settingsDefault, SETTINGS_NUM));
		return false;
	}
	return true;
}

void Settings::set(SETTING setting, uint8_t value)
{
	if(settings[setting] != value)
	{
		settings[setting] = value;
		_isEdit = true;
	}
}

uint8_t Settings::get(SETTING setting)
{
	return settings[setting];
}

void Settings::save(void)
{
	for(uint8_t i = 0; i < SETTINGS_NUM; i++)
	{
		eeprom_update_byte(&settingsEE[i], settings[i]);		
	}
	eeprom_update_byte(&settingsEE[SETTINGS_NUM], crc8(settings, SETTINGS_NUM));
	_isEdit = false;
}

/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
uint8_t Settings::crc8(const uint8_t *pcBlock, uint16_t len)
{
    uint8_t crc = 0xFF;
    uint16_t i;

    while (len--)
    {
        crc ^= *pcBlock++;

        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }

    return crc;
}

bool Settings::isEdit(void)
{
	return _isEdit;
}