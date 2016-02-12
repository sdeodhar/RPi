/*

My own graphics library for RPi

*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <math.h>
//#include "arial24h.h"
//#include "Century_Schoolbook114h.h"
#include "bakmain.h"


#define factory_password	32
#define Supervesor_password	45		
#define password_reset_num	30

INT32U Operator_password = 50;


/*#define INT8U      unsigned char
#define INT16U     unsigned int
#define INT32U	   unsigned long
#define INT8S      signed   char
#define INT16S	   signed   int
#define INT32S     signed   long*/
#define XMAX	800
#define YMAX	480

#include "arial24h.h"
#include "Century_Schoolbook114h.h"

// 'global' variables to store screen info

/*char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;*/

//extern INT8U Arial18h[];

//extern INT8U Century_Schoolbook114h[];
//extern const char Arial18h[] __attribute__((aligned(2)));
#define TRANSPARENT	0x55
#define NONTRANSPARENT	0xaa

#define	MAXFONTSIZE	800//128
#define MAX_SCREENS	100

INT8U keysay,status,dummy,pre_button;
//INT8U FixtureNo;

INT8U Hi_Calib_flag ,Lo_Calib_flag ,ProbeSettMaster_flag,res_dppos,dp_edit_flag;

#define CurEditMenuScreen  37
INT16U adcval,adcval1;
INT8U digbydig;
typedef struct 
{
	INT16U info;
	INT16U FontID;
	INT16U FirstcharID;
	INT16U LastcharID;
	INT16U Height;

}Font_info;

typedef struct
{
	INT8U width;
	INT16U offset;

}Char_info;

// 'global' variables to store screen info

char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
Font_info 	cur_font ;
Char_info 	cur_char ;

INT8U 		*curpt ;
INT16U 		flsb , fmsb , xcurs , ycurs ;
INT8U 		style , fore_color , back_color ;
INT8U 		*fontarray ;

INT8U           curglif[ MAXFONTSIZE ] ;

INT32U x_oldval,x_newval,y_oldval,y_newval;

INT32U 	LastUpdateButton_x ;
INT32U  LastUpdateButton_xstep;
INT8U	LastUpdate_i ;
//////////////////////////////////////////////////////////
#define BCM2708_PERI_BASE       0x20000000
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)	// GPIO controller 
 
#define BLOCK_SIZE 		(4*1024)
// IO Acces
struct bcm2835_peripheral 
{
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct bcm2835_peripheral gpio = {GPIO_BASE};
 
// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int map_peripheral(struct bcm2835_peripheral *p)
{
   // Open /dev/mem
   if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   }
 
   p->map = mmap(
      NULL,
      BLOCK_SIZE,
      PROT_READ|PROT_WRITE,
      MAP_SHARED,
      p->mem_fd,      // File descriptor to physical memory virtual file '/dev/mem'
      p->addr_p       // Address in physical map that we want this memory block to expose
   );
 
   if (p->map == MAP_FAILED) 
   {
        perror("mmap");
        return -1;
   }
 
   p->addr = (volatile unsigned int *)p->map;
 
   return 0;
}
 
void unmap_peripheral(struct bcm2835_peripheral *p) 
{
    munmap(p->map, BLOCK_SIZE);
    close(p->mem_fd);
}
///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x)
#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0
 
#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BSC0_BASE     (BCM2708_PERI_BASE + 0x205000)  // I2C controller 
#define BSC1_BASE     (BCM2708_PERI_BASE + 0x804000)  // I2C controller 

struct bcm2835_peripheral bsc1;	
 
// I2C macros
#define BSC1_C          *(bsc1.addr + 0x00)
#define BSC1_S          *(bsc1.addr + 0x01)
#define BSC1_DLEN     *(bsc1.addr + 0x02)
#define BSC1_A          *(bsc1.addr + 0x03)
#define BSC1_FIFO     *(bsc1.addr + 0x04)
 
#define BSC_C_I2CEN     (1 << 15)
#define BSC_C_INTR      (1 << 10)
#define BSC_C_INTT      (1 << 9)
#define BSC_C_INTD      (1 << 8)
#define BSC_C_ST        (1 << 7)
#define BSC_C_CLEAR     (1 << 4)
#define BSC_C_READ       1
 
#define START_READ      BSC_C_I2CEN|BSC_C_ST|BSC_C_CLEAR|BSC_C_READ
#define START_WRITE     BSC_C_I2CEN|BSC_C_ST
 
#define BSC_S_CLKT    (1 << 9)
#define BSC_S_ERR     (1 << 8)
#define BSC_S_RXF     (1 << 7)
#define BSC_S_TXE     (1 << 6)
#define BSC_S_RXD     (1 << 5)
#define BSC_S_TXD     (1 << 4)
#define BSC_S_RXR     (1 << 3)
#define BSC_S_TXW     (1 << 2)
#define BSC_S_DONE    (1 << 1)
#define BSC_S_TA       1
 
#define CLEAR_STATUS    BSC_S_CLKT|BSC_S_ERR|BSC_S_DONE

//////////////////////////////////////////////////////////////

void wait_i2c_done();
void UpdateADCNumberScreen( INT16U val);

//INT8U Arial18h[] = { 0,1,2,3,4,5,6,7,8};

