#include "LEDRGB.h"

/******************************************************************************/
/* ��������  : LED_Init      	  		      	  	      	               	  */
/* ��������  : ��ʼ��LED�ƣ�R��G��B������ɫ��Ϊ�͵�ƽ��Ϩ��״̬				  */	
/* �������  : ��	                                                          */
/* ��������  : ��					                       		              */
/* ����ֵ    : ��			                                                  */
/******************************************************************************/
void LED_Init()
{
	ColorR = LOW;
	ColorG = LOW;
	ColorB = LOW;
}

/******************************************************************************/
/* ��������  : LED_X     	  			      	  	      	               	  */
/* ��������  : ͨ��ÿ�ε����ĵƲ�һ���� ʹ��ӵ����˸��Ч��					  */	
/* �������  : ��	                                                          */
/* ��������  : ��					                       		              */
/* ����ֵ    : ��			                                                  */
/******************************************************************************/
void LED_R()
{
	ColorR = HIGH;
	ColorG = LOW;
	ColorB = LOW;
}

void LED_G()
{
	ColorR = LOW;
	ColorG = HIGH;
	ColorB = LOW;
}

void LED_B()
{
	ColorR = LOW;
	ColorG = LOW;
	ColorB = HIGH;
}

void LED_RG()
{
	ColorR = HIGH;
	ColorG = HIGH;
	ColorB = LOW;
}

void LED_RB()
{
	ColorR = HIGH;
	ColorG = LOW;
	ColorB = HIGH;
}

void LED_GB()
{
	ColorR = LOW;
	ColorG = HIGH;
	ColorB = HIGH;
}

void LED_RGB()
{
	ColorR = HIGH;
	ColorG = HIGH;
	ColorB = HIGH;
}

void LED_Close()
{
	ColorR = LOW;
	ColorG = LOW;
	ColorB = LOW;
}

void LED_Show()
{
	LED_R();
	Delay40ms();
	LED_Close();
	Delay40ms();
	LED_G();
	Delay40ms();
	LED_Close();
	Delay40ms();
	LED_B();
	Delay40ms();
	LED_Close();
	Delay40ms();
	LED_RG();
	Delay40ms();
	LED_Close();
	Delay40ms();
	LED_RB();
	Delay40ms();
	LED_Close();
	Delay40ms();
	LED_GB();
	Delay40ms();
	LED_Close();
	Delay40ms();
	LED_RGB();
	Delay40ms();
	LED_Close();
	Delay40ms();
}
