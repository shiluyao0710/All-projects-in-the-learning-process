/*
Date:2024/2/26
Author:sly
Act:��Ϸ���� 
*/

#include "cursor.h"
#include "var.h"
#include "interface.h"


//��ɫ����
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //��ɫ����
	//ע��SetConsoleTextAttribute��һ��API��Ӧ�ó����̽ӿڣ�
}

//��ʼ������
void InitInterface()
{
	int i; 
	int j;
	color(6); //��ɫ����Ϊ����ɫ
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (j == 0 || j == COL - 1)
			{
				face[i][j] = WALL; //��Ǹ�λ��Ϊǽ
				CursorJump(2 * j, i);
				printf("��");
				
			}
			else if (i == 0 || i == ROW - 1)
			{
				face[i][j] = WALL; //��Ǹ�λ��Ϊǽ
				CursorJump(2 * j, i);
				printf("��");

			}
			else
			{
				face[i][j] = KONG; //��Ǹ�λ��Ϊ��
			}
		}
	}
	color(7); //��ɫ����Ϊ��ɫ
	CursorJump(0+10, ROW);
	printf("��ǰ�÷�:%d", grade);
	CursorJump(COL+14, ROW);
	printf("��ʷ��ߵ÷�:%d", max);
}

