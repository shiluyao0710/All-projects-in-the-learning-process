#include <reg52.h>
#include "DefineVar.h"
#include "MoveCar.h"
#include "DELAY.h"

sfr AUXR = 0x8E;
void UART_Init()
{
	AUXR = 0x01;
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
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