INT16U valcolor[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
INT16U value[100]={10,10,20,20,30,15,34,67,23,89,90,56,87};

INT16U CurrentScreen, NextScreen ;
INT8U Key, KeyPressed ;
INT32U num;

INT32U accumes,reads;
//------------------- COLORS  ----------------------------
#define BLACK			0
#define WHITE			15
#define LIGHTGREEN		10
#define GREEN 			10	
#define GRAY			7
#define RED			12	
#define LIGHTBLUE		8
#define BLUE			3

#define	FONTCOLOR 		BLACK
#define TITLE_FONT_COLOR	WHITE
#define TITLEBACKCOLOR		8
#define SCR_BACK_COLOR		6//GRAY
#define MENU_ACTIVE_COLOR	LIGHTBLUE
#define MENU_INACTIVE_COLOR	WHITE
#define MENU_INACTIVE_BACK	GRAY
#define MENU_ACTIVE_BACK	WHITE
#define OLDVAL_BACK_COLOR	WHITE
#define CHOIC_OK_COLOR		LIGHTGREEN
#define CHOIC_NOT_OK_COLOR	RED
#define BUTTON_INACTIVE		GRAY
#define BUTTON_ACTIVE		BLUE	

#define DIGBYDIG	0
#define WHOLE		1
//---------------- FONT  ---------------------------------

#define TITLEFONT Arial18h
#define NORMALFONT Arial18h
#define ATTARACTFONT CenturySchoolbook114h
//----------------------- Key Codes -----------------------

#define KEYENT		0 
#define KEYCANCEL	5
#define KEYSHIFT	4
#define KEYINC		1
#define KEYDEC		2
#define KEYRUN		3
#define KEYSET		6

#define KEYNEWADC	8 
#define NOKEY		9
//////////////////////////////     Screens         //////////////////////////////////

//----------------------- Screen Types ---------------------

#define NUMBERS         0
#define ADCNUMBERS      1
#define MENUS           2
#define DISPBAR		3
#define VIEW		4
#define STRINGS		5

#define MAXSCREENS	2000


#define MAX_NUMBERS	35
#define MAX_ADCNUMBERS	15
#define MAX_MENUS	60

#define OLDBAR 		0
#define NEWBAR		1

//INT32U curNUMval[MAX_NUMBERS] = { 0,1000 , 2000 };
//INT32U calcount[MAX_ADCNUMBERS]={ 2580 , 3456 };

INT16U ADC_Val;
INT8U adccal_flag;
INT16U cur_dig;
INT8U curdig[8],dig_no;
INT8U choice;

typedef void(*Ptr2fun)(void);
/*--------------------------------- Data Structures for Interaction Manager ---------------------------------*/
INT8U OldStr[20] = "OLD SET VALUE";
INT8U NewStr[20] = "NEW CURRENT VALUE";
INT8U CurProNo, CurResNo ,CurFixNo ;

typedef struct 
{
	INT8U  *allstrings;
	const INT8U  NoDigit;
	const INT8U  NoChoice;       /* Can be Maximum 8 */
	INT8U	     *OldChoice;
	Ptr2fun	ExtHook;
	Ptr2fun	*EntHook;//[16];
}MenusStructure;

typedef struct 
{
	INT8U EditType ;   /* 0 DIGBYDIG    1 WHOLE   */
	const INT8U	NoDigit;
	const INT32S	LoLimit, HiLimit;
//	INT32S		CurVal;
	INT32S		*CurVal;
	INT8U     dp_pos;
	Ptr2fun EntHook;
	Ptr2fun ExtHook;
}NumberStructure;

typedef struct 
{
	const INT8U	NoDigit;
	const INT32S	LoLimit, HiLimit;
	INT32S		CalCount;
	Ptr2fun EntHook;
	Ptr2fun ExtHook;
}AdcNumberStructure;

typedef struct 
{
	INT8U ScreenType ;
	const INT16U *EnterScreen ;
	const INT16U EscScreen ;
	INT8S *Title ;
	void  *ObjPtr ;
}setscreen ;

//setscreen AllScreens[ MAXSCREENS ] ;

INT16U     Currentscreen,Newscreen ;

AdcNumberStructure  *CurADCNum;
NumberStructure	    *CurNum;
MenusStructure      *CurMenu;

MenusStructure      *StrEditMenu;

INT32U num,incr,oldnum;
INT8U *CurMenuChar;
INT8U *StrEditChar;
INT8U Current_Choice;
INT8U update_cur_flag , store_cur_flag , old_val_flag ;
INT8U StrFlag;

float CurProbe1Val,CurProbe2Val,CurProbe3Val,CurProbe4Val,CurProbe5Val,CurProbe6Val,CurProbe7Val,CurProbe8Val;
INT8U CurProbe1pol,CurProbe2pol,CurProbe3pol,CurProbe4pol,CurProbe5pol,CurProbe6pol,CurProbe7pol,CurProbe8pol;

//INT8U CurLablestr[17];
INT32U sincr,sdig_no,scurdig;
INT8U CurLablestr[17];
INT8U CurLetterPos;

INT8U Probe0str[6]= "Probe";
INT8U Probe1str[8]= "Probe 1";
INT8U Probe2str[8]= "Probe 2";
INT8U Probe3str[8]= "Probe 3";
INT8U Probe4str[8]= "Probe 4";
INT8U Probe5str[8]= "Probe 5";
INT8U Probe6str[8]= "Probe 6";
INT8U Probe7str[8]= "Probe 7";
INT8U Probe8str[8]= "Probe 8";
INT8U ProbeFactorstr[13]= "Probe Factor";
INT8U Probe1Factorstr[8]= "+ 0.000";
INT8U Probe2Factorstr[8]= "+ 0.000";
INT8U Probe3Factorstr[8]= "+ 0.000";
INT8U Probe4Factorstr[8]= "+ 0.000";
INT8U Probe5Factorstr[8]= "+ 0.000";
INT8U Probe6Factorstr[8]= "+ 0.000";
INT8U Probe7Factorstr[8]= "+ 0.000";
INT8U Probe8Factorstr[8]= "+ 0.000";
INT8U *Probestr[19]= {Probe0str,Probe1str,Probe2str,Probe3str,Probe4str,Probe5str,Probe6str,Probe7str,Probe8str,ProbeFactorstr,
		     Probe1Factorstr,Probe2Factorstr,Probe3Factorstr,Probe4Factorstr,Probe5Factorstr,Probe6Factorstr,Probe7Factorstr,Probe8Factorstr};
//////////////////////////////                         //////////////////////////////////
	INT8U Button1str[6]= " ENT ";
	INT8U Button6str[6]= "    X";
	INT8U Button2str[6]= " INC ";
	INT8U Button3str[6]= " DEC ";
	INT8U Button5str[6]= "SHIFT";
	INT8U Button4str[6]= " RUN ";
	INT8U Button7str[6]= " SET ";
	INT8U Button8str[6]= " EXIT";
	INT8U *Buttonstr[8]= {Button1str,Button2str,Button3str,Button4str,Button5str,Button6str,Button7str,Button8str};
////////////////////////////////////////////////////////////////////////////////////////////////




/*
#define		RUN			0
#define		CALIBRATION		1

#define		DISABLE			0
#define		ENABLE 			1

#define		MEASURE_OD		0
#define		MEASURE_ID		1

#define		METRIC			0
#define		INCH			1

#define		COMPARATIVE		0
#define		ABSOLUTE		1

#define		STATIC			0
#define		DYNAMIC			1

#define		RESMIN			0
#define		RESMAX			1
#define		RESAVG			2
#define		RESTIR			3
#define		RESMINMIN		4
#define		RESMAXMAX 		5

#define		ALPHABETIC		0
#define		NUMERIC			1

#define		LOW_TO_HIGH		0
#define		HIGH_TO_LOW		1

#define		UNIFORM			0
#define		NONUNIFORM		1

#define 	Zero 			0
#define 	Span 			1 
*/

INT8U noresults;

void PasswordEntHook(void)
{		
	LOADval();

	if(num == factory_password) Newscreen = Factory_Setup;

	else if(num == Supervesor_password)Newscreen = Supervisor_Setup;

	else if(num == Operator_password)  Newscreen = Operator_Settings;

	else if(num == password_reset)     Newscreen = password_reset;

	else Newscreen = Password;		
		
}


/*			
GRADEE_DISABLEEntHook()//	MENUS			6
{	
	f( Choice == 0)
	 = ENABLE;
	else if( Choice == 1)
	 = DISABLE;	
}	

GRADETYPEEntHook()	//	MENU	
{
	if( Choice == 0)
	GradeType = NONUNIFORM	;			//7
	else if( Choice == 1)
	GradeType = UNIFORM;	
}	

UTL_LTLHook()
{
	if( Choice == 0)
	GradeStartFlag = LOW_TO_HIGH;
	else if( Choice == 1)
	GradeStartFlag = HIGH_TO_LOW;		
}
*/


void UpdateFixNo(void)
{
	CurFixNo = choice;
//printf("curfix = %d\n",CurFixNo);
}

void UpdateProbeNo(void)
{
	CurProNo = choice;
//printf("curpro = %d\n",CurProNo);
}

void UpdateResultNo(void)
{
	CurResNo = choice;
//printf("curres = %d\n",CurResNo);
}

void ResHiHook(void)
{
	Hi_Calib_flag = 1;
	Lo_Calib_flag = 0;
	ProbeSettMaster_flag = 0;
}

void ResLoHook(void)
{
	Hi_Calib_flag = 0;
	Lo_Calib_flag = 1;
	ProbeSettMaster_flag = 0;
}


void SETTINGS_TYPE(void);
void CALIBERATION_TYPE(void);
void GET_GRADE_SETUP(void);
void OpCal_EnbChk(void);
void Editdp(void);

/////////////////////////////       MENU ENT HOOK ARRAYS ////////////////////////////////////////
Ptr2fun MenuEntArr0[3] ={ NULL,	NULL, NULL};
Ptr2fun MenuEntArr1[2] ={ NULL,	NULL};
Ptr2fun MenuEntArr2[4] ={ NULL,	NULL, NULL,NULL};
Ptr2fun MenuEntArr3[4] ={ NULL,	NULL, NULL, NULL};
Ptr2fun MenuEntArr4[2] ={ NULL,	NULL};
Ptr2fun MenuEntArr5[2] ={ NULL,	NULL};
Ptr2fun MenuEntArr6[2] ={ NULL,	NULL};
Ptr2fun MenuEntArr7[2] ={ NULL,	NULL};
Ptr2fun MenuEntArr8[6] ={ UpdateResultNo,UpdateResultNo,UpdateResultNo,UpdateResultNo,UpdateResultNo,UpdateResultNo};
Ptr2fun MenuEntArr9[3] ={ NULL,	NULL, NULL};
Ptr2fun MenuEntArr10[8]={ NULL,	NULL, NULL, NULL, NULL,	NULL, NULL, NULL};
Ptr2fun MenuEntArr11[7]={ NULL,	NULL, NULL, NULL, NULL,	NULL, NULL};
Ptr2fun MenuEntArr12[8]={ NULL,	NULL, NULL, NULL, NULL,	NULL, NULL, NULL};
Ptr2fun MenuEntArr13[2]={ NULL,	NULL};
Ptr2fun MenuEntArr14[2]={ NULL,	NULL};
Ptr2fun MenuEntArr15[2]={ NULL,	NULL};
Ptr2fun MenuEntArr16[2]={ NULL,	NULL};
Ptr2fun MenuEntArr17[2]={ NULL,	NULL};
Ptr2fun MenuEntArr18[2]={ NULL,	NULL};
Ptr2fun MenuEntArr19[2]={ NULL,	NULL};
Ptr2fun MenuEntArr20[2]={ NULL,	NULL};
Ptr2fun MenuEntArr21[8]={ NULL,	NULL, NULL, NULL, NULL,	NULL, NULL, NULL};
Ptr2fun MenuEntArr22[2]={ NULL,	NULL};
Ptr2fun MenuEntArr23[16]={UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo,UpdateFixNo};
Ptr2fun MenuEntArr24[3]={ NULL,	NULL, NULL};
Ptr2fun MenuEntArr25[6]={ NULL,	NULL, NULL, NULL, NULL,	NULL};
Ptr2fun MenuEntArr26[2]={ NULL,	NULL};
Ptr2fun MenuEntArr27[2]={ NULL,	NULL};
Ptr2fun MenuEntArr28[6]={ UpdateResultNo,UpdateResultNo,UpdateResultNo,UpdateResultNo,UpdateResultNo,UpdateResultNo};
Ptr2fun MenuEntArr29[7]={ NULL,	NULL, NULL, NULL, NULL, NULL, NULL};
Ptr2fun MenuEntArr30[2]={ NULL,	NULL};
Ptr2fun MenuEntArr31[2]={ NULL,	NULL};
Ptr2fun MenuEntArr32[2]={ NULL,	NULL};
Ptr2fun MenuEntArr33[2]={ NULL,	NULL};
Ptr2fun MenuEntArr34[2]={ NULL,	NULL};
Ptr2fun MenuEntArr35[4]={ NULL,	NULL, NULL, NULL};
Ptr2fun MenuEntArr36[2]={ NULL,	NULL};
Ptr2fun MenuEntArr37[4]={ Editdp ,Editdp,Editdp,Editdp};
Ptr2fun MenuEntArr38[2]={ NULL,	NULL};
Ptr2fun MenuEntArr39[2]={ NULL,	NULL};
Ptr2fun MenuEntArr40[16]={NULL,	NULL, NULL, NULL, NULL,	NULL, NULL, NULL, NULL,	NULL, NULL, NULL, NULL,	NULL, NULL, NULL};
Ptr2fun MenuEntArr41[3]={ NULL,	NULL,NULL};
Ptr2fun MenuEntArr42[2]={ NULL,	NULL};
Ptr2fun MenuEntArr43[3]={ NULL,	NULL, NULL};
Ptr2fun MenuEntArr44[3]={ NULL,	NULL, NULL};
Ptr2fun MenuEntArr45[4]={ NULL,	NULL, NULL, NULL};
Ptr2fun MenuEntArr46[2]={ ResHiHook,ResLoHook};
Ptr2fun MenuEntArr47[7]={ NULL,	NULL, NULL, NULL, NULL,	NULL, NULL};
Ptr2fun MenuEntArr48[7]={ NULL,	NULL, NULL, NULL, NULL,	NULL, NULL};
Ptr2fun MenuEntArrCal[6]={OpCal_EnbChk,OpCal_EnbChk,OpCal_EnbChk,OpCal_EnbChk,OpCal_EnbChk,OpCal_EnbChk};


#include "NewScreens.h"

///////////////////////////////////////////////////////////////////
void Editdp(void)
{
	switch(choice)
	{
		case 0: res_dppos = 3; dp_edit_flag = 1; break;
		case 1: res_dppos = 2; dp_edit_flag = 1; break;
		case 2: res_dppos = 2; dp_edit_flag = 1; break;
		case 3: res_dppos = 1; dp_edit_flag = 1; break;
	}
printf("dppos is = %d\n",res_dppos);
}
void OpCal_EnbChk(void)
{
	
printf("op curfix = %d\n",CurFixNo);
	if( Fixture[CurFixNo].SlopeCalEnbStat == 0 )
	{
printf("2 pt curres = %d\n",CurResNo);
//printf(" Enb stat= %d\n",CurrentFixture.SlopeCalEnbStat[CurFixNo]);
		switch(CurResNo)
		{
			case 0: Newscreen =Two_Pt_Caliberation0; break;
			case 1: Newscreen =Two_Pt_Caliberation1; break;
			case 2: Newscreen =Two_Pt_Caliberation2; break;
			case 3: Newscreen =Two_Pt_Caliberation3; break;
			case 4: Newscreen =Two_Pt_Caliberation4; break;
			case 5: Newscreen =Two_Pt_Caliberation5; break;
		}
	}
	else
	{
//printf("1 pt curres = %d\n",CurResNo);
//printf(" Enb stat= %d\n",CurrentFixture.SlopeCalEnbStat[CurFixNo]);
		switch(CurResNo)
		{
			case 0: Newscreen =Single_Caliberation0;ProbeSettMaster_flag = 1;
				Hi_Calib_flag = 0;Lo_Calib_flag = 0;break;
			case 1: Newscreen =Single_Caliberation1;ProbeSettMaster_flag = 1;
				Hi_Calib_flag = 0;Lo_Calib_flag = 0;break;
			case 2: Newscreen =Single_Caliberation2;ProbeSettMaster_flag = 1;
				Hi_Calib_flag = 0;Lo_Calib_flag = 0;break;
			case 3: Newscreen =Single_Caliberation3;ProbeSettMaster_flag = 1;
				Hi_Calib_flag = 0;Lo_Calib_flag = 0;break;
			case 4: Newscreen =Single_Caliberation4;ProbeSettMaster_flag = 1;
				Hi_Calib_flag = 0;Lo_Calib_flag = 0;break;
			case 5: Newscreen =Single_Caliberation5;ProbeSettMaster_flag = 1;
				Hi_Calib_flag = 0;Lo_Calib_flag = 0;break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------

//////////////////////////////      BAKER SCREENS END     /////////////////////////////////////


INT8U GetKey(void);
INT8U GetAdc(void);
//////////////////////////////                         /////////////////////////////////////

// helper function to 'plot' a pixel in given color
void put_pixel(int pix_x, int pix_y, int c)
{
    // calculate the pixel's byte offset inside the buffer
    unsigned int pix_offset = pix_x + pix_y * finfo.line_length;
    // now this is about the same as 'fbp[pix_offset] = value'
    *((char*)(fbp + pix_offset)) = c;
}

void clearscreen(int colour) 
{
    int x, y;
    for (y = 0; y < (vinfo.yres); y++) 
    {
        for (x = 0; x < vinfo.xres; x++) 
	{   // color based on the 16th of the screen width
            int c = colour;
            // call the helper function
            put_pixel(x, y, c);
        }
    }
}

// helper function for drawing - no more need to go mess with
// the main function when just want to change what to draw...
void draw() 
{
    int x, y;
    for (y = 0; y < (vinfo.yres); y++) 
    {
        for (x = 0; x < vinfo.xres; x++) 
	{   // color based on the 16th of the screen width
            int c = 16 * x / vinfo.xres;
            // call the helper function
            put_pixel(x, y, c);
        }
    }
}

int Line(INT16U x1, INT16U y1, INT16U x2, INT16U y2 ,int color)
{
    INT16S   deltaX, deltaY, error, stepErrorLT, stepErrorGE, stepX, stepY, steep, temp, slope;
    INT8U    lineType = 0,lineThickness = 1;
    INT16U   style = 0 , type = 1;
    //MoveTo(x2, y2);
	unsigned int pix_offset = x2 + y2 * finfo.line_length;
	if(x1 == x2)
   	{ 
	if(y1 > y2)
        {
            temp = y1;
            y1 = y2;
            y2 = temp;
        }
        style = 0; type = 1;
        for(temp = y1; temp < y2 + 1; temp++)
        {
            if((++style) == lineType)
            {
             //   type ^= 1;
              //  style = 0;
            }
            if(type)
            {
                put_pixel(x1, temp,color);
                if(lineThickness)
                {
                    put_pixel(x1 + 1, temp,color);
                    put_pixel(x1 - 1, temp,color);
                }
            }
        } return (1);
    }
    if(y1 == y2)
    {
        if(x1 > x2)
        {
            temp = x1; x1 = x2; x2 = temp;
        }
        style = 0;
        type = 1;
        for(temp = x1; temp < x2 + 1; temp++)
        {
            if((++style) == lineType)
            {
                //type ^= 1;
                //style = 0;
            }

            if(type)
            {
                put_pixel(temp, y1,color);
                if(lineThickness)
                {
                    put_pixel(temp, y1 + 1,color);
                    put_pixel(temp, y1 - 1,color);
                }
            }
        }
        return (1);
    }
    stepX = 0;
    deltaX = x2 - x1;
    if(deltaX < 0)
    {
        deltaX = -deltaX;
        --stepX;
    }
    else
    {
        ++stepX;
    }
    stepY = 0;
    deltaY = y2 - y1;
    if(deltaY < 0)
    {
        deltaY = -deltaY;
        --stepY;
    }
    else
    {
        ++stepY;
    }
    steep = 0;
    if(deltaX < deltaY)
    {
        ++steep;
        temp = deltaX;
        deltaX = deltaY;
        deltaY = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
        temp = stepX;
        stepX = stepY;
        stepY = temp;
        put_pixel(y1, x1,color);
    }
    else
    {
        put_pixel(x1, y1,color);
    }
    // If the current error greater or equal zero
    stepErrorGE = deltaX << 1;
    // If the current error less than zero
    stepErrorLT = deltaY << 1;
    // Error for the first pixel
    error = stepErrorLT - deltaX;
    style = 0;
    type = 1;
    while(--deltaX >= 0)
    {
        if(error >= 0)
        {
            y1 += stepY;
            error -= stepErrorGE;
        }
        x1 += stepX;
        error += stepErrorLT;
        if((++style) == lineType)
        {
            //type ^= 1;
            //style = 0;
        }
        if(type)
        {
            if(steep)
            {
                put_pixel(y1, x1,color);
                if(lineThickness)
                {
                    put_pixel(y1 + 1, x1,color);
                    put_pixel(y1 - 1, x1,color);
                }
            }
            else
            {
                put_pixel(x1, y1,color);
                if(lineThickness)
                {
                    put_pixel(x1, y1 + 1,color);
                    put_pixel(x1, y1 - 1,color);
                }
            }
        }
    }   // end of while
    return (1);
}

int Bar(INT16U left, INT16U top, INT16U right, INT16U bottom,INT8U color)
{
    INT16U   x, y;
    {
        for(y = top; y < bottom + 1; y++)
        for(x = left; x < right + 1; x++)
        put_pixel(x, y,color);
    }
    return (1);
}


int Grid( INT16U x1, INT16U y1,INT16U x2,INT16U y2, INT16U xdiv, INT16U ydiv, INT8U color)
{
	Bar(x1,y1,x2,y2,7);
	INT16U x,y;
	for( x = x1+xdiv ; x < x2 ;x+=xdiv)
	{
		Line(x,y1,x,y2,color);
	}
	for(y = y1+ydiv ; y < y2;y+=ydiv)
	{
		Line(x1,y,x2,y,color);
	}
	return 1;
}

int Plotgraph(INT16U x0,INT16U y0,INT16U xdiv,INT16U ydiv,INT16U xmax,INT16U ymax , INT8U color)
{	
	INT16U x,y,i=0,yprv;
	y = y0;
	for(x = x0; x < xmax; x+=xdiv)
	{
		y = ymax - reading[i];i+=ydiv;
		if(x > x0)
		{yprv = ymax - reading[i-1] ;
		Line(x,y,x-xdiv,yprv,color);}
	}
}

int BarGraph(INT16U no ,INT16U x1,INT16U y1, INT16U x2,INT16U y2,INT8U color)
{
	INT16U xvar,yvar,x,i;
	Bar(x1,y1,x2,y2,color);
	xvar = ((x2 - x1)/(no*2));
	for(x = x1,i = 0 ; x < x2,i < no ; x += (xvar*2),i++)
	{
		Bar(x,y2 - value[i],x+xvar,y2,valcolor[i]);
	}
}

int DrawArc(INT16U cx, INT16U cy, INT16U r1, INT16U startAngle, INT16U endAngle,INT8U scalecolor, INT8U color)
{
INT16U i,x1,y1,x2,y2,x,y;
float r = r1,deltax,deltay;
	for(i=0;i<=180;i++)
	{		
		deltax = r * cos((((i*0.5)+225)*2*3.14)/(360));
		deltay = r * sin((((i*0.5)+225)*2*3.14)/(360));
		y = cy + (deltay) ;// -(r*sin(i))/180;
		x = cx + (deltax) ;//(r*cos(i))/180;
		Line(cx,cy,x,y,color);
	}
	for(i=0;i<=10;i++)
	{	
		deltax = r * cos((((i*9.0)+225)*2*3.14)/(360));
		deltay = r * sin((((i*9.0)+225)*2*3.14)/(360));
		y = cy + (deltay) ;// -(r*sin(i))/180;
		x = cx + (deltax) ;//(r*cos(i))/180;
		Line(cx,cy,x,y,scalecolor);
	}	
	return 1;	
}

int DrawMeter(INT16U x1,INT16U y1,INT16U x2,INT16U y2,INT16U val,INT8U div, INT8U color)
{
INT16U cx = (x1+x2)/2 , i , x , y ;
Bar(x1,y1,x2,y2,7);
float deltax,deltay;
INT16U cy = y2 - 10;
INT8U offcet =((y2 - y1)/10);
int r = (y2 - y1) - offcet;
int arclen = r - ( r / 4 );
Line(cx,cy,cx,cy-r,4);
DrawArc(cx,cy,r,0,0,0,8);
DrawArc(cx,cy,arclen,0,0,7,7);
i = val;
	if(i>0 && i<90)
	{
		deltax = arclen * cos(((i+225)*2*3.14)/(360));
		deltay = arclen * sin(((i+225)*2*3.14)/(360));
		y = cy + deltay ;// -(r*sin(i))/180;
		x = cx + deltax ;//(r*cos(i))/180;
		Line(cx ,cy ,x,y,color);
	}
	return 1;
}

void read_fontinfo( void )
{
	INT8U *fontaddr , trial ;
	fontaddr = fontarray;
	cur_font.info = *fontaddr; fontaddr++; 
	cur_font.FontID = *fontaddr; fontaddr++;

	flsb = *fontaddr; fontaddr++;
	fmsb = *fontaddr; fontaddr++;
	cur_font.FirstcharID = flsb + (fmsb << 8 );
	flsb = *fontaddr; fontaddr++;
	fmsb = *fontaddr; fontaddr++;
	cur_font.LastcharID = flsb + (fmsb << 8 );
	flsb = *fontaddr; fontaddr++;
	fmsb = *fontaddr; fontaddr++;
	cur_font.Height = flsb + (fmsb << 8 );
}

void readcharinfo( INT16U curchar)
{
	curpt = fontarray +( ( ( curchar - cur_font.FirstcharID ) * 4) + 8) ;
	cur_char.width = *curpt; curpt++;
	flsb = *curpt; curpt++;
	fmsb = *curpt; curpt++;
	cur_char.offset = flsb + (fmsb << 8 );
}

void renderchar( void )
{
	INT16U x = xcurs, y = ycurs, mask;
	INT32U i,j,maxlen,row,col;
	curpt = fontarray + cur_char.offset ;
	maxlen = ((( cur_char.width - 1 ) /8 ) + 1) * cur_font.Height;
	for( i = 0 ; i < maxlen ; i++ )
	{
		curglif[i] = *curpt ;	curpt++;
	}
	for( row = 0,i=0 ; row < cur_font.Height ; row++ )
	{
		mask = 0x01;
		for( col = 0 ; col < cur_char.width ; col++ )
		{
			if( curglif[i] & mask ) put_pixel( x, y, fore_color ) ;
			else if( style != TRANSPARENT ) put_pixel( x, y, back_color );
			x++; mask = mask << 1 ;
			if(mask == 0x100)
			{
				mask = 0x01; i++;
			}
		}
		x = xcurs;y++;
		if( cur_char.width % 8) i++;
	}
}

INT8U outtext_xy(INT16U out_x, INT16U out_y , INT8U font_color, INT8U bk_color, INT8U *string ,INT8U *font , INT8U curstyle)
{
	INT16U counter=0, ch;
	xcurs = out_x; ycurs = out_y;
	fore_color = font_color;back_color = bk_color;
	fontarray  = font;
	style = curstyle;
	read_fontinfo();   
	while((ch = *(string + counter)) != 0)
	{
		if(digbydig)
		{	cur_dig = *curdig;

			if(counter == dig_no)	
			{	fore_color = bk_color;	back_color = font_color;
			}
			else if((counter == CurLetterPos)&&(StrFlag == 1))
			{	fore_color = bk_color;	back_color = font_color;
			}
			else
			{	fore_color = font_color;back_color = bk_color;
			}

		}
		else
		{	fore_color = font_color; back_color = bk_color;
		}
		readcharinfo(ch);
		renderchar();
		counter++;
		xcurs += cur_char.width;
	}return 1;
}

INT8U GetKey()
{	INT32U key_status;
	BSC1_A = 0x7;
	INP_GPIO(25);
	usleep(5);   
	key_status = GPIO_READ(25);
	if(key_status == 0)
	{
		BSC1_DLEN = 1;
		BSC1_S = CLEAR_STATUS;  // Reset status bits
		BSC1_C = START_READ;    // Start Read after clearing FIFO
		wait_i2c_done();
		keysay = BSC1_FIFO;
		printf("key = %d\n", keysay);
		KeyPressed = 1;	
		return keysay;
	}
	else if( adccal_flag ) 
	{ 	if(GetAdc())
		{	reads++; accumes+= adcval;
			if(reads == 16)
			{
				accumes = accumes >> 4 ;
				reads = 0; ADC_Val = accumes;
				accumes = 0; 
				return KEYNEWADC;
			}
		}return NOKEY ;
	}else return NOKEY;
}

INT8U GetAdc()
{	INT32U adc_status;
	BSC1_A = 0x78;
 	usleep(3);	
	INP_GPIO(24);   
	usleep(3);
	adc_status = GPIO_READ(24);
	if(adc_status == 0)
	{
		BSC1_DLEN = 3;
		BSC1_S = CLEAR_STATUS;  // Reset status bits
		BSC1_C = START_READ;    // Start Read after clearing FIFO
		wait_i2c_done();
		adcval = BSC1_FIFO;
		adcval1 = BSC1_FIFO ;
		dummy = BSC1_FIFO;
		adcval = adcval + (adcval1<<8);
		printf("ADC -> %5d\n", adcval);
		return 1;
	}return 0;
}
////////////////////////        BUTTON BAR                  /////////////////////////////

void DrawButtonBar(void)
{
	INT32U xstep = 0,x,i ;
	Bar( 0 , (YMAX - (YMAX / 8) - 4) , XMAX , YMAX , BLACK ); 
	Bar( 2 , (YMAX - (YMAX / 8) - 2) , XMAX , YMAX , 8);//WHITE ); 
	xstep = XMAX / 8 ;
	for( x = 2,i = 0 ; x < XMAX ; x += xstep, i++ )
	{ 
		Bar( x  , (YMAX - (YMAX / 8))+ 2 , x + xstep - 4 , YMAX-4 ,WHITE);//BLACK);
		Bar( x + 2 , (YMAX - (YMAX / 8))+ 4 , x + xstep - 4 , YMAX-4 ,BUTTON_INACTIVE);
		outtext_xy( x + 10 , (YMAX - (YMAX / 8))+20 , FONTCOLOR ,BUTTON_INACTIVE , (INT8U *)Buttonstr[i]  , (INT8U *) NORMALFONT,TRANSPARENT);
	}
}

void ButtonUpdate(INT8U buttonno)
{
	INT32U xstep = 0,x,i=0 ;
	Bar( 0 , (YMAX - (YMAX / 8) - 4) , XMAX , YMAX , BLACK ); 
	Bar( 2 , (YMAX - (YMAX / 8) - 2) , XMAX , YMAX , 8);//WHITE ); 
	xstep = XMAX / 8 ;	
	
	for( x = 2,i = 0 ; x < XMAX ; x += xstep, i++ )
	{ 
		Bar( x  , (YMAX - (YMAX / 8))+ 2 , x + xstep - 4 , YMAX-4 ,WHITE);//BLACK);
		Bar( x + 2 , (YMAX - (YMAX / 8))+ 4 , x + xstep - 4 , YMAX-4 , BUTTON_INACTIVE);
		outtext_xy( x + 10 , (YMAX - (YMAX / 8))+20 , FONTCOLOR ,BUTTON_INACTIVE , (INT8U *)Buttonstr[i]  , (INT8U *) NORMALFONT,TRANSPARENT);
		if( i == Key/*buttonno*/ )
		{
			Bar( x  , (YMAX - (YMAX / 8))+ 2 , x + xstep - 4 , YMAX-4 ,BLACK);
			Bar( x + 2 , (YMAX - (YMAX / 8))+ 4 , x + xstep - 4 , YMAX-4 , BUTTON_ACTIVE);
			outtext_xy( x + 10 , (YMAX - (YMAX / 8))+20 , FONTCOLOR ,BUTTON_INACTIVE , (INT8U *)Buttonstr[i]  , (INT8U *) NORMALFONT,TRANSPARENT);
			LastUpdateButton_x = x;
			LastUpdateButton_xstep = xstep;
			LastUpdate_i = i;
		}
	}
}

void DrawTitleBar(void)
{
	clearscreen( SCR_BACK_COLOR );
	Bar( 13 , 3 , XMAX - 13 , 34  /*cur_font.Height*/ , BLACK );
	Bar( 15 , 5 , XMAX - 13 , 34  /*cur_font.Height*/ , GRAY );
	Bar( 15 , 5 , XMAX - 15 , 32  /*cur_font.Height*/ , TITLEBACKCOLOR );
	outtext_xy( XMAX/4 , 7 , TITLE_FONT_COLOR , TITLEBACKCOLOR , (INT8U *)AllScreens[CurrentScreen].Title, (INT8U *)TITLEFONT, TRANSPARENT);
}

void DrawNumberBar(INT32U val)
{
	INT32U xstep = 0,x = 0 , y = 0,i ;
	x = XMAX /10; xstep = XMAX / 5;
	y = ((YMAX / 2) - ( YMAX / 5));
	num = val;
	INT8U CurValstr[6] ;
	sprintf(CurValstr, "%06d" ,val);
	Bar( 5, y - 22 , XMAX-7 , (y + (YMAX /2)-2),BLACK); 
	
	if(CurNum->dp_pos) 
	{
	sprintf(CurValstr, "%07d",val);
		CurValstr[CurNum->dp_pos - 1] = CurValstr[CurNum->dp_pos];
		CurValstr[CurNum->dp_pos] = '.';
	}
	Bar( 7, y - 20 , XMAX-5 , (y + (YMAX /2)),WHITE); 
	Bar( 7, y - 20 , XMAX-7 , (y + (YMAX /2)-2),BLUE); 

	outtext_xy( x -10 , y + 5 , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)OldStr , (INT8U *)NORMALFONT ,TRANSPARENT);
	/* convert to string first */
	Bar( 15 ,(y +( YMAX/8)-2), 15+(2* xstep) + 45 , y +(YMAX/3)+20,BLACK);
	Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) + 45 , y +(YMAX/3)+20,1);
	Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) + 43 , y +((YMAX/3)+18),WHITE);
	outtext_xy( 20 , y+(YMAX/8) , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)CurValstr , (INT8U *)ATTARACTFONT,TRANSPARENT );
	x_oldval = 20;y_oldval = y+(YMAX/8);
	outtext_xy( x + (2*xstep)+15, y+5 , FONTCOLOR ,OLDVAL_BACK_COLOR , (INT8U *)NewStr , (INT8U *) NORMALFONT ,TRANSPARENT);
	/* convert to string first */
	Bar( x +(2*xstep)-2,(y +( YMAX/8))-2, x+(4* xstep)+45 , y +((YMAX/3))+20,BLACK);
	Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+45 , y +((YMAX/3))+20,1);
	Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+43 , y +((YMAX/3)+18),WHITE);
	outtext_xy( (x + (2*xstep)+ 6), y+(YMAX/8) , FONTCOLOR ,OLDVAL_BACK_COLOR , (INT8U *)CurValstr  , (INT8U *) ATTARACTFONT ,TRANSPARENT);  
	/* cal val for back color*/
	x_newval =x + (2*xstep)+10; y_newval = y+(YMAX/8) ;  
}

