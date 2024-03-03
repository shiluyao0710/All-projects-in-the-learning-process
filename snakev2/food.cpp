#include "globalDef.h"
#include "drawInference.h"
#include "globalVar.h"

//声明食物左上点坐标
extern int foodx;
extern int foody;
//是否生成食物
extern int foodFlag;
//墙的坐标
extern int leftWall;
extern int rightWall;
extern int topWall;
extern int bottomWall;
//得分
extern int getScore;
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

void produceFood()//产生食物
{
	if (foodFlag == YES)
	{
		do
		{
			foodx = rand() % 68 + 6;//生成的食物避开墙
			foody = rand() % 34 + 5;
		}while (
			(((foodx * 10) >= leftObstacleOne && (foody * 10) == topObstacleOne && (foodx * 10 + 10) <= rightObstacleOne)) ||   //生成的食物避开障碍1
			(((foodx * 10) >= leftObstacleTwo && (foody * 10) == topObstacleTwo && (foodx * 10 + 10) <= rightObstacleTwo))//生成的食物避开障碍2
			);
		foodFlag = NO;
	}
	setlinecolor(RGB(218, 74, 74));
	setfillcolor(WHITE);//填充颜色为白色
	setlinestyle(PS_SOLID, 1);
	fillrectangle(foodx * 10, foody *10, foodx * 10 + 10, foody * 10 + 10);//有边框的填充矩形
}

void produceWall()//产生墙
{
	if (localLevel == 1 || localLevel == 2)//关卡1和2没有障碍物
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
	else if (localLevel == 3 || localLevel == 4)//关卡3和4有障碍物
	{
		//墙
		setlinecolor(RGB(78, 182, 135));
		setfillcolor(RGB(78, 182, 135));
		setlinestyle(PS_DASHDOT, 5);
		leftWall = 50;
		rightWall = window_length - 50;
		topWall = 40;
		bottomWall = window_width - 100;
		rectangle(leftWall, topWall, rightWall, bottomWall);
		//障碍物1
		setlinestyle(PS_SOLID, 1);
		leftObstacleOne = leftWall + 150;
		topObstacleOne = topWall + 100;
		rightObstacleOne = rightWall - 150;
		bottomObstacleOne = topWall + 110;
		//障碍物2
		leftObstacleTwo = leftWall + 150;
		topObstacleTwo = bottomWall - 110;
		rightObstacleTwo = rightWall - 150;
		bottomObstacleTwo = bottomWall - 100;
		//画出障碍物
		fillrectangle(leftObstacleOne, topObstacleOne, rightObstacleOne, bottomObstacleOne);
		fillrectangle(leftObstacleTwo, topObstacleTwo, rightObstacleTwo, bottomObstacleTwo);
	}
	//当前分数
	char s[30];
	sprintf(s, "分数:%d", getScore);
	nomal_botton(leftWall + 50, bottomWall + 30, leftWall + 50 + 80, bottomWall + 30 + 20, s, 20);
	memset(s, 0, sizeof(s));
	//当前关卡
	sprintf(s, "关卡:%d", localLevel);
	nomal_botton(leftWall + 300, bottomWall + 30, leftWall + 300 + 60, bottomWall + 30 + 20, s, 20);
	//当前通关要求
	memset(s, 0, sizeof(s));
	if (localLevel == 1)
	{
		sprintf(s, "通关要求:%d", FIRSTLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
	else if (localLevel == 2)
	{
		sprintf(s, "通关要求:%d", SECONDLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
	else if (localLevel == 3)
	{
		sprintf(s, "通关要求:%d", THIRDLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
	else if (localLevel == 4)
	{
		sprintf(s, "通关要求:%d", FOURTHLEVEL);
		nomal_botton(leftWall + 520, bottomWall + 30, leftWall + 520 + 120, bottomWall + 30 + 20, s, 20);
	}
}
	