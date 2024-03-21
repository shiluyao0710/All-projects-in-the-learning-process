#include "LEDRGB.h"

/******************************************************************************/
/* 函数名称  : LED_Init      	  		      	  	      	               	  */
/* 函数描述  : 初始化LED灯，R、G、B三种颜色都为低电平，熄灭状态				  */	
/* 输入参数  : 无	                                                          */
/* 参数描述  : 无					                       		              */
/* 返回值    : 无			                                                  */
/******************************************************************************/
void LED_Init()
{
	ColorR = LOW;
	ColorG = LOW;
	ColorB = LOW;
}

/******************************************************************************/
/* 函数名称  : LED_X     	  			      	  	      	               	  */
/* 函数描述  : 通过每次点亮的灯不一样， 使得拥有闪烁的效果					  */	
/* 输入参数  : 无	                                                          */
/* 参数描述  : 无					                       		              */
/* 返回值    : 无			                                                  */
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
