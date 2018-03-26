/*
 * geiger.cpp
 *
 * Created: 18.01.2018 8:40:33
 * Author : a.tarletskiy
 */ 

#include <util/delay.h>
#include <inttypes.h>

#include "GPIO.h"
#include "Timer.h"
#include "HD44780.h"
#include "portability.h"
#include "AnalogToDigital.h"
#include "gvars.h"
#include "global.h"
#include "PulseWidthModulation.h"
#include "HighSuply.h"
#include "LiquidMenu.h"
#include "MT10S.h"
#include "Counter.h"
#include "Buttons.h"
#include "Logger.h"
#include "Settings.h"

#define RENTGEN_KOEFF 10
#define SIEVERT_KOEFF (RENTGEN_KOEFF * 10)

#define STRING_LENGTH 11

const char metricPrefix[] = {'n', 'u', 'm', ' '};

enum UNIT_TYPE
{
	NONE,
	RENTGEN,
	SIEVERT,
	COUNTS,
	NUM_OF_TYPES,
};

enum EXPO_STATE
{
	EXPO_NONE,
	EXPO_START,
	EXPO_EXEC,
};

struct DosePower
{
	uint32_t value;
	char unit[STRING_LENGTH];
};

void buttonTest(Buttons & buttons, Buzzer & buzzer);
void expoExecute(void);
void getDosePower(DosePower &dosePower, uint8_t unitType, uint32_t expoCounter, uint32_t expoTime);
uint8_t getMetricPrefixIndex(uint32_t val);
void expoProc(void);
void searchProc(void);
void buttonsProc(void);
void proc(void);
void changeExpoUnitType(void);
void changeSearchUnitType(void);
void switchBuzzer(void);
void changeExpoTime(void);
void resetExpoTime(void);
void changeLedPWM(void);
void gotoInfo(void);
void batLevelProc(bool isInit = false);

char unitSymbols[] = "NRSC";

char gSearchString[STRING_LENGTH] = "";
char gExpoString[STRING_LENGTH] = "PUSH ENTER";
uint8_t gExpoState = EXPO_NONE;

uint8_t gExpoTimeSecond = 10;
uint32_t gExpoTime = gExpoTimeSecond * Counter::SECOND;
uint8_t gExpoUnitType = RENTGEN;
uint8_t gSearchUnitType = SIEVERT;
char gExpoUnitTypeSymbol = unitSymbols[gExpoUnitType];
char gSearchUnitTypeSymbol = unitSymbols[gSearchUnitType];
char gBuzzer = 'N';
uint8_t gLEDPWM;
uint8_t gBatteryLevel = 0;
bool startWithoutBat = false;

GPIO * pio = &GPIO::Instance();

Settings settings;

MT10S lcd(pio, 16, 17, 18, 19, 23, 24);
//HD44780 lcd(pio, 16, 17, 18, 19, 23, 24);


Timer8 timer8_0(&TCCR0A, &TCCR0B, &TCNT0, &OCR0A, &OCR0B, &TIMSK0, &TIFR0, &GTCCR, &GTCCR);	
PulseWidthModulation8 pwmLCDLED(&timer8_0);
Timer16 timer16_1(&TCCR1A, &TCCR1B, &TCNT1, &OCR1A, &OCR1B, &TIMSK1, &TIFR1, &TCCR1C, &ICR1);
PulseWidthModulation16 pwmHV(&timer16_1);

Timer8 timer8_2(&TCCR2A, &TCCR2B, &TCNT2, &OCR2A, &OCR2B, &TIMSK2, &TIFR2, &ASSR, &GTCCR);	
AnalogToDigital adc(AnalogToDigital::AREF,0,AnalogToDigital::PR_128);

Buzzer buzzer(pio);
Buzzer buzzerStatus(pio);

HighSuply counterSupply(&pwmHV, &adc, AnalogToDigital::CH_3);

Counter c(&counterSupply, &buzzer);

Buttons buttons(pio, &c);

//--------------work-screen-------------------	
LiquidLine searchLine(0, 0, gSearchString);
LiquidLine expositionLine(0, 1, gExpoString);


