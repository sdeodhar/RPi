
void lcd_command(unsigned char cmd)
{
   RS=0;
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
   RS = 1;
   DATA=((data >>4) & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN = 1;
   DelayMs(10);
   EN = 0;
   DATA=(data & 0x0f);
   d0 = DATA & 0x01;
   d1 = (DATA & 0x02) >> 1;
   d2 = (DATA & 0x04) >> 2;
   d3 = (DATA & 0x08) >> 3;
   EN = 1;
   DelayMs(10);
   EN = 0;
   DelayMs(5);
}

void Display(void)
{
    unsigned int i;
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
}