void UpdateNumberBar(INT32U numval,INT32U uplim , INT32U lolim,INT8U bartype)
{
	INT32U xstep = 0,x = 0 , y = 0,i ;
	INT8U str[6] ,BKKCOL;
	x = XMAX /10; xstep = XMAX / 5;
	y = ((YMAX / 2) - ( YMAX / 5));
	
	sprintf(str, "%06d",numval);
	if(CurNum->dp_pos) 
	{
			sprintf(str, "%07d",numval);
			str[CurNum->dp_pos - 1] = str[CurNum->dp_pos];
			str[CurNum->dp_pos] = '.';
	}
	if(bartype == OLDBAR)
	{	Bar( 15 ,(y +( YMAX/8)-2), 15+(2* xstep) + 45 , y +(YMAX/3)+20,BLACK);
		Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) + 45 , y +(YMAX/3)+20,1);
		if(numval > uplim || numval < lolim) BKKCOL = RED; else BKKCOL = 2;//GREEN;  
		Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) +43 , y +((YMAX/3)+18),BKKCOL);
		outtext_xy( 20 , y+(YMAX/8) , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)str , (INT8U *)ATTARACTFONT,TRANSPARENT );
	}
	if(bartype == NEWBAR)
	{	Bar( x +(2*xstep)-2,(y +( YMAX/8))-2, x+(4* xstep)+45 , y +((YMAX/3))+20,BLACK);
		Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+45 , y +((YMAX/3))+20,1);
		if(numval > uplim || numval < lolim) BKKCOL = RED; else BKKCOL = 2;//GREEN;  
		Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+43 , y +((YMAX/3)+18),BKKCOL);
		outtext_xy( (x + (2*xstep)+6), y+(YMAX/8) , FONTCOLOR ,OLDVAL_BACK_COLOR,(INT8U *)str,(INT8U *)ATTARACTFONT,TRANSPARENT);/*calval for back color*/
	}	
}
		  

