#include "DELAY.h"

/******************************************************************************/
/* 函数名称  : Delay xx us/ms              	  	        	                  */
/* 函数描述  : 利用软件定时器定时											  */	
/* 输入参数  : 无                                                             */
/* 参数描述  : 无  					                       		              */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Delay10us()		//@11.0592MHz
{
	unsigned char i;
	i = 2;
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

void Delay40ms()		//@11.0592MHz
{
	unsigned char i, j;
	i = 72;
	j = 181;
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

void Delay300ms()		//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	i = 3;
	j = 26;
	k = 223;
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
