/*
Date:2024/2/26
Author:sly
Act:�������ʳ�� 
*/

#include "cursor.h"
#include "interface.h"
#include "var.h"
#include "food.h"


//�������ʳ��
void RandFood()
{
	int i, j;
	do
	{
		//�������ʳ��ĺ������꣨��ֵ��ΧΪ0~ROW/0~COL�� 
		i = rand() % ROW;
		j = rand() % COL;
	} while (face[i][j] != KONG); //ȷ������ʳ���λ��Ϊ�գ�����Ϊ������������
	face[i][j] = FOOD; //��ʳ��λ�ý��б��
	color(12); //��ɫ����Ϊ��ɫ
	CursorJump(2 * j, i); //�����ת�����ɵ����λ�ô�
	printf("��"); //��ӡʳ��
}

