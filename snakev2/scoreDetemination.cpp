#include "globalDef.h"
#include "globalVar.h"
#include "drawInference.h"
#include "scoreAccess.h"
#include "food.h"
#include "snakeAction.h"

//�����Ƿ�����ʳ��
extern int foodFlag;
//ʳ�����ϵ�����
extern int foodx;
extern int foody;
//������ͷ
extern int reserveSnake;
//�÷�
extern int getScore;
//�ߵ��ٶ�
extern int snakeSpeed;
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

void scoreOrEnd(int left, int top, int right, int bottom)//�ж���Ϸ�÷������
{
	if (left < leftWall + 5 || right > rightWall - 5 || top < topWall + 5 || bottom > bottomWall - 5)	//��ײǽ��
	{
		endInterface();
	}
	else if (left>= leftObstacleOne && right <= rightObstacleOne && top == topObstacleOne && bottom == bottomObstacleOne)	//��ײ��һ���ϰ���
	{
		endInterface();
	}
	else if (left >= leftObstacleTwo && right <= rightObstacleTwo && top == topObstacleTwo && bottom == bottomObstacleTwo)//��ײ�ڶ����ϰ���
	{
		endInterface();
	}
	else if( left == foodx * 10  &&  top == foody * 10 )//��ײ��ʳ��
	{
		getScore += 10;
		foodFlag = YES;
		reserveSnake = YES;
		cleardevice();//����֮��������Ⱦ����(����ᵼ��ɾ�����֮��֮ǰ��Ⱦ�Ļ��������ڽ����ϣ��γ�û��ɾ���ļ���)
		BeginBatchDraw();
		produceWall();
		produceFood();
		if (getScore == 200 && localLevel == 1)//ͨ���ؿ�1
		{
			Sleep(1000);
			localLevel += 1;
			getScore = 0;
			if(snakeSpeed == SPEEDSLOW)
			{
				snakeSpeed = SPEEDMIDDLE;
			}
			else if(snakeSpeed == SPEEDMIDDLE)
			{
				snakeSpeed = SPEEDMIDDLE;
			}
			else if(snakeSpeed == SPEEDFAST)
			{
				snakeSpeed = SPEEDFAST;
			}
			gameLevel();
			gameInterface();
		}
		else if(getScore == 300 && localLevel == 2)//ͨ���ؿ�2
		{
			Sleep(1000);
			localLevel += 1;
			getScore = 0;
			if (snakeSpeed == SPEEDMIDDLE)
			{
				snakeSpeed = SPEEDMIDDLE;
			}
			else if (snakeSpeed == SPEEDFAST)
			{
				snakeSpeed = SPEEDFAST;
			}
			gameLevel();
			gameInterface();
		}
		else if (getScore == 400 && localLevel == 3)//ͨ���ؿ�3
		{
			Sleep(1000);
			localLevel += 1;
			getScore = 0;
			snakeSpeed = SPEEDFAST;
			gameLevel();
			gameInterface();
		}
		else if (getScore == 1000 && localLevel == 4)//ͨ���ؿ�4
		{
			Sleep(1000);
			finishTheGame();
			recordHighScore();
		}
	}
}