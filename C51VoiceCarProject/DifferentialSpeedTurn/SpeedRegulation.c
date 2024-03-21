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
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x33;		//���ö�ʱ��ֵ
	TH0 = 0xFE;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	EA = 1;
	ET0 = 1;
}

void Time1_Init()
{
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x33;		//���ö�ʱ��ֵ
	TH1 = 0xFE;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF0��־
	TR1 = 1;		//��ʱ��0��ʼ��ʱ
	EA = 1;
	ET1 = 1;
}

void Time0_Handle() interrupt 1
{
	left_cnt++;
	TL0 = 0x33;		//���ö�ʱ��ֵ
	TH0 = 0xFE;	
	if(left_cnt < Left_Speed)
	{
		Left_Wheel_Go();
	}
	else
	{
		Left_Wheel_Stop();
	}
	if(left_cnt == 40)    //20msΪ����
	{
		left_cnt = 0;
	}
}

void Time1_Handle() interrupt 3
{
	right_cnt++;
	TL1 = 0x33;		//���ö�ʱ��ֵ
	TH1 = 0xFE;	
	if(right_cnt < Right_Speed)
	{
		Right_Wheel_Go();
	}
	else
	{
		Right_Wheel_Stop();
	}
	if(right_cnt == 40)    //20msΪ����
	{
		right_cnt = 0;
	}
}