LiquidScreen workScreen(searchLine, expositionLine);

//--------------settings-screen-------------------
LiquidLine lcdLedLine(0, 0, "LED", gLEDPWM, "    ");
LiquidLine expoUnitLine(0, 1, "EUNIT:", gExpoUnitTypeSymbol);
LiquidLine searchUnitLine(0, 2, "SUNIT:", gSearchUnitTypeSymbol);
LiquidLine buzzerLine(0, 3, "BUZZER:", gBuzzer);
LiquidLine expoTimeLine(0, 4, "ET: ", gExpoTimeSecond, "s");
LiquidLine infoLine(0, 5, "...INFO...");

LiquidScreen settingsScreen(lcdLedLine, expoUnitLine, searchUnitLine, buzzerLine);

//-------------info-screen-------------------------
LiquidLine headerInfoLine(0, 0, "COUNTER1.0");
LiquidLine batteryLevelLine(0, 1, "BAT:", gBatteryLevel, "%");

LiquidScreen infoScreen(headerInfoLine, batteryLevelLine);

LiquidMenu menu(lcd, workScreen, settingsScreen, infoScreen);	
	
int main(void)
{	
	logger.setLevel(Logger::DEBUG_3);
	settings.init();
	
	pio->pinMode(11,GPIO::OUTPUT);
	pio->pinMode(15,GPIO::OUTPUT);


	gExpoTimeSecond = settings.get(Settings::EXPO_TIME);
	gExpoUnitType = settings.get(Settings::EXPO_UNIT);
	gSearchUnitType = settings.get(Settings::SEARCH_UNIT);
	gBuzzer = settings.get(Settings::BUZZER);
	// if(gBuzzer == 'N')
	// {
	// 	buzzer.enable(false);
	// 	logger.log(Logger::DEBUG_3,"BUZZER_N=%c",gBuzzer);
	// }
	// else
	// {
	// 	ogger.log(Logger::DEBUG_3,"BUZZER_Y=%c",gBuzzer);
	// 	buzzer.enable(true);
	// }
	gLEDPWM = settings.get(Settings::LCD_LED_BRIGHT);
	gExpoUnitTypeSymbol = unitSymbols[gExpoUnitType];
	gSearchUnitTypeSymbol = unitSymbols[gSearchUnitType];
	
	settingsScreen.add_line(expoTimeLine);
	settingsScreen.add_line(infoLine);

	expositionLine.attach_function(1, expoExecute);
	lcdLedLine.attach_function(1, changeLedPWM);
	expoUnitLine.attach_function(1, changeExpoUnitType);
	searchUnitLine.attach_function(1, changeSearchUnitType);
	buzzerLine.attach_function(1, switchBuzzer);
	expoTimeLine.attach_function(1, changeExpoTime);
	expoTimeLine.attach_function(2, resetExpoTime);
	infoLine.attach_function(1, gotoInfo);
	
	lcd.init();


	timer8_0.setInterrupt(INT_OVERFLOW);
	pwmLCDLED.initPWM(CO_FAST_PWM_OCnB, WG_FAST_PWM_1, CS_1PR);	
	pwmLCDLED.setMaxPWMBorder(255);
	
	timer16_1.setInterrupt(INT_OVERFLOW);	
	pwmHV.initPWM(CO_FAST_PWM_OCnA, WG_FAST_PWM_9BIT, CS_1PR);

	pwmHV.setMaxPWMBorder(80);	
    adc.setChannel(AnalogToDigital::CH_3);	 
	
	buzzer.enable((gBuzzer == 'Y' ? true : false));		
	pwmLCDLED.setPWM(gLEDPWM);

	counter = &c;
	counter->init();

	menu.set_focusPosition(Position::RIGHT_EDGE);
	menu.set_focusSymbol(Position::RIGHT_EDGE, spaceSymbol);
	menu.set_focusSymbol(Position::RIGHT, spaceSymbol);
	menu.update();

	batLevelProc(true);
	batLevelProc(true);
	batLevelProc(true);
	batLevelProc(true);
	if(gBatteryLevel)
	{
		lcd.setCursor(0, 0);
		lcd.printf("INIT...");
		if(!counter->initHighVoltage())
		{
			lcd.setCursor(0, 0);
			lcd.printf("HV_ERROR");
			while(1);
		}	
	}
	else
	{
		lcd.setCursor(0, 0);
		lcd.printf("NO BAT!");
		_delay_ms(2000);
		lcd.clear();
		startWithoutBat = true;
	}

	menu.set_focusSymbol(Position::RIGHT_EDGE, spaceSymbol);
	menu.update();
    
    while(1) 
    {
		proc();
    }
}

