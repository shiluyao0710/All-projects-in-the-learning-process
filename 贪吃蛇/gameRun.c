/*
Date:2024/2/26
Author:sly
Act:��Ϸ�߼��Ͱ��� 
*/

#include "cursor.h"
#include "interface.h"
#include "var.h"
#include "gradFile.h"
#include "snakeAct.h"
#include "gameRun.h"


//ִ�а���
void run(int x, int y)
{
	int t = 0;
	while (1)
	{
		if (t == 0)
			t = 8000; //����tԽС�����ƶ��ٶ�Խ�죨���Ը��ݴ�������Ϸ�Ѷȣ�
		while (--t)
		{
			if (kbhit() != 0) //�����̱��û������˳�ѭ��
				break;
		}
		if (t == 0) //����δ���û�
		{
			JudgeFunc(x, y); //�жϵ����λ�ú��Ƿ�÷�����Ϸ����
			MoveSnake(x, y); //�ƶ���
		}
		else //���̱��û�
		{
			break; //����Game������ȡ��ֵ
		}
	}
}

//��Ϸ�����߼�����
void Game()
{
	int n = RIGHT; //��ʼ��Ϸʱ��Ĭ������ƶ�
	int tmp = 0; //��¼�ߵ��ƶ�����
	goto first; //��һ�ν���ѭ������Ĭ�Ϸ���ǰ��
	while (1)
	{
		getch(); //��ͷΪ˫��ֵ�����յ�һ����ֵ 
		n = getch(); //��ȡ��ֵ
		//printf("��ȡ��ֵΪ��%d\n",n);
		//��ִ��ǰ����Ҫ������ȡ�İ������е���
		switch (n)
		{
		case UP:
		case DOWN: //����û����ǡ��ϡ����¡�
			if (tmp != LEFT&&tmp != RIGHT) //������һ���ߵ��ƶ������ǡ��󡱻��ҡ�
			{
				n = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
			}
			break;
		case LEFT:
		case RIGHT: //����û����ǡ��󡱻��ҡ�
			if (tmp != UP&&tmp != DOWN) //������һ���ߵ��ƶ������ǡ��ϡ����¡�
			{
				n = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
			}
			break; 
		case SPACE:
		case ESC:
		case 'r':
		case 'R':
			break; //���ĸ��������
		default:
			n = tmp; //��������Ч��Ĭ��Ϊ��һ�����ƶ��ķ���
			break;
		}
	first: //��һ�ν���ѭ������Ĭ�Ϸ���ǰ��
		switch (n)
		{
		case UP: //���������
			run(0, -1); //�����ƶ���������ƫ��Ϊ0��������ƫ��Ϊ-1��
			tmp = UP; //��¼��ǰ�ߵ��ƶ�����
			break;
		case DOWN: //���������
			run(0, 1); //�����ƶ���������ƫ��Ϊ0��������ƫ��Ϊ1��
			tmp = DOWN; //��¼��ǰ�ߵ��ƶ�����
			break;
		case LEFT: //���������
			run(-1, 0); //�����ƶ���������ƫ��Ϊ-1��������ƫ��Ϊ0��
			tmp = LEFT; //��¼��ǰ�ߵ��ƶ�����
			break;
		case RIGHT: //���������
			run(1, 0); //�����ƶ���������ƫ��Ϊ1��������ƫ��Ϊ0��
			tmp = RIGHT; //��¼��ǰ�ߵ��ƶ�����
			break;
		case SPACE: //��ͣ
			system("pause>nul"); //��ͣ�����������
			break;
		case ESC: //�˳�
			system("cls"); //�����Ļ
			color(7); //��ɫ����Ϊ��ɫ
			CursorJump(COL - 8, ROW / 2);
			printf("  ��Ϸ����  ");
			CursorJump(COL - 8, ROW / 2 + 2);
			exit(0);
		case 'r':
		case 'R': //���¿�ʼ
			system("cls"); //�����Ļ
			main(); //����ִ��������
		}
	}
}

