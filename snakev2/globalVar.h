#pragma once

//ȫ�ֱ���

//��Ŀ����ǰ����״̬
int songTrack;
int songONorOFF;
//ʳ��
int foodx;
int foody;
int foodFlag;
//ǽ
int leftWall;
int rightWall;
int topWall;
int bottomWall;
//�ϰ���1
int leftObstacleOne;
int rightObstacleOne;
int topObstacleOne;
int bottomObstacleOne;
//�ϰ���2
int leftObstacleTwo;
int rightObstacleTwo;
int topObstacleTwo;
int bottomObstacleTwo;
//�ؿ�
int levelMax;
int localLevel;
//�÷�
int getScore;
//�ߵ���ɫ
int snakeColor;
//�ߵ��ٶ�
int snakeSpeed;
//�Ƿ���ͷ���
int reserveSnake;
//��ͷ
int snakeHeadFlag;
//��
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