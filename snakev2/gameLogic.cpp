#include "globalDef.h"
#include "drawInference.h"
#include "food.h"
#include "globalVar.h"
#include "snakeAction.h"
#include "scoreDetemination.h"

//声明当前关卡
extern int localLevel;
extern struct Snake *head;
extern struct Snake* tail;
//蛇的速度
extern int snakeSpeed;

void singlePlayerMode() //单人模式
{
	gameLevel();
	gameInterface();
}

int getKey(int tmpdir) //捕获按键
{
	int ch1,ch2;
	int tmp = tmpdir;
	ch1 = _getch();//方向键为双键值，其他键为单键值
	ch2 = _getch();
	switch (ch2)
	{
	case KEY_UP:
		if (tmpdir == KEY_DOWN)
		{
			return tmp;
		}
		else
		{
			return ch2;
		}
	case KEY_DOWN:
		if (tmpdir == KEY_UP)
		{
			return tmp;
		}
		else
		{
			return ch2;
		}
	case KEY_LEFT:
		if (tmpdir == KEY_RIGHT)
		{
			return tmp;
		}
		else
		{
			return ch2;
		}
	case KEY_RIGHT:
		if (tmpdir == KEY_LEFT)
		{
			return tmp;
		}
		else
		{
			return ch2;
		}
	default:
		return tmp;
	}
}

int ifKbhit(int tmpdir)//是否有键按下
{
	int tmpSnakeSpeed = snakeSpeed;
	while (tmpSnakeSpeed--)
	{
		if(_kbhit() != 0)//无阻塞的判断是否有键盘按下，若有则返回非零，反之返回零
		{
			return getKey(tmpdir);
		}
	}
	return tmpdir;
}


void ExecuteKey(int left, int top, int right, int bottom)//执行按键操作
{
	scoreOrEnd(left, top, right, bottom); //判断到达该位置后，是否得分与游戏结束
	snakeMovement(left, top, right, bottom); //移动蛇
}