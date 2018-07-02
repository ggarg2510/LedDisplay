
#include "general.h"

/*
void *_memchr(const unsigned char *str, unsigned char c, unsigned int n)
{ 
	while(*str != 0)
	{
		if(*str == c)
			return str;
		str++;	
	}
	return NULL;
}
*/
void *_memcpy(unsigned char *str1, const unsigned char *str2, unsigned int n)
{
	unsigned char *temp_ptr=str1;
	while(n-- > 0)
	{
		*str1++ = *str2++;
	}
	return temp_ptr;
}

void _memset(unsigned char *str, unsigned char c, int n)
{
//	far unsigned char *temp_ptr=str;
	while(n!=0)
	{
		*str = c;
		n--;
		str++;
	}
//	return temp_ptr;
}
/*
unsigned char *_strcat(unsigned char *dest, const unsigned char *src)
{
	unsigned char *temp_ptr=dest;
	
	while(*dest!=0)	dest++;
	_memcpy(dest,src,_strlen(src));
	
	*(dest+_strlen(src))=0;
	return temp_ptr;
}
*/
/*
unsigned char *_strncat(unsigned char *dest, const unsigned char *src, unsigned int n)
{
	unsigned char *temp_ptr=dest;
	
	while(*dest!=0)	dest++;
	_memcpy(dest, src, n);
	
	return temp_ptr;
}
*/
/*
unsigned char *_strchr(const unsigned char *str, unsigned char c)
{
	while(*str!=0)
	{
		if(*str == c )
			return str;
		str++;
	}
	return NULL;
}
*/
/*
unsigned char *_strcpy(unsigned char *dest, const unsigned char *src)
{
	unsigned char temp_ptr=dest;
	_memcpy(dest, src, _strlen(src));
	return temp_ptr;
}
*/
/*
unsigned char *_strncpy(unsigned char *dest, const unsigned char *src, unsigned int n)
{
	//unsigned char temp_ptr=dest;
	unsigned int length=0;
	
	length=_strlen(src);
	if(length < n)
		_memset(src+length,0x00, n-length);
	_memcpy(dest,src,n);
		
	return dest;		
}
*/
/*
unsigned int _strlen(const unsigned char *str)
{
	register unsigned int length=0;
	while(*str != 0)
	{
		length++;
		str++;
	}	
	return length;

}
*/