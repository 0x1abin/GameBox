#include "config.h"
#include "IO_defines.h"

uint8 imbuff[16];

void buffcpy(uint8 *dest, const uint8 *src);
{
	uint8 i;
	for(i=0; i<16; i++)
	{
		dest[i] = src[i];
	}
}

void clear()
{
	uint8 i;
	for(i=0; i<16; i++)
	{
		imbuff[i] = 0;
	}
}

void refresh()
{
	uint8 i;
	for(i=0; i<16; i++)
	{
		buffer[i] = imbuff[i];
	}
}