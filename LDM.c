
#include "LDM.h"
#include "htc.h"
#include "font.h"
#include "PIC16f887_interface.h"
#include "general.h"

unsigned int dispRam1[32];
unsigned int dispRam2[32];
unsigned int right_side[20];
struct character			char_cntrl;
//unsigned char display_str[40];

void putRowData(unsigned int data1, unsigned int data2)
{
	unsigned char i=0;

	ROW_RSTB = 0;
	ROW_RSTB = 1;
	for(i=0; i<=15; i++)
	{
		ROW_DATA2=(data1&0x0001) ? 1:0;			data1>>=1;
		ROW_DATA1=(data2&0x0001) ? 1:0;			data2>>=1;
		ROW_CLK = 0;	
		ROW_CLK = 1;
	}
//	ROW_LAT = 0;
//	ROW_LAT = 1;
}	

void refresh_display()
{
	unsigned char i=31;

	COL_RSTB = 0;
	COL_RSTB = 1;
	COL_DATA1 = COL_DATA2 = 1;
	ROW_ENB  = 0;
	COL_ENB = 1;
	putRowData(dispRam1[i], dispRam2[i]);
	ROW_LAT = 0;
	ROW_LAT = 1;
	i--;
	for(;;)
	{	
		COL_CLK =0;
		COL_CLK =1;
		COL_LAT = 0;
		COL_LAT = 1;

		COL_ENB = 0;
		if(i==0xFF)	break;
		__delay_us(600);
		putRowData(dispRam1[i], dispRam2[i]);
		i--;
		COL_DATA1 = COL_DATA2 = 0;
		COL_ENB = 1;
		ROW_LAT = 0;
		ROW_LAT = 1;
	}	
	__delay_us(600);
}	

void charUpdate()
{
	unsigned char charac;
	unsigned char i;
	unsigned char *ptr;
	unsigned int temp;
	unsigned char col=0;
	unsigned char size=0;
	unsigned char j=0;
	
//	charac=display_str[char_cntrl.char_count];
	charac=eeprom_read(EE_STR_ADD+char_cntrl.char_count+j);
	char_cntrl.char_length = *get_Arial_Rounded_MT_Bold15x16(charac);
	while(charac!=0xFF)
	{
		ptr = get_Arial_Rounded_MT_Bold15x16(charac);
		size = *ptr;
		j++;
		for(i=0; i<size; i++,col++)
		{
			if(i==0)	temp=0;
			else
			{
			
				temp=*(++ptr+1);
				temp<<=8;
				temp|=*(ptr++);
	/*
				temp=*(++ptr);
				temp<<=8;
				temp|=*(++ptr);
		*/
			}	
			if(col<=31)										dispRam1[col]=temp;
			else if(col>=32 && col<=63)		dispRam2[col-32]=temp;
			else if(col>=64 && col<=83)   right_side[col-64] = temp;		
			else return;
		}	
	//	charac=display_str[char_cntrl.char_count+j];
		charac=eeprom_read(EE_STR_ADD+char_cntrl.char_count+j);
	}	
}	

void screenShift()
{
	unsigned char i;
	unsigned int temp=dispRam2[0];
	for(i=0;	i<31; i++)
	{
		dispRam1[i] = dispRam1[i+1];
		dispRam2[i] = dispRam2[i+1];
	}	
		dispRam1[31] = temp;
		dispRam2[31] = right_side[0];
	for(i=0;  i<19; i++)
	{
		right_side[i] = right_side[i+1];
	}	
	right_side[19]=0;
}	

void small_font_disp(unsigned char *ptr, unsigned char length, unsigned char line_no)
{
	unsigned char i=0;
	unsigned char *data_ptr;
	unsigned char count=0;
	unsigned int font_data=0;

	while(length--)
	{
		data_ptr=get_font_5X7(*ptr);
		for(i=0; i<6; i++,count++)
		{
			if(count>64)			return;
			if(i==5)	font_data=00;
			else			font_data=*(data_ptr+i);
			if(line_no==1)    font_data<<=8;
			fillRAM(count, font_data);		
		}
		ptr++;	
	}	
}	
void fillRAM(unsigned char col, unsigned int data)
{
	if(col>=0 && col<32)
	{
		dispRam1[col] |= data;
	}
	else if(col>=32 && col <64)
	{
		dispRam2[col-32] |= data;		
	}
}
void clr_disp()
{
	 _memset((unsigned char *)dispRam1,0x00,sizeof(dispRam1));   
	 _memset((unsigned char *)dispRam2,0x00,sizeof(dispRam2));   
}
		 			