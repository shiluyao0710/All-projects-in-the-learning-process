#include "drawInference.h"
#include "globalDef.h"
#include "globalVar.h"
#include "scoreAccess.h"
#include "gameLogic.h"

int main() 
{
	srand((unsigned int)time(NULL));
	//��ʼ������
	songTrack= rand() % 3 + 8006;
	songONorOFF = NO;//��������
	levelMax = 1;//��߹ؿ�
	localLevel = 1;//��ǰ�ؿ�
	foodFlag = YES;//�Ƿ�����ʳ��
	getScore = 0;//��ʼ�÷�
	snakeColor = SNAKERED;//�ߵ���ɫ
	snakeSpeed = SPEEDSLOW;//�ߵ��ٶ�
	snakeHeadFlag = NO;//�Ƿ�Ϊ��ͷ
	reserveSnake = NO;//�Ƿ�����ͷ
	leftObstacleOne = 0;//�ϰ���1����
	topObstacleOne = 0;
	rightObstacleOne = 0;
	bottomObstacleOne = 0;
	leftObstacleTwo = 0;//�ϰ���2����
	topObstacleTwo = 0;
	rightObstacleTwo = 0;
	bottomObstacleTwo = 0;
	getHighScore();
	mainInterface(YES);
	return 0;
}