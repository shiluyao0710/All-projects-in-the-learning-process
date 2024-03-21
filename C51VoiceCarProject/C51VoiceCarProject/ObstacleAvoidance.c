#include "ObstacleAvoidance.h"

/********************************变量定义****************************************/
float dis_middle;
float dis_left;
float dis_right;

/******************************************************************************/
/* 函数名称  : Obstacle_Peripheral                                            */
/* 函数描述  : 进入避障模式后，打开LED灯，打开蜂鸣器，预警                     */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无			                                                 */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Obstacle_Peripheral()
{
	LED_Show();
	Buzzer();
}

/******************************************************************************/
/* 函数名称  : Obstacle_Avoidance_Pattern                                     */
/* 函数描述  : 避障模式，超声波测距+SG90舵机，实现左中右的测距，通过判断不同方位*/
/* 			   的距离，实现直行，左右转弯。                                    */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无			                                                 */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Obstacle_Avoidance_Pattern()
{
	Obstacle_Peripheral();//初始化预警外设，LED灯和蜂鸣器
	dis_middle = HCSR04_Distance();//测量前方距离
	if(dis_middle > ADVANCEDISTANCE)//判断前方距离是否满足继续直行的条件
	{
		Go_Forward();
		Delay10ms();
	}
	else if(dis_middle < BACKWAY)//若前方距离小于最下距离时，开始后退
	{
		Go_Back();
		Delay10ms();
	}
	else//当前方距离介于直行和后退条件之间时，停车进行左右测距，判断转弯方向
	{
		Stop();
		Shake_Head_Left();
		Delay300ms();
		dis_left = HCSR04_Distance();//测量车头左侧距离
		Shake_Head_Middle();
		Delay300ms();
		Shake_Head_Right();
		Delay300ms();
		dis_right = HCSR04_Distance();//测量车头右侧距离
		Shake_Head_Middle();
		Delay300ms();
		if(dis_left > dis_right)//左侧距离大于右侧距离时，左转弯，避开障碍物
		{
			Go_Left();
			Delay10ms();
		}
		else if(dis_right >= dis_left)//否测右转弯，避开障碍物
		{
			Go_Right();
			Delay10ms();
		}
	}
}
