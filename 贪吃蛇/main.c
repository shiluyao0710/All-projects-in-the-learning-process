/*
Date:2024/2/26
Author:sly
Act:�����ļ� 
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
#pragma warning (disable:4996) //��������
	max = 0, grade = 0; //��ʼ������
	system("title ̰����"); //����cmd���ڵ�����
	system("mode con cols=84 lines=23"); //����cmd���ڵĴ�С
	HideCursor(); //���ع��
	ReadGrade(); //���ļ���ȡ��߷ֵ�max����
	InitInterface(); //��ʼ������
	InitSnake(); //��ʼ����
	srand((unsigned int)time(NULL)); //����������������
	RandFood(); //�������ʳ��
	DrawSnake(1); //��ӡ��
	Game(); //��ʼ��Ϸ
	return 0;
}

