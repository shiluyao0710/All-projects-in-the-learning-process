/*
Date:2024/2/26
Author:sly
Act:启动文件 
*/

#include "cursor.h"
#include "interface.h"
#include "var.h"
#include "gradFile.h"
#include "snakeAct.h"
#include "food.h"
#include "gameRun.h"


int main()
{
#pragma warning (disable:4996) //消除警告
	max = 0, grade = 0; //初始化变量
	system("title 贪吃蛇"); //设置cmd窗口的名字
	system("mode con cols=84 lines=23"); //设置cmd窗口的大小
	HideCursor(); //隐藏光标
	ReadGrade(); //从文件读取最高分到max变量
	InitInterface(); //初始化界面
	InitSnake(); //初始化蛇
	srand((unsigned int)time(NULL)); //设置随机数生成起点
	RandFood(); //随机生成食物
	DrawSnake(1); //打印蛇
	Game(); //开始游戏
	return 0;
}

