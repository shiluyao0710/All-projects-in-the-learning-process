#ifndef _UART_H
#define _UART_H

/********************************头文件****************************************/
#include <reg52.h>
#include "DELAY.h"
#include "MoveCar.h"

/********************************宏定义****************************************/
#define GOFORWARD '2'
#define GOBACK '3'
#define GOLEFT '4'
#define GORIGHT '5'
/********************************特殊寄存器定义****************************************/
sfr AUXR = 0x8E;  //防止干扰

/********************************函数声明****************************************/
void UART_Init();
void Write_Byte(char byte);
void Write_Data(char * str);

#endif
