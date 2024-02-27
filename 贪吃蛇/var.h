#ifndef _VAR_H
#define _VAR_H


#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROW 22 //游戏区行数
#define COL 42 //游戏区列数

#define KONG 0 //标记空（什么也没有）
#define WALL 1 //标记墙
#define FOOD 2 //标记食物
#define HEAD 3 //标记蛇头
#define BODY 4 //标记蛇身

#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define SPACE 32 //暂停
#define ESC 27 //退出

//蛇头
struct Snake
{
	int len; //记录蛇身长度
	int x; //蛇头横坐标
	int y; //蛇头纵坐标
}snake;

//蛇身
struct Body
{
	int x; //蛇身横坐标
	int y; //蛇身纵坐标
}body[ROW*COL]; //开辟足以存储蛇身的结构体数组

int face[ROW][COL]; //标记游戏区各个位置的状态

int max, grade; //全局变量


#endif

