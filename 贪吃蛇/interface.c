/*
Date:2024/2/26
Author:sly
Act:游戏界面 
*/

#include "cursor.h"
#include "var.h"
#include "interface.h"


//颜色设置
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
	//注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}

//初始化界面
void InitInterface()
{
	int i; 
	int j;
	color(6); //颜色设置为土黄色
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (j == 0 || j == COL - 1)
			{
				face[i][j] = WALL; //标记该位置为墙
				CursorJump(2 * j, i);
				printf("■");
				
			}
			else if (i == 0 || i == ROW - 1)
			{
				face[i][j] = WALL; //标记该位置为墙
				CursorJump(2 * j, i);
				printf("■");

			}
			else
			{
				face[i][j] = KONG; //标记该位置为空
			}
		}
	}
	color(7); //颜色设置为白色
	CursorJump(0+10, ROW);
	printf("当前得分:%d", grade);
	CursorJump(COL+14, ROW);
	printf("历史最高得分:%d", max);
}

