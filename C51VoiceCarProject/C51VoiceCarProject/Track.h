#ifndef _TRACK_H
#define _TRACK_H

/********************************ͷ�ļ�****************************************/
#include <reg52.h>
#include "MoveCar.h"
#include "DELAY.h"
#include "TTLDefine.h"

/********************************λ����****************************************/
sbit Track_Left = P2^2;
sbit Track_Right = P3^5;

/********************************��������****************************************/
void Track_Pattern();

#endif
