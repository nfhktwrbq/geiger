/* 
* GPIO.h
*
* Created: 19.01.20116 14:24:56
* Author: a.tarletskiy
*/


#ifndef __TIMER_H__
#define __TIMER_H__

#include <inttypes.h>
#include <avr/io.h>

enum  COMPARE_OUTPUT_8
{
	CO_FAST_PWM_OCnA = 0x80,
	CO_FAST_PWM_OCnA_INVERTING = 0xC0,
	CO_FAST_PWM_OCnB = 0x20,
	CO_FAST_PWM_OCnB_INVERTING = 0x30,
};

enum WAVE_FORM_GENERATION_8
{
	WG_NORMAL = 0,
	WG_PWM_PC_1 = 1,
	WG_CTC = 2,
	WG_FAST_PWM_1 = 3,
	WG_PWM_PC_2 = 5,
	WG_FAST_PWM_2 = 7,
};

enum CLOCK_SELECTION_8
{
	CS_1PR = 1,
	
};

typedef COMPARE_OUTPUT_8 COMPARE_OUTPUT_16;
// enum  COMPARE_OUTPUT_16
// {

// };
enum WAVE_FORM_GENERATION_16
{
	WG_FAST_PWM_9BIT = 0x06,
};

typedef CLOCK_SELECTION_8 CLOCK_SELECTION_16;
// enum CLOCK_SELECTION_16
// {
	
	
// };

enum INTERRUPT
{
	INT_OVERFLOW = 0x01,
	
};
	
enum INTERRUPT_FLAG
{
	

};





template <typename T, typename CO,  typename WG,  typename CS, typename INT,  typename INT_F>
		 
//		+-----------+-----------+-----------+-----------+
//		|			|	8_0		|	16_1	|	8_2		|
//		+-----------+-----------+-----------+-----------+
//		|	AREG1	|	----	|	TCCRC	|	ASSR	|
//		+-----------+-----------+-----------+-----------+
//		|	AREG2	|	GTCCR	|	ICR		|	GTCCR	|
//		+-----------+-----------+-----------+-----------+		

class Timer
{
//variables
	private:
		volatile uint8_t * TCCRA;
		volatile uint8_t * TCCRB;
		volatile T * TCNT;
		volatile T * OCRA;
		volatile T * OCRB;
		volatile uint8_t * TIMSK;
		volatile uint8_t * TIFR;
		volatile uint8_t * AREG1;
		volatile T * AREG2;
	public:
		typedef T U_TYPE;
		typedef CO COMPARE_OUTPUT_TYPE;
		typedef WG WAVE_FORM_GENERATION_TYPE;
		typedef CS CLOCK_SELECTION_TYPE;
		
//functions
	public:
		Timer(volatile uint8_t * TCCRA, volatile uint8_t * TCCRB, volatile T * TCNT, volatile T * OCRA, volatile T * OCRB, volatile uint8_t * TIMSK, volatile uint8_t * TIFR, volatile uint8_t * AREG1, volatile T * AREG2) : 
		TCCRA(TCCRA), TCCRB(TCCRB), TCNT(TCNT), OCRA(OCRA), OCRB(OCRB), TIMSK(TIMSK), TIFR(TIFR), AREG1(AREG1),  AREG2( AREG2)
		{
		}
		
		~Timer()
		{
		}
				
		void setCompareOutputMode(CO mode)
		{
			*TCCRA &= 0x0f;
			*TCCRA |= (mode & 0xf0);
		}		
		
		uint8_t getCompareOutputMode(void)
		{
			return *TCCRA;
		}

		void setWaveformGenerationMode(WG mode)
		{
			*TCCRA &= 0xfc;
			*TCCRB &= 0xe7;
			*TCCRA |= (mode & 0x03);
			*TCCRB |= ((mode  & 0x0c) << 1);
		}

		uint8_t getWaveformGenerationMode(void)
		{
			return (((*TCCRB & 0x18) >> 1) | (*TCCRA & 0x03));
		}

		void setClockSelection(CS mode)
		{
			*TCCRB &= 0xf8;
			*TCCRB |= (mode & 0x07);			
		}
		
		T getTimerCounter(void)
		{
			return *TCNT;
		}

		void setTimerCounter(T tc)
		{
			*TCNT = tc;
		}

		T getOutputCompareA(void)
		{
			return *OCRA;
		}

		void setOutputCompareA(T oc) 
		{
			*OCRA = oc;			
		}

		T getOutputCompareB(void)
		{
			return *OCRB;
		}

		void setOutputCompareB(T oc)
		{
			*OCRB = oc;
		}

		void enableInterrupt(bool en)
		{			
			if(en)
			{
				*TIMSK |= 0x20;
			}
			else
			{
				*TIMSK = 0;
			}
		}

		void setInterrupt(INT mode)
		{
			*TIMSK |= mode;
		}
		
		uint8_t getInterrupt(void)
		{
			return *TIMSK;
		}

		void setInterruptFlag(INT_F flag)
		{
			*TIFR |= flag;
		}

		uint8_t getInterruptFlag(void) 
		{
			return *TIFR;
		}
		
		void setAREG1(uint8_t mode)
		{
			*AREG1 = mode;			
		} 
		
		uint8_t getAREG1(void)
		{
			return *AREG1;
		}

		void setAREG2(T mode)
		{
			*AREG2 = mode;
		}

		T getAREG2(void)
		{
			return *AREG2;
		}
	private:
		Timer( const Timer &c );
		Timer& operator=( const Timer &c );
}; //Timer

typedef Timer<uint8_t, COMPARE_OUTPUT_8,  WAVE_FORM_GENERATION_8,  CLOCK_SELECTION_8, INTERRUPT,  INTERRUPT_FLAG> Timer8;
typedef Timer<uint16_t, COMPARE_OUTPUT_16,  WAVE_FORM_GENERATION_16,  CLOCK_SELECTION_16, INTERRUPT,  INTERRUPT_FLAG> Timer16;

#endif //__TIMER_H__
