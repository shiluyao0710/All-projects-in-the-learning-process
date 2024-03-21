#include "Track.h"

/******************************************************************************/
/* 函数名称  : Track_Pattern              		  	                          */
/* 函数描述  : 通过判断发射出的红外线是否被反射回来，控制小车行进路线，实现小车 */	
/* 			   循迹(巡线)。红外反射回来输出低电平，被黑线吸收则返回高电平 	  */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无  					                       		              */
/* 返回值    : 无                                                             */
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
