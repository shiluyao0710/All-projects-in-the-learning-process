#pragma once

//全局变量

//曲目、当前歌曲状态
int songTrack;
int songONorOFF;
//食物
int foodx;
int foody;
int foodFlag;
//墙
int leftWall;
int rightWall;
int topWall;
int bottomWall;
//障碍物1
int leftObstacleOne;
int rightObstacleOne;
int topObstacleOne;
int bottomObstacleOne;
//障碍物2
int leftObstacleTwo;
int rightObstacleTwo;
int topObstacleTwo;
int bottomObstacleTwo;
//关卡
int levelMax;
int localLevel;
//得分
int getScore;
//蛇的颜色
int snakeColor;
//蛇的速度
int snakeSpeed;
//是否保留头结点
int reserveSnake;
//蛇头
int snakeHeadFlag;
//蛇
struct Snake
{
	int left;
	int top;
	int right;
	int bottom;
	int speed;
	struct Snake* next;
};
struct Snake* head;
struct Snake* tail;