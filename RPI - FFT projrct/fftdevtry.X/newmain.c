/* 
 * File:   main.c
 * Author: Shreya V Deodhar
 *  PIC side code to 
 *
 * Created on March 10, 2015, 2:12 PM
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
_FOSC(CSW_FSCM_OFF & XT_PLL8); //_FOSC(CSW_FSCM_OFF & FRC_PLL16);
                                //routed via the PLL in 16x multiplier mode
                                //For the 7.3728 MHz crystal we will derive a
                                //throughput of 7.3728e+6*16/4 = 29.4 MIPS(Fcy)
                                //,~33.9 nanoseconds instruction cycle time(Tcy).

_FWDT(WDT_OFF);                 //Turn off the Watch-Dog Timer.
_FBORPOR(MCLR_EN & PWRT_OFF);   //Enable MCLR reset pin and turn off the
                                //power-up timers.
_FGS(CODE_PROT_OFF);            //Disable Code Protection

#define RS       LATEbits.LATE1 //There is no RW connection
#define EN       LATEbits.LATE0
#define d0       LATEbits.LATE2
#define d1       LATEbits.LATE3
#define d2       LATEbits.LATE4
#define d3       LATEbits.LATE5
//#define STARTFFTPIN LATEbits.LATE8

#define I2C_SLAVE_ADDR 0x71                         // 7 bit slave is 0x08 to 0x77 addresses

int	peakFrequencyBin = 0;				/* Declare post-FFT variables to compute the */
unsigned long peakFrequency = 0;			/* frequency of the largest spectral component */
char TxCompleteFlag;

/* Extern definitions */
extern fractcomplex sigCmpx[FFT_BLOCK_LENGTH] 		/* Typically, the input signal to an FFT  */
__attribute__ ((section (".ydata, data, ymemory"), 	/* routine is a complex array containing samples */
aligned (FFT_BLOCK_LENGTH * 2 *2)));      			/* of an input signal. For this example, */
													/* we will provide the input signal in an */
													/* array declared in Y-data space. */
extern int sigCmpx1[FFT_BLOCK_LENGTH*2];
/* we will provide the input signal in an */

//unsigned int TxBuff[256];//[16];
/* Global Definitions */
#ifndef FFTTWIDCOEFFS_IN_PROGMEM
fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2] 	/* Declare Twiddle Factor array in X-space*/
__attribute__ ((section (".xbss, bss, xmemory"), aligned (FFT_BLOCK_LENGTH*2)));
#else
extern const fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2]	/* Twiddle Factor array in Program memory */
__attribute__ ((space(auto_psv), aligned (FFT_BLOCK_LENGTH*2)));
#endif

int FFT_Waveform[FFT_BLOCK_LENGTH];
/*
const char Lcd_L1[]= "INITIALLIING EAR"  ;
const char Lcd_L2[]= "                "  ;
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

 unsigned int bandhign[16]= {20,40,60,80,100,120,140,160,180,200,220,240,260,280};
 unsigned int bandlow[16] = {0 ,20,40,60,80 ,100,120,140,160,180,200,220,240,260};
 unsigned int bandmid[16] = {10,30,50,70,90 ,110,130,150,170,190,210,230,250,270};
 unsigned char BarValup[16] ={0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0xa0,0,1,2,3,4,5,6,7};
 unsigned char BarValdwn[16]= {0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,7};
*/

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

void Init_IOs(void)
{
	TRISB=0x1FF;
        Nop();
	TRISD=0x0D;
        Nop();
	TRISF=0b00010000;//0x00;
        Nop();
	TRISE=0x00;
        Nop();
	TRISC=0xC00;
        Nop();
	ADPCFG = 0xFFF0;        		// Lowest 4 PORTB pins are analog inputs
}

int MaxFreq()
{
    int i = 1,maxi = i,max = FFT_Waveform[i];
    float h1,h2,h3,h;
    float x2,x3;
    int x;

    for(i = 2 ; i < FFT_BLOCK_LENGTH ; i++)
    {
        if( FFT_Waveform[i] > max)
        {
            max = FFT_Waveform[i];
            maxi = i;
        }
    }
    if(FFT_Waveform[maxi+1] > FFT_Waveform[maxi-1])
    {
        h3 = FFT_Waveform[maxi + 1];
        x3 = (maxi + 1)* ((float)SAMPLING_RATE/FFT_BLOCK_LENGTH);
        h1 = FFT_Waveform[maxi - 1];
    }
    else
    {
        h1 = FFT_Waveform[maxi + 1];
        x3 = (maxi - 1) * ((float)SAMPLING_RATE/FFT_BLOCK_LENGTH);
        h3 = FFT_Waveform[maxi - 1];
    }
    h2 = FFT_Waveform[maxi];
    x2 = maxi * ((float)SAMPLING_RATE/FFT_BLOCK_LENGTH);;

    h = (h1 - h3)/(h1 - h2);
    h = h * ( x3 - x2 );
    x = h + (2 * x2);
    x = x/2;
    //x = x * ((float)SAMPLING_RATE/FFT_BLOCK_LENGTH);

    USART2WriteString("Actual Peak Freq: \t");
    USART2WriteInt(x);
    USART2WriteString("\t");

    return maxi;
}


