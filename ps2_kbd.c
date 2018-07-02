
#include <pic.h>
#include "ps2_kbd.h"
#include "PIC16f887_interface.h"
#include "LDM.h"
#include "general.h"
#include "font.h"
#include "eeprom.h"

unsigned char kbd_queue[MAX_QUEUE_SIZE];
unsigned char inptr,outptr;
//unsigned int kbd_count;
//unsigned char delayShift;

struct kbd_vars		bitVars;
unsigned char kbd_byte;
unsigned char bit_count;
//unsigned char started;
//unsigned long kbd_count=0;


const unsigned char key[][2]={
	' ', 0x29,
	'a', 0x1C,
	'b', 0x32,
	'c', 0x21,
	'd', 0x23,
	'e', 0x24,
	'f', 0x2B,
	'g', 0x34,
	'h', 0x33,
	'i', 0x43,
	'j', 0x3B,
	'k', 0x42,
	'l', 0x4B,
	'm', 0x3A,
	'n', 0x31,
	'o', 0x44,
	'p', 0x4D,
	'q', 0x15,
	'r', 0x2D,
	's', 0x1B,
	't', 0x2C,
	'u', 0x3C,
	'v', 0x2A,
	'w', 0x1D,
	'x', 0x22,
	'y', 0x35,
	'z', 0x1A,
	
	'0', 0x45,
  '1', 0x16,
  '2', 0x1E,
  '3', 0x26,
  '4', 0x25,
  '5', 0x2E,
  '6', 0x36,
  '7', 0x3D,
  '8', 0x3E,
  '9', 0x46,

  '`', 0x0E,
  '-', 0x4E,
  '=', 0x55,
  '\\',0x5D,
  '[', 0x54,
  ']', 0x5B,
  ';', 0x4C,
  '\'',0x52,
  ',', 0x41,
  '.', 0x49,
  '/', 0x4A,

	'0', 0x70,
  '1', 0x69,
  '2', 0x72,
  '3', 0x7A,
  '4', 0x6B,
  '5', 0x73,
  '6', 0x74,
  '7', 0x6C,
  '8', 0x75,
  '9', 0x7D,
  
   0,	 0x05,
 	 1,	 0x06,
   2,  0x04,
 	 3,	 0x0C,
 	 4,	 0x03,
 	 5,	 0x0B,
 	 6,	 0X83,
 	 7,	 0X0A,
 	 8,	 0X01,
 	 9,	 0X09,
 	 10, 0X78,
 	 11, 0X07,
 	 
 //	 12, 0X12,
 	 13, 0X14,
 	 14, 0X11,
 //	 15, 0X59,
 	 16, 0X5A,
 	 17, 0X76,
 	 18, 0X66,
// 	 19, 0X29,
 	 20, 0X0D,
 //	 21, 0X58,
 	 22, 0X7E,
 	 //
 
	
	157,	0X77,
	158,	0X7C,
	159,	0X7B,
	160,	0X79,
	161,	0X71


};
const unsigned char Ext_key[][2]={
	 23,	0X70,
 	 24,	0X6C,
 	 25,	0X7D,
 	 26,	0X71,
 	 27,	0X69,
 	 28,	0X7A,
 	 29,	0X75,
 	 30,	0X6B,
 	 31,	0X72,
 	
	
	128,	0X1F,
	129,	0X14,
	130,	0X27,
	131,	0X11,
	132,	0X2F,
	133,	0X7C,
	134,	0X4A,
	135,	0X5A,
	
	136,	0X37,
	137,	0X3F,
	138,	0X5E,
	
	139,	0X4D,
	140,	0X15,
	141,	0X3B,
	142,	0X34,
	143,	0X23,
	144,	0X32,
	145,	0X21,
	146,	0X50,
	147,	0X48,
	
	148,	0X2B,
	149,	0X40,
	
	150,	0X10,
	151,	0X3A,
	152,	0X38,
	153,	0X30,	
	154,	0X28,
	155,	0X20,
	156,	0X18,
	
	162,	0X74
};	
const unsigned char Shift_key[][2]={	
  ')', 0x70,
  '!', 0x69,
  '@', 0x72,
  '#', 0x7A,
  '$', 0x6B,
  '%', 0x73,
  '^', 0x74,
  '&', 0x6C,
  '*', 0x75,
  '(', 0x7D,
  
  '~', 0x0E,
  '_', 0x4E,
  '+', 0x55,
  '|', 0x5D,
  '{', 0x54,
  '}', 0x5B,
  ':', 0x4C,
  '"', 0x52,
  '<', 0x41,
  '>', 0x49,
  '?', 0x4A,

};
  
  
void decode_key(unsigned char data)
{
	unsigned char i=0;
	
	if(bitVars.ExtenKey == 0)
	{
		for(i=0; i<(sizeof(key)/2);	i++)
		{
			if(key[i][1] == data)
			{
				if((i>=27 && i<=48) && bitVars.ShiftKey == 1)
				{
					bitVars.ShiftChar=1;
					fill_kbd_buff(Shift_key[i-27][0]);
					bitVars.ShiftChar=0;
		 		}
		 		else
				{
					fill_kbd_buff(key[i][0]);
			 	}	 		
			 	return;

			}
			
			if(key[i][1] == data)
			{
				fill_kbd_buff(key[i][0]);
		 	 return;
			}
		}
	}	
	else
	{
		for(i=0; i<(sizeof(Ext_key)/2);	i++)
		{
			if(Ext_key[i][1] == data)
			{
				fill_kbd_buff(Ext_key[i][0]);
		 	 return;
			}
		}			
	}	
//	fill_kbd_buff(data);
}	
void fill_kbd_buff(unsigned char data)
{
	if((data>='a' && data<='z') && ((bitVars.ShiftKey==1) || (bitVars.CapsKey==1)) )	
			data-=0x20;
	kbd_queue[inptr++]=data;
	if(inptr==MAX_QUEUE_SIZE)		inptr=0;	
}	
/*
char isKeyLeft()
{
	return (inptr!=outptr);	
}	
*/
void putKey(unsigned char key)
{
	kbd_queue[inptr++]=key;
	if(inptr==MAX_QUEUE_SIZE)		inptr=0;	
	
}	
char getKey()
{
	unsigned char data=kbd_queue[outptr++];
//	outptr=outptr%MAX_QUEUE_SIZE;
	if(outptr == MAX_QUEUE_SIZE)	outptr=0;
	return data;
}	
void kbd()
{
	// check for the clk_pin. make sure it is LOW
	if(KBD_CLK == 1)		return;
	
	if(!bitVars.Started)
	{
		if(KBD_DATA == 0)
		{
			bitVars.Started=1;		
			kbd_byte=0;
			bit_count=0;
		}
			return;		
	}
	else if(bit_count<8)
	{
		if(KBD_DATA==1)			kbd_byte|=(1<<bit_count);
		bit_count++;
		return;
	}	
	else if(bit_count == 8)
	{
		//check for parity. till not implemented here
		bit_count++;
		return;
	}			
	else
	{
		// stop bit
		bit_count=0;
		bitVars.Started=0;
	}	
	// TILL HERE THE COMPLETE BYTE HAS CAME
	
	if(kbd_byte == 0xF0)
	{
		bitVars.Release=1;
		kbd_byte=0;
		return;
	}	
	else if((kbd_byte == KBD_L_SHIFT) || (kbd_byte == KBD_R_SHIFT))	
	{
		if(bitVars.Release == 0)
		{
			bitVars.ShiftKey=1;
		}
		else
		{
			bitVars.ShiftKey=0;
			bitVars.Release=0;
		}		
		return;
	}
	else if(kbd_byte == KBD_CAPS)
	{
		if(bitVars.Release == 1)
			bitVars.CapsKey=~bitVars.CapsKey;

//			bitVars.ShiftKey=~bitVars.ShiftKey;
		bitVars.Release=0;
	}	
	else
	{
		if(bitVars.Release == 0)
		{		
			if(kbd_byte == 0xE0)
			{
				bitVars.ExtenKey=1;	
				return;
			}
		//	asm("nop");
		//	if(bitVars.ExtenKey == 0)
				decode_key(kbd_byte);	
		//	else
		//		fill_kbd_buff(kbd_byte);
		}
		else if(bitVars.Release == 1)		
		{		
	//		kbd_count=0;
			bitVars.Started=0;		
			bitVars.Release=0;
			bitVars.ExtenKey=0;
			
		}
		kbd_byte=0;
	}		
}
void put_cursor(unsigned char loc)
{
	unsigned char i=0;
	unsigned int font_data=0x8000;
	
	loc*=6;
	for(i=0; i<5;	i++,loc++)
	{
		//font_data=0x80;
	//  font_data<<=8;
		fillRAM(loc, font_data);	
	}	
	fillRAM(loc, 0);
}	
void keybrdInput()
{
	unsigned char key=0xFF;
	unsigned char wait=0xEF;
	
	unsigned char max_len=40;
	unsigned char cursor_i=0;
	unsigned char max_i=7;
	unsigned char display_str[7+3];
	unsigned char min_i=2;
	unsigned char offset_i=0;
	unsigned char totalChar=0;
	unsigned char count=0;
	
	clr_disp();
	small_font_disp((unsigned char*)"WAIT...",7,0);

	while(--wait)				refresh_display();

	wait=0XEF;
	clr_disp();
	small_font_disp((unsigned char*)"TYPE NOW.",9,0);
	put_cursor(cursor_i);

	RESET_KEYBUFFER;
	_memset(display_str,' ',sizeof(display_str));
	
	while(key!=KBD_ESC)
	{
		refresh_display();
		if(inptr!=outptr)
		{
			clr_disp();
			key=getKey();
			switch(key)
			{
			/*	
				case KBD_F1:
					select_scrll_speed();
					bitVars.PS2Active=0;
					RESET_KEYBUFFER;
					return;
			//	break;
			*/
				/*
				case KBD_DELETE:
					Back(cursor_i+offset_i, max_len);
				//	Back(display_str,cursor_i+offset_i,sizeof(display_str));
					totalChar--;
				break;
*/
				case KBD_LEFT:			
					if((cursor_i+offset_i)==0)	
						break;
					if((cursor_i > min_i) || (cursor_i <= 2 && offset_i==0))			
							cursor_i--;
					else					offset_i--;			
				break;

				case KBD_RIGHT:
					if((cursor_i+offset_i) == max_len)		
						break;
					if(cursor_i < max_i)		cursor_i++;
					else										offset_i++;
				break;
/*
				case KBD_BACKSPACE:				
						if((cursor_i+offset_i)==0)					break;
						if((cursor_i > min_i) || (cursor_i <= 2 && offset_i==0))			
								cursor_i--;
						else					offset_i--;	
						
						Back(cursor_i+offset_i, max_len);
						//Back(display_str,cursor_i+offset_i,sizeof(display_str));
						totalChar--;
				break;
				*/
				
				case KBD_F2:
					asm("nop");
					count=0;
					while(count!=(max_len+LEAD_TAIL_SPACES/*+LEAD_TAIL_SPACES*/) )
					{
						eeprom_write(EE_STR_ADD+count, ' ');
						count++;	
					}
					totalChar=0;
					offset_i=0;
					cursor_i=0;
					totalChar=0;	
				break;
				
				default:
					if((cursor_i+offset_i) == max_len)		
						break;
					

					if(key>=32 && key<=127)
					{ 
						eeprom_write(EE_STR_ADD+LEAD_TAIL_SPACES+cursor_i+offset_i,key);
					//	display_str[cursor_i+offset_i]=key;
						totalChar++;
						if(cursor_i < max_i)		cursor_i++;
						else										offset_i++;
					}
				break;				
			}
			
			small_font_disp((unsigned char*)"TYPE NOW.",9,0);
		//	small_font_disp(display_str+offset_i,max_i,1);
			
			eeprom_str_read(display_str, LEAD_TAIL_SPACES+offset_i, max_i);

			small_font_disp(display_str,max_i,1);
			put_cursor(cursor_i);
		}
	}	
	
	clr_disp();
	small_font_disp((unsigned char*)"WAIT...",7,0);
		
	while(--wait)			refresh_display();
	clr_disp();
	
	eeprom_write(TOTALBYTES_ADD,totalChar+1*LEAD_TAIL_SPACES);
	
//	eeprom_write(0x00,totalChar+16);
	eeprom_str_write((unsigned char*)"        ", EE_STR_ADD, LEAD_TAIL_SPACES);
//	eeprom_str_write(display_str,EE_STR_ADD+0x09,totalChar);

//	eeprom_str_write((unsigned char*)"        ",EE_STR_ADD+LEAD_TAIL_SPACES+totalChar, LEAD_TAIL_SPACES);
	bitVars.PS2Active=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	
}	
/*
void Back(unsigned char *ptr,unsigned char cur_loc, unsigned char Buffsize)
{
	while(cur_loc != (Buffsize-1))
	{
		*(ptr+cur_loc)=*(ptr+(cur_loc+1));
		cur_loc++;
	}
	*(ptr+cur_loc)=' ';
}
*/

