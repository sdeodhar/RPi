/*
 * File:   main.c
 * Author: Admin
 *
 * Created on February 18, 2015, 4:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<libpic30.h>
//#include<p30f4011.h>
#include <p30Fxxxx.h>
#include <dsp.h>
#include "fft.h"
#include "ADC.h"

/******************************************************************************/
/* Configuration bits                                                         */
/******************************************************************************/
_FOSC(CSW_FSCM_OFF & FRC_PLL16); //Run this project using an external crystal
                                //routed via the PLL in 16x multiplier mode
                                //For the 7.3728 MHz crystal we will derive a
                                //throughput of 7.3728e+6*16/4 = 29.4 MIPS(Fcy)
                                //,~33.9 nanoseconds instruction cycle time(Tcy).
_FWDT(WDT_OFF);                 //Turn off the Watch-Dog Timer.
_FBORPOR(MCLR_EN & PWRT_OFF);   //Enable MCLR reset pin and turn off the
                                //power-up timers.
_FGS(CODE_PROT_OFF);            //Disable Code Protection

#define RS       LATEbits.LATE1      //There is no RW connection
#define EN       LATEbits.LATE0
#define d0       LATEbits.LATE2
#define d1       LATEbits.LATE3
#define d2       LATEbits.LATE4
#define d3       LATEbits.LATE5


/* Extern definitions */
extern fractcomplex sigCmpx[FFT_BLOCK_LENGTH] 		/* Typically, the input signal to an FFT  */
__attribute__ ((section (".ydata, data, ymemory"), 	/* routine is a complex array containing samples */
aligned (FFT_BLOCK_LENGTH * 2 *2)));      			/* of an input signal. For this example, */
													/* we will provide the input signal in an */
													/* array declared in Y-data space. */
/* Global Definitions */
#ifndef FFTTWIDCOEFFS_IN_PROGMEM
fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2] 	/* Declare Twiddle Factor array in X-space*/
__attribute__ ((section (".xbss, bss, xmemory"), aligned (FFT_BLOCK_LENGTH*2)));
#else
extern const fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2]	/* Twiddle Factor array in Program memory */
__attribute__ ((space(auto_psv), aligned (FFT_BLOCK_LENGTH*2)));
#endif

int FFT_Waveform[FFT_BLOCK_LENGTH];
	
const char Lcd_L1[]= "HELLO ALL   HEY "  ;
const char Lcd_L2[]= "HI :) ;) ;O :D  "  ;
const char Lcd_L3[]= " BUFFER FILLED  "  ;
const char Lcd_L4[]= " NEW ACQUISITION"  ;

char Lcd_LINE1[16];
char Lcd_LINE2[16];

