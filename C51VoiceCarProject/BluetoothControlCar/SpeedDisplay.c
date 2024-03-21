#include <reg52.h>
#include <stdio.h>
#include "DefineVar.h"
#include "UART.h"
#include <math.h>

int count = 0;
void Time0_Init()
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;
	TL0 = 0x33;		//设置定时初值 0.5ms
	TH0 = 0xFE;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EX0 = 1;
	IE0 = 0;
	IT0 = 0;  		//低电平触发外部中断1
}


//码盘20个格子，被遮挡（高电平），不遮挡（低电平）
//轮子直径6.5cm,一圈距离：3.14*6.5 = 20.41cm

void Int0_Handle() interrupt 0
{
	count++;
}

void Time0_Handle() interrupt 1
{
	static int cnt = 0;
	u8 SPEED[20];
	cnt++;
	TL0 = 0x33;		//设置定时初值
	TH0 = 0xFE;		//设置定时初值
	if(cnt == 2000)
	{
		sprintf(SPEED,"SPEED:%dcm/s\r\n",count);
		Write_Data(SPEED);
		count = 0;
		cnt = 0;
	}
}
