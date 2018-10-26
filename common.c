#include "common.h"

void* memset(void* bufptr, int value, unsigned int size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (unsigned int i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

bool  strcmp(char* a, char* b)
{
	int i = 0;
	while(a[i] != 0x00 && b[i] != 0x00)
	{
		if(a[i] != b[i])
		{
			return FALSE;
		}
		i++;
	}
	if(a[i] != 0x00)
	{
		return FALSE;
	}
	if(b[i] != 0x00)
	{
		return FALSE;
	}
	
	return TRUE;
}
