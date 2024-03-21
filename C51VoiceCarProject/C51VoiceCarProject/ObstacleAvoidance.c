#include "ObstacleAvoidance.h"

/********************************��������****************************************/
float dis_middle;
float dis_left;
float dis_right;

/******************************************************************************/
/* ��������  : Obstacle_Peripheral                                            */
/* ��������  : �������ģʽ�󣬴�LED�ƣ��򿪷�������Ԥ��                     */
/* �������  : ��                                                             */
/* ��������  : ��			                                                 */
/* ����ֵ    : ��                                                             */
/******************************************************************************/
void Obstacle_Peripheral()
{
	LED_Show();
	Buzzer();
}

/******************************************************************************/
/* ��������  : Obstacle_Avoidance_Pattern                                     */
/* ��������  : ����ģʽ�����������+SG90�����ʵ�������ҵĲ�࣬ͨ���жϲ�ͬ��λ*/
/* 			   �ľ��룬ʵ��ֱ�У�����ת�䡣                                    */
/* �������  : ��                                                             */
/* ��������  : ��			                                                 */
/* ����ֵ    : ��                                                             */
/******************************************************************************/
void Obstacle_Avoidance_Pattern()
{
	Obstacle_Peripheral();//��ʼ��Ԥ�����裬LED�ƺͷ�����
	dis_middle = HCSR04_Distance();//����ǰ������
	if(dis_middle > ADVANCEDISTANCE)//�ж�ǰ�������Ƿ��������ֱ�е�����
	{
		Go_Forward();
		Delay10ms();
	}
	else if(dis_middle < BACKWAY)//��ǰ������С�����¾���ʱ����ʼ����
	{
		Go_Back();
		Delay10ms();
	}
	else//��ǰ���������ֱ�кͺ�������֮��ʱ��ͣ���������Ҳ�࣬�ж�ת�䷽��
	{
		Stop();
		Shake_Head_Left();
		Delay300ms();
		dis_left = HCSR04_Distance();//������ͷ������
		Shake_Head_Middle();
		Delay300ms();
		Shake_Head_Right();
		Delay300ms();
		dis_right = HCSR04_Distance();//������ͷ�Ҳ����
		Shake_Head_Middle();
		Delay300ms();
		if(dis_left > dis_right)//����������Ҳ����ʱ����ת�䣬�ܿ��ϰ���
		{
			Go_Left();
			Delay10ms();
		}
		else if(dis_right >= dis_left)//�����ת�䣬�ܿ��ϰ���
		{
			Go_Right();
			Delay10ms();
		}
	}
}
