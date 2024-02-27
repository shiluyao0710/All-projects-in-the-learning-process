/*
Date:2024/2/26
Author:sly
Act:游戏分数 
*/

#include "cursor.h"
#include "interface.h"
#include "var.h"
#include "gradFile.h"


//从文件读取最高分
void ReadGrade()
{
	FILE* pf = fopen("贪吃蛇最高得分记录.txt", "r"); //以只读的方式打开文件
	if (pf == NULL) //打开文件失败
	{
		pf = fopen("贪吃蛇最高得分记录.txt", "w"); //以只写的方式打开文件
		fwrite(&max, sizeof(int), 1, pf); //将max写入文件（此时max为0），即将最高得分初始化为0
	}
	fseek(pf, 0, SEEK_SET); //使文件指针pf指向文件开头
	fread(&max, sizeof(int), 1, pf); //读取文件当中的最高得分到max当中
	fclose(pf); //关闭文件
	pf = NULL; //文件指针及时置空
}

//更新最高分到文件
void WriteGrade()
{
	FILE* pf = fopen("贪吃蛇最高得分记录.txt", "w"); //以只写的方式打开文件
	if (pf == NULL) //打开文件失败
	{
		printf("保存最高得分记录失败\n");
		exit(0);
	}
	fwrite(&grade, sizeof(int), 1, pf); //将本局游戏得分写入文件当中
	fclose(pf); //关闭文件
	pf = NULL; //文件指针及时置空
}

