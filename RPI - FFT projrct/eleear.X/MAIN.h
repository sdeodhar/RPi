/* 
 * File:   MAIN.h
 * Author: Shreya V. Deodhar
 *
 * Created on March 25, 2015, 12:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//#include <pic18f4620.h>
#include <htc.h>

#define S1M0 LATB1
#define S1M1 LATB0
#define S1M2 LATD7
#define S2M0 LATD6
#define S2M1 LATD5
#define S2M2 LATD4

#define EN LATA5
#define RS LATD1
#define d0 LATA1
#define d1 LATA2
#define d2 LATA3
#define d3 LATA4

#define FFTSTATPIN RB0

#define BACK	 RA7
#define MODE	 RA6
#define NEXT	 RC0
#define ENTER	 RC1 //<< change clash with CCP pin
#define CYCLE	 RD0

#define ENTKEY   2//0b00001
#define NXTKEY   3//0b00010
#define PRVKEY   5//0b00100
#define CYCKEY   1//0b01000
#define MODEKEY  4//0b10000
#define CONFIG   6//0b11111

#define FFT_MAX_SIZE 128

#define G0 0
#define G1 1
#define G2 2
#define G3 3
#define G4 4
#define G5 5
#define G6 6
#define G7 7
#define G8 8
#define G9 9
#define G10 10
#define G11 11
#define G12 12
#define G13 13
#define G14 14
#define G15 15
#define G16 16
#define G17 17
#define G18 18
#define G19 19
#define G20 20
#define G21 21
#define G22 22
#define G23 23
#define G24 24
#define G25 25
#define G26 26
#define G27 27
#define G28 28
#define G29 29
#define G30 30
#define G31 31
#define G32 32
#define G33 33
#define G34 34
#define G35 35

#define int8u   unsigned char
#define int16u  unsigned int
#define int32u	unsigned long
#define int8s   signed   char
#define int16s	signed   int
#define int32s  signed   long

const char Lcd_L1[]= "Hello All       "  ;
const char Lcd_L2[]= "HI Welcome ....."  ;
const char Lcd_L3[]= " KEY   ADC Count"  ;
const char Lcd_L4[]= "                "  ;

char Lcd_LINE1[16];
char Lcd_LINE2[16];

int8u i2c_rx_buff[8];
int8u i2c_tx_buff[8];
int8u data[FFT_MAX_SIZE];

unsigned char pattern0[8] = {0,0,0,0,0,0,0,0x1F};
unsigned char pattern1[8] = {0,0,0,0,0,0,0x1F,0x1F};
unsigned char pattern2[8] = {0,0,0,0,0,0x1F,0x1F,0x1F};;
unsigned char pattern3[8] = {0,0,0,0,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern4[8] = {0,0,0,0x1F,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern5[8] = {0,0,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern6[8] = {0,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
unsigned char pattern7[8] = {0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
//unsigned char patternsmile[8] = {0x00,0x00,0x0A,0x00,0x11,0x0E,0x00,0x00};
float cur_gain;
float gainarr[36]= {    0.25,   0.50,   0.75    ,1.0    ,1.25   ,
                        1.50,   1.75,   2.0     ,2.50   ,3.0    ,
                        3.5 ,   4.0 ,   5.0     ,6.0    ,7.0    ,
                        8.0,    10.0,   12.0    ,14.0   ,16.0   ,
                        20.0,   24.0,   28.0    ,32.0   ,40.0   ,
                        48.0,   56.0,   64.0    ,80.0   ,96.0   ,
                        112.0,  128.0,  160.0   ,192.0  ,224.0  ,
                        256.0
                   };

int16u ADC_Count;
int8u FFT_ready_flag;
int8u dutyvolt,dutycurrent;

extern void DelayMs(unsigned int Ms);
extern int waitkey(void);

extern void lcd_command(unsigned char cmd);
extern void lcd_data(unsigned char data);
extern void Display(void);
extern void lcd_init( void );
extern void dispnum( int num,unsigned  char pos,unsigned  char nodigit);		//display the numbers
extern void dispchoice(unsigned int p ,unsigned  int pos);                              //to display particular choice
extern int getnum(unsigned int uplim ,unsigned int lowlim ,unsigned int num,unsigned  int pos,unsigned int nodig);

extern void Adc_init(void);
extern void Get_ADC_Count(void);

extern int getkey(void);

extern void LCD_build(unsigned char location, unsigned char *ptr);
extern void Initcustom_char(void);
extern int get_LCD_FFT(unsigned int val);

extern void Init_i2c( void );
extern int8u Read_FFT(unsigned int idx_addr,int8u no_readings);
extern void Write_FFT(int8u data);
extern void Init_i2c( void );

extern void USARTinit(void);
extern void USARTWriteChar(char ch);
extern void USARTWriteString(const char *str);
extern void USARTWriteInt(int32s val);
extern int8u UARTGetChar(void);
extern int32s str_to_num( int8u *String );

extern void Calc_percentageFull(void);
extern void Disp_Mill_fill(void);

extern int8u RdByte( int8u addr );
extern int32u ReadEEP(int8u addr);
extern int8u WrByte( int8u addr , int8u data );
extern int8u WriteEEP( int32u Data, int8u addr);

extern void Init_PWM( void );
extern void Set_PWM_Duty( void );
extern int8u ICalc_DutyCyc(int8u voltop, int8u currentop);