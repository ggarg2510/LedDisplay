

#include <pic.h>
//__CONFIG(0X20F2);
#include "LDM.h"
#include "general.h"
#include "eeprom.h"
#include "PIC16f887_interface.h"
#include "ps2_kbd.h"

	unsigned char NoOfBytes;

void interrupt ISR()
{
//	char j=0;
	static unsigned char delay=0,i=0;
	//GIE = 0;	
//	asm("FSET I");
	if(INTF)
	{
		bitVars.PS2Active=1;
		kbd();
		INTF=0;
	}			
	else if(TMR0IF)					//TIMER 0 INTERRUPT HANDLER
	{ 

		TMR0IE = 0;
	//	putRowData(0,0);
//	for(j=0; j<=128;j++)
		refresh_display();
		TMR0IF=0;
		TMR0IE = 1;
	}	
	else if(TMR1IF)
	{
		TMR1ON=0;	
		TMR0IE = 0;		
		delay++;		  
		//disables the TIMER1 delay check has been made
		//so that screen-shift not to be made after each 
		//interrupt. Done only for the purpose of making 
		//screen-shifting a bit slow and delay check 
		//could be adjusted according to the need.
		if(delay == 1/*delayShift*/)
		{
			delay=0;
			screenShift();
			i++;
			//the "char_cntrl.char_length" will have the
			//character length of the character pointed by
			//"display_str+char_cntrl.char_count". When the
			//screen-shift equivalent to that length has been
			//made, then display screen updation would take
			//place with an increment with "char_cntrl.char_count" 
			if(i == char_cntrl.char_length)
			{
				char_cntrl.char_count++;
				i=0;
				
				if(char_cntrl.char_count>=NoOfBytes)
				{
					char_cntrl.char_count = 0;
					char_cntrl.char_length= 0;
				}
				charUpdate();		
			}
		}	
		TMR1IF=0;
		TMR1ON=1;	
		TMR0IE = 1;
	}		
//	GIE=1;
}	


void main()
{
	unsigned char wait=0xfF;
	bitVars.PS2Active=0;
	bitVars.CapsKey=0;
	COL_ENB = 1;
	ROW_ENB  = 0;

	ANSELH=0x00;
	TRISB=0xFF;
	TRISC=0x00;
	TRISD=0x00;
	PORTD=0x00;
	PORTC=0x00;

	EEPGD=0;
	GIE = 1;	
	PEIE = 1;
	TMR0IE = 0;
	OPTION_REG = 0x04;
	TMR0 = 0;
	TMR0IF=0;
	
	TMR1IE=1;
	TMR1IF=0;
	T1CON=0X30;
	TMR1H=0X0F;
	TMR1L=0XFF;

		

/*
 !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
 */
 

//	_memset(display_str,0,sizeof(display_str));
//NoOfBytes = 22;
//		eeprom_write(TOTALBYTES_ADD,NoOfBytes);
//	_memcpy(display_str, "     VIPERTRONICS     ",22);
	NoOfBytes = eeprom_read(TOTALBYTES_ADD);		//get number of bytes to be read
	if(NoOfBytes == 0xFF)
	{
		eeprom_str_write("        ENTER SOME TEXT        ",EE_STR_ADD,31);
		NoOfBytes = 31;
		eeprom_write(TOTALBYTES_ADD, NoOfBytes);
	}
	
//	eeprom_str_read(display_str,0x01,NoOfBytes);

 //eeprom_str_write((unsigned char*)"     VIPERTRONICS     ", EE_STR_ADD, 22);
	char_cntrl.char_count = 0;
	char_cntrl.char_length= 0;
	clr_disp();
	small_font_disp((unsigned char*)"WAIT...",7,0);

	while(--wait)				refresh_display();

	clr_disp();
	charUpdate();
	TMR1ON=1;
	TMR0IE=1;
	RESET_KEYBUFFER;
	bitVars.PS2Active=0;
	INTEDG = 0;	// denotes falling edge interrupt on RB0
	INTE=1;
	INTF=0;

	while(1)
	{
		if(bitVars.PS2Active==1)
		{
			TMR0IE=0;
			TMR1ON=0;
			keybrdInput();
			if(bitVars.PS2Active==0)
			{
				clr_disp();
				bitVars.PS2Active=0;
		//		_memset(display_str,0,sizeof(display_str));
		
				NoOfBytes = eeprom_read(TOTALBYTES_ADD);		//get number of bytes to be read
		//		eeprom_str_read(display_str,0x01,NoOfBytes);	
				
				char_cntrl.char_count = 0;
				char_cntrl.char_length= 0;
		//		reset_char_cntrl();			
				charUpdate();
				TMR1ON=1;
				TMR0IE=1;
				bitVars.PS2Active=0;
			}
		}	
	}
	
}
/*
void main()
{

 eeprom_str_write((unsigned char*)"     VIPERTRONICS     ", EE_STR_ADD, 22);
	NoOfBytes = eeprom_read(0x00);		//get number of bytes to be read
//	if(NoOfBytes == 0xFF)
	//{
		//eeprom_str_write("        ENTER SOME TEXT        ",0x01,31);
	//	eeprom_write(0x00,22);	
//	}	
	NoOfBytes = 22;//eeprom_read(0x00);
	
	charUpdate();
//		_memset((unsigned char *)&dispRam2, 0xfF, sizeof(dispRam2));
	//		_memset((unsigned char *)&dispRam1, 0xfF, sizeof(dispRam1));
			TMR0IE = 1;
			TMR1IE=1;
	TMR1ON=1;
	bitVars.PS2Active=0;
		while(1)
		
		{
	if(bitVars.PS2Active==1)
	{
				TMR0IE=0;
			TMR1ON=0;
			keybrdInput();
			
	}	
	}
	
}


	/*
	ROW_DATA1=1;
	ROW_DATA2=1;
	COL_DATA1=1;
	COL_DATA2=1;
	
COL_LAT	=1;
	COL_ENB=1;
	COL_RSTB=1;
COL_CLK=1;

ROW_RSTB=1;
ROW_CLK=1;
ROW_LAT=1;
	ROW_ENB=1;
	
		
	ROW_DATA1=0;
	ROW_DATA2=0;
	COL_DATA1=0;
	COL_DATA2=0;
	
COL_LAT	=0;
	COL_ENB=0;
	COL_RSTB=0;
COL_CLK=0;

ROW_RSTB=0;
ROW_CLK=0;
ROW_LAT=0;
	ROW_ENB=0;
	
	#define ROW_DATA1		RC0
#define ROW_DATA2		RC3
#define COL_DATA1		RC1
#define COL_DATA2		RC2

#define	COL_LAT		RD0
#define	COL_ENB		RD1
#define COL_RSTB	RD2
#define COL_CLK		RD3
				  	
#define	ROW_RSTB	RD4
#define	ROW_CLK		RD5
#define	ROW_LAT		RD6
#define	ROW_ENB		RD7
*/
