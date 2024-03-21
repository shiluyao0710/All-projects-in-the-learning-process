#ifndef _HCSR04_H
#define _HCSR04_H

/********************************ͷ�ļ�****************************************/
#include <reg52.h>
#include "DELAY.h"
#include "TTLDefine.h"

/********************************λ����****************************************/
sbit Trig = P2^4;
sbit Echo = P2^5;

/********************************��������****************************************/
void HSCR04_Init();
void Timer2_Init();
void Trig_Init();
void Start_Time();
void End_Time();
float Get_Time();
float Get_Dis( unsigned int time);
float HCSR04_Distance();

#endif
