#include "globalDef.h"
#include "drawInference.h"
#include "food.h"
#include "globalVar.h"
#include "snakeAction.h"
#include "scoreDetemination.h"

//������ǰ�ؿ�
extern int localLevel;
extern struct Snake *head;
extern struct Snake* tail;
//�ߵ��ٶ�
extern int snakeSpeed;

void singlePlayerMode() //����ģʽ
{
	gameLevel();
	gameInterface();
}

int getKey(int tmpdir) //���񰴼�
{
	int ch1,ch2;
	int tmp = tmpdir;
	ch1 = _getch();//�����Ϊ˫��ֵ��������Ϊ����ֵ
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

int ifKbhit(int tmpdir)//�Ƿ��м�����
{
	int tmpSnakeSpeed = snakeSpeed;
	while (tmpSnakeSpeed--)
	{
		if(_kbhit() != 0)//���������ж��Ƿ��м��̰��£������򷵻ط��㣬��֮������
		{
			return getKey(tmpdir);
		}
	}
	return tmpdir;
}


void ExecuteKey(int left, int top, int right, int bottom)//ִ�а�������
{
	scoreOrEnd(left, top, right, bottom); //�жϵ����λ�ú��Ƿ�÷�����Ϸ����
	snakeMovement(left, top, right, bottom); //�ƶ���
}