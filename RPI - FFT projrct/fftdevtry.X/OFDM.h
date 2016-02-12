#ifndef		_OFDM_HEADER
#define		_OFDM_HEADER

//#define	ADD_NOISE

void Init_OFDM(void);
void Bits_To_Frequency(void);
void Assign_Phase(int FrequencyBin, unsigned char Val);
void Frequency_To_Bits(void);

#endif

