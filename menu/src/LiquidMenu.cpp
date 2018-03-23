/**
@file
Contains the LiquidMenu class definition.
*/

/*
The MIT License (MIT)

Copyright (c) 2016 Vasil Kalchev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "LiquidMenu.h"


const uint8_t DIVISION_LINE_LENGTH = 40; ///< Sets the length of the division line.

LiquidMenu::LiquidMenu(DisplayClass &liquidCrystal, uint8_t startingScreen)
  : _p_liquidCrystal(&liquidCrystal), _screenCount(0),
    _currentScreen(startingScreen - 1) {
#ifndef I2C
  _p_liquidCrystal->createChar(5, rightFocus);
  _p_liquidCrystal->createChar(4, leftFocus);
  _p_liquidCrystal->createChar(3, customFocus);
#endif
}

LiquidMenu::LiquidMenu(DisplayClass &liquidCrystal, LiquidScreen &liquidScreen,
                       uint8_t startingScreen)
  : LiquidMenu(liquidCrystal, startingScreen) {
  add_screen(liquidScreen);
}

LiquidMenu::LiquidMenu(DisplayClass &liquidCrystal, LiquidScreen &liquidScreen1,
                       LiquidScreen &liquidScreen2, uint8_t startingScreen)
  : LiquidMenu(liquidCrystal, liquidScreen1, startingScreen) {
  add_screen(liquidScreen2);
}

LiquidMenu::LiquidMenu(DisplayClass &liquidCrystal, LiquidScreen &liquidScreen1,
                       LiquidScreen &liquidScreen2, LiquidScreen &liquidScreen3,
                       uint8_t startingScreen)
  : LiquidMenu(liquidCrystal, liquidScreen1, liquidScreen2, startingScreen) {
  add_screen(liquidScreen3);
}

LiquidMenu::LiquidMenu(DisplayClass &liquidCrystal, LiquidScreen &liquidScreen1,
                       LiquidScreen &liquidScreen2, LiquidScreen &liquidScreen3,
                       LiquidScreen &liquidScreen4, uint8_t startingScreen)
  : LiquidMenu(liquidCrystal, liquidScreen1, liquidScreen2, liquidScreen3,
               startingScreen) {
  add_screen(liquidScreen4);
}

bool LiquidMenu::add_screen(LiquidScreen &liquidScreen) {
  print_me((uintptr_t)this);
  if (_screenCount < MAX_SCREENS) {
    _p_liquidScreen[_screenCount] = &liquidScreen;
    _screenCount++;
    return true;
  }
  return false;
}

void LiquidMenu::next_screen() {
  _p_liquidCrystal->clear();
  do {
    if (_currentScreen < _screenCount - 1)  {
      _currentScreen++;
    } else {
      _currentScreen = 0;
    }
  } while (_p_liquidScreen[_currentScreen]->_hidden == true);
  update();
}

void LiquidMenu::operator++() {
  next_screen();
}

void LiquidMenu::operator++(int) {
  next_screen();
}

void LiquidMenu::previous_screen() {
  _p_liquidCrystal->clear();
  do {
    if (_currentScreen > 0) {
      _currentScreen--;
    } else {
      _currentScreen = _screenCount - 1;
    }
  } while (_p_liquidScreen[_currentScreen]->_hidden == true);
  update();
}

void LiquidMenu::operator--() {
  previous_screen();
}

void LiquidMenu::operator--(int) {
  previous_screen();
}

bool LiquidMenu::change_screen(uint8_t number) {
  uint8_t index = number - 1;
  if (index <= _screenCount) {
    _p_liquidCrystal->clear();
    _currentScreen = index;

    update();
    return true;
  } else {
    return false;
  }
}

bool LiquidMenu::change_screen(LiquidScreen &p_liquidScreen) {
  // _p_liquidMenu[_currentMenu]->_p_liquidCrystal->clear();
  for (uint8_t s = 0; s < _screenCount; s++) {
    _p_liquidCrystal->clear();
    if ((uintptr_t)&p_liquidScreen == (uintptr_t) & (*_p_liquidScreen[s])) {
      _currentScreen = s;
      update();
      return true;
    }
  }
  return false;
}

bool LiquidMenu::operator=(uint8_t number) {
  return change_screen(number);
}

bool LiquidMenu::operator=(LiquidScreen &p_liquidScreen) {
  return change_screen(p_liquidScreen);
}

void LiquidMenu::switch_focus(bool forward) {
  _p_liquidCrystal->clear();
  _p_liquidScreen[_currentScreen]->switch_focus(forward);
  update();
}

bool LiquidMenu::set_focusPosition(Position position) {
  print_me((uintptr_t)this);
  if (position == Position::CUSTOM) {
    DEBUGLN(F("Can't set a custom focus position for the whole menu at once"));
    return false;
  } else {
    for (uint8_t s = 0; s < _screenCount; s++) {
      _p_liquidScreen[s]->set_focusPosition(position);
    }
    return true;
  }
}

bool LiquidMenu::set_focusSymbol(Position position, uint8_t symbol[8]) {
  switch (position) {
  case Position::RIGHT_EDGE: {
    _p_liquidCrystal->createChar(5, symbol);
    break;
  } //case RIGHT
  case Position::RIGHT: {
    _p_liquidCrystal->createChar(5, symbol);
    break;
  } //case RIGHT
  case Position::LEFT: {
    _p_liquidCrystal->createChar(4, symbol);
    break;
  } //case LEFT
  case Position::CUSTOM: {
    _p_liquidCrystal->createChar(3, symbol);
    break;
  } //case CUSTOM
  default: {
    return false;
  } //default
  } //switch (position)
  return true;
}

bool LiquidMenu::call_function(uint8_t number) const {
  bool returnValue = _p_liquidScreen[_currentScreen]->call_function(number);
  update();
  return returnValue;
}

void LiquidMenu::update() const {
  logger.log(Logger::DEBUG_3, "Update\n");
  //_p_liquidCrystal->clear();
  softUpdate();
}

void LiquidMenu::softUpdate() const {  
  _p_liquidScreen[_currentScreen]->print(_p_liquidCrystal); 
}

void LiquidMenu::init() const {
  _p_liquidCrystal->createChar(5, rightFocus);
  _p_liquidCrystal->createChar(4, leftFocus);
  _p_liquidCrystal->createChar(3, customFocus);
}
