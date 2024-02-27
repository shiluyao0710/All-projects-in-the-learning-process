/*
Date:2024/2/26
Author:sly
Act:��ʼ���ߣ���ӡ���Լ����ƶ� 
*/

#include "cursor.h"
#include "interface.h"
#include "var.h"
#include "snakeAct.h"


//��ʼ����
void InitSnake()
{
	snake.len = 2; //�ߵ����峤�ȳ�ʼ��Ϊ2
	snake.x = COL / 2; //��ͷλ�õĺ�����
	snake.y = ROW / 2; //��ͷλ�õ�������
	//��������ĳ�ʼ��
	body[0].x = COL / 2 - 1;
	body[0].y = ROW / 2;
	body[1].x = COL / 2 - 2;
	body[1].y = ROW / 2;
	//����ͷ������λ�ý��б��
	face[snake.y][snake.x] = HEAD;
	face[body[0].y][body[0].x] = BODY;
	face[body[1].y][body[1].x] = BODY;
}

//��ӡ���븲����
void DrawSnake(int flag)
{
	int i;
	if (flag == 1) //��ӡ��
	{
		color(10); //��ɫ����Ϊ��ɫ
		CursorJump(2 * snake.x, snake.y);
		printf("��"); //��ӡ��ͷ
		for (i = 0; i < snake.len; i++)
		{
			CursorJump(2 * body[i].x, body[i].y);
			printf("��"); //��ӡ����
		}
	}
	else //������
	{
		if (body[snake.len - 1].y != 0) //��ֹlen++��(0, 0)λ�õ�ǽ����
		{
			//����β����Ϊ�ո񼴿�
			CursorJump(2 * body[snake.len - 1].x, body[snake.len - 1].y);
			printf("  ");
		}
	}
}

//�ƶ���
void MoveSnake(int x, int y)
{	
	int i;
	DrawSnake(0); //�ȸ��ǵ�ǰ����ʾ����
	face[body[snake.len - 1].y][body[snake.len - 1].x] = KONG; //���ƶ�����β���±��Ϊ��
	face[snake.y][snake.x] = BODY; //���ƶ�����ͷ��λ�ñ�Ϊ����
	//���ƶ����������λ��������Ҫ����
	for (i = snake.len - 1; i > 0; i--)
	{
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	//���ƶ�����ͷλ����Ϣ��Ϊ��0�������λ����Ϣ
	body[0].x = snake.x;
	body[0].y = snake.y;
	//��ͷ��λ�ø���
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	DrawSnake(1); //��ӡ�ƶ������
}

//�жϵ÷������
void JudgeFunc(int x, int y)
{
	//����ͷ���������λ����ʳ���÷�
	if (face[snake.y + y][snake.x + x] == FOOD)
	{
		snake.len++; //����ӳ�
		grade += 10; //���µ�ǰ�÷�
		color(7); //��ɫ����Ϊ��ɫ
		CursorJump(0+10, ROW);
		printf("��ǰ�÷�:%d", grade); //���´�ӡ��ǰ�÷�
		RandFood(); //�����������ʳ��
	}
	//����ͷ���������λ����ǽ������������Ϸ����
	else if (face[snake.y + y][snake.x + x] == WALL || face[snake.y + y][snake.x + x] == BODY)
	{
		Sleep(1000); //������ҷ�Ӧʱ��
		system("cls"); //�����Ļ
		color(7); //��ɫ����Ϊ��ɫ
		CursorJump(2 * (COL / 3), ROW / 2 - 3);
		if (grade > max)
		{
			printf("��ϲ�������߼�¼����߼�¼����Ϊ%d", grade);
			WriteGrade();
		}
		else if (grade == max)
		{
			printf("����߼�¼��ƽ�������ٴ��Ѽ�", grade);
		}
		else
		{
			printf("��������ͣ���ǰ����߼�¼���%d", max - grade);
		}
		CursorJump(2 * (COL / 3), ROW / 2);
		printf("GAME OVER");
		while (1) //ѯ������Ƿ�����һ��
		{
			char ch;
			CursorJump(2 * (COL / 3), ROW / 2 + 3);
			printf("����һ��?(y/n):");
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
			{
				system("cls");
				main();
			}
			else if (ch == 'n' || ch == 'N')
			{
				CursorJump(2 * (COL / 3), ROW / 2 + 5);
				exit(0);
			}
			else
			{
				CursorJump(2 * (COL / 3), ROW / 2 + 5);
				printf("ѡ��������ٴ�ѡ��");
			}
		}
	}
}

