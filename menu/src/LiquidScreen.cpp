/**
@file
Contains the LiquidScreen class definition.
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

LiquidScreen::LiquidScreen()
	: _lineCount(0), _focus(0), _hidden(false), _offset(0) {}

LiquidScreen::LiquidScreen(LiquidLine &liquidLine)
	: LiquidScreen() {
	add_line(liquidLine);
}

LiquidScreen::LiquidScreen(LiquidLine &liquidLine1, LiquidLine &liquidLine2)
	: LiquidScreen(liquidLine1) {
	add_line(liquidLine2);
}

LiquidScreen::LiquidScreen(LiquidLine &liquidLine1, LiquidLine &liquidLine2,
                           LiquidLine &liquidLine3)
	: LiquidScreen(liquidLine1, liquidLine2) {
	add_line(liquidLine3);
}

LiquidScreen::LiquidScreen(LiquidLine &liquidLine1, LiquidLine &liquidLine2,
                           LiquidLine &liquidLine3, LiquidLine &liquidLine4)
	: LiquidScreen(liquidLine1, liquidLine2, liquidLine3) {
	add_line(liquidLine4);
}

bool LiquidScreen::add_line(LiquidLine &liquidLine) {
	print_me((uintptr_t)this);
	if (_lineCount < MAX_LINES) {
		_p_liquidLine[_lineCount] = &liquidLine;
		_lineCount++;
		//_focus++;
		_focus = 0;
		return true;
	}
	return false;
}

bool LiquidScreen::set_focusPosition(Position position) {
	print_me((uintptr_t)this);
	if (position == Position::CUSTOM) {
		return false;
	} else {
		for (uint8_t l = 0; l < _lineCount; l++) {
			_p_liquidLine[l]->set_focusPosition(position);
		}
		return true;
	}
}

void LiquidScreen::hide(bool hide) {
	_hidden = hide;
}

void LiquidScreen::print(DisplayClass *p_liquidCrystal){
	if(_focus  >= (_offset + LINES_PER_SCREEN))
	{
		_offset++;
	}	
	if(_focus < _offset)
	{
		_offset--;
	}
	logger.log(Logger::DEBUG_3, "Offset = %u, focus = %u\n", _offset, _focus);

	for (uint8_t l = 0; l < _lineCount; l++) {
		bool focus = true;
		if (_focus != l) {
			focus = false;
		} else {
		}
		logger.log(Logger::DEBUG_3, "LiquidScreen print:\n");
		_p_liquidLine[l]->print(p_liquidCrystal, focus, _offset);
	}
}

void LiquidScreen::switch_focus(bool forward) {
	print_me((uintptr_t)this);
	//do {
		if (forward) {
			if (_focus < _lineCount - 1) {
				_focus++;
				if (_focus == _lineCount) {
					//break;
				}
			} else {
				//_focus = 0;
			}
		} else { //else (forward)
			if (_focus == 0) {
				//_focus = _lineCount;
				//break;
			} else {
				_focus--;
			}
		} //else (forward)
	//} while (_p_liquidLine[_focus]->_focusable == false);
}

bool LiquidScreen::call_function(uint8_t number) const {
	if (_focus != _lineCount) {
		return _p_liquidLine[_focus]->call_function(number);
	}
	return false;
}

void LiquidScreen::set_focus(uint8_t focus)
{
	_focus = focus;
	logger.log(Logger::DEBUG_1, "LiquidScreen print:\n");
}