#ifndef _MOVECAR_H
#define _MOVECAR_H

/********************************头文件****************************************/
#include <reg52.h>
#include "TTLDefine.h"

/********************************位定义****************************************/
sbit A1_Right = P0^0;
sbit A2_Right = P0^1;
sbit B1_Left = P0^3;
sbit B2_Left = P0^2;

/********************************函数声明****************************************/
void Go_Forward();
void Go_Back();
void Go_Left();
void Go_Right();
void Stop();
void Left_Wheel_Go();
void Right_Wheel_Go();
void Left_Wheel_Stop();
void Right_Wheel_Stop();

#endif
