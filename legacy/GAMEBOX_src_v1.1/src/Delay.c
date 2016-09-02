#include "config.h"

static void Delay1us()		//@33.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 5;
	while (--i);
}
static void Delay1ms()		//@33.000MHz
{
	unsigned char i, j;

	i = 33;
	j = 22;
	do
	{
		while (--j);
	} while (--i);
}

void delayus(unsigned int n)
{
	while(n--)	Delay1us();
}

void delayms(unsigned int n)
{
	while(n--)	Delay1ms();
}