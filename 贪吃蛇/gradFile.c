/*
Date:2024/2/26
Author:sly
Act:��Ϸ���� 
*/

#include "cursor.h"
#include "interface.h"
#include "var.h"
#include "gradFile.h"


//���ļ���ȡ��߷�
void ReadGrade()
{
	FILE* pf = fopen("̰������ߵ÷ּ�¼.txt", "r"); //��ֻ���ķ�ʽ���ļ�
	if (pf == NULL) //���ļ�ʧ��
	{
		pf = fopen("̰������ߵ÷ּ�¼.txt", "w"); //��ֻд�ķ�ʽ���ļ�
		fwrite(&max, sizeof(int), 1, pf); //��maxд���ļ�����ʱmaxΪ0����������ߵ÷ֳ�ʼ��Ϊ0
	}
	fseek(pf, 0, SEEK_SET); //ʹ�ļ�ָ��pfָ���ļ���ͷ
	fread(&max, sizeof(int), 1, pf); //��ȡ�ļ����е���ߵ÷ֵ�max����
	fclose(pf); //�ر��ļ�
	pf = NULL; //�ļ�ָ�뼰ʱ�ÿ�
}

//������߷ֵ��ļ�
void WriteGrade()
{
	FILE* pf = fopen("̰������ߵ÷ּ�¼.txt", "w"); //��ֻд�ķ�ʽ���ļ�
	if (pf == NULL) //���ļ�ʧ��
	{
		printf("������ߵ÷ּ�¼ʧ��\n");
		exit(0);
	}
	fwrite(&grade, sizeof(int), 1, pf); //��������Ϸ�÷�д���ļ�����
	fclose(pf); //�ر��ļ�
	pf = NULL; //�ļ�ָ�뼰ʱ�ÿ�
}

