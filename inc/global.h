/*
 * global.h
 *
 * Created: 19.01.2018 14:59:10
 *  Author: a.tarletskiy
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "Logger.h"

extern uint8_t spaceSymbol[8];

extern uint8_t rightFocus[8];

/// The focus glyph shown on the left.
extern uint8_t leftFocus[8];

/// The focus glyph shown when custom focus is set.
extern uint8_t customFocus[8];


extern Logger logger;

#define DEFAULT_COUNTER_VOLTAGE 400

//Buttons
#define LONG_PRESS_TIMEOUT 60000
#define BAT_LEVEL_PERCENT_COEF 8
#define BAT_LEVEL_EMPTY_TRESHOLD 200
#define BAT_LEVEL_FULL_TRESHOLD 1023


#endif /* GLOBAL_H_ */