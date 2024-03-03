#include "globalDef.h"
#include "globalVar.h"
#include "drawInference.h"
#include "scoreAccess.h"
#include "food.h"
#include "snakeAction.h"

//声明是否生成食物
extern int foodFlag;
//食物左上点坐标
extern int foodx;
extern int foody;
//保留蛇头
extern int reserveSnake;
//得分
extern int getScore;
//蛇的速度
extern int snakeSpeed;
//障碍物1坐标
extern int leftObstacleOne;
extern int topObstacleOne;
extern int rightObstacleOne;
extern int bottomObstacleOne;
//障碍物2坐标
extern int leftObstacleTwo;
extern int topObstacleTwo;
extern int rightObstacleTwo;
extern int bottomObstacleTwo;

void scoreOrEnd(int left, int top, int right, int bottom)//判断游戏得分与结束
{
	if (left < leftWall + 5 || right > rightWall - 5 || top < topWall + 5 || bottom > bottomWall - 5)	//碰撞墙壁
	{
		endInterface();
	}
	else if (left>= leftObstacleOne && right <= rightObstacleOne && top == topObstacleOne && bottom == bottomObstacleOne)	//碰撞第一个障碍物
	{
		endInterface();
	}
	else if (left >= leftObstacleTwo && right <= rightObstacleTwo && top == topObstacleTwo && bottom == bottomObstacleTwo)//碰撞第二个障碍物
	{
		endInterface();
	}
	else if( left == foodx * 10  &&  top == foody * 10 )//碰撞到食物
	{
		getScore += 10;
		foodFlag = YES;
		reserveSnake = YES;
		cleardevice();//清屏之后，重新渲染界面(否则会导致删除结点之后，之前渲染的画面留存在界面上，形成没有删除的假象)
		BeginBatchDraw();
		produceWall();
		produceFood();
		if (getScore == 200 && localLevel == 1)//通过关卡1
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
		else if(getScore == 300 && localLevel == 2)//通过关卡2
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
		else if (getScore == 400 && localLevel == 3)//通过关卡3
		{
			Sleep(1000);
			localLevel += 1;
			getScore = 0;
			snakeSpeed = SPEEDFAST;
			gameLevel();
			gameInterface();
		}
		else if (getScore == 1000 && localLevel == 4)//通过关卡4
		{
			Sleep(1000);
			finishTheGame();
			recordHighScore();
		}
	}
}