void StringEdit(void);
void DisplaySetValues(void);
void Run(void);

void StringEditUpdate(void)
{
	INT32U xstep = 0,x = 0 , y = 0,i=0 ;
	digbydig = 1;StrFlag = 1;
	x = XMAX /10; xstep = XMAX / 5;
	y = ((YMAX / 2) - ( YMAX / 5));
	Bar( x +(2*xstep)-2,(y +( YMAX/8))-2, x+(4* xstep)+30 , y +((YMAX/3))+20,BLACK);
	Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+30 , y +((YMAX/3))+20,1);
	Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+28 , y +((YMAX/3)+18),8);
	outtext_xy( (x + (2*xstep)+ 35), y+(YMAX/5) , FONTCOLOR ,OLDVAL_BACK_COLOR , (INT8U *)CurLablestr  , (INT8U *) NORMALFONT ,TRANSPARENT); 
	if(Key == KEYENT)
	{	digbydig = 0;
		Bar( 15 ,(y +( YMAX/8)-2), 15+(2* xstep) + 30 , y +(YMAX/3)+20,BLACK);
		Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) + 30 , y +(YMAX/3)+20,1);
		Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) +28 , y +((YMAX/3)+18),GREEN);
		outtext_xy( x - 5  , y+(YMAX/5) , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)CurLablestr , (INT8U *)NORMALFONT,TRANSPARENT );
