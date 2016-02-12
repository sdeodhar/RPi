
#include "MAIN.h"

#define I2C_DATA_ACK 0
#define I2C_DATA_NOACK 1
#define I2C_WRITE_CMD 0
#define I2C_READ_CMD 1

#define I2C_START_CMD 0
#define I2C_REP_START_CMD 1
#define I2C_REQ_ACK 0
#define I2C_REQ_NOACK 0

#define FFT_ADDR  0x70

void i2c_idle(void)
{
  while (( SSPCON2 & 0x1F ) || (RW));
}

void i2c_start(int8u stype)
{
  i2c_idle();                
  if (stype == I2C_START_CMD)
  {
    SEN = 1;          
    while(SEN);
  }
  else
  {
    RSEN = 1;         
    while(RSEN);
  }
}

void i2c_stop(void)
{
  PEN = 1;
  while(PEN);
}

int8u i2c_slave_ack(void)
{
  // Return: 1 = Acknowledge was not received from slave
  //         0 = Acknowledge was received from slave
  return(ACKSTAT);
}

void i2c_write(int8u data)
{
  SSPBUF = data;
  if (WCOL)         // Check for write collision
    return;
  while(BF);        // Wait until write cycle is complete
  i2c_idle();                   // Ensure the I2C module is idle
}

void i2c_master_ack(int8u ack_type)
{
  ACKDT = ack_type;   // 1 = Not Acknowledge, 0 = Acknowledge
  ACKEN = 1;          // Enable Acknowledge
  while (ACKEN == 1);
}

int8u i2c_read(void)
{
  i2c_idle();
  RCEN = 1;          
  while(!BF);         // Wait until buffer is full
  return(SSPBUF);
}

int8u Read_FFT(unsigned int idx_addr,int8u no_readings)
{
  int8u i;
  i2c_start(I2C_START_CMD);
  i2c_write(FFT_ADDR|I2C_WRITE_CMD);
  i2c_write(idx_addr & 0x00FF);
  i2c_start(I2C_REP_START_CMD);
  i2c_write(FFT_ADDR|I2C_READ_CMD);
  for( i = 0 ; i < no_readings ; i++ )
  {
      data[idx_addr + i] = i2c_read();
  }
  i2c_master_ack(I2C_DATA_NOACK);
  i2c_stop();
  return(0);
}

void Write_FFT(int8u data)
{
  i2c_start(I2C_START_CMD);
  i2c_write(FFT_ADDR|I2C_WRITE_CMD);
  i2c_write(data);
  i2c_master_ack(I2C_DATA_NOACK);
  i2c_stop();
}

void Init_i2c( void )
{
    TRISC3 = 1;
    TRISC4 = 1;

    SSPSTAT |= 0xc0;
    SSPCON1 |= 0x08;
    SSPCON2 |= 0x80;
    
    SSPADD = 0x09;//39;

    SSPEN = 1;
    SSPIF = 0;
}
