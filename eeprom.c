
#include <pic.h>

void eeprom_str_write(unsigned char *ptr, unsigned char address, unsigned char length)
{
	unsigned char i=0;
	while(i!=length)
	{
		eeprom_write(address+i,*(ptr+i));
		i++;
	}	
}	
void eeprom_str_read(unsigned char *ptr, unsigned char address, unsigned char length)
{
	unsigned char i=0;
	while(i!=length)
	{
		*(ptr+i)=eeprom_read(address+i);	
		i++;
	}	
}	