

#include"myString.h"
//typedef unsigned char U8bit
//typedef unsigned int  U16bit


void *_memchr(const unsigned char *str, unsigned char c, unsigned int n)
{ 
	while(*str) != 0)
	{
		if(*str) == c)
			return str;
		str++;	
	}
	return NULL;
}

signed int _memcmp(const unsigned char *str1, const unsigned char *str2, int n)
{
	
	return 0;
}

void *_memcpy(unsigned char *str1, const unsigned char *str2, int n)
{
	unsigned char *temp_ptr=str1;
	while(n-- > 0)
	{
		*str1++ = *str2++;
	}
	return str1;
}

void *_memmove(unsigned char *str1, const unsigned char *str2, int n)
{
	return 0;
}

void *_memset(void *str, int c, int n)
{
	far unsigned char *temp_ptr=str;
	while(n!=0)
	{
		*((unsigned char *)str) = c;
		n--;
		str++;
	}
	return temp_ptr;
}
unsigned char *_strcat(char *dest, const char *src)
{
	unsigned char *temp_ptr=dest;
	
	while(*dest!=0)	dest++;
	_memcpy(dest,src,_strlen(src));
	
	*(dest+strlen(src))=0;
	return temp_ptr;
}
unsigned char *_strncat(unsigned char *dest, const unsigned char *src, unsigned int n)
{
	unsigned char temp_ptr=dest;
	
	while(*dest!=0)	dest++;
	_memcpy(dest, src, n);
	
	return temp_ptr;
}
unsigned char *_strchr(const unsigned char *str, unsigned int c)
{
	while(*str!=0)
	{
		if(*str == (unsigned char)c )
			return str;
		str++;
	}
	return NULL;
}
int strcmp(const char *str1, const char *str2)
{return 0;
}
int strncmp(const char *str1, const char *str2, int n)
{return 0;
}
int _strcoll(const char *str1, const char *str2)
{return 0;
}
unsigned char *_strcpy(unsigned char *dest, const unsigned char *src)
{
	unsigned char temp_ptr=dest;
	_memcpy(dest, src, _strlen(src));
	return temp_ptr;
}
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
int _strcspn(const char *str1,const char *str2)
{return 0;
}
char *_strerror(int errnum)
{return 0;
}
unsigned int _strlen(const unsigned char *str)
{/*
	register unsigned int length=0;
	while(*str++ != 0)	length++;
	
	return length;
*/
}
char *strpbrk(const char *str1, const char *str2)
{
	return 0;
}
char *strrchr(const char *str, int c)
{return 0;
}
int strspn(const char *str1, const char *str2)
{return 0;
}
char *strstr(const char *haystack, const char *needle)
{return 0;
}
char *strtok(char *str, const char *delim)
{return 0;
}
int strxfrm(char *dest, const char *src, int n)
{return 0;
}