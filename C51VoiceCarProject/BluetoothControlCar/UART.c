#include <reg52.h>
#include "DefineVar.h"
#include "MoveCar.h"
#include "DELAY.h"

sfr AUXR = 0x8E;
void UART_Init()
{
	AUXR = 0x01;
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA = 1;
	ES = 1;
}

void Write_Byte(u8 byte)
{
	SBUF = byte;
	while(!TI);
	TI = 0;
}

void Write_Data(u8 *str)
{
	while(*str != '\0')
	{
		Write_Byte(*str);
		str++;
	}
}

void UART_Handle() interrupt 4
{
	u8 tmp;
	if(RI)
	{
		RI = 0;
		tmp = SBUF;
		switch(tmp)
		{
			case GOFORWARD:
				Go_Forward();
				Delay10ms();
			break;
			case GOBACK:
				Go_Back();
				Delay10ms();
			break;
			case GOLEFT:
				Go_Left();
				Delay10ms();
			break;
			case GORIGHT:
				Go_Right();
				Delay10ms();
			break;
		}
	}
}
