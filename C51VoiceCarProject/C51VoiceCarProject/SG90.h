#ifndef _SG90_H
#define _SG90_H

/********************************头文件****************************************/
#include <reg52.h>
#include "TTLDefine.h"

/********************************宏定义****************************************/
#define LEFT 5
#define RIGHT 1
#define MIDDLE 3

/********************************位定义****************************************/
sbit sg_90 = P3^3;

/********************************函数声明****************************************/
void Timer0_Init();
void SG90_Init();
void Shake_Head_Left();
void Shake_Head_Right();
void Shake_Head_Middle();

#endif