//strncpy(StrEditMenu->allstrings,CurLablestr,1);//StrEditMenu->NoDigit);
	} 
	digbydig = 0;StrFlag = 0;
}

void StringEdit(void)
{	
	INT8U Letter = CurLablestr[CurLetterPos],i=0;
	switch (Key)
	{	case KEYSHIFT: CurLetterPos++;
	 		       if(CurLetterPos > 15 )CurLetterPos = 0;
		       	       break;
		case KEYINC  : if( (Letter>='0')&&(Letter <= '8'))Letter++;
		    	       else if((Letter >= 'A')&&(Letter <='Y')) Letter++;
			       else if( Letter == '9') Letter = 'A';
			       else if( Letter == ' ') Letter = '0';
			       else if( Letter == 'Z') Letter = ' ';
 			       CurLablestr[CurLetterPos] = Letter;
		     	       break;
		case KEYDEC  : if( (Letter >='1')&&(Letter <= '9'))Letter--;
		    	       else if((Letter >= 'B')&&(Letter <='Z')) Letter--;
			       else if( Letter == '0') Letter = ' ';
			       else if( Letter == ' ') Letter = 'Z';
			       else if( Letter == 'A') Letter = '9';
 			       CurLablestr[CurLetterPos] = Letter;
		     	       break;
		case KEYCANCEL:digbydig =0;
			       Newscreen = AllScreens[CurrentScreen].EscScreen;/*2;*/
	   	 	       break;
		case KEYENT  : digbydig = 0; 
			       for(i=0;i<16;i++)
			       {
				*(StrEditChar+(16*CurFixNo)+i) = CurLablestr[i];
			       }
			       Newscreen = AllScreens[CurrentScreen].EnterScreen[0];/*1;*/	
		 	       break;
	}
	StringEditUpdate();
}

void StringDraw(void)
{
	DrawTitleBar();
	INT32U xstep = 0,x = 0 , y = 0,i=0 ;
	CurLetterPos = 0;
	x = XMAX /10; xstep = XMAX / 5;
	y = ((YMAX / 2) - ( YMAX / 5));
	INT8U CurValstr[17];
	StrEditMenu = (MenusStructure *)AllScreens[CurEditMenuScreen].ObjPtr;
	StrEditChar = StrEditMenu->allstrings;
	strncpy(CurValstr,StrEditChar+(16*CurFixNo),StrEditMenu->NoDigit);

	for(i=0;i<16;i++)
	{
		if(!((CurValstr[i]==' ')||((CurValstr[i]>='0')&&(CurValstr[i]<='9'))||((CurValstr[i]>='A')&&(CurValstr[i]<='Z'))))
		CurValstr[i] = ' ';
	}
	strncpy(CurLablestr,CurValstr,16);
	Bar( 5, y - 22 , XMAX-7 , (y + (YMAX /2)-2),BLACK); 
	Bar( 7, y - 20 , XMAX-5 , (y + (YMAX /2)),WHITE); 
	Bar( 7, y - 20 , XMAX-7 , (y + (YMAX /2)-2),BLUE); 

	outtext_xy( x -10 , y + 5 , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)OldStr , (INT8U *)NORMALFONT ,TRANSPARENT);
	/* convert to string first */
	Bar( 15 ,(y +( YMAX/8)-2), 15+(2* xstep) + 30 , y +(YMAX/3)+20,BLACK);
	Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) + 30 , y +(YMAX/3)+20,1);
	Bar( 17 ,(y +( YMAX/8)), 15+(2* xstep) +28 , y +((YMAX/3)+18),WHITE);
	outtext_xy( x - 5 , y+(YMAX/5) , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)CurValstr , (INT8U *)NORMALFONT,TRANSPARENT );
	x_oldval = 20;	y_oldval = y+(YMAX/8);
	outtext_xy( x + (2*xstep)+15, y+5 , FONTCOLOR ,OLDVAL_BACK_COLOR , (INT8U *)NewStr , (INT8U *) NORMALFONT ,TRANSPARENT);
	/* convert to string first */
	Bar( x +(2*xstep)-2,(y +( YMAX/8))-2, x+(4* xstep)+30 , y +((YMAX/3))+20,BLACK);
	Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+30 , y +((YMAX/3))+20,1);
	Bar( x +(2*xstep),(y +( YMAX/8)), x+(4* xstep)+28 , y +((YMAX/3)+18),WHITE);
	outtext_xy( (x + (2*xstep)+ 35), y+(YMAX/5) , FONTCOLOR ,OLDVAL_BACK_COLOR , (INT8U *)CurValstr  , (INT8U *) NORMALFONT ,TRANSPARENT);  
	DrawButtonBar();
}

void DisplaySetValues(void)
{
	INT32U i,x=30,y,ystep = YMAX/13;

	/*sprintf(Probe1Factorstr,"+ %1.3f",CurProbe1Val);
	sprintf(Probe2Factorstr,"+ %1.3f",CurProbe2Val);
	sprintf(Probe3Factorstr,"+ %1.3f",CurProbe3Val);
	sprintf(Probe4Factorstr,"+ %1.3f",CurProbe4Val);
	sprintf(Probe5Factorstr,"+ %1.3f",CurProbe5Val);
	sprintf(Probe6Factorstr,"+ %1.3f",CurProbe6Val);
	sprintf(Probe7Factorstr,"+ %1.3f",CurProbe7Val);
	sprintf(Probe8Factorstr,"+ %1.3f",CurProbe8Val);*/

	sprintf(Probe1Factorstr,"   %04d",Result[CurResNo].ProbeFactor[0]);
	sprintf(Probe2Factorstr,"   %04d",Result[CurResNo].ProbeFactor[1]);
	sprintf(Probe3Factorstr,"   %04d",Result[CurResNo].ProbeFactor[2]);
	sprintf(Probe4Factorstr,"   %04d",Result[CurResNo].ProbeFactor[3]);
	sprintf(Probe5Factorstr,"   %04d",Result[CurResNo].ProbeFactor[4]);
	sprintf(Probe6Factorstr,"   %04d",Result[CurResNo].ProbeFactor[5]);
	sprintf(Probe7Factorstr,"   %04d",Result[CurResNo].ProbeFactor[6]);
	sprintf(Probe8Factorstr,"   %04d",Result[CurResNo].ProbeFactor[7]);
	
	Probe1Factorstr[2] = Probe1Factorstr[3];
	Probe1Factorstr[3]='.';
	Probe2Factorstr[2] = Probe2Factorstr[3];
	Probe2Factorstr[3]='.';
	Probe3Factorstr[2] = Probe3Factorstr[3];
	Probe3Factorstr[3]='.';
	Probe4Factorstr[2] = Probe4Factorstr[3];
	Probe4Factorstr[3]='.';
	Probe5Factorstr[2] = Probe5Factorstr[3];
	Probe5Factorstr[3]='.';
	Probe6Factorstr[2] = Probe6Factorstr[3];
	Probe6Factorstr[3]='.';
	Probe7Factorstr[2] = Probe7Factorstr[3];
	Probe7Factorstr[3]='.';
	Probe8Factorstr[2] = Probe8Factorstr[3];
	Probe8Factorstr[3]='.';
		
	if(Result[CurResNo].ProbePolarity[0] == 0)
	strncpy(Probe1Factorstr,"+",1);
	else
	strncpy(Probe1Factorstr,"-",1);

	if(Result[CurResNo].ProbePolarity[1] == 0)
	strncpy(Probe2Factorstr,"+",1);
	else
	strncpy(Probe2Factorstr,"-",1);

	if(Result[CurResNo].ProbePolarity[2] == 0)
	strncpy(Probe3Factorstr,"+",1);
	else
	strncpy(Probe3Factorstr,"-",1);
	
	if(Result[CurResNo].ProbePolarity[3] == 0)
	strncpy(Probe4Factorstr,"+",1);
	else
	strncpy(Probe4Factorstr,"-",1);

	if(Result[CurResNo].ProbePolarity[4] == 0)
	strncpy(Probe5Factorstr,"+",1);
	else
	strncpy(Probe5Factorstr,"-",1);

	if(Result[CurResNo].ProbePolarity[5] == 0)
	strncpy(Probe6Factorstr,"+",1);
	else
	strncpy(Probe6Factorstr,"-",1);

	if(Result[CurResNo].ProbePolarity[6] == 0)
	strncpy(Probe7Factorstr,"+",1);
	else
	strncpy(Probe7Factorstr,"-",1);

	if(Result[CurResNo].ProbePolarity[7] == 0)
	strncpy(Probe8Factorstr,"+",1);
	else
	strncpy(Probe8Factorstr,"-",1);
	
	DrawTitleBar();
	Bar( 5,(YMAX/8)-22 , XMAX-7 , YMAX-(YMAX/8)-10 ,BLACK); 
	Bar( 7,(YMAX/8)-20 , XMAX-5 , YMAX-(YMAX /8)-8,WHITE); 
	Bar( 7,(YMAX/8)-20 , XMAX-7 , (YMAX- (YMAX /8)-10),BLUE);
	 
	Bar( 17,(YMAX/8)-10 ,(XMAX/4)-17 ,(YMAX- (YMAX /8)-18),BLACK);
	Bar( 19,(YMAX/8)-8  ,(XMAX/4)-15 ,(YMAX- (YMAX /8)-16),WHITE);
	Bar( 19,(YMAX/8)-8  ,(XMAX/4)-17 ,(YMAX- (YMAX /8)-18),BLUE);
	Bar( (XMAX/4)-10    ,(YMAX/8)-10 , (XMAX/2)+(XMAX/3)+10,(YMAX- (YMAX /8)-18),BLACK);
	Bar( (XMAX/4)-8     ,(YMAX/8)-8  , (XMAX/2)+(XMAX/3)+12,(YMAX- (YMAX /8)-18)+2,WHITE);
	Bar( (XMAX/4)-8     ,(YMAX/8)-8  , (XMAX/2)+(XMAX/3)+10,(YMAX- (YMAX /8)-18),BLUE);

	for( y = YMAX/8, i = 0; i < 9 ; y += ystep,i++)
	{	outtext_xy( x , y , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)Probestr[i] , (INT8U *)NORMALFONT ,TRANSPARENT);
	}
	x = XMAX/2; 
	for( y = YMAX/8, i = 9; i<18 ; y += ystep,i++)
	{	outtext_xy( x , y , FONTCOLOR ,OLDVAL_BACK_COLOR ,(INT8U *)Probestr[i] , (INT8U *)NORMALFONT ,TRANSPARENT);
	}
	DrawButtonBar();
}

