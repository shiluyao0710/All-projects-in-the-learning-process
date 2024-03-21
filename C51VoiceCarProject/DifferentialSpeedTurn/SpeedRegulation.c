#include <reg52.h>
#include "MoveCar.h"
#include "DefineVar.h"

typedef unsigned char u8;

u8 left_cnt;
u8 right_cnt;
u8 Left_Speed = 0;
u8 Right_Speed = 0;

void Time0_Init()
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x33;		//设置定时初值
	TH0 = 0xFE;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	EA = 1;
	ET0 = 1;
}

void Time1_Init()
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
	TL1 = 0x33;		//设置定时初值
	TH1 = 0xFE;		//设置定时初值
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
	EA = 1;
	ET1 = 1;
}

void Time0_Handle() interrupt 1
{
	left_cnt++;
	TL0 = 0x33;		//设置定时初值
	TH0 = 0xFE;	
	if(left_cnt < Left_Speed)
	{
		Left_Wheel_Go();
	}
	else
	{
		Left_Wheel_Stop();
	}
	if(left_cnt == 40)    //20ms为周期
	{
		left_cnt = 0;
	}
}

void Time1_Handle() interrupt 3
{
	right_cnt++;
	TL1 = 0x33;		//设置定时初值
	TH1 = 0xFE;	
	if(right_cnt < Right_Speed)
	{
		Right_Wheel_Go();
	}
	else
	{
		Right_Wheel_Stop();
	}
	if(right_cnt == 40)    //20ms为周期
	{
		right_cnt = 0;
	}
}

