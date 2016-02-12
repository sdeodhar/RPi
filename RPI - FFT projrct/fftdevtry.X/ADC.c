
#include "ADC.h"


/* Extern definitions */
extern int sigCmpx1[FFT_BLOCK_LENGTH*2]; 		/* Typically, the input signal to an FFT  */
//__attribute__ ((section (".ydata, data, ymemory"), 	/* routine is a complex array containing samples */
//aligned (FFT_BLOCK_LENGTH * 2 *2)));      			/* of an input signal. For this example, */
								/* we will provide the input signal in an */
ADC_Result Converted_Data;

//Functions:
//ADC_Init() is used to configure A/D to convert 16 samples of 1 input
//channel per interrupt. The A/D is set up for a sampling rate of 1MSPS
//Timer3 is used to provide sampling time delay.
//The input pin being acquired and converted is AN7.


void Init_ADC(void)
{
	// Initialize result buffer to zero
	for(Converted_Data.Counter = 0; Converted_Data.Counter < FFT_BLOCK_LENGTH; Converted_Data.Counter++)
	{
		Converted_Data.ADCBuffer[Converted_Data.Counter] = 0;
	}
	Converted_Data.Counter = 0;
	Converted_Data.Buffer_State = BUFFER_EMPTY;

        //ADCON1 Register
        //Set up A/D for Automatic Sampling
        //Use internal counter (SAMC) to provide sampling time
        //Set up A/D conversrion results to be read in 1.15 fractional
        //number format.
        //Set up Sequential sampling for multiple S/H amplifiers
        //All other bits to their default state
        ADCON1bits.FORM = 3;	// Signed fraction data
        ADCON1bits.SSRC = 2;	// Timer - 3 trigger for ADC
        ADCON1bits.ASAM = 1;
        ADCON1bits.SIMSAM = 0;

        //ADCON2 Register
        //Set up A/D for interrupting after 10 samples get filled in the buffer
        //Set up to sample on 2 S/H amplifiers - CH0 and CH1
        //All other bits to their default state
        ADCON2bits.SMPI = 15; // 16 samples
        ADCON2bits.CHPS = 0;  // CH0 only
	ADCON2bits.VCFG = 0b111;//3;  //references VDD

        //ADCON3 Register
        //We would like to set up a sampling rate of 1 MSPS
        //Total Conversion Time= 1/Sampling Rate = 125 microseconds
        //At 29.4 MIPS, Tcy = 33.9 ns = Instruction Cycle Time
        //The A/D converter will take 12*Tad periods to convert each sample
        //So for ~1 MSPS we need to have Tad close to 83.3ns
        //Using equaion in the Family Reference Manual we have
        //ADCS = 2*Tad/Tcy - 1
        ADCON3bits.SAMC = 2;
        ADCON3bits.ADCS = 10;	//4;

        //ADCHS Register
        //Set up A/D Channel Select Register to convert AN3 on Mux A input
        //of CH0
        ADCHS = 0x0002;//0x0003;

        //ADCSSL Register
        //Channel Scanning is disabled. All bits left to their default state
        ADCSSL = 0x0000;

        //ADPCFG Register
        //Set up channels AN7 as analog input and configure rest as digital
        //Recall that we configured all A/D pins as digital when code execution
        //entered main() out of reset
        ADPCFG = 0xFFFF;
        ADPCFGbits.PCFG2 = 0;

        //Clear the A/D interrupt flag bit
        IFS0bits.ADIF = 0;
        
        //Set the A/D interrupt enable bit
        //ENABLE_ADC_INTERRUPT();

        //Turn on the A/D converter
        //This is typically done after configuring other registers
        //ENABLE_ADC_MODULE();
}


//_ADCInterrupt() is the A/D interrupt service routine (ISR).
//The routine must have global scope in order to be an ISR.
//The ISR name is chosen from the device linker script.
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt(void)
{
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF0;
                //Converted_Data.ADCBuffer[Converted_Data.Counter] = (int)(sigCmpx1[Converted_Data.Counter] );//Dummy
                Converted_Data.Counter++;

		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF1;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF2;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF3;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF4;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF5;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF6;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF7;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF8;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUF9;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUFA;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUFB;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUFC;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUFD;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUFE;
		Converted_Data.Counter++;
		Converted_Data.ADCBuffer[Converted_Data.Counter] = ADCBUFF;	
		Converted_Data.Counter++;

		if(Converted_Data.Counter >= (FFT_BLOCK_LENGTH ))
		{
			DISABLE_ADC_INTERRUPT();
			DISABLE_ADC_MODULE();
			Converted_Data.Counter = 0;
			Converted_Data.Buffer_State = BUFFER_FULL;
		}
        //Clear the A/D Interrupt flag bit or else the CPU will
        //keep vectoring back to the ISR
        IFS0bits.ADIF = 0;
}

/**************************************************************************
*
*
* 
**************************************************************************/	
void Init_Timer3(void)
{
	T3CON = 0;
	PR3 = TIMER_3_Reload;
	START_TIMER_3();		// Run timer-3
}
/**************************************************************************
*
*
* 
**************************************************************************/	
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void)
{
	while(1);
}	

