#ifndef _SU03T_H
#define _SU03T_H

/********************************头文件****************************************/
#include <reg52.h>
#include "OLED.h"
#include "TTLDefine.h"
#include "Track.h"
#include "UART.h"
#include "Follow.h"
#include "ObstacleAvoidance.h"

/********************************宏定义****************************************/
#define TRACKING_MODE 6
#define REMOTE_MODE 7
#define FOLLOW_MODE 8
#define	OBSTACLEAVOIDANCE_MODE 9
#define PAGEROW 3
#define COL 0

/********************************位定义****************************************/
sbit A25 = P1^1;
sbit A26 = P1^2;
sbit A27 = P1^3;
sbit B3 = P1^4;

/********************************函数声明****************************************/
void SU03T_Init();
void Mode_Selection();
void SU03T();

#endif