void changeExpoUnitType(void)
{
	gExpoUnitType++;	
	if(gExpoUnitType >= NUM_OF_TYPES)
	{
		gExpoUnitType = NONE;
	}
	gExpoUnitTypeSymbol = unitSymbols[gExpoUnitType];
	settings.set(Settings::EXPO_UNIT, gExpoUnitType);
}

void changeSearchUnitType(void)
{
	gSearchUnitType++;
	gSearchUnitTypeSymbol = unitSymbols[gSearchUnitType];
	if(gSearchUnitType >= NUM_OF_TYPES)
	{
		gSearchUnitType = NONE;
	}
	gSearchUnitTypeSymbol = unitSymbols[gSearchUnitType];
	settings.set(Settings::SEARCH_UNIT, gSearchUnitType);
}

void changeExpoTime(void)
{
	gExpoTimeSecond += 10;
	gExpoTime = gExpoTimeSecond * Counter::SECOND;
	settings.set(Settings::EXPO_TIME, gExpoTimeSecond);
}

void resetExpoTime(void)
{
	gExpoTimeSecond = 0;
	settings.set(Settings::EXPO_TIME, gExpoTimeSecond);
}

void changeLedPWM(void)
{
	gLEDPWM += 32;
	pwmLCDLED.setPWM(gLEDPWM);
	settings.set(Settings::LCD_LED_BRIGHT, gLEDPWM);
}

void switchBuzzer(void)
{
	if(buzzer.isEnable())
	{
		buzzer.enable(false);
		settings.set(Settings::BUZZER, false);
		gBuzzer = 'N';
	}
	else
	{
		buzzer.enable(true);
		settings.set(Settings::BUZZER, true);
		gBuzzer = 'Y';
	}
}

void gotoInfo(void)
{
	menu.change_screen(infoScreen);
}

void expoExecute(void)
{
	gExpoState = EXPO_START;
	//logger.log(Logger::DEBUG_2, "Start expo\n");
}

void batLevelProc(bool isInit)
{
	static uint32_t timer = 0;
	uint16_t adcResultFromBat;
	if(startWithoutBat)
	{
		return;
	}
	if(counter->getTimer() - timer > Counter::SECOND || isInit)
	{
		timer = counter->getTimer();
	
		adc.setChannel(AnalogToDigital::CH_2);
		adcResultFromBat = adc.proc();
		//logger.log(Logger::DEBUG_3, "Result adc = %u", adcResultFromBat);
		if(adcResultFromBat <= BAT_LEVEL_EMPTY_TRESHOLD)
		{
			gBatteryLevel = 0;
			adc.setChannel(AnalogToDigital::CH_3);
			if(!isInit)
			{
				counter->enableHighVoltageAdjust(false);
				pwmHV.setPWM(0);
				lcd.setCursor(0, 0);
				lcd.print("BAT LOW ER");
				while(1);
			}
			return;
		}
		gBatteryLevel = (uint8_t)(100 * (adcResultFromBat - BAT_LEVEL_EMPTY_TRESHOLD)/(BAT_LEVEL_FULL_TRESHOLD - BAT_LEVEL_EMPTY_TRESHOLD));
		if(gBatteryLevel > 100)
		{
			gBatteryLevel = 100;
		}		
		if(gBatteryLevel < 10)
		{
			menu.set_focusSymbol(Position::RIGHT_EDGE, lowBatSymbol10);
		}
		if(gBatteryLevel < 5)
		{
			menu.set_focusSymbol(Position::RIGHT_EDGE, lowBatSymbol5);
		}
		adc.setChannel(AnalogToDigital::CH_3);
	}
}

