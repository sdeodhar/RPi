#include "MAIN.h"

void USARTinit(void)
{
    TRISC |= 0b10000000;// RC7 = RX out
    TRISC &= 0b1111111111110111111;// RC6 = TX in

    BRGH = 1;//0;
    BRG16 = 0;
    SYNC = 0;
    TX9 = 0;        // select 8 data bits
    TXEN = 1;     // enable transmit
    TXIE = 0;
    TXCKP = 0;
    //RCSTAbits.CREN = 1;
    RCSTAbits.SPEN= 1;       // serial port is enabled
    RX9 = 0;        // select 8 data bits
    SPBRG  = 12;//25;//51;      //9600 at 8MHz
    SPBRGH = 0;
}

void USARTWriteChar(char ch)
{
  while(!TRMT){};
  if(TXIF)
  {
        TXREG = ch;
        TXIF =0;
  }
  //while(!TRMT){};
}

void USARTWriteString(const char *str)
{
  while(*str!='\0')
  {
      USARTWriteChar(*str);
      str++;
  }
}

void USARTWriteInt(int32s val)
{
    char str[8]={'0','0','0','0','0','0','0','0'};
    int i = 7;
    //Handle negative integers
    if( val < 0 )
    {
        USARTWriteChar('-');   //Write Negative sign
        val = val * -1;     //convert to positive
    }
    else
    {
        USARTWriteChar('+');
    }
    while(val)
    {
        str[i]=(val % 10)+'0';
        val = val / 10;
        i--;
        if ( i == 0 ) break ;
    }
    for( i = 0 ; i < 8 ; i++ )
    {
        USARTWriteChar(str[i]);
    }
}

int8u UARTGetChar(void)
{
    int8u temp;
    RCIE = 1;
    RCEN = 1;
    while( !RCIF );
    temp = RCREG;
    // Clear error flag
    OERR = 0;
    RCIF = 0; //RCIE = 0;
    RCEN = 0;
    return temp;
}

int32s str_to_num( int8u *String )
{
        int8u i ;
	int32s Num = 0 ;
	for( i = 0 ; String[ i ] != '\0' ; i++ )
	{
		//if( ( String[ i ] != '/' ) && ( String[ i ] != ':' ) && ( String[ i ] != '.' ) && ( String[ i ] != '-' ) )
                if((String[ i ] >= '0')&&(String[ i ] <= '9'))
		{
			Num *= 10 ;
			Num += String[ i ] - '0' ;
		}
	}
	if( String[ 0 ] == '-' ) Num *= -1 ;
	return Num ;
}

