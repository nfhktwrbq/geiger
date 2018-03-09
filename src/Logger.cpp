#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>
#include "Logger.h"



Logger::Logger(uint32_t rate)
{
	this->level = CLEAR;
	UBRR0 = (F_CPU / 16 / rate - 1);
	UCSR0B = (1 << TXEN0);
	UCSR0C = (3 << UCSZ00);
}

inline Logger::LEVEL operator ~(Logger::LEVEL a)
{
    return static_cast<Logger::LEVEL>(~(static_cast<int>(a)));
}

inline Logger::LEVEL operator |(Logger::LEVEL a, Logger::LEVEL b)
{
    return static_cast<Logger::LEVEL>(static_cast<int>(a) | static_cast<int>(b));
}

inline Logger::LEVEL operator &(Logger::LEVEL a, Logger::LEVEL b)
{
    return static_cast<Logger::LEVEL>(static_cast<int>(a) & static_cast<int>(b));
}

inline Logger::LEVEL& operator |=(Logger::LEVEL& a, Logger::LEVEL b)
{
    return a= a |b;
}

inline Logger::LEVEL& operator &=(Logger::LEVEL& a, Logger::LEVEL b)
{
    return a= a &b;
}

Logger::~Logger()
{

}

void Logger::log(LEVEL level, const char * format, ...)
{
	char str[MAX_STRING_LEN];
	if(this->level & level)
	{
		va_list args;
		va_start(args, format);

		str[0] = '(';
		str[1] = 0x30 + level;
		str[2] = ')';		
		vsnprintf(&str[3], MAX_STRING_LEN - 3, format, args);		
	
		for(uint8_t i = 0; i < MAX_STRING_LEN && str[i]; i++)
		{
			while(!(UCSR0A & (1 << UDRE0)))
			{}
			UDR0 = str[i];
		}
		va_end(args);
	}
}

void Logger::setLevel(LEVEL level)
{
	this->level |= level;
}

void Logger::clearLevel(LEVEL level)
{
	this->level &= ~level;
}

uint8_t Logger::getLevel(void)
{
	return this->level;
}


	

