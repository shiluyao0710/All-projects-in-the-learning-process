#include "SU03T.h"

/********************************变量定义****************************************/
unsigned char mode;
unsigned char remark;

/******************************************************************************/
/* 函数名称  : SU03T_Init              		  	        	                  */
/* 函数描述  : 初始化模式													  */	
/* 输入参数  : 无                                                             */
/* 参数描述  : 无  					                       		              */
/* 返回值    : 无                                                             */
/******************************************************************************/
void SU03T_Init()
{
	mode = REMOTE_MODE;
	remark = 0;
}

/******************************************************************************/
/* 函数名称  : Mode_Selection              			       	                  */
/* 函数描述  : 模式选择，语音模块中的引脚A25、A26、A27、B3负责为MCU输出电平	  */	
/* 输入参数  : 无                                                             */
/* 参数描述  : 无  					                       		              */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Mode_Selection()
{
	if(A25 == LOW && A26 == HIGH && A27 == HIGH && B3 == HIGH)
	{
		mode = TRACKING_MODE;
	}
	else if(A25 ==HIGH && A26 == LOW && A27 == HIGH && B3 == HIGH)
	{
		mode = REMOTE_MODE;
	}
	else if(A25 == HIGH && A26 == HIGH && A27 == LOW && B3 == HIGH)
	{
		mode = FOLLOW_MODE;
	}
	else if(A25 == HIGH && A26 == HIGH && A27 == HIGH && B3 == LOW)
	{
		mode = OBSTACLEAVOIDANCE_MODE;
	}
	else
	{
		mode = mode;
	}
}

/******************************************************************************/
/* 函数名称  : SU03T              					       	                  */
/* 函数描述  : 通过语音模块选择不同的模式，并在OLED屏幕中显示模式				  */	
/* 输入参数  : 无                                                             */
/* 参数描述  : 无  					                       		              */
/* 返回值    : 无                                                             */
/******************************************************************************/
void SU03T()
{
	Mode_Selection();
	switch(mode)
	{
		case TRACKING_MODE:
			if(remark != TRACKING_MODE)
			{
				OLED_Clear_Model();
				OLED_Show_Str(PAGEROW, COL, "Model:Track");
			}
			remark = TRACKING_MODE;
			Track_Pattern();
		break;
		case REMOTE_MODE:
			if(remark != REMOTE_MODE)
			{
				OLED_Clear_Model();
				OLED_Show_Str(PAGEROW, COL, "Model:RemoteCtr");
			}
			remark = REMOTE_MODE;
		break;
		case FOLLOW_MODE:
			if(remark != FOLLOW_MODE)
			{
				OLED_Clear_Model();
				OLED_Show_Str(PAGEROW, COL, "Model:Follow");
			}
			remark = FOLLOW_MODE;
			Follow_Pattern();
		break;
		case OBSTACLEAVOIDANCE_MODE:
			if(remark != OBSTACLEAVOIDANCE_MODE)
			{
				OLED_Clear_Model();
				OLED_Show_Str(PAGEROW, COL, "Model:ObsAvoid");
			}
			remark = OBSTACLEAVOIDANCE_MODE;
			Obstacle_Avoidance_Pattern();
		break;
	}
}
