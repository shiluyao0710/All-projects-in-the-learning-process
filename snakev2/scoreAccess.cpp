#include "globalDef.h"

//������߹ؿ��͵�ǰ�ؿ�
extern int levelMax;
extern int localLevel;

void getHighScore()//��ȡ��߹ؿ�
{
	FILE* fp1;
	fp1 = fopen("D:\\Ƕ��ʽ�������\\��Ŀ\\snakev2\\snakev2\\levelMax.txt", "r");
	if (fp1 == NULL) 
	{
		fp1 = fopen("D:\\Ƕ��ʽ�������\\��Ŀ\\snakev2\\snakev2\\levelMax.txt", "w");
		fwrite(&levelMax, sizeof(levelMax), 1, fp1);
	}
	fread(&levelMax, sizeof(levelMax), 1, fp1);
	fclose(fp1);
	fp1 = NULL;
}

char * recordHighScore() //��¼��߹ؿ�
{
	char s[100];
	memset(s, 0, sizeof(s));
	if (localLevel > levelMax)//�жϵ�ǰ��Ϸ�Ĺؿ�����߹ؿ�
	{
		levelMax = localLevel;
		FILE* fp1;
		fp1 = fopen("D:\\Ƕ��ʽ�������\\��Ŀ\\snakev2\\snakev2\\levelMax.txt", "w");//���ı��ļ����в���
		fwrite(&levelMax, sizeof(levelMax), 1, fp1);
		fclose(fp1);
		fp1 = NULL;
		sprintf(s, "��ϲ����������߼�¼��");
	}
	else if (localLevel == levelMax) 
	{
		sprintf(s, "���ĳɼ�����ƽ��߼�¼��");
	}
	else 
	{
		sprintf(s, "��������߼�¼���:%d�أ�", levelMax - localLevel);
	}
	return s;
}

