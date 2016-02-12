
#include <dsp.h>
#include "fft.h"

/***********************************************************************
* Square wave 1KHz sampled at 10KHz
*
*
************************************************************************/
fractcomplex sigCmpx[FFT_BLOCK_LENGTH] __attribute__ ((section (".ydata, data, ymemory"), aligned (FFT_BLOCK_LENGTH * 2 *2))) = 
{
  /*  0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x8001,*/
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000
    
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000,

0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000

/*
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000
*/
};

int sigCmpx1[FFT_BLOCK_LENGTH * 2] = //__attribute__ ((section (".ydata, data, ymemory"), aligned (FFT_BLOCK_LENGTH * 2 *2))) =
{
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001, 0x8001, 0x8001, 0x8001, 0x8001,
0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
0x8001 

//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
//0x0000, 0x0000, 0x0000, 0x0000
 /*
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000,

0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000
*/
/*
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000
*/
};
