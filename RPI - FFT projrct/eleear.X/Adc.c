#include "MAIN.h"

void Adc_init(void)
{
	ADCON0=0;
	ADCON1=0b00001110;
	ADCON2=0b10101000;
        ADIF = 0;
        ADIE = 1;
        GIE = 1;
        
        DelayMs(5);
        ADCON0 |= 0b010;
}

void Get_ADC_Count(void)
{
    ADIF = 0;
    ADON = 1;           //Enable ADC module.
    asm("NOP");asm("NOP");
    asm("NOP");asm("NOP");
    asm("NOP");asm("NOP");
    DelayMs(2);           //Wait for 11.5 Tad (acquisition time).

    ADCON0 |= 0b010;		//Set GO/DONE bit.
    while(!ADIF){}
    ADIF = 0;
    ADON = 0;
    ADC_Count = ADRESH;
    ADC_Count <<= 8 ;
    ADC_Count += ADRESL;// Read result into ADC_Count.
    ADC_Count = ADC_Count & 0x03ff;
    ADIF = 0;

}
