#include "fft.h"
#include "OFDM.h"
#include <dsp.h>

/*
#define SUB_CARRIER_01	10
#define SUB_CARRIER_02	15
#define SUB_CARRIER_03	20
#define SUB_CARRIER_04	25
#define SUB_CARRIER_05	30
#define SUB_CARRIER_06	35
#define SUB_CARRIER_07	40
#define SUB_CARRIER_08	45
#define SUB_CARRIER_09	50
#define SUB_CARRIER_10	55
#define SUB_CARRIER_11	60
#define SUB_CARRIER_12	65
#define SUB_CARRIER_13	70
#define SUB_CARRIER_14	75
#define SUB_CARRIER_15	80
#define SUB_CARRIER_16	85
#define SUB_CARRIER_17	90
#define SUB_CARRIER_18	95
*/

#define	TOTAL_SUB_CARRIERS		18
#define MAX_STRING_LENGTH		((TOTAL_SUB_CARRIERS * 4)/8)	// 4 = 4 bits in each sub-carrier
																// 8 = 8 bit of data

unsigned char Tx_String[MAX_STRING_LENGTH] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
//unsigned char Tx_String[MAX_STRING_LENGTH] = "@@@@@@@@@";
unsigned char Rx_String[MAX_STRING_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

long Sub_Carrier_Frequency[TOTAL_SUB_CARRIERS] = {
10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 
50000, 55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000
};

int Sub_Carrier_FrequencyBin[TOTAL_SUB_CARRIERS];

extern fractcomplex sigCmpx[FFT_BLOCK_LENGTH];
/**************************************************************************
*
*
* 
**************************************************************************/	
void Init_OFDM(void)
{
	int i;

// Create the number on Complex array for each sub carrier	
/*	for(i = 0; i < TOTAL_SUB_CARRIERS; i++)
	{
		Sub_Carrier_FrequencyBin[i] = (Sub_Carrier_Frequency[i] * FFT_BLOCK_LENGTH)/SAMPLING_RATE;
	}*/
	for(i = 0; i < FFT_BLOCK_LENGTH; i++)
	{
		sigCmpx[i].real = 0;
		sigCmpx[i].imag = 0;
	}	
	
//		sigCmpx[13].real = 30000;
//		sigCmpx[13].imag = 0;
	
	for(i = 13; i <= 121; i++ )
	{
		sigCmpx[i].real = 22000;
		sigCmpx[i].imag = 0;
		i++;
		i++;
		i++;
		sigCmpx[i].real = 0;
		sigCmpx[i].imag = 22000;
		i++;
		i++;
		i++;				
	}
		
/*
	for(i = 85; i <= 95; i++ )
	{
		sigCmpx[i].real = 30000;
		sigCmpx[i].imag = 0;
//		i = i + 5;
		i++;
	}	
*/	
}	

/**************************************************************************
*
*
* 
**************************************************************************/	
void Bits_To_Frequency(void)
{
	unsigned char Four_Bit = 0;	
	int FrequencyBin = 0;
	unsigned int Character_Count = 0;

	sigCmpx[10].real = 30000;
	sigCmpx[10].imag = 0;//30000;	

	sigCmpx[11].real = 30000;
	sigCmpx[11].imag = 0;//30000;
	
	sigCmpx[12].real = 30000;
	sigCmpx[12].imag = 0;//30000;
	
	sigCmpx[13].real = 30000;
	sigCmpx[13].imag = 0;//30000;
	
	sigCmpx[14].real = 30000;
	sigCmpx[14].imag = 0;//30000;
	
	sigCmpx[15].real = 30000;
	sigCmpx[15].imag = 0;//30000;
	
	sigCmpx[16].real = 30000;
	sigCmpx[16].imag = 0;//30000;
	
	sigCmpx[17].real = 30000;
	sigCmpx[17].imag = 0;//30000;	
	
	sigCmpx[18].real = 30000;
	sigCmpx[18].imag = 0;//30000;
	
	sigCmpx[19].real = 30000;
	sigCmpx[19].imag = 0;//30000;
	
	sigCmpx[20].real = 30000;
	sigCmpx[20].imag = 0;//30000;										

//	sigCmpx[15].real = 30000;
//	sigCmpx[15].imag = 0;//30000;	

	sigCmpx[30].real = 30000;
	sigCmpx[30].imag = 0;//30000;

//	sigCmpx[45].real = 30000;
//	sigCmpx[45].imag = 0;//30000;
	
//	sigCmpx[60].real = 30000;
//	sigCmpx[60].imag = 0;//30000;
	
//	sigCmpx[75].real = 30000;
//	sigCmpx[75].imag = 0;//30000;
	
//	sigCmpx[90].real = 30000;
//	sigCmpx[90].imag = 0;//30000;
	

/*	
	for(Character_Count = 0; Character_Count < MAX_STRING_LENGTH; Character_Count++)
	{
		Four_Bit = Tx_String[Character_Count] & 0x0F;			// LSB
		Assign_Phase(FrequencyBin, Four_Bit);
		FrequencyBin++;
		if(FrequencyBin >= TOTAL_SUB_CARRIERS)
			break;		
		
		Four_Bit = ((Tx_String[Character_Count] >> 4) & 0x0F);
		Assign_Phase(FrequencyBin, Four_Bit);
		FrequencyBin++;
		if(FrequencyBin >= TOTAL_SUB_CARRIERS)
			break;
	}	
*/	
}	
/**************************************************************************
*
*
* 
**************************************************************************/	
void Assign_Phase(int FrequencyBin, unsigned char Val)
{
	switch(Val)
	{
		case 0x00:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 30000;			
			break;
		}	
		case 0x01:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 10000;			
			break;
		}
		case 0x02:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 	-30000;		
			break;
		}
		case 0x03:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = -10000;			
			break;
		}
		case 0x04:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 30000;			
			break;
		}
		case 0x05:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 10000;			
			break;
		}
		case 0x06:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = -30000;			
			break;
		}
		case 0x07:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = -10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = -10000;			
			break;
		}
		case 0x08:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 30000;			
			break;
		}
		case 0x09:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 10000;			
			break;
		}
		case 0x0A:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = -30000;			
			break;
		}
		case 0x0B:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 30000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = -10000;			
			break;
		}
		case 0x0C:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 30000;			
			break;
		}
		case 0x0D:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = 10000;			
			break;
		}
		case 0x0E:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = -30000;			
			break;
		}	
		case 0x0F:
		{
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real = 10000;
			sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag = -10000;			
			break;
		}																							
		default:
			break;
	}	
}	
/**************************************************************************
*
*
* 
**************************************************************************/	
void Frequency_To_Bits(void)
{
	int FrequencyBin = 0;
	int Real_Part = 0;
	int Imag_Part = 0;
	unsigned int Byte_Count = 0;
	unsigned int Bit_Count = 0;
	
	for(FrequencyBin = 0; FrequencyBin < TOTAL_SUB_CARRIERS; FrequencyBin++)
	{
		Real_Part = sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].real;
		Imag_Part = sigCmpx[Sub_Carrier_FrequencyBin[FrequencyBin]].imag;
		
		if(((Real_Part < -360) && (Real_Part > -700)) && ((Imag_Part < -350) && (Imag_Part > -700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x00 << Bit_Count);
		}
		else if(((Real_Part < -360) && (Real_Part > -700)) && ((Imag_Part < -1) && (Imag_Part > -350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x01 << Bit_Count);
		}			
		else if(((Real_Part < -360) && (Real_Part > -700)) && ((Imag_Part > 360) && (Imag_Part < 700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x02 << Bit_Count);
		}					
		else if(((Real_Part < -360) && (Real_Part > -700)) && ((Imag_Part > 0) && (Imag_Part < 350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x03 << Bit_Count);
		}	
		else if(((Real_Part < -1) && (Real_Part > -350)) && ((Imag_Part < -350) && (Imag_Part > -700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x04 << Bit_Count);
		}			
		else if(((Real_Part < -1) && (Real_Part > -350)) && ((Imag_Part < -1) && (Imag_Part > -350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x05 << Bit_Count);
		}		
		else if(((Real_Part < -1) && (Real_Part > -350)) && ((Imag_Part > 360) && (Imag_Part < 700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x06 << Bit_Count);
		}
		else if(((Real_Part < -1) && (Real_Part > -350)) && ((Imag_Part > 0) && (Imag_Part < 350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x07 << Bit_Count);
		}				
		else if(((Real_Part > 360) && (Real_Part < 700)) && ((Imag_Part < -360) && (Imag_Part > -700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x08 << Bit_Count);
		}
		else if(((Real_Part > 360) && (Real_Part < 700)) && ((Imag_Part < -1) && (Imag_Part > -350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x09 << Bit_Count);
		}		
		else if(((Real_Part > 360) && (Real_Part < 700)) && ((Imag_Part > 360) && (Imag_Part < 700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x0A << Bit_Count);
		}
		else if(((Real_Part > 360) && (Real_Part < 700)) && ((Imag_Part > 0) && (Imag_Part < 350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x0B << Bit_Count);
		}				
		else if(((Real_Part > 0) && (Real_Part < 350)) && ((Imag_Part < -360) && (Imag_Part > -700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x0C << Bit_Count);
		}
		else if(((Real_Part > 0) && (Real_Part < 350)) && ((Imag_Part < -1) && (Imag_Part > -350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x0D << Bit_Count);
		}		
		else if(((Real_Part > 0) && (Real_Part < 350)) && ((Imag_Part > 350) && (Imag_Part < 700)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x0E << Bit_Count);
		}
		else if(((Real_Part > 0) && (Real_Part < 350)) && ((Imag_Part > 0) && (Imag_Part < 350)))
		{
			Rx_String[Byte_Count] = Rx_String[Byte_Count] | (0x0E << Bit_Count);
		}				
		
		
						
		Bit_Count = Bit_Count + 4;
		
		if(Bit_Count >= 8)
		{
			Bit_Count = 0;	
			Byte_Count++;
		}	
	}	
}	
