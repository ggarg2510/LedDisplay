

/*	

#define ROW_ENB			RD7
#define ROW_CLK			RD5
#define ROW_LAT			RD6
#define ROW_RSTB		RD4



#define COL_CLK			RD3
#define COL_RSTB		RD2
#define COL_ENB			RD1
#define COL_LAT			RD0
*/



/*
enum{	COL_LAT		= 0x01,
	  	COL_ENB		= 0x02,
	  	COL_RSTB	= 0x04,
			COL_CLK		= 0x08,
				  	
			ROW_RSTB	= 0x10,
			ROW_CLK		= 0x20,
			ROW_LAT		= 0x40,
			ROW_ENB		= 0x80
};
*/	





//#define  LO(x)	(PORTD&=~x)
//#define  HI(x)	(PORTD|=x)

#define TOTALBYTES_ADD		101
#define EE_STR_ADD		0x00
#define LEAD_TAIL_SPACES		7


struct character
{
	unsigned char char_count;
	unsigned char char_length;
};

extern struct character			char_cntrl;	
		
extern unsigned int dispRam1[32];
extern unsigned int dispRam2[32];
//extern unsigned char display_str[40];
		
void test();		
void putRowData(unsigned int data1, unsigned int data2);
void refresh_display();
void charUpdate();
void screenShift();
void small_font_disp(unsigned char *ptr, unsigned char length, unsigned char line_no);
void fillRAM(unsigned char col, unsigned int data);
void clr_disp();