void Back(unsigned char cur_loc, unsigned char Buffsize)
{
	unsigned char tempChar=0;
	unsigned int address = EE_STR_ADD+LEAD_TAIL_SPACES;
	while(cur_loc != (Buffsize-1))
	{
		tempChar = eeprom_read(address+cur_loc+1);
		eeprom_write(address+cur_loc,tempChar);
		cur_loc++;
	}
	eeprom_write(address+cur_loc,' ');	
}

void select_scrll_speed()
{
	unsigned char key=0xFF;
	unsigned char speed_selected=0;
	unsigned char wait=0XFF;
		/*
	clr_disp();
	small_font_disp((unsigned char*)" Sel. Spe",9,0);
	put_cursor(0);

	RESET_KEYBUFFER;
	key=eeprom_read(0xFF);
	if(key!=0xFF)	
		putKey(key);
	
	while(key!=KBD_ESC)
	{
		refresh_display();
		if(inptr!=outptr)
		{
			clr_disp();
			key=getKey();
			
			if(key>='1' && key<='9')
			{ 
				speed_selected = key;
//				display_str[0]=key;
			}

			small_font_disp((unsigned char*)" Sel. Spe",9,0);
//			small_font_disp(display_str,1,1);
			put_cursor(0);
		}
	}
	clr_disp();
	small_font_disp((unsigned char*)"WAIT...",7,0);
	while(--wait)				refresh_display();
	RESET_KEYBUFFER;
	eeprom_write(0xFF,speed_selected);
	
	delayShift=eeprom_read(0xFF);
	if(delayShift==0xFF)		delayShift='1';
	delayShift-='0';
	*/				
}
		