void ExitEditVal(void)
{
	if(Key == KEYENT)		Newscreen = AllScreens[CurrentScreen].EnterScreen[0];/*2;*/
	else if(Key == KEYCANCEL)	Newscreen = AllScreens[CurrentScreen].EscScreen;/*2;*/
}

void UpdateTextbox( INT16U X1, INT16U Y1, INT16U X2, INT16U Y2,INT8U * string,INT8U Fontcolour,INT8U backColour )
{
	Bar( X1,Y1,X2-2,Y2-2,backColour);
	outtext_xy( X1+28, Y1+10 , Fontcolour, 0, (INT8U *)string ,NORMALFONT, TRANSPARENT );
}
void DrawTextbox( INT16U X1, INT16U Y1, INT16U X2, INT16U Y2,INT8U * string,INT8U Fontcolour,INT8U backColour )
{
	Bar( X1-2,Y1-2,X2,Y2,BLACK);
	Bar( X1,Y1,X2,Y2,WHITE);
	Bar( X1,Y1,X2-2,Y2-2,backColour);
	outtext_xy( X1+28, Y1+10 , Fontcolour, 0, (INT8U *)string ,NORMALFONT, TRANSPARENT );
}



void UpdateBarGraph( INT16U X1, INT16U Y1, INT16U X2, INT16U Y2,INT8U * title,INT16U barminval,INT16U barmaxval ,INT16U barval, INT8U barColour)
{
	Bar( X1+(5)+2,Y1+(5)+2,X2-(5)-2,Y2-(5)-2,WHITE);
	Bar( X1+(5)+2, Y2-(5)-barval,X2-(5)-2,Y2-(5)-2,barColour);
}
void DrawBarGraph( INT16U X1, INT16U Y1, INT16U X2, INT16U Y2,INT8U * title,INT16U barminval,INT16U barmaxval ,INT16U barval, INT8U barColour)
{
	Bar( X1,Y1,X2,Y2,BLACK);
	//Bar( X1,Y1,X2,Y2,WHITE);
	Bar( X1+2,Y1+2,X2-2,Y2-2,GRAY);

	Bar( X1+(5),Y1+(5),X2-(5),Y2-(5),BLACK);
	Bar( X1+(5)+2,Y1+(5)+2,X2-(5)-2,Y2-(5)-2,WHITE);
//calval
	Bar( X1+(5)+2, Y2-(5)-barval,X2-(5)-2,Y2-(5)-2,barColour);
	//Bar( X1+2,Y1+,X2-2,Y2-2,barColour);
	outtext_xy( X1+8, Y2+3 , BLACK, 0, (INT8U *)title ,NORMALFONT, TRANSPARENT );
        
}

INT8U randomval;

UpdateRun()
{
INT8U i,CrRd[6];
INT16U CurBar[26] = { 130,50,7,100,0,10 , 230,150,70,10,190,100,330,250,170,1,90,0, 30,300,270,10,290,30,5,88 };
	
	INT8U CurBarValStr1[6];
	INT8U CurBarValStr2[6];
	INT8U CurBarValStr3[6];
	INT8U CurBarValStr4[6];
	INT8U CurBarValStr5[6];
	INT8U CurBarValStr6[6];

	INT8U *CurValStr[6]= {CurBarValStr1,CurBarValStr2,CurBarValStr3,CurBarValStr4,CurBarValStr5,CurBarValStr6};
	for( i = 0 ; i < 6 ; i++ )
	{
randomval++;
if(randomval > 26) randomval = 0;
		sprintf(CurValStr[i],"%d",CurBar[randomval]);
CrRd[i] = CurBar[randomval];
	}
	UpdateTextbox( 610, 58, 780 ,110, CurBarValStr1, WHITE,  	 2/*INDIGO*/  ) ;
	UpdateTextbox( 610, 114, 780,165, CurBarValStr2, 8/*DARKGREEN*/,  3/*LIGHTMAGENTA*/ ) ;
	UpdateTextbox( 610, 169, 780,220, CurBarValStr3, RED,    	 4/*LIGHTYELLOW*/ ) ;
	UpdateTextbox( 610, 224, 780,275, CurBarValStr4, 6/*INDIGO*/,     10/*LIGHTORANGE*/ ) ;
	UpdateTextbox( 610, 279, 780,330, CurBarValStr5, 13/*BROWN*/,  	 1/*PARROTGREEN*/ ) ;
	UpdateTextbox( 610, 334, 780,385, CurBarValStr6, 1/*ORANGE*/, 	 14/*SKYBLUE*/ ) ;

	UpdateBarGraph( 10,  57, 90,387, "CH1", 0, 1000,CrRd[0]/* CurBar[0]*/ , 2/*INDIGO*/);
	UpdateBarGraph( 110, 57, 190,387, "CH2", 0, 1000, CrRd[1]/*CurBar[1]*/ , 3/*LIGHTMAGENTA*/);
	UpdateBarGraph( 210, 57, 290,387, "CH3", 0, 1000, CrRd[2]/*CurBar[2]*/ , 4/*LIGHTYELLOW*/);
	UpdateBarGraph( 310, 57, 390,387, "CH4", 0, 1000, CrRd[3]/*CurBar[3]*/ , 10/*LIGHTORANGE*/);
	UpdateBarGraph( 410, 57, 490,387, "CH5", 0, 1000, CrRd[4]/*CurBar[4]*/ , 1/*PARROTGREEN*/);
	UpdateBarGraph( 510, 57, 590,387, "CH6", 0, 1000, CrRd[5]/*CurBar[5]*/ , 14/*SKYBLUE*/);


}

void DrawRunScreen(void)
{
	INT16U CurBarVal[6] = { 30,50,70,10,190,100};
	INT8U i;
	INT8U CurBarValStr1[6];
	INT8U CurBarValStr2[6];
	INT8U CurBarValStr3[6];
	INT8U CurBarValStr4[6];
	INT8U CurBarValStr5[6];
	INT8U CurBarValStr6[6];

	INT8U *CurValStr[6]= {CurBarValStr1,CurBarValStr2,CurBarValStr3,CurBarValStr4,CurBarValStr5,CurBarValStr6};
	
	for( i = 0 ; i < 6 ; i++ )
	{
		sprintf(CurValStr[i],"%d",CurBarVal[i]);
	}

	DrawTextbox( 610, 58, 780 ,110, CurBarValStr1, WHITE,  	 2/*INDIGO*/  ) ;
	DrawTextbox( 610, 114, 780,165, CurBarValStr2, 8/*DARKGREEN*/,  3/*LIGHTMAGENTA*/ ) ;
   	DrawTextbox( 610, 169, 780,220, CurBarValStr3, RED,    	 4/*LIGHTYELLOW*/ ) ;
    	DrawTextbox( 610, 224, 780,275, CurBarValStr4, 6/*INDIGO*/,     10/*LIGHTORANGE*/ ) ;
    	DrawTextbox( 610, 279, 780,330, CurBarValStr5, 13/*BROWN*/,  	 1/*PARROTGREEN*/ ) ;
    	DrawTextbox( 610, 334, 780,385, CurBarValStr6, 1/*ORANGE*/, 	 14/*SKYBLUE*/ ) ;

    DrawBarGraph( 10,  57, 90,387, "CH1", 0, 1000, CurBarVal[0] , 2/*INDIGO*/);
    DrawBarGraph( 110, 57, 190,387, "CH2", 0, 1000, CurBarVal[1] , 3/*LIGHTMAGENTA*/);
    DrawBarGraph( 210, 57, 290,387, "CH3", 0, 1000, CurBarVal[2] , 4/*LIGHTYELLOW*/);
    DrawBarGraph( 310, 57, 390,387, "CH4", 0, 1000, CurBarVal[3] , 10/*LIGHTORANGE*/);
    DrawBarGraph( 410, 57, 490,387, "CH5", 0, 1000, CurBarVal[4] , 1/*PARROTGREEN*/);
    DrawBarGraph( 510, 57, 590,387, "CH6", 0, 1000, CurBarVal[5] , 14/*SKYBLUE*/);
}

