////////////////////////////////////////////////////////////////////////////////

/* RPi side program to get FFT and store for further analysis*/

////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <math.h>

#define INT8U      unsigned char
#define INT16U     unsigned int
#define INT32U	   unsigned long
#define INT8S      signed   char
#define INT16S	   signed   int
#define INT32S     signed   long*/
#define XMAX	800
#define YMAX	480

// 'global' variables to store screen info

char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

//extern INT8U Arial18h[];

//extern INT8U Century_Schoolbook114h[];
//extern const char Arial18h[] __attribute__((aligned(2)));

INT8U keysay,status,dummy,pre_button;
INT16U FFTVal[128];

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

INT8U Key, KeyPressed ;
INT32U num;


INT16U ADC_Val;
INT8U adccal_flag;

typedef void(*Ptr2fun)(void);
/*--------------------------------- Data Structures for Interaction Manager ---------------------------------*/

INT8U GetKey(void);
INT8U GetAdc(void);

INT8U GetFFT()
{	INT32U status;
	INT16U i ;
	BSC1_A = 0x7;
	INP_GPIO(25);
	usleep(5);   
	status = GPIO_READ(25);
	if(status == 0)
	{
		for( i = 0 ; i < 128 ; i++ )
		{
			BSC1_DLEN = 1;
			BSC1_S = CLEAR_STATUS;  // Reset status bits
			BSC1_C = START_READ;    // Start Read after clearing FIFO
			wait_i2c_done();
			FFTVal[i] = BSC1_FIFO;
			printf("FFT[%d] = %d\n",i, FFTVal[i]);
			//return keysay;
		}
	}
	else {printf("FFT Not Ready Yet");}//return 0;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////

// application entry point
int main(void)
{
    INT32U drx,dry, i;
    int fbfd = 0;
    struct fb_var_screeninfo orig_vinfo;
    long int screensize = 0;

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
                 
        i2c_init();

	while(1)
	{
		GetFFT();
	}
	
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

