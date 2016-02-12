/* 
 * File:   main.c
 * Author: Shreya V Deodhar
 *
 * Created on March 23, 2015, 5:02 PM
 */

#include "MAIN.h"

__CONFIG(1, IESODIS & FCMDIS & RCIO);
__CONFIG(2,BORDIS & PWRTDIS & WDTDIS);
__CONFIG(3,MCLRDIS & LPT1DIS & PBDIGITAL & CCP2RC1);
__CONFIG(4,XINSTDIS & DEBUGDIS & LVPEN & STVRDIS);

__CONFIG(5,UNPROTECT);
__CONFIG(6,WRTEN);
__CONFIG(7,TRPB);


void Init_stat_isr(void)
{
    INT0IF = 0;
    INT0IE = 1;
    INTEDG0 = 1;
}

void timer0_init(void)
{
	T0CON=0b00001000;
	TMR0H=0XF8;
	TMR0L=0X30;
	INTCONbits.GIE=1;
        INTCONbits.PEIE=1;
	INTCONbits.TMR0IE=1;
        T0CON|=0b10000000;
}

void main(void)
{
    int8u dec_key;

    OSCTUNE = 0;
    OSCCON = 0b01100011;//0b01110011;
    //TRISA = 0b11000001;
    //TRISE = 0;
    //TRISC = 0b0111;

    TRISA=0b11000001;
    //TRISAbits.RA6=1;
    //TRISAbits.RA7=1;
    TRISC=0b0111;
    TRISE=0b000000000;
    TRISB7=0;    TRISD3=0;
    TRISD2=0;    TRISD1=0;
    TRISD0=1;    TRISB0=0;
    TRISB1=0;    TRISD4=0;
    TRISD5=0;    TRISD6=0;      TRISD7=0;

    USARTinit();
    lcd_init();
    Initcustom_char();
    cur_gain = 0.25;
    /*strncpy( Lcd_LINE1 , Lcd_L1 , 16 ) ;
    strncpy( Lcd_LINE2 , Lcd_L2 , 16 ) ;
    Display();
    strncpy( Lcd_LINE1 , Lcd_L3 , 16 ) ;
    strncpy( Lcd_LINE2 , Lcd_L4 , 16 ) ;
    Display();*/

    //while(1);
    Adc_init();
    Init_i2c();
    Init_stat_isr();
    Init_PWM();
    dutyvolt = 0; dutycurrent = 0;
    Set_PWM_Duty();
    /*while(1)
    {
        Display();
        USARTWriteChar('U');
        USARTWriteString(" Hi All\n\r");
        dec_key = getkey();dispnum( dec_key  ,1,2);
        Get_ADC_Count();   dispnum( ADC_Count,5,7);
        DelayMs(1000);
    }*/

    FFT_ready_flag = 0;
    while(1)
    {
        if(FFT_ready_flag)
        {
            INT0IE = 0;

            Read_FFT(0,128);
            FFT_ready_flag = 0;

            Calc_percentageFull();
            Disp_Mill_fill();

            INT0IE = 1;
        }
    }
}

void interrupt isr(void)
{
  if (TMR0IE && TMR0IF)			// Overflow interrupt
      TMR0IF = 0;			// Clear T0IF every time

  if (TMR1IF && TMR1IE)
  {			// Gate interrupt
	TMR1IF = 0;
        TMR0 = 0;
        TMR1ON = 0;
       // raw_reading = TMR1L + (unsigned int)(TMR1H << 8);
        TMR1L   = 0x00;					// Reset Timer1
        TMR1H   = 0x00;					//   "     "
        TMR1ON  = 1;					// Restart Timer1
        //TMR0    = 0xFE;
        TMR0    = 0;
        //T1GGO   = 1;
  }
  
  if(INT0IE && INT0IF)
  {
      INT0IF = 0;
      FFT_ready_flag = 1;
  }
}