int main(void)
{
	unsigned int i = 0, j = 0;
	unsigned int x;

        #ifndef FFTTWIDCOEFFS_IN_PROGMEM					/* Generate TwiddleFactor Coefficients */
	        TwidFactorInit (LOG2_BLOCK_LENGTH, &twiddleFactors[0], 0);	/* We need to do this only once at start-up */
        #endif

        Init_IOs();
        asm("NOP");asm("NOP");//DelayMs(5) ;
	//lcd_init() ;

        InitUART2();
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");//DelayMs(5);

        /*
        while(1)
        {
            USART2WriteChar('U');
            USART2WriteString("Hi Hello...\n\r");
        }
        */

        /*strncpy( Lcd_LINE1 , Lcd_L1 , 16 ) ;
        strncpy( Lcd_LINE2 , Lcd_L2 , 16 ) ;
        Display() ;
        */
        /*LCD_build(0,pattern0);
        LCD_build(1,pattern1);
        LCD_build(2,pattern2);
        LCD_build(3,pattern3);
        LCD_build(4,pattern4);
        LCD_build(5,pattern5);
        LCD_build(6,pattern6);
        LCD_build(7,pattern7);*/

        STARTFFTPIN = 0;
        Converted_Data.Counter = 0;
	Init_ADC();
	DISABLE_ADC_INTERRUPT();
	Init_Timer3();
	ENABLE_ADC_INTERRUPT();
	ENABLE_ADC_MODULE();
        i2cSetup(I2C_SLAVE_ADDR);
        FFTaddr = 0 ;
        TxCompleteFlag = 0;

        while (1)
        {
		if(Converted_Data.Buffer_State == BUFFER_FULL)
		{
                        //STARTFFTPIN = 0;
                   	for(i = 0; i < FFT_BLOCK_LENGTH; i++)
			{
				sigCmpx[i].real = Converted_Data.ADCBuffer[i];//Input_Data[i];
                                //USART2WriteInt(sigCmpx[i].real);
                                //USART2WriteString("\n");
				sigCmpx[i].imag = 0x0000;		// make imaginary = 0
			}
                      
                        //USART2WriteString("DONE ADC READINGS\n\r");
                        //STARTFFTPIN = 1;
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
                        
                        USART2WriteString("FFT Waveform VALS\n\r");

                        for(x = 0; x <= FFT_BLOCK_LENGTH; x++)
			{
                            USART2WriteInt(FFT_Waveform[x]);
                            USART2WriteString("\n");
                        }

                        FFTaddr = 0;
                        STARTFFTPIN = 1;
                        while( TxCompleteFlag == 0 ){};
                        //while()
                        /*USART2WriteString("FFT w/o square VALS\n\r");
                        for(x = 0; x <= FFT_BLOCK_LENGTH; x++)
			{
                             USART2WriteInt(sigCmpx[x]);
                             USART2WriteString("\n");
                        }*/

                        USART2WriteString("FFT VALS DONE\n\r");
                        //VectorMax(FFT_BLOCK_LENGTH/2, &FFT_Waveform[1], &peakFrequencyBin);
                        peakFrequencyBin = MaxFreq();
                        /* Compute the frequency (in Hz) of the largest spectral component */
                        peakFrequency = peakFrequencyBin * ((float)SAMPLING_RATE/FFT_BLOCK_LENGTH);

                        USART2WriteString("Peak Freq by FFT: \t");
                        USART2WriteInt(peakFrequency);
                        USART2WriteString("\n\r");
                        
		     /*	for(x = 5; x < FFT_BLOCK_LENGTH; x++)
			{
                              y = (unsigned char)(FFT_Waveform[x]);
                           
                              get_LCD_FFT(y);
                              //get_LCD_FFT(sigCmpx[x].real);
                              lcd_command(0x80+j);
                              lcd_data(FFTlcd_DataUp);
                              lcd_command(0xc0+j);
                              lcd_data(FFTlcd_DataDwn);
                              j++;
                              //dispnum(FFT_Waveform[x],0,4);
                              //dispnum(sigCmpx[x].real,0,4);
			}
                    */
                        
                        TxCompleteFlag = 0;
			Converted_Data.Buffer_State = BUFFER_EMPTY;
                        Converted_Data.Counter = 0;

			ENABLE_ADC_INTERRUPT();
			ENABLE_ADC_MODULE();
                        j = 0;
                        
		}
        }
}

