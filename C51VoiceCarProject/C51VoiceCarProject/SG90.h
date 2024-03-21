#ifndef _SG90_H
#define _SG90_H

/********************************ͷ�ļ�****************************************/
#include <reg52.h>
#include "TTLDefine.h"

/********************************�궨��****************************************/
#define LEFT 5
#define RIGHT 1
#define MIDDLE 3

/********************************λ����****************************************/
sbit sg_90 = P3^3;

/********************************��������****************************************/
void Timer0_Init();
void SG90_Init();
void Shake_Head_Left();
void Shake_Head_Right();
void Shake_Head_Middle();

#endif
