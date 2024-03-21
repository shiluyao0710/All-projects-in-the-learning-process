#ifndef _OBSTACLEAVOIDANCE_H
#define _OBSTACLEAVOIDANCE_H

/********************************头文件****************************************/
#include <reg52.h>
#include "MoveCar.h"
#include "DELAY.h"
#include "SG90.h"
#include "HCSR04.h"
#include "LEDRGB.h"
#include "buzzer.h"

/********************************宏定义****************************************/
#define ADVANCEDISTANCE 35
#define BACKWAY 10

/********************************函数声明****************************************/
void Obstacle_Peripheral();
void Obstacle_Avoidance_Pattern();

#endif
