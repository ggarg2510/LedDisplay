
#ifndef _PS2_KBD_H
#define _PS2_KBD_H
#define MAX_QUEUE_SIZE		5


#define KBD_F1		0
#define KBD_F2		1
#define KBD_F3		2
#define KBD_F4		3
#define KBD_F5		4
#define KBD_F6		5
#define KBD_F7		6
#define KBD_F8		7
#define KBD_F9		8
#define KBD_F10		9
#define KBD_F11		10
#define KBD_F12		11

#define KBD_L_SHIFT			0X12//12
#define KBD_L_CNTRL			13
#define KBD_L_ALT  			14
#define KBD_R_SHIFT			0X59//15
#define KBD_ENTER				16
#define KBD_ESC   			17
#define KBD_BACKSPACE		18
//#define KBD_SPACE	  		19
#define KBD_TAB					20
#define KBD_CAPS			0X58//	21
#define KBD_SCROLL			22


#define KBD_NUM   			157
#define KBD_KP_MUL  		158
#define KBD_KP_SUB				159
#define KBD_KP_ADD				160
#define KBD_KP_DOT 			  161


 
//***************  EXTENDED CODE ****************
#define KBD_INSERT	  	23
#define KBD_HOME	  		24
#define KBD_PGUP				25
#define KBD_DELETE			26
#define KBD_END		 	    27
#define KBD_PGDN   			28
#define KBD_UP		      29
#define KBD_LEFT	  		30
#define KBD_DOWN				31
#define KBD_RIGHT				162


#define KBD_L_GUI		 	  128
#define KBD_R_CNTRL   	129
#define KBD_R_GUI	  	  130
#define KBD_R_ALT		    131
#define KBD_APPS				132
#define KBD_PRTSCR  	  133
#define KBD_KP_/		    134
#define KBD_KP_ENTER		135
		 	
#define KBD_POWER	  	  136
#define KBD_SLEEP		    137
#define KBD_WAKE				138

#define KBD_NXT_TRACK	  139
#define KBD_PRE_TRACK   140
#define KBD_STOP				141
#define KBD_PLAY_PAUSE  142
#define KBD_MUTE		    143
#define KBD_VOL_UP			144
#define KBD_VOL_DOWN 	  145
#define KBD_MEDIA_SEL   146
#define KBD_EMAIL				147

#define KBD_CALC	  	  148
#define KBD_MY_COMP	    149

#define KBD_WWW_SEARCH	    150
#define KBD_WWW_HOME	  	  151
#define KBD_WWW_BACK		    152
#define KBD_WWW_FORWARD			153
#define KBD_WWW_STOP	  	  154
#define KBD_WWW_REFRESH	    155
#define KBD_WWW_FAVORITES		156 




/*
#define KBD_F1		0x05
#define KBD_F2		0x06
#define KBD_F3		0x04
#define KBD_F4		0x0C
#define KBD_F5		0x03
#define KBD_F6		0x0B
#define KBD_F7		0x83
#define KBD_F8		0x0A
#define KBD_F9		0x01
#define KBD_F10		0x09
#define KBD_F11		0x78
#define KBD_F12		0x07

#define KBD_L_SHIFT			0x12
#define KBD_L_CNTRL			0x14
#define KBD_L_ALT  			0x11
#define KBD_R_SHIFT			0x59
#define KBD_ENTER				0x5A
#define KBD_ESC   			0x76
#define KBD_BACKSPACE		0x66
#define KBD_SPACE	  		0x29
#define KBD_TAB					0x0D
#define KBD_CAPS				0x58
#define KBD_SCROLL			0x7E

#define KBD_NUM   			0x77
#define KBD_KP_*	  		0x7C
#define KBD_KP_-				0x7B
#define KBD_KP_+				0x79
#define KBD_KP_. 			  0x71


//***************  EXTENDED CODE ****************
#define KBD_INSERT	  	0x70
#define KBD_HOME	  		0x6C
#define KBD_PGUP				0x7D
#define KBD_DELETE			0x71
#define KBD_END		 	    0x69
#define KBD_PGDN   			0x7A
#define KBD_UP		      0x75
#define KBD_LEFT	  		0x6B
#define KBD_DOWN				0x72
#define KBD_RIGHT				0x74

#define KBD_L_GUI		 	  0x1F
#define KBD_R_CNTRL   	0x14
#define KBD_R_GUI	  	  0x27
#define KBD_R_ALT		    0x11
#define KBD_APPS				0x2F
#define KBD_PRTSCR  	  0x7C
#define KBD_KP_/		    0x4A
#define KBD_KP_ENTER		0x5A

#define KBD_POWER	  	  0x37
#define KBD_SLEEP		    0x3F
#define KBD_WAKE				0x5E

#define KBD_NXT_TRACK	  0x4D
#define KBD_PRE_TRACK   0x15
#define KBD_STOP				0x3B
#define KBD_PLAY_PAUSE  0x34
#define KBD_MUTE		    0x23
#define KBD_VOL_UP			0x32
#define KBD_VOL_DOWN 	  0x21
#define KBD_MEDIA_SEL   0x50
#define KBD_EMAIL				0x48

#define KBD_CALC	  	  0x2B
#define KBD_MY_COMP	    0x40

#define KBD_WWW_SEARCH	    0x10
#define KBD_WWW_HOME	  	  0x3A
#define KBD_WWW_BACK		    0x38
#define KBD_WWW_FORWARD			0x30
#define KBD_WWW_STOP	  	  0x28
#define KBD_WWW_REFRESH	    0x20
#define KBD_WWW_FAVORITES		0x18
*/

#define RESET_KEYBUFFER				inptr=outptr

struct kbd_vars
{
	unsigned char Started:1;
	unsigned char Release:1;
	unsigned char ExtenKey:1;	
	unsigned char ShiftKey:1;	
	unsigned char CapsKey:1;	
	unsigned char PS2Active:1;
	unsigned char ShiftChar:1;
};
extern unsigned char delayShift;

extern unsigned char inptr,outptr;
extern unsigned char kbd_byte;
extern unsigned char bit_count;
//extern unsigned long kbd_count;
extern struct kbd_vars		bitVars;
extern unsigned char kbd_queue[MAX_QUEUE_SIZE];
void decode_key(unsigned char data);
void fill_kbd_buff(unsigned char data);
void reset_keyBuffer();
char isKeyLeft();
void putKey(unsigned char key);
char getKey();
void kbd();
void keybrdInput();
void Back(unsigned char cur_loc, unsigned char Buffsize);

//void Back(unsigned char *ptr,unsigned char cur_loc, unsigned char Buffsize);
void put_cursor(unsigned char loc);


void select_scrll_speed();


#endif