unsigned char pattern0[8] = {0,0,0,0,0,0,0,0x1F};
unsigned char pattern1[8] = {0,0,0,0,0,0,0x1F,0x1F};
unsigned char pattern2[8] = {0,0,0,0,0,0x1F,0x1F,0x1F};;
unsigned char pattern3[8] = {0,0,0,0,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern4[8] = {0,0,0,0x1F,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern5[8] = {0,0,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern6[8] = {0,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern7[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
unsigned char patternsmile[8] = {0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00};

unsigned int DATA,lcdl1flag;
unsigned char FFTlcd_DataUp,FFTlcd_DataDwn;

 unsigned int bandhign[16]= {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160};
 unsigned int bandlow[16] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150};
 unsigned int bandmid[16] = {5,15,25,35,45,55,65,75,85,95,105,115,125,135,145,155};
 unsigned char BarValup[16] =  {0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0,1,2,3,4,5,6,7};
 unsigned char BarValdwn[16] = {0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,7};

void DelayMs(unsigned int Ms)
{
   unsigned int delay_cnst;
   while(Ms>0)
   {
        Ms--;
        //for(delay_cnst = 0;delay_cnst <6000;delay_cnst++);
        for(delay_cnst = 0;delay_cnst <1000;delay_cnst++);
   }
}

void lcd_command(unsigned char cmd)
{
   RS=0;
   DATA=((cmd>>4) & 0x0f);
   d0 =  DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DATA=(cmd & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DelayMs(5);
}

void lcd_data(unsigned char data)
{
   RS=1;
   DATA=((data >>4) & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DATA=(data & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DelayMs(5);
}

/*LCD*/
void Display(void)
{
    unsigned int i;
    if(lcdl1flag==0)
    {  lcd_command(0x01) ;
       DelayMs(20) ;
       lcd_command(0x80) ;
       DelayMs(20) ;
       for(i=0;i!=16;i++)
       {
          lcd_data(Lcd_LINE1[i]);
          DelayMs(5);
       }
       lcd_command(0xc0);
       DelayMs(20);
       for(i=0;i!=16;i++)
       {
          lcd_data(Lcd_LINE2[i]);
          DelayMs(5);
       }
    }
    if(lcdl1flag==1)
    {  lcd_command(0xc0);
       DelayMs(20);
       for(i=0;i!=16;i++)
       {
          lcd_data(Lcd_LINE2[i]);
          DelayMs(5);
       }
       lcdl1flag=0;
    }

}

void lcd_init( void )
{
   DelayMs(100);
   lcd_command(0x03);
   DelayMs(250);
   lcd_command(0x03);
   DelayMs(250);
   lcd_command(0x03);
   DelayMs(250);
   lcd_command(0x02);
   DelayMs(250);
   lcd_command(0x28);
   DelayMs(250);
   lcd_command(0x28);
   DelayMs(250);
   lcd_command(0x28);
   DelayMs(250);
   lcd_command(0x0C);
   DelayMs(250);
   lcd_command(0x06);
   DelayMs(250);
   //lcd_command(0x0E);
   //DelayMs(250);
   lcd_command(0x01);
   DelayMs(250);
}
/*
void dispnum( int num,unsigned  char pos,unsigned  char nodigit)		//display the numbers
{
	int i;                                                                  //select a counter
        if(num<0) num=0-num ;
	for( i = 0 ; i < nodigit ; i++ )					//initialise it to 0 increment it upto no. of digits
	{
		Lcd_LINE2[ pos + nodigit - 1 - i ] = ( num % 10 ) + '0' ;       //display it on lcd
                num = num / 10 ;                                    		//unpack the number
                lcdl1flag=1;
        }
        Display();
}

void dispchoice(unsigned int p ,unsigned  int pos)                              //to display particular choice
{
        int nodigit ;

	if(p < 10) nodigit = 1 ;
	if(p < 100 && p > 9) nodigit = 2 ;
	if(p > 99) nodigit = 3 ;
	if(p > 999 && p < 10000) nodigit = 4;
	dispnum( p, pos, nodigit);
}
*/
void initialisation()
{
	TRISB=0x1FF;
        Nop();
	TRISD=0x0D;
        Nop();
	TRISF=0x00;
        Nop();
	TRISE=0x100;
        Nop();
	TRISC=0xC00;
        Nop();
	ADPCFG = 0xFFF0;        		// Lowest 4 PORTB pins are analog inputs

}

void LCD_build(unsigned char location, unsigned char *ptr)
{
      unsigned char i;
      if(location<8)
      {
          lcd_command(0x40+(location*8));
          for(i=0;i<8;i++)
             lcd_data(ptr[ i ]);
      }

}

int get_LCD_FFT(unsigned int val)
{
    int k ;
    for(k = 0 ; k < 16 ; k++)
    {
        if( val == 0 )
        {
            FFTlcd_DataUp = 0xa0;
            FFTlcd_DataDwn = 0xa0;
            return 0;
        }
        else if( (val == bandhign[k]) || (val == bandlow[k]) )
        {
            FFTlcd_DataUp = BarValup[k];
            FFTlcd_DataDwn = BarValdwn[k];
            return 0;
        }
        else if( (val < bandhign[k] )&& (val > bandlow[k]) )
        {
            if(val > bandmid[k])
            {
                FFTlcd_DataUp = BarValup[k+1];
                FFTlcd_DataDwn = BarValdwn[k+1];
                return 0;
            }
            else if(val < bandmid[k])
            {
                FFTlcd_DataUp = BarValup[k];
                FFTlcd_DataDwn = BarValdwn[k];
                return 0;
            }
        }

    }
}

void Init_IOs(void)
{
	TRISB=0x1FF;
        Nop();
	TRISD=0x0D;
        Nop();
	TRISF=0x00;
        Nop();
	TRISE=0x100;
        Nop();
	TRISC=0xC00;
        Nop();
	ADPCFG = 0xFFF0;        		// Lowest 4 PORTB pins are analog inputs
}



int main(void)
{
	unsigned int i = 0;
	unsigned int x, y, y_Next;
	unsigned int Temp = 0;
		
        #ifndef FFTTWIDCOEFFS_IN_PROGMEM					/* Generate TwiddleFactor Coefficients */
	        TwidFactorInit (LOG2_BLOCK_LENGTH, &twiddleFactors[0], 0);	/* We need to do this only once at start-up */
        #endif
	
        Init_IOs();
        DelayMs( 50 ) ;
	lcd_init() ;

        strncpy( Lcd_LINE1 , Lcd_L1 , 16 ) ;
        strncpy( Lcd_LINE2 , Lcd_L2 , 16 ) ;
        Display( ) ;

        LCD_build(0,pattern0);
        LCD_build(1,pattern1);
        LCD_build(2,pattern2);
        LCD_build(3,pattern3);
        LCD_build(4,pattern4);
        LCD_build(5,pattern5);
        LCD_build(6,pattern6);
        LCD_build(7,pattern7);

	Init_ADC();
	DISABLE_ADC_INTERRUPT();
	Init_Timer3();
	ENABLE_ADC_INTERRUPT();
	ENABLE_ADC_MODULE();	

        while (1)
        {
		if(Converted_Data.Buffer_State == BUFFER_FULL)
		{
			
			for(i = 0; i < FFT_BLOCK_LENGTH; i++)
			{
				sigCmpx[i].real = Converted_Data.ADCBuffer[i];//Input_Data[i];
				sigCmpx[i].imag = 0x0000;		// make imaginary = 0
			}
			
			// Perform FFT operation
			#ifndef FFTTWIDCOEFFS_IN_PROGMEM
				FFTComplexIP (LOG2_BLOCK_LENGTH, &sigCmpx[0], &twiddleFactors[0], COEFFS_IN_DATA);
			#else
				FFTComplexIP (LOG2_BLOCK_LENGTH, &sigCmpx[0], (fractcomplex *) __builtin_psvoffset(&twiddleFactors[0]), (int) __builtin_psvpage(&twiddleFactors[0]));
			#endif
			
			// Store output samples in bit-reversed order of their addresses
			BitReverseComplex (LOG2_BLOCK_LENGTH, &sigCmpx[0]);
			// Compute the square magnitude of the complex FFT output array so we have a Real output vetor
			SquareMagnitudeCplx(FFT_BLOCK_LENGTH, &sigCmpx[0], FFT_Waveform);
			
			for(x = 0; x <= 16; x++)
			{
				//y = (unsigned char)(FFT_Waveform[x]);
				//y_Next = (unsigned char)(FFT_Waveform[x + 1]);
				//Plot_Bar(x, y, (x + 1), y_Next);

                                get_LCD_FFT(FFT_Waveform[x]);
                                lcd_command(0x80+x);
                                lcd_data(FFTlcd_DataUp);
                                lcd_command(0xc0+x);
                                lcd_data(FFTlcd_DataDwn);
			}
			
			Converted_Data.Buffer_State = BUFFER_EMPTY;	
			ENABLE_ADC_INTERRUPT();
			ENABLE_ADC_MODULE();

                        strncpy( Lcd_LINE1 , Lcd_L3 , 16 ) ;
                        strncpy( Lcd_LINE2 , Lcd_L4 , 16 ) ;
                        Display( ) ;
		}
	} 
}
