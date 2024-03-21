#ifndef _TRACK_H
#define _TRACK_H

/********************************头文件****************************************/
#include <reg52.h>
#include "MoveCar.h"
#include "DELAY.h"
#include "TTLDefine.h"

/********************************位定义****************************************/
sbit Track_Left = P2^2;
sbit Track_Right = P3^5;

/********************************函数声明****************************************/
void Track_Pattern();

#endif
