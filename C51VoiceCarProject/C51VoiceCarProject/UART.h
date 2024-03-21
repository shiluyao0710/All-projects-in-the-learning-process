#ifndef _UART_H
#define _UART_H

/********************************ͷ�ļ�****************************************/
#include <reg52.h>
#include "DELAY.h"
#include "MoveCar.h"

/********************************�궨��****************************************/
#define GOFORWARD '2'
#define GOBACK '3'
#define GOLEFT '4'
#define GORIGHT '5'
/********************************����Ĵ�������****************************************/
sfr AUXR = 0x8E;  //��ֹ����

/********************************��������****************************************/
void UART_Init();
void Write_Byte(char byte);
void Write_Data(char * str);

#endif
