#include "globalDef.h"
#include "globalVar.h"

//声明头指针和尾指针
extern struct Snake* head;
extern struct Snake* tail;
//蛇颜色
extern int snakeColor;
//保留蛇尾
extern int reserveSnake;
//是否为蛇头
extern int snakeHeadFlag;

void addNode(int left, int top, int right, int bottom)//末尾插入一个结点
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

void deleteNode()//删除头结点
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

void snakeInit()//初始化链表
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

void snakeDraw(int left, int top, int right, int bottom, int snakeHeadFlag)//渲染蛇
{
	if (snakeColor == SNAKERED)//蛇为红色
	{
		if(snakeHeadFlag == NO)
		{
			setfillcolor(BLACK);//填充颜色为黑色
		}
		else
		{
			setfillcolor(RED);//填充颜色为红色
		}
		setlinecolor(RED);
	}
	else 	if (snakeColor == SNAKEGREEN)//蛇为绿色
	{
		if (snakeHeadFlag == NO)
		{
			setfillcolor(BLACK);//填充颜色为黑色
		}
		else
		{
			setfillcolor(GREEN);//填充颜色为绿色
		}
		setlinecolor(GREEN);
	}
	else if (snakeColor == SNAKEBLUE)//蛇为蓝色
	{
		if (snakeHeadFlag == NO)
		{
			setfillcolor(BLACK);//填充颜色为黑色
		}
		else
		{
			setfillcolor(RGB(45, 30, 246));//填充颜色为蓝色
		}
		setlinecolor(RGB(45, 30, 246));
	}
	setlinestyle(PS_SOLID, 1);
	fillrectangle(left, top, right, bottom);
}

void snakePrint()//遍历链表
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

void snakeMovement(int left, int top, int right, int bottom)//移动蛇
{
	addNode(left, top, right, bottom);
	if(reserveSnake != YES)
	{
		deleteNode();
	}
	snakePrint();
}
