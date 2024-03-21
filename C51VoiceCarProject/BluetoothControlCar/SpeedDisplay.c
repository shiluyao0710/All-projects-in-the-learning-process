#include <reg52.h>
#include <stdio.h>
#include "DefineVar.h"
#include "UART.h"
#include <math.h>

int count = 0;
void Time0_Init()
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;
	TL0 = 0x33;		//���ö�ʱ��ֵ 0.5ms
	TH0 = 0xFE;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
	EX0 = 1;
	IE0 = 0;
	IT0 = 0;  		//�͵�ƽ�����ⲿ�ж�1
}


//����20�����ӣ����ڵ����ߵ�ƽ�������ڵ����͵�ƽ��
//����ֱ��6.5cm,һȦ���룺3.14*6.5 = 20.41cm

void Int0_Handle() interrupt 0
{
	count++;
}

void Time0_Handle() interrupt 1
{
	static int cnt = 0;
	u8 SPEED[20];
	cnt++;
	TL0 = 0x33;		//���ö�ʱ��ֵ
	TH0 = 0xFE;		//���ö�ʱ��ֵ
	if(cnt == 2000)
	{
		sprintf(SPEED,"SPEED:%dcm/s\r\n",count);
		Write_Data(SPEED);
		count = 0;
		cnt = 0;
	}
}
