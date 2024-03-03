#include "globalDef.h"
#include "globalVar.h"

//����ͷָ���βָ��
extern struct Snake* head;
extern struct Snake* tail;
//����ɫ
extern int snakeColor;
//������β
extern int reserveSnake;
//�Ƿ�Ϊ��ͷ
extern int snakeHeadFlag;

void addNode(int left, int top, int right, int bottom)//ĩβ����һ�����
{
	struct Snake* newBody = (struct Snake*)malloc(sizeof(struct Snake));
	if (newBody == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	newBody->left = left;
	newBody->top = top;
	newBody->right = right;
	newBody->bottom = bottom;
	tail->next = newBody;
	newBody->next = NULL;
	tail = newBody;
}

void deleteNode()//ɾ��ͷ���
{
	if (head == NULL) 
	{
		return;
	}
	struct Snake* tmpNode = head;
	head = head->next;
	free(tmpNode);
	tmpNode = NULL;
}

void snakeInit()//��ʼ������
{
	head = (struct Snake*)malloc(sizeof(struct Snake));
	if (head == NULL) {
		perror("malloc");
		exit(-1);
	}
	head->left = 320;
	head->top = 220;
	head->right = 330;
	head->bottom = 230;
	head->next = NULL;
	tail = head;
	addNode(330, 220, 340, 230);
	addNode(340, 220, 350, 230);
	addNode(350, 220, 360, 230);
}

void snakeDraw(int left, int top, int right, int bottom, int snakeHeadFlag)//��Ⱦ��
{
	if (snakeColor == SNAKERED)//��Ϊ��ɫ
	{
		if(snakeHeadFlag == NO)
		{
			setfillcolor(BLACK);//�����ɫΪ��ɫ
		}
		else
		{
			setfillcolor(RED);//�����ɫΪ��ɫ
		}
		setlinecolor(RED);
	}
	else 	if (snakeColor == SNAKEGREEN)//��Ϊ��ɫ
	{
		if (snakeHeadFlag == NO)
		{
			setfillcolor(BLACK);//�����ɫΪ��ɫ
		}
		else
		{
			setfillcolor(GREEN);//�����ɫΪ��ɫ
		}
		setlinecolor(GREEN);
	}
	else if (snakeColor == SNAKEBLUE)//��Ϊ��ɫ
	{
		if (snakeHeadFlag == NO)
		{
			setfillcolor(BLACK);//�����ɫΪ��ɫ
		}
		else
		{
			setfillcolor(RGB(45, 30, 246));//�����ɫΪ��ɫ
		}
		setlinecolor(RGB(45, 30, 246));
	}
	setlinestyle(PS_SOLID, 1);
	fillrectangle(left, top, right, bottom);
}

void snakePrint()//��������
{
	struct Snake *tmp =head;
	while (tmp!= NULL) {
		if (tmp->next == NULL)
		{
			snakeHeadFlag = YES;
			snakeDraw(tmp->left, tmp->top, tmp->right, tmp->bottom, snakeHeadFlag);
		}
		else
		{
			snakeHeadFlag = NO;
			snakeDraw(tmp->left, tmp->top, tmp->right, tmp->bottom, snakeHeadFlag);
		}
		tmp = tmp->next;
	}
	free(tmp);
	tmp = NULL;
}

void snakeMovement(int left, int top, int right, int bottom)//�ƶ���
{
	addNode(left, top, right, bottom);
	if(reserveSnake != YES)
	{
		deleteNode();
	}
	snakePrint();
}
