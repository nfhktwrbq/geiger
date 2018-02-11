#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <inttypes.h>
#include "HighSuply.h"

class Counter
{
	private:
		uint32_t countSpeed;
		static const uint32_t SECOND = 62500;
		static const uint32_t HIGH_SUPLY_ADJUST_PERIOD = SECOND * 10;
		HighSuply * highSuply;
	public:
		Counter();
		Counter(HighSuply * highSuply);
		~Counter();
		
		uint32_t getCountSpeed(void);
		void proc(void);
		void procCounter(void);
		void procHighSuply(void);
};

#endif