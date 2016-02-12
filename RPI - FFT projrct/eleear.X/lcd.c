
#include "MAIN.h"

unsigned int DATA;
unsigned int lcdl1flag;
char  keytmr ;

/*DELAY ROUTINE*/

void DelayMs(unsigned int Ms)
{
   unsigned int delay_cnst;
   while(Ms>0)
   {
        Ms--;
        //for(delay_cnst = 0;delay_cnst <100;delay_cnst++);
        for(delay_cnst = 0;delay_cnst <50;delay_cnst++);
   }
}


int waitkey(void)
{
    char  key ;
    while(1)
    {
        if (ENTER == 0 && BACK  == 0 && CYCLE == 0 && MODE == 0  )
        {
            key  = CONFIG ;
            return key ;
        }
        if (ENTER == 0 || NEXT  == 0 || BACK  == 0 ||CYCLE == 0 || MODE == 0  )
        {
           if ( ENTER == 0 ) key = ENTKEY ;//key |= ENTKEY ;
           if ( NEXT  == 0 ) key = NXTKEY ;//key |= NXTKEY ;
           if ( BACK  == 0 ) key = PRVKEY ;//key |= PRVKEY ;
           if ( CYCLE == 0 ) key = CYCKEY ;//key |= CYCKEY ;
           if ( MODE  == 0 ) key = MODEKEY ;//key |= MODEKEY ;
            return key ;
        }
    }
}

int getkey(void)
{
   char  key = 0 ;
   if (ENTER == 0 && BACK  == 0 && CYCLE == 0 && MODE == 0  )
   {
       key  = CONFIG ;
   }
   if (ENTER == 0 || NEXT  == 0 || BACK  == 0 ||CYCLE == 0 || MODE == 0  )
   {
       if ( ENTER == 0 ) key = ENTKEY ;//key |= ENTKEY ;
       if ( NEXT  == 0 ) key = NXTKEY ;//key |= NXTKEY ;
       if ( BACK  == 0 ) key = PRVKEY ;//key |= PRVKEY ;
       if ( CYCLE == 0 ) key = CYCKEY ;//key |= CYCKEY ;
       if ( MODE  == 0 ) key = MODEKEY ;//key |= MODEKEY ;
   }
   return key ;
}

void lcd_command(unsigned char cmd)
{
   RS = 0;
   DATA=((cmd>>4) & 0x0f);
   d0 =  DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DATA=(cmd & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DelayMs(5);
}

void lcd_data(unsigned char data)
{
   RS=1;
   DATA=((data >>4) & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DATA=(data & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN=1;
   DelayMs(10);
   EN=0;
   DelayMs(5);
}

/*LCD*/
void Display(void)
{
    int i;
    if(lcdl1flag==0)
    {  lcd_command(0x01) ;
       DelayMs(20) ;
       lcd_command(0x80) ;
       DelayMs(20) ;
       for(i=0;i!=16;i++)
       {
          lcd_data(Lcd_LINE1[i]);
          DelayMs(5);
       }
       lcd_command(0xc0);
       DelayMs(20);
       for(i=0;i!=16;i++)
       {
          lcd_data(Lcd_LINE2[i]);
          DelayMs(5);
       }
    }
    if(lcdl1flag==1)
    {  lcd_command(0xc0);
       DelayMs(20);
       for(i=0;i!=16;i++)
       {
          lcd_data(Lcd_LINE2[i]);
          DelayMs(5);
       }
       lcdl1flag=0;
    }
}

void lcd_init( void )
{
   DelayMs(100);
   lcd_command(0x03);
   DelayMs(250);
   lcd_command(0x03);
   DelayMs(250);
   lcd_command(0x03);
   DelayMs(250);
   lcd_command(0x02);
   DelayMs(250);
   lcd_command(0x28);
   DelayMs(250);
   lcd_command(0x28);
   DelayMs(250);
   lcd_command(0x28);
   DelayMs(250);
   lcd_command(0x0C);
   DelayMs(250);
   lcd_command(0x06);
   DelayMs(250);
   //lcd_command(0x0E);
   //DelayMs(250);
   lcd_command(0x01);
   DelayMs(250);
}

void dispnum( int num,unsigned  char pos,unsigned  char nodigit)		//display the numbers
{
	int i;                                                                  //select a counter
        if(num<0) num=0-num ;
	for( i = 0 ; i < nodigit ; i++ )					//initialise it to 0 increment it upto no. of digits
	{
		Lcd_LINE2[ pos + nodigit - 1 - i ] = ( num % 10 ) + '0' ;       //display it on lcd
                num = num / 10 ;                                    		//unpack the number
                lcdl1flag=1;
        }
        Display();
}

void dispchoice(unsigned int p ,unsigned  int pos)                              //to display particular choice
{
        int nodigit ;
	if(p < 10) nodigit = 1 ;
	if(p < 100 && p > 9) nodigit = 2 ;
	if(p > 99) nodigit = 3 ;
	if(p > 999 && p < 10000) nodigit = 4;
	dispnum( p, pos, nodigit);
}

int getnum(unsigned int uplim ,unsigned int lowlim ,unsigned int num,unsigned  int pos,unsigned int nodig)		//to select particular choice
{
    int key  ;
    while ( 1 )
    {
        dispnum(num,pos,nodig);                                  			//Display the choices
        DelayMs(25);
        key = waitkey();
        if ( key )
        {
             if(key==NXTKEY)							//If key pressed is next
             {
                num++;                    					//increment choice to next value
                if(num >= uplim)						//if choice>nochoices then
                 num = uplim;							//initialise it to last but one value
                 if( num < lowlim )						//if choice<0
		num = lowlim ;
             }
            else if(key==PRVKEY)						//if key pressed is back
            {
		num--;								//go to the previous value
                if( num < lowlim )						//if choice<0
		num = lowlim ;							//initialise it to 0
            }
             else if(key==ENTKEY)						//if enter key is pressed
            {
                 return num ;							//return the value
            }
       }
    }
}

void LCD_build(unsigned char location, unsigned char *ptr)
{
      unsigned char i;
      if(location<8)
      {
          lcd_command(0x40+(location*8));
          for(i=0;i<8;i++)
             lcd_data(ptr[ i ]);
      }
}

void Initcustom_char(void)
{
     LCD_build(0,pattern0);
     LCD_build(1,pattern1);
     LCD_build(2,pattern2);
     LCD_build(3,pattern3);
     LCD_build(4,pattern4);
     LCD_build(5,pattern5);
     LCD_build(6,pattern6);
     LCD_build(7,pattern7);

}
/*
int get_LCD_FFT(unsigned int val)
{
    int k ;
    for(k = 0 ; k < 16 ; k++)
    {
        if( val == 0 )
        {
            FFTlcd_DataUp = 0xa0;
            FFTlcd_DataDwn = 0xa0;
            return 0;
        }
        else if( (val == bandhign[k]) || (val == bandlow[k]) )
        {
            FFTlcd_DataUp = BarValup[k];
            FFTlcd_DataDwn = BarValdwn[k];
            return 0;
        }
        else if( (val < bandhign[k] )&& (val > bandlow[k]) )
        {
            if(val > bandmid[k])
            {
                FFTlcd_DataUp = BarValup[k+1];
                FFTlcd_DataDwn = BarValdwn[k+1];
                return 0;
            }
            else if(val < bandmid[k])
            {
                FFTlcd_DataUp = BarValup[k];
                FFTlcd_DataDwn = BarValdwn[k];
                return 0;
            }
        }
    }
}*/