void Run(void)
{
	DrawTitleBar();
	DrawRunScreen();
	DrawButtonBar();
}
/////////////////                 NUMBER                     ///////////////////////////////////////////////////

void NumberScreen( void )
{
	CurNum = (NumberStructure*)AllScreens[CurrentScreen].ObjPtr;
	DrawTitleBar();
	if(dp_edit_flag){ CurNum->dp_pos = res_dppos; dp_edit_flag = 0;}
printf("Curno dppos = %d\n",CurNum->dp_pos);	
	if( num > CurNum->HiLimit) num = CurNum->HiLimit;
	if( num < CurNum->LoLimit) num = CurNum->LoLimit;
	DrawNumberBar(*(CurNum->CurVal));
	DrawButtonBar();
	incr = 1; dig_no = 5;
	if(CurNum->dp_pos) dig_no = 6;
	num = *(CurNum->CurVal);
}

void UpdateNumberVal(INT32U number)
{	switch(Key)
	{
        	case KEYDEC	: if( CurNum->EditType == DIGBYDIG )digbydig = 1;
				  else digbydig = 0; 
				  UpdateNumberBar(number,CurNum->HiLimit , CurNum->LoLimit,NEWBAR);
			          break;
		case KEYINC	: if( CurNum->EditType == DIGBYDIG )digbydig = 1;
				  else digbydig = 0;
	 			  UpdateNumberBar(number,CurNum->HiLimit , CurNum->LoLimit,NEWBAR);
				  break;
		case KEYSHIFT	: if( CurNum->EditType == DIGBYDIG )digbydig = 1;
				  else digbydig = 0; 
				  UpdateNumberBar(number,CurNum->HiLimit , CurNum->LoLimit,NEWBAR);
				  break;
		case KEYENT	: UpdateNumberBar(number,CurNum->HiLimit , CurNum->LoLimit,OLDBAR);break;
		case KEYCANCEL	: UpdateNumberBar(number,CurNum->HiLimit , CurNum->LoLimit,NEWBAR);break;
	}
	digbydig = 0;
}

void NumberEdit( void )
{	INT8U maxdig = 9,mindig = 0,i;
	INT32U oldnum = *(CurNum->CurVal),dig,maxincr = 1;
	for(i=0;i < (CurNum->NoDigit-1); i++)
	{
		maxincr*=10;
	}

//	oldnum = *( CurNum->CurVal ) ;
	switch (Key)
	{	case KEYSHIFT: if( CurNum->EditType == DIGBYDIG ) 
			       {incr*=10;dig_no--;
				if(CurNum->dp_pos) 
				{ 
					if(dig_no == CurNum->dp_pos){ dig_no--;}
				}
				if( incr > maxincr ) {incr = 1; dig_no = 5; if(CurNum->dp_pos)dig_no = 6;}//CurNum->NoDigit - 1;}
		       	       } break;

		case KEYINC  : if( CurNum->EditType == DIGBYDIG ) 
			       { if(((num%(10*incr))/incr)< maxdig)
				 num += incr; 
				 dig = ((num%(10*incr))/incr);
				 //sprintf(curdig,"%d",dig);
		     	       }	
		     	       else if( CurNum->EditType == WHOLE )
		     	       { num += 1 ;
		    		 if( num > CurNum->HiLimit) num = CurNum->HiLimit;
		     	       } break;

		case KEYDEC  : if( CurNum->EditType == DIGBYDIG ) 
			       { if(((num%(10*incr))/incr)> mindig)
		     		 num -= incr;
				 dig = ((num%(10*incr))/incr);
				 //sprintf(curdig,"%d",dig);
			       }
		     	       else if( CurNum->EditType == WHOLE )
		     	       { num -= 1 ;
		        	 if( num < CurNum->LoLimit) num = CurNum->LoLimit;
		     	       } break;

		case KEYCANCEL: num = oldnum;digbydig =0;
				Newscreen = AllScreens[CurrentScreen].EscScreen;/*2;*/
				if(CurNum->ExtHook != NULL)CurNum->ExtHook();
	   	 		break;

		case KEYENT   : digbydig = 0; 
//				CurNum->CurVal = num;
				*(CurNum->CurVal) = num ;
				Newscreen = AllScreens[CurrentScreen].EnterScreen[0];/*1;*/
				if(CurNum->EntHook != NULL)CurNum->EntHook();
		 		break;
	}UpdateNumberVal( num );
}

///////////////////////////////            MENU              ////////////////////////////////////////////////

MenuScreen( void )
{
	INT8U cur_menu_str[50]; 
	INT32U MENU_BACK, x = 0 , y = 0 , i = 0 ,xmenu = 0 , ymenu = 0 ,ystep = 0 ;
	CurMenu = (MenusStructure *)AllScreens[CurrentScreen].ObjPtr;
	CurMenuChar = CurMenu->allstrings;
	INT8U strlenval = 20;//CurMenu->NoDigit;//10; //testonly
	clearscreen( SCR_BACK_COLOR );
        choice = *(CurMenu->OldChoice); 

	xmenu = (XMAX/2) - (XMAX /4) ;
	ymenu = 40;
	ystep = 32;//(((y - (YMAX/8)) - 30) /5);// CurMenu->NoChoice ) ;
	DrawTitleBar();
	Bar( xmenu - 30, ymenu + 6 , XMAX - (XMAX/3)-2 , YMAX - (YMAX/6)-2 , BLACK );
	Bar( xmenu - 28, ymenu + 8 , XMAX - (XMAX/3) , YMAX - (YMAX/6) , WHITE );
	Bar( xmenu - 28, ymenu + 8 , XMAX - (XMAX/3)-2  , YMAX - (YMAX/6) - 2 ,BLUE );
	
	for( i = 0 ; i < CurMenu->NoChoice ; i++ )
	{
		x = xmenu;	y = ymenu + ystep ;	ymenu = y;
		Bar( x - 5 , y - 5 ,( x + (strlenval*15)+ 2) ,( y + cur_font.Height) ,BLACK);
		if( i == *(CurMenu->OldChoice) )MENU_BACK = MENU_ACTIVE_BACK;
		else MENU_BACK = MENU_INACTIVE_BACK; 
		Bar( x - 3 , y - 3, (x + (strlenval*15)) ,( y + cur_font.Height - 2) ,MENU_BACK);
	 	strncpy(cur_menu_str,CurMenuChar,CurMenu->NoDigit);
		cur_menu_str[CurMenu->NoDigit] = '\0';
		outtext_xy( x + 20, y , FONTCOLOR , MENU_BACK , (INT8U *)cur_menu_str, (INT8U *)NORMALFONT , TRANSPARENT);
		CurMenuChar += CurMenu->NoDigit;
	}
	DrawButtonBar();
}

void UpdateMenuVal( INT8U ChoiceCode )
{
	INT8U cur_menu_str[50] ;
	CurMenuChar = CurMenu->allstrings;
	//INT8U strlenval = CurMenu->NoDigit ;//10; //testonly
	INT8U strlenval = 20; //testonly
	INT32U x = 0 , y = 0 , i = 0 ,xmenu = 0 , ymenu = 0 ,ystep = 0 ,MENU_BACK;
	xmenu = (XMAX/2) - (XMAX /4) ;
	ymenu = 40;
	ystep = 32;//(((y - (YMAX/8)) - 30) /5);// CurMenu->NoChoice ) ;
	
Init[0] = 0;
	for( i = 0 ; i < CurMenu->NoChoice ; i++ )
	{
		x = xmenu;
		y = ymenu + ystep ;
		ymenu = y;
		Bar( x - 5 , y - 5 , (x + (strlenval*15)+ 2) , (y + cur_font.Height) , BLACK);
		if( i == ChoiceCode )
		{
			MENU_BACK = MENU_ACTIVE_BACK;
			if(Key == KEYENT) MENU_BACK = GREEN;
		}
		else MENU_BACK = MENU_INACTIVE_BACK; 
		Bar( x - 3 , y - 3 , (x + (strlenval*15)) , (y + cur_font.Height - 2) , MENU_BACK);
	 	strncpy(cur_menu_str,CurMenuChar,CurMenu->NoDigit);
		cur_menu_str[CurMenu->NoDigit] = '\0';
	 	outtext_xy( x + 20 , y , FONTCOLOR , MENU_BACK , (INT8U *) cur_menu_str, (INT8U *)NORMALFONT , TRANSPARENT);
		CurMenuChar += CurMenu->NoDigit ;
	}	
}

void MenusSurf( void )
{	
	INT8U nochoice = CurMenu->NoChoice;
	INT8U oldchoice = *(CurMenu->OldChoice);
	switch(Key)
	{
		case KEYDEC   : if(choice == 0/*&0x80*/) choice = nochoice - 1 ;
				else choice--;
			     	break;

		case KEYINC   : choice++;
			     	if(choice == nochoice) choice = 0 ;
  			     	break;

		case KEYENT   : *(CurMenu->OldChoice) = choice ;
				Current_Choice = choice;
				Newscreen = AllScreens[CurrentScreen].EnterScreen[choice];/*0;*/ 
				if((CurMenu->EntHook[choice]) != NULL) CurMenu->EntHook[choice]();
		  	   	break;

		case KEYCANCEL: choice = oldchoice ; 
				Newscreen = AllScreens[CurrentScreen].EscScreen;/*1;*/
				if((CurMenu->ExtHook) != NULL) CurMenu->ExtHook(); 		    
			  	break;
	}
	UpdateMenuVal(choice);
}

//////////////////////////               ADC-NUM           //////////////////////////////////////////////////


