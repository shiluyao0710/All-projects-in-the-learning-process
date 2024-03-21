#include <intrins.h>


void Delay300us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 135;
	while (--i);
}


void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}


void Delay400ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 206;
	k = 43;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay3000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