void batLowLevelInfoShow(void)
{
	static uint32_t timer = 0;
	if(counter->getTimer() - timer > Counter::SECOND * 10)
	{
		timer = counter->getTimer();
		if(gBatteryLevel <= 10)
		{
			lcd.clear();
			lcd.printf("%u OF BAT", gBatteryLevel);
		}	
	}
}

void proc(void)
{
	static uint32_t t = 0;
	counter->proc();
	expoProc();	
	buttonsProc();
	batLevelProc();
	
 	if(counter->getTimer() - t > Counter::SECOND )
 	{
 		t = counter->getTimer();
 		searchProc();
 		menu.update();    	
		//logger.log(Logger::DEBUG_1, "UPDATE %s\n", gSearchString);
		//logger.log(Logger::DEBUG_2, "Expo state = %u\n", gExpoState);
	}
}

void buttonsProc(void)
{
	buttons.proc();
	if(buttons.getButtonClick(Buttons::BUTTON_LEFT))
	{
		menu.switch_focus(false);
		//logger.log(Logger::DEBUG_3, "Left click\n");
	}
	if(buttons.getButtonClick(Buttons::BUTTON_RIGHT))
	{
		 menu.switch_focus(true);
		// logger.log(Logger::DEBUG_3, "Right click\n");
	}
	if(buttons.getButtonClick(Buttons::BUTTON_CENTER))
	{
		 menu.call_function(1);
		 //logger.log(Logger::DEBUG_3, "Center click\n");
	}
	if(buttons.getButtonLongPress(Buttons::BUTTON_LEFT))
	{
		 menu.change_screen(workScreen);
		 if(settings.isEdit())
		 {
			settings.save();	 
		 }		 
		 menu.set_focusSymbol(Position::RIGHT_EDGE, spaceSymbol);
		 //logger.log(Logger::DEBUG_3, "Left lobg press\n");
	}
	if(buttons.getButtonLongPress(Buttons::BUTTON_RIGHT))
	{
		 menu.change_screen(settingsScreen);
		 menu.set_focusSymbol(Position::RIGHT_EDGE, customFocus);
		// logger.log(Logger::DEBUG_3, "Right long press\n");
	}
	if(buttons.getButtonLongPress(Buttons::BUTTON_CENTER))
	{
		 menu.call_function(2);
		 //logger.log(Logger::DEBUG_3, "Center long press\n");
	}
}

void searchProc(void)
{
	DosePower dosePower;
	getDosePower(dosePower, gSearchUnitType, counter->getCountSpeed(), Counter::SECOND);
	memset(gSearchString, 0, STRING_LENGTH);
	sprintf(gSearchString,"%4lu", dosePower.value);
	strcat(gSearchString, dosePower.unit);
}

void expoProc(void)
{
	static uint32_t expoTimer = 0;
	static uint32_t expoCounter = 0;
	static uint32_t timeGap = 0; 
	static uint8_t i = 1; 
	DosePower dosePower;
	switch(gExpoState)
	{
		case EXPO_NONE:
			getDosePower(dosePower, gExpoUnitType, expoCounter, gExpoTime);
			memset(gExpoString, 0, STRING_LENGTH);
			sprintf(gExpoString,"%4lu", dosePower.value);
			strcat(gExpoString, dosePower.unit);		
		break;
		case EXPO_START:
			expoTimer = counter->getTimer();
			expoCounter = counter->getCounter();
			timeGap = gExpoTime / (STRING_LENGTH);
			memset(gExpoString, 0, STRING_LENGTH);	
			gExpoState = EXPO_EXEC;
			i = 1;
			//logger.log(Logger::DEBUG_2, "expoTimer = %lu\n", expoTimer);
			///logger.log(Logger::DEBUG_2, "timeGap = %lu\n", timeGap);
			//logger.log(Logger::DEBUG_2, "Counter = %lu\n", expoCounter);		
		break;
		case EXPO_EXEC:
			if(counter->getTimer() - expoTimer > timeGap * i)
			{
				strncat(gExpoString, "*", STRING_LENGTH - strlen(gExpoString));
				//logger.log(Logger::DEBUG_2, "expo proc %u\n", i);
				i++;			
			}
			if(i > (STRING_LENGTH))
			{
				expoCounter = counter->getCounter() - expoCounter;
				gExpoState = EXPO_NONE;
				menu.update();
				//logger.log(Logger::DEBUG_2, "expo complete!\n");		
			}
		break;
	}
}

