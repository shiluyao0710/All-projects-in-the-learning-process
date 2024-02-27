#ifndef _SNAKEACT_H
#define _SNAKEACT_H


//初始化蛇
void InitSnake();

//打印蛇与覆盖蛇
void DrawSnake(int flag);

//移动蛇
void MoveSnake(int x, int y);

//判断得分与结束
void JudgeFunc(int x, int y); 


#endif

