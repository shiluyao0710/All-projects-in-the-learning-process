#include "drawInference.h"
#include "globalDef.h"
#include "globalVar.h"
#include "scoreAccess.h"
#include "gameLogic.h"

int main() 
{
	srand((unsigned int)time(NULL));
	//初始化配置
	songTrack= rand() % 3 + 8006;
	songONorOFF = NO;//歌曲开关
	levelMax = 1;//最高关卡
	localLevel = 1;//当前关卡
	foodFlag = YES;//是否生成食物
	getScore = 0;//初始得分
	snakeColor = SNAKERED;//蛇的颜色
	snakeSpeed = SPEEDSLOW;//蛇的速度
	snakeHeadFlag = NO;//是否为蛇头
	reserveSnake = NO;//是否保留蛇头
	leftObstacleOne = 0;//障碍物1坐标
	topObstacleOne = 0;
	rightObstacleOne = 0;
	bottomObstacleOne = 0;
	leftObstacleTwo = 0;//障碍物2坐标
	topObstacleTwo = 0;
	rightObstacleTwo = 0;
	bottomObstacleTwo = 0;
	getHighScore();
	mainInterface(YES);
	return 0;
}