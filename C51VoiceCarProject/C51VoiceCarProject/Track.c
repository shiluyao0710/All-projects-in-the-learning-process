#include "Track.h"

/******************************************************************************/
/* ��������  : Track_Pattern              		  	                          */
/* ��������  : ͨ���жϷ�����ĺ������Ƿ񱻷������������С���н�·�ߣ�ʵ��С�� */	
/* 			   ѭ��(Ѳ��)�����ⷴ���������͵�ƽ�������������򷵻ظߵ�ƽ 	  */
/* �������  : ��                                                             */
/* ��������  : ��  					                       		              */
/* ����ֵ    : ��                                                             */
/******************************************************************************/
void Track_Pattern()
{
	if(Track_Left == HIGH && Track_Right == LOW)
	{
		Go_Left();
		Delay10ms();
	}
	else if(Track_Left == LOW && Track_Right == HIGH)
	{
		Go_Right();
		Delay10ms();
	}
	else if(Track_Left == LOW && Track_Right == LOW)
	{
		Go_Forward();
		Delay10ms();
	}
	else if(Track_Left == HIGH && Track_Right == HIGH)
	{
		Stop();
	}
}
