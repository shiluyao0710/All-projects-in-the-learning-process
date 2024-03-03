#include "globalDef.h"
#include "drawInference.h"
#include "globalVar.h"

//����ʳ�����ϵ�����
extern int foodx;
extern int foody;
//�Ƿ�����ʳ��
extern int foodFlag;
//ǽ������
extern int leftWall;
extern int rightWall;
extern int topWall;
extern int bottomWall;
//�÷�
extern int getScore;
//�ϰ���1����
extern int leftObstacleOne;
extern int topObstacleOne;
extern int rightObstacleOne;
extern int bottomObstacleOne;
//�ϰ���2����
extern int leftObstacleTwo;
extern int topObstacleTwo;
extern int rightObstacleTwo;
extern int bottomObstacleTwo;

void produceFood()//����ʳ��
{
	if (foodFlag == YES)
	{
		do
		{
			foodx = rand() % 68 + 6;//���ɵ�ʳ��ܿ�ǽ
			foody = rand() % 34 + 5;
		}while (
			(((foodx * 10) >= leftObstacleOne && (foody * 10) == topObstacleOne && (foodx * 10 + 10) <= rightObstacleOne)) ||   //���ɵ�ʳ��ܿ��ϰ�1
			(((foodx * 10) >= leftObstacleTwo && (foody * 10) == topObstacleTwo && (foodx * 10 + 10) <= rightObstacleTwo))//���ɵ�ʳ��ܿ��ϰ�2
			);
		foodFlag = NO;
	}
	setlinecolor(RGB(218, 74, 74));
	setfillcolor(WHITE);//�����ɫΪ��ɫ
	setlinestyle(PS_SOLID, 1);
	fillrectangle(foodx * 10, foody *10, foodx * 10 + 10, foody * 10 + 10);//�б߿��������
}

void produceWall()//����ǽ
{
	if (localLevel == 1 || localLevel == 2)//�ؿ�1��2û���ϰ���
	{
		setlinecolor(RGB(78, 182, 135));
		setlinestyle(PS_DASHDOT, 5);
		setfillcolor(BLACK);
		leftWall = 50;
		rightWall = window_length - 50;
		topWall = 40;
		bottomWall = window_width - 100;
		rectangle(leftWall, topWall, rightWall, bottomWall);
	}
	else if (localLevel == 3 || localLevel == 4)//�ؿ�3��4���ϰ���
	{
		//ǽ
		setlinecolor(RGB(78, 182, 135));
		setfillcolor(RGB(78, 182, 135));
		setlinestyle(PS_DASHDOT, 5);
		leftWall = 50;
		rightWall = window_length - 50;
		topWall = 40;
		bottomWall = window_width - 100;
		rectangle(leftWall, topWall, rightWall, bottomWall);
		//�ϰ���1
		setlinestyle(PS_SOLID, 1);
		leftObstacleOne = leftWall + 150;
		topObstacleOne = topWall + 100;
		rightObstacleOne = rightWall - 150;
		bottomObstacleOne = topWall + 110;
		//�ϰ���2
		leftObstacleTwo = leftWall + 150;
		topObstacleTwo = bottomWall - 110;
		rightObstacleTwo = rightWall - 150;
		bottomObstacleTwo = bottomWall - 100;
		//�����ϰ���
		fillrectangle(leftObstacleOne, topObstacleOne, rightObstacleOne, bottomObstacleOne);
		fillrectangle(leftObstacleTwo, topObstacleTwo, rightObstacleTwo, bottomObstacleTwo);
	}
	//��ǰ����
	char s[30];
	sprintf(s, "����:%d", getScore);
	nomal_botton(leftWall + 50, bottomWall + 30, leftWall + 50 + 80, bottomWall + 30 + 20, s, 20);
	memset(s, 0, sizeof(s));
	//��ǰ�ؿ�
	sprintf(s, "�ؿ�:%d", localLevel);
	nomal_botton(leftWall + 300, bottomWall + 30, leftWall + 300 + 60, bottomWall + 30 + 20, s, 20);
	//��ǰͨ��Ҫ��
	memset(s, 0, sizeof(s));
	if (localLevel == 1)
	{
		sprintf(s, "ͨ��Ҫ��:%d", FIRSTLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
	else if (localLevel == 2)
	{
		sprintf(s, "ͨ��Ҫ��:%d", SECONDLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
	else if (localLevel == 3)
	{
		sprintf(s, "ͨ��Ҫ��:%d", THIRDLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
	else if (localLevel == 4)
	{
		sprintf(s, "ͨ��Ҫ��:%d", FOURTHLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
}
	