#include "globalDef.h"

//声明最高关卡和当前关卡
extern int levelMax;
extern int localLevel;

void getHighScore()//获取最高关卡
{
	FILE* fp1;
	fp1 = fopen("D:\\嵌入式软件开发\\项目\\snakev2\\snakev2\\levelMax.txt", "r");
	if (fp1 == NULL) 
	{
		fp1 = fopen("D:\\嵌入式软件开发\\项目\\snakev2\\snakev2\\levelMax.txt", "w");
		fwrite(&levelMax, sizeof(levelMax), 1, fp1);
	}
	fread(&levelMax, sizeof(levelMax), 1, fp1);
	fclose(fp1);
	fp1 = NULL;
}

char * recordHighScore() //记录最高关卡
{
	char s[100];
	memset(s, 0, sizeof(s));
	if (localLevel > levelMax)//判断当前游戏的关卡与最高关卡
	{
		levelMax = localLevel;
		FILE* fp1;
		fp1 = fopen("D:\\嵌入式软件开发\\项目\\snakev2\\snakev2\\levelMax.txt", "w");//对文本文件进行操作
		fwrite(&levelMax, sizeof(levelMax), 1, fp1);
		fclose(fp1);
		fp1 = NULL;
		sprintf(s, "恭喜您，打破最高记录！");
	}
	else if (localLevel == levelMax) 
	{
		sprintf(s, "您的成绩，持平最高记录！");
	}
	else 
	{
		sprintf(s, "您距离最高记录相差:%d关！", levelMax - localLevel);
	}
	return s;
}

