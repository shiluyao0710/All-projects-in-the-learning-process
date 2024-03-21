#ifndef _FOLLOW_H
#define _FOLLOW_H

/********************************头文件****************************************/
#include <reg52.h>
#include "MoveCar.h"
#include "DELAY.h"
#include "TTLDefine.h"

/********************************位定义****************************************/
sbit Follow_Left = P2^3;
sbit Follow_Right = P3^4;

/********************************函数声明****************************************/
void Follow_Pattern();

#endif
