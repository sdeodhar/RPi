#include <p30Fxxxx.h>
#include <I2C.h>
#include "fft.h"

#define LOOP_LENGTH    56
#define PLL_VALUE      8.0//4.0

static long n;
static unsigned char receivedMessage;
static unsigned char slaveStatus;
static unsigned char registerAddress;
static unsigned char registerData;
static unsigned char nextByte;

static unsigned char intCount;
//static unsigned char slaveValues[16];
static unsigned char registers[16];

int FFTaddr;

#define REGISTER_ADDRESS 0
#define REGISTER_VALUE   1

void delayMs(int ms)
{
// rather crude delay mechanism, works for a
// 7.3728 MHz clock with PLL*4 - modify appropriately
// if using different PLL rate
// only works well if ms >= 20
    n=(long)(0.5+((ms-4.19)*PLL_VALUE*7372.8/LOOP_LENGTH));
    while(n-->0);
}

void __attribute__((__interrupt__, no_auto_psv)) _MI2CInterrupt(void)
{
        IFS0bits.MI2CIF=0;
}

void __attribute__((__interrupt__, no_auto_psv)) _SI2CInterrupt(void)
{
    unsigned char byte;
    slaveStatus = (I2CSTATbits.TBF)+(I2CSTATbits.RBF*2)+(I2CSTATbits.R_W*4)+(I2CSTATbits.D_A*8);
    //slaveValues[intCount++]=slaveStatus;

    if(slaveStatus == 0xa) // write mode - the master is writing to the slave
    {
        byte=SlaveReadI2C();
        if(nextByte == REGISTER_ADDRESS) // first byte of message - it's the register address
        {
            registerAddress = byte;
            nextByte = REGISTER_VALUE;
        }

        else if(nextByte == REGISTER_VALUE) // second byte of message - it's the register contents
        {
            registerData = byte;
            registers[(registerAddress)&0xf] = registerData;
            receivedMessage = 1;
        }
    }
    else if(slaveStatus==0x2) // write mode - we have just had an address match
    {
            byte = SlaveReadI2C();
            nextByte = REGISTER_ADDRESS;
    }
    else if(slaveStatus==0x6) // read mode - it wants a byte
    {
            SlaveWriteI2C(registers[(registerAddress)&0xf]);
    }
    I2CCONbits.SCLREL = 1;
    IFS0bits.SI2CIF = 0;
}

void i2cSetup(unsigned char slaveAddress)
{
    unsigned int config1,config2;
    config2 = 6;	// 100 kHz
    config1 = I2C_ON & I2C_IDLE_CON & I2C_CLK_REL/*HLD*/ & I2C_IPMI_DIS & I2C_7BIT_ADD & I2C_SLW_EN/*DIS*/ & I2C_SM_DIS & I2C_GCALL_DIS & I2C_STR_EN
            & I2C_NACK & I2C_ACK_DIS & I2C_RCV_DIS & I2C_STOP_DIS & I2C_RESTART_DIS & I2C_START_DIS;
    I2CADD = slaveAddress;
    OpenI2C(config1,config2);
    ConfigIntI2C(SI2C_INT_ON & SI2C_INT_PRI_5 & MI2C_INT_OFF);
    IdleI2C();

    TRISFbits.TRISF2 = 1; // SDA
    TRISFbits.TRISF3 = 1; // SCL

    receivedMessage = 0;
    registerAddress = 0;
    registerData = 0;
    nextByte = REGISTER_ADDRESS;
    intCount = 0;
}

void SlaveWriteI2C(unsigned char data_out)
{
     I2CTRN = FFT_Waveform[FFTaddr];//data_out;      /* data transferred to I2CTRN reg */
     FFTaddr++;
     if(FFTaddr >= FFT_BLOCK_LENGTH){ FFTaddr = 0 ; STARTFFTPIN = 0; TxCompleteFlag = 1;}
     I2CCONbits.SCLREL = 1;	/* Release the clock */
}
