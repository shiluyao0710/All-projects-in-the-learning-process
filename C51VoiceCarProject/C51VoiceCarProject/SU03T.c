#include "SU03T.h"

/********************************��������****************************************/
unsigned char mode;
unsigned char remark;

/******************************************************************************/
/* ��������  : SU03T_Init              		  	        	                  */
/* ��������  : ��ʼ��ģʽ													  */	
/* �������  : ��                                                             */
/* ��������  : ��  					                       		              */
/* ����ֵ    : ��                                                             */
/******************************************************************************/
void SU03T_Init()
{
	mode = REMOTE_MODE;
	remark = 0;
}

/******************************************************************************/
/* ��������  : Mode_Selection              			       	                  */
/* ��������  : ģʽѡ������ģ���е�����A25��A26��A27��B3����ΪMCU�����ƽ	  */	
/* �������  : ��                                                             */
/* ��������  : ��  					                       		              */
/* ����ֵ    : ��                                                             */
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
/* ��������  : SU03T              					       	                  */
/* ��������  : ͨ������ģ��ѡ��ͬ��ģʽ������OLED��Ļ����ʾģʽ				  */	
/* �������  : ��                                                             */
/* ��������  : ��  					                       		              */
/* ����ֵ    : ��                                                             */
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
