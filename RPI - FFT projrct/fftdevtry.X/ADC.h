/******************************************************************
* Driver for interfacing the ADC module in dsPIC
* Debraj Deb, Bangalore, India.	
* debrajdeb[AT]yahoo.com
******************************************************************/
#ifndef		_ADC_HEADER
#define		_ADC_HEADER

#include "p30fxxxx.h"
#include "fft.h"
#include "dsp.h"

#define		BUFFER_FULL	1
#define		BUFFER_EMPTY	0

typedef struct ADC_Result
{
	int ADCBuffer[FFT_BLOCK_LENGTH];
	unsigned char Counter;
	unsigned char Buffer_State;
}ADC_Result;

#define		DISABLE_ADC_INTERRUPT()			\
{											\
	IEC0bits.ADIE = 0;						\
}											\

#define		ENABLE_ADC_INTERRUPT()			\
{											\
	IEC0bits.ADIE = 1;						\
}											\

#define		DISABLE_ADC_MODULE()			\
{											\
	ADCON1bits.ADON = 0;					\
}											\

#define		ENABLE_ADC_MODULE()				\
{											\
	ADCON1bits.ADON = 1;					\
}											\

//Functions and Variables with Global Scope:
void __attribute__((__interrupt__)) _ADCInterrupt(void);


#define	TIMER_3_Reload		((DESIREDMIPS/(SAMPLING_RATE)) - 1)

#define	START_TIMER_3()				\
{									\
	T3CONbits.TON = 1;				\
}									\

#define	STOP_TIMER_3()				\
{									\
	T3CONbits.TON = 0;				\
}									\

void Init_Timer3(void);
void Init_ADC(void);

extern ADC_Result Converted_Data;

#endif

