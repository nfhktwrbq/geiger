/**
@file
Contains the LiquidLine class definition.
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

void print_me(uintptr_t address) {
	return;
	address = address;
}


bool LiquidLine::attach_function(uint8_t number, void (*function)(void)) {
	print_me((uintptr_t)this);
	if (number <= MAX_FUNCTIONS) {
		_function[number - 1] = function;
		_focusable = true;
		return true;
	} else {
		return false;
	}
}

bool LiquidLine::set_focusPosition(Position position, uint8_t column, uint8_t row) {
	print_me((uintptr_t)this);
	if (position <= Position::CUSTOM) {
		_focusPosition = position;
		_focusColumn = column;
		_focusRow = row;
		if (_focusPosition == Position::CUSTOM) {
		}
		return true;
	} else {
		return false;
	}
}

bool LiquidLine::set_asGlyph(uint8_t number) {
	uint8_t index = number - 1;
	if ( (index < MAX_VARIABLES) && (_variableType[index] == DataType::UINT8_T) ) {
		_variableType[index] = DataType::GLYPH;
		return true;
	} else {
		return false;
	}
}

bool LiquidLine::set_asProgmem(uint8_t number) {
	uint8_t index = number - 1;
	if ((index < MAX_VARIABLES) && (_variableType[index] == DataType::CONST_CHAR_PTR)) {
		_variableType[index] = DataType::PROG_CONST_CHAR_PTR;
		return true;
	}
	else {
			return false;
	}
}

void LiquidLine::print(DisplayClass *p_liquidCrystal, bool isFocused) {
	p_liquidCrystal->setCursor(_column, _row);
	for (uint8_t v = 0; v < MAX_VARIABLES; v++) {
		print_variable(p_liquidCrystal, v);
	}

	if (isFocused) {
		switch (_focusPosition) {
		case Position::RIGHT: {
			p_liquidCrystal->write((uint8_t)15);
			break;
		} //case RIGHT
		case Position::LEFT: {
			p_liquidCrystal->setCursor(_column - 1, _row);
			p_liquidCrystal->write((uint8_t)14);
			break;
		} //case LEFT
		case Position::CUSTOM: {
			p_liquidCrystal->setCursor(_focusColumn, _focusRow);
			p_liquidCrystal->write((uint8_t)13);
			break;
		} //case CUSTOM
		default: {
			_focusPosition = Position::NORMAL;
			p_liquidCrystal->write((uint8_t)15);
			break;
		} //default
		} //switch (_focusPosition)
	} else {
		//p_liquidCrystal->print(NOTHING);
	}
}

void LiquidLine::print_variable(DisplayClass *p_liquidCrystal, uint8_t number) {
	switch (_variableType[number]) {

	case DataType::CONST_CHAR_PTR: {
		const char* variable = reinterpret_cast<const char*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case CONST_CHAR_PTR
	case DataType::CHAR_PTR: {
		char* variable = *reinterpret_cast<char**>( const_cast<void*>(_variable[number]) );
		p_liquidCrystal->print(variable);
		break;
	} //case CHAR_PTR
	case DataType::CHAR: {
		const char variable = *static_cast<const char*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case CHAR

	case DataType::INT8_T: {
		const int8_t variable = *static_cast<const int8_t*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case INT8_T
	case DataType::UINT8_T: {
		const uint8_t variable = *static_cast<const uint8_t*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case UINT8_T

	case DataType::INT16_T: {
		const int16_t variable = *static_cast<const int16_t*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case INT16_T
	case DataType::UINT16_T: {
		const uint16_t variable = *static_cast<const uint16_t*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case UINT16_T

	case DataType::INT32_T: {
		const int32_t variable = *static_cast<const int32_t*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case INT32_T
	case DataType::UINT32_T: {
		const uint32_t variable = *static_cast<const uint32_t*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case UINT32_T

	case DataType::FLOAT: {
		const float variable = *static_cast<const float*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case FLOAT

	case DataType::BOOL: {
		const bool variable = *static_cast<const bool*>(_variable[number]);
		p_liquidCrystal->print(variable);
		break;
	} //case BOOL

	case DataType::GLYPH: {
		const uint8_t variable = *static_cast<const uint8_t*>(_variable[number]);
		p_liquidCrystal->write((uint8_t)variable);
		break;
	} //case BOOL

	case DataType::PROG_CONST_CHAR_PTR: {
		const char* variable = reinterpret_cast<const char*>(_variable[number]);
		volatile const int len = strlen_P(variable);
		char buffer[len];
		for (uint8_t i = 0; i < len; i++) {
			buffer[i] = pgm_read_byte_near(variable + i);
		}
		buffer[len] = '\0';
		p_liquidCrystal->print(buffer);
		break;
	} //case PROG_CONST_CHAR_PTR

	default: { break; }

	} //switch (_variableType)
}

bool LiquidLine::call_function(uint8_t number) const {
	if (_function[number - 1]) {
		(*_function[number - 1])();
		return true;
	} else {
		return false;
	}
}