void getDosePower(DosePower &dosePower, uint8_t unitType, uint32_t expoCounter, uint32_t expoTime)
{
	uint32_t dp = (expoCounter * Counter::SECOND) / expoTime;
	uint8_t index = 0;
	uint8_t rank;
	memset(dosePower.unit, 0, STRING_LENGTH);
	strcpy(dosePower.unit, "   /h");
	switch(unitType)
	{
		case RENTGEN:
			dosePower.unit[2] = 'R';
			index = 1;
			dp = (uint32_t)(dp * RENTGEN_KOEFF);
		break;
		case SIEVERT:
			dosePower.unit[2] = 'S';
			dp *=  SIEVERT_KOEFF;
		break;
		case COUNTS:
			dosePower.unit[2] = 'C';
			dosePower.unit[4] = 's';
		break;
		case NONE:
			memset(dosePower.unit, 0, STRING_LENGTH);
			sprintf(dosePower.unit, "/%u", (uint16_t)(expoTime / Counter::SECOND) );
			dosePower.value = dp;
			return;
		break;
	}		
	rank = getMetricPrefixIndex(dp);
	index += rank;
	if(unitType != COUNTS)
	{
		dosePower.unit[1] = metricPrefix[index];
	}

	for(uint8_t i = 0; i < rank; i++)
	{
		dp /= 1000;
		logger.log(Logger::DEBUG_3, "Enter\n");

	}
	dosePower.value = dp;	
	logger.log(Logger::DEBUG_3, "Dose = %lu\n", dp);
}

uint8_t getMetricPrefixIndex(uint32_t val)
{
	uint8_t index = 0;
	if(val / 1000 > 9 && val / 1000 < 10000)
	{
		index = 1;
	}
	if(val / 1000000 > 9 && val / 1000000 < 100000)
	{
		index = 2;
	}
	return index;
}

void buttonTest(Buttons & buttons, Buzzer &buzzer)
{
	buttons.proc();
	if(buttons.getButtonLongPress(Buttons::BUTTON_LEFT))
	{
		buzzer.on();
		lcd.clear();
		lcd.setCursor(0,0);
	    lcd.printf("LONG LEFT");
	}

	if(buttons.getButtonLongPress(Buttons::BUTTON_CENTER))
	{
		buzzer.on();
		lcd.clear();
		lcd.setCursor(0,0);
	    lcd.printf("LONG CENTER");
	}

	if(buttons.getButtonLongPress(Buttons::BUTTON_RIGHT))
	{
		buzzer.on();
		lcd.clear();
		lcd.setCursor(0,0);
	    lcd.printf("LONG RIGHT");
	}

	if(buttons.getButtonClick(Buttons::BUTTON_LEFT))
	{
		buzzer.on();
		lcd.clear();
		lcd.setCursor(0,0);
	    lcd.printf("CLICK LEFT");
	}

	if(buttons.getButtonClick(Buttons::BUTTON_CENTER))
	{
		buzzer.on();
		lcd.clear();
		lcd.setCursor(0,0);
	    lcd.printf("CLICK CENTER");
	}

	if(buttons.getButtonClick(Buttons::BUTTON_RIGHT))
	{
		buzzer.on();
		lcd.clear();
		lcd.setCursor(0,0);
	    lcd.printf("CLICK RIGHT");
	}
}