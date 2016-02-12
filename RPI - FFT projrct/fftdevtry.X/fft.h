/******************************************************************************/
/* Clock definition                                                           */
/******************************************************************************/
//#define PLLIN		7372800		// External Crystal or Clock Frequency (Hz)
#define DESIREDMIPS	29491200/2	// Enter desired MIPS. If RTDM is used, copy

//#define DPLL		(unsigned int)(2.0*DESIREDMIPS/PLLIN)	// PLL ratio
//#define FOSC		(PLLIN*DPLL)	// Clock frequency (Hz)

/******************************************************************************/
/* definition for FFT                                                         */
/******************************************************************************/
#define FFT_BLOCK_LENGTH	128     /* = Number of frequency points in the FFT */
#define LOG2_BLOCK_LENGTH 	7		/* = Number of "Butterfly" Stages in FFT processing */
#define SAMPLING_RATE           20000	/* = Rate at which input signal was sampled */
                                    /* SAMPLING_RATE is used to calculate the frequency*/
                                    /* of the largest element in the FFT output vector*/

#define FFTTWIDCOEFFS_IN_PROGMEM 	/*<---Comment out this line of the code if twiddle factors (coefficients) */
                                	/*reside in data memory (RAM) as opposed to Program Memory */
                                	/*Then remove the call to "TwidFactorInit()" and add the twiddle factor*/
                                	/*coefficient file into your Project. An example file for a 256-pt FFT*/
                                	/*is provided in this Code example */
extern int FFTaddr;
extern int FFT_Waveform[FFT_BLOCK_LENGTH];
#define STARTFFTPIN LATEbits.LATE8
extern char TxCompleteFlag;
