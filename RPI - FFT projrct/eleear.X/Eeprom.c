#include "MAIN.h"

int8u RdByte( int8u addr )
{
    int8u Data ;
    EEADR = addr ;
    EECON1 = 0x01 ;
    EEPGD = 0 ;
    RD = 1 ;
    while ( RD == 1 ) {}

    Data = EEDATA ;
    RD = 0 ;
    return Data ;
}

int32u ReadEEP(int8u addr)
{
    int32u DataH = 0 ;
    int8u i ;
    for ( i = 0 ; i < 4 ; i++ )
    {
        DataH <<= 8 ;
        DataH |= RdByte( addr ) ;
        addr++ ;
    }
    return DataH ;
}

int8u WrByte( int8u addr , int8u data )
{
    EEADR = addr ;
    EEDATA = data ;

    EECON1 = 0x00 ;
    WREN=1;							//write enable set
    GIE=0;
    EECON2=0x55;
    EECON2=0xAA;
    WR=1;							//set WR register to write
    GIE=1;
    WREN=0;							//write enable cleared
    while( WR == 1 ) {}
    if(EEIF==1)					//poll write operation
    {
	EEIF=0;					//clear the write flag
	return 1;				//return 1 if write completed
    }
    else
    {
	return 0;				//else return 0
    }
}

int8u WriteEEP( int32u Data, int8u addr)
{
    int8u i , status = 1 ;
    addr += 3 ;
    for ( i = 0 ; ( i < 4 ) && ( status ); i++ )
    {
        status = WrByte( addr , Data & 0xff ) ;
        addr-- ;
        Data >>= 8 ;
    }
    return status;
}
