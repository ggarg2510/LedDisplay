

#include<pic.h>
#define _XTAL_FREQ	20000000

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


#define  KBD_CLK			    RB0
#define  KBD_DATA		      RB1	
