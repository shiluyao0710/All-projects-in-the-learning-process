/*
Date:2024/2/26
Author:sly
Act:随机生成食物 
*/

#include "cursor.h"
#include "interface.h"
#include "var.h"
#include "food.h"


//随机生成食物
void RandFood()
{
	int i, j;
	do
	{
		//随机生成食物的横纵坐标（数值范围为0~ROW/0~COL） 
		i = rand() % ROW;
		j = rand() % COL;
	} while (face[i][j] != KONG); //确保生成食物的位置为空，若不为空则重新生成
	face[i][j] = FOOD; //将食物位置进行标记
	color(12); //颜色设置为红色
	CursorJump(2 * j, i); //光标跳转到生成的随机位置处
	printf("●"); //打印食物
}

