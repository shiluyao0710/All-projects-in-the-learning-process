#ifndef _FOLLOW_H
#define _FOLLOW_H

/********************************ͷ�ļ�****************************************/
#include <reg52.h>
#include "MoveCar.h"
#include "DELAY.h"
#include "TTLDefine.h"

/********************************λ����****************************************/
sbit Follow_Left = P2^3;
sbit Follow_Right = P3^4;

/********************************��������****************************************/
void Follow_Pattern();

#endif
