#include<p30fxxxx.h>
#include <math.h>

#define FCY (unsigned long)( 7372800 )   //add your operating frequency
#define UART1_BAUD 9600
#define UART2_BAUD 9600
#define UBRG1_VALUE (FCY/UART1_BAUD)/16 - 1
#define UBRG2_VALUE (FCY/UART2_BAUD)/16 - 1

/*
void InitUART1(void)
{
    U1BRG = UBRG1_VALUE;
    U1MODEbits.ALTIO=0;
    IEC0bits.U1RXIE=1;
    U1STA&=0xfffc;
    U1MODEbits.UARTEN=1;
    U1STAbits.UTXEN=1;
}

void WriteUART1(unsigned int data)
{
    while (U1STAbits.TRMT==0);
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

void WriteStringUART1(const char * s)
{
    while(*s)
    WriteUART1(*s++);
}
*/
/************************************ UART2 *******************************/
void InitUART2(void)
{
    U2BRG = UBRG2_VALUE;
    U2STA &= 0xfffc;
    IEC1bits.U2RXIE = 0; // disable RX2 interrupt
    U2MODEbits.UARTEN = 1; // UARTEN: UART Enable bit
    U2STAbits.UTXEN = 1; // transmition ON
}

void USART2WriteChar(char ch)
{
  while(!U2STAbits.TRMT);
  U2TXREG = ch;
}

void USART2WriteString(const char *str)
{
  while(*str!='\0')
  {
      USART2WriteChar(*str);
      str++;
  }
}

void USART2WriteInt(int val)
{
    char str[8]={'0','0','0','0','0','0','0','0'};
    int i = 7;
    //Handle negative integers
    if( val < 0 )
    {
        USART2WriteChar('-');   //Write Negative sign
        val = val * -1;     //convert to positive
    }
    else
    {
        USART2WriteChar('+');
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
        USART2WriteChar(str[i]);
    }
}
