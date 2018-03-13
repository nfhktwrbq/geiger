#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "GPIO.h"


class Logger
{
public:
	enum LEVEL : uint8_t
	{
		CLEAR = 0x00,
		CRITICAL = 0x01,
		INFO = 0x02,
		WARNING = 0x04,
		DEBUG_1 = 0x08,
		DEBUG_2 = 0x10,
		DEBUG_3 = 0x20,
		DEBUG_4 = 0x40,
		DEBUG_5 = 0x80,
	};
private:
	const static size_t MAX_STRING_LEN = 200;
	LEVEL level;
public:
	Logger(uint32_t rate);
	~Logger();

	void log(LEVEL level, const char * format, ...);
	void setLevel(LEVEL level);
	void clearLevel(LEVEL level);
	uint8_t getLevel(void);

private:
	Logger( const Logger &c );
	Logger& operator=( const Logger &c );
	
};

#endif