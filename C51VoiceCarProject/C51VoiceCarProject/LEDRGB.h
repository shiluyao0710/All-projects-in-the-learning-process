#ifndef _LEDRGB_H
#define _LEDRGB_H

/********************************ͷ�ļ�****************************************/
#include <reg52.h>
#include "DELAY.h"
#include "TTLDefine.h"

/********************************λ����****************************************/
sbit ColorB = P1^7;
sbit ColorG = P1^6;
sbit ColorR = P1^5;

/********************************��������****************************************/
void LED_Init();
void LED_R();
void LED_G();
void LED_B();
void LED_RG();
void LED_RB();
void LED_GB();
void LED_RGB();
void LED_Close();
void LED_Show();

#endif
