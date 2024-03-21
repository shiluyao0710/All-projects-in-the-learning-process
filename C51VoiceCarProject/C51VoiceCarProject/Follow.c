#include "Follow.h"

/******************************************************************************/
/* ��������  : Follow_Pattern              		  	                          */
/* ��������  : ͨ���жϷ�����ĺ������Ƿ񱻷������������С���н�·�ߣ�ʵ��С�� */	
/* 			   ���档���ⷴ���������͵�ƽ��û���յ�����ĺ����򷵻ظߵ�ƽ 	  */
/* �������  : ��                                                             */
/* ��������  : ��  					                       		              */
/* ����ֵ    : ��                                                             */
/******************************************************************************/
void Follow_Pattern()
{
	if(Follow_Left == LOW && Follow_Right == LOW)	
	{
		Go_Forward();
		Delay10ms();
	}
	else if(Follow_Left == LOW && Follow_Right == HIGH)
	{
		Go_Left();
		Delay10ms();
	}
	else if(Follow_Left == HIGH && Follow_Right == LOW)
	{
		Go_Right();
		Delay10ms();
	}
	else if(Follow_Left == HIGH && Follow_Right == HIGH)
	{
		Stop();
	}
}
