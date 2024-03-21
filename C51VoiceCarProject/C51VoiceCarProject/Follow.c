#include "Follow.h"

/******************************************************************************/
/* 函数名称  : Follow_Pattern              		  	                          */
/* 函数描述  : 通过判断发射出的红外线是否被反射回来，控制小车行进路线，实现小车 */	
/* 			   跟随。红外反射回来输出低电平，没有收到反射的红外则返回高电平 	  */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无  					                       		              */
/* 返回值    : 无                                                             */
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