INT16U adc_to_val( INT16U CurAdcVal)
{

INT16U ConvVal;

    if(Hi_Calib_flag) { Fixture[CurFixNo].ResultHighMaster[ CurResNo ] = CurAdcVal;}	/* Result Calibration: slope */

    else if(Lo_Calib_flag){Fixture[CurFixNo].ResultLowMaster[ CurResNo ] =  CurAdcVal;}	/* Result Calibration: origin */

    else if(ProbeSettMaster_flag){Fixture[CurFixNo].ResultProbeSettMaster[ CurResNo ] =  CurAdcVal;}

    else return CurAdcVal;

// CalCulate Value to be displayed
    

    return ConvVal;

}
void ADCNumberScreen( void )
{
	CurADCNum = (AdcNumberStructure *)AllScreens[CurrentScreen].ObjPtr;
	clearscreen( SCR_BACK_COLOR );
	DrawTitleBar();
	DrawNumberBar(CurADCNum->CalCount);				
	DrawButtonBar();
} 

void UpdateADCNumberScreen( INT16U val)
{
	INT32U hilim = CurADCNum->HiLimit;
	INT32U lolim = CurADCNum->LoLimit;

	val = adc_to_val(val);

	if(update_cur_flag){UpdateNumberBar(val , hilim ,lolim,NEWBAR);	}

	if(store_cur_flag) {UpdateNumberBar(val , hilim ,lolim,OLDBAR);	}

	if(old_val_flag)   {UpdateNumberBar(val , hilim ,lolim,NEWBAR);	}
}

void AdcNumberEdit( void )
{
	switch (Key)
	{
		case KEYNEWADC:	update_cur_flag = 1 ;
				UpdateADCNumberScreen( ADC_Val );
				break;
		case KEYENT   :	store_cur_flag  = 1 ;	
				UpdateADCNumberScreen( ADC_Val );
				adccal_flag = 0;
				CurADCNum->CalCount = ADC_Val;
				Newscreen = AllScreens[CurrentScreen].EnterScreen[0];//2; 
				break;
		case KEYCANCEL:	old_val_flag    = 1 ;	
				UpdateADCNumberScreen( CurADCNum->CalCount );
				adccal_flag = 0;
				Newscreen = AllScreens[CurrentScreen].EscScreen;//0; 
				break;
	}
	update_cur_flag = 0 ; store_cur_flag  = 0 ; old_val_flag    = 0 ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Drawscreen( INT8U screen )
{
	sleep(1);
	switch ( screen )//AllScreens[screen].ScreenType )
	{
		case NUMBERS 	: NumberScreen( );break; 
		case ADCNUMBERS : ADCNumberScreen( );  
				  accumes = 0; reads = 0;
				  adccal_flag = 1;break;
		case MENUS 	: MenuScreen( );  break;
		case STRINGS	: StringDraw();   break;
		case VIEW	: DisplaySetValues();break;
		case DISPBAR	: Run();   	  break;
	}
}
 
void IManager( void )
{
	if ( Newscreen != CurrentScreen )
	{
		CurrentScreen = Newscreen ;
		Drawscreen( AllScreens[Newscreen].ScreenType ) ;
	}
	Key = GetKey();
	if ( Key != NOKEY )
	{
		ButtonUpdate(Key+1);

		switch(AllScreens[CurrentScreen].ScreenType)
		{
		  case NUMBERS	 : NumberEdit();   		break;
		  case ADCNUMBERS: AdcNumberEdit();usleep(3000);break;
		  case MENUS	 : MenusSurf();    		break;
		  case STRINGS	 : StringEdit();   		break;
		  case VIEW	 : ExitEditVal();		break;
		  case DISPBAR	 : UpdateRun();	   		break;
		}
		Key = 9 ;
		KeyPressed = 0 ;

	}
}
//////////////////////////////////////////////////////////////////////////////////////
// I2C Function Prototypes
void i2c_init();
struct bcm2835_peripheral bsc1 = {BSC1_BASE};
 
// Initialize I2C
void i2c_init()
{
    INP_GPIO(2);
    SET_GPIO_ALT(2, 0);
    INP_GPIO(3);
    SET_GPIO_ALT(3, 0);
}  
 
// Function to wait for the I2C transaction to complete
void wait_i2c_done() 
{
        int timeout = 50;
        while((!((BSC1_S) & BSC_S_DONE)) && --timeout) {
            usleep(1000);
        }
        if(timeout == 0)
            printf("Error: wait_i2c_done() timeout.\n");
}


void initvals(void)
{
	
  INT8U i,j;

	for( j = 0 ; j < NUM_PROBES ; j++ )
	{
		Probe[j].ProbeStatus = 0;	/* enabled/disabled */
    		Probe[j].ProbeZeroCount = 0; 	/* ADC Calibration ? origin */
    		Probe[j].ProbeSpanCount = 0;	/* ADC Calibration ? slope */
    		Probe[j].ProbeZeroVal = 0;
    		Probe[j].ProbeSpanVal = 0;
	}

	for( i = 0 ; i < NUM_FIXTURES ;i++ )
	{
		for( j = 0 ; j < MAX_RESULTS ; j++ )
		{
			Result[j].Lable[i] = 0;                 /* curr val/min/max/avg/tir/minmin/maxmax options */
    			Result[j].ProbePolarity[i]= 0;
    			Result[j].ProbeFactor[i]= 0;
			Fixture[i].Dimension[j]= 0;	/* ID/OD */
    			Fixture[i].Unit[j]= 0;		/* metric/inch */
    			Fixture[i].Type[j]= 0;		/* comparative/absolute */
    			Fixture[i].Mode[j]= 0;		/* static/dynamic */
    			Fixture[i].ResultType[j]= 0;///* curr val/min/max/avg/tir/minmin/maxmax options */
    			Fixture[i].SlopeCalibration[j]= 0;	/* En/Dis */
	
    			Fixture[i].NominalValue[j]= 0;          /* nominal value of the result */
    			Fixture[i].Utl[j]= 0;                   /* upper tolerance limit */
    			Fixture[i].Ltl[j]= 0;                   /* lower tolerance limit */
    			Fixture[i].RangeHigh[j]= 0;             /* upper end of range calculated by s/w as UTL + (50% of (UTL-LTL)) */
    			Fixture[i].RangeLow[j]= 0;              /* lower end of range calculated by s/w as LTL ? (50% of (UTL-LTL)) */

	    		Fixture[i].LowerMasterValue[j]= 0;	/* Lower Master Value */
    			Fixture[i].HigherMasterValue[j]= 0;	/* Higher Master Value */
    			Fixture[i].ProbeSettMasterValue[j]= 0;	/* ProbeSetting Master Value */
		}
 		

    		Fixture[i].NumResults = 6 ;
    		Fixture[i].OperatorIDval = 0 ;
    		Fixture[i].OperatorIDstat = 0 ;
  		Fixture[i].TransmissionType = 0 ;  
    		Fixture[i].TxDataType = 0 ;  
    		Fixture[i].SlopeCalEnbStat = 0 ;  
    		Fixture[i].RTCEnbStat = 0 ;

	}

	for( i = 0 ; i < NUM_FIXTURES ;i++ )
	{
		for( j = 0 ; j < 17 ; j++ )
		{
			Fixture[i].Lable[i] = 0 ;	/* sixteen character string input */
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

// application entry point
int main(void)
{
    INT32U drx,dry, i;
    int fbfd = 0;
    struct fb_var_screeninfo orig_vinfo;
    long int screensize = 0;
    Current_Choice = 0; pre_button =0 ;
    cur_lim = 6;

initvals();

    if(map_peripheral(&gpio) == -1) {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -1;
    }
    if(map_peripheral(&bsc1) == -1) {
        printf("Failed to map the physical BSC1 (I2C) registers into the virtual memory space.\n");
        return -1;
    }

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (!fbfd) {
      printf("Error: cannot open framebuffer device.\n");
      return(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
      printf("Error reading variable information.\n");
    }
    printf("Original %dx%d, %dbpp\n", vinfo.xres, vinfo.yres, 
       vinfo.bits_per_pixel );

    // Store for reset (copy vinfo to vinfo_orig)
    memcpy(&orig_vinfo, &vinfo, sizeof(struct fb_var_screeninfo));

    // Change variable info
    vinfo.bits_per_pixel = 8;
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo)) {
      printf("Error setting variable information.\n");
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
      printf("Error reading fixed information.\n");
    }

	 digbydig = 0; 
    // map fb to user mem 
    screensize = vinfo.xres * vinfo.yres;
    fbp = (char*)mmap(0, 
              screensize, 
              PROT_READ | PROT_WRITE, 
              MAP_SHARED, 
              fbfd, 
              0);

    if ((int)fbp == -1) {
        printf("Failed to mmap.\n");
    }
    else {
        // draw...
        /*draw();
	for(drx = 0;drx < 800 ;drx++)
	{
		if(drx < 480) dry = drx;
		put_pixel(drx,dry,4);
	}
        sleep(5);
	for(drx = 0;drx < 16 ;drx++)
	{
		clearcsreen(drx);
		sleep(2);
	}*/
         
        i2c_init();
	/*clearscreen(0);
	get_reading();
	Grid(50,50,450,350,40,30,8);
	Plotgraph(50,350,1,1,450,350,4);
	BarGraph(8,50,360,450,460,7);
	DrawMeter(460,50,790,250,50,10,4);
	outtext_xy((INT16U)600,(INT16U)300,(INT8U)4,(INT8U)7,(INT8U *)str1,(INT8U *)Arial18h,(INT8U)TRANSPARENT);
	//sleep(5);
	outtext_xy(500,350,4,7,(INT8U *)str2,(INT8U *)Arial18h,NONTRANSPARENT);
	//sleep(25);
	getchar();

	clearscreen(0);
	Bar(5,5,785,475,7);:
	Bar(20,20,100,70,0);
	Bar(22,22,98,68,7);
	
	Bar(15,100,85,472,0);
	Bar(17,102,83,470,7);
	Line(35,100,35,472,0);
	Bar(17,102,34,200,6);

	DrawBakerBar(0,0,100,480);
*/
	CurrentScreen = 3 ;Newscreen = 1 ;
	while(1)
	{
		IManager();
	}
	/*AllScreens[CurrentScreen].Title = " NUMBER EDIT ";
	NumberScreen();
	getchar();
	AllScreens[CurrentScreen].Title = " MENU EDIT ";
	MenuScreen();
	getchar();
	AllScreens[CurrentScreen].Title = " ADC NO DISP ";
	ADCNumberScreen();
	getchar();*/
    }		
    unmap_peripheral(&gpio);
    unmap_peripheral(&bsc1);
    // cleanup
    munmap(fbp, screensize);
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
        printf("Error re-setting variable information.\n");
    }
 //   close(fbfd);

    return 0;
  
}

