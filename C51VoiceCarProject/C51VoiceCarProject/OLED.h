#ifndef _OLED_H
#define _OLED_H

/********************************头文件****************************************/
#include "IIC.h"

/********************************函数声明****************************************/
void OLED_Write_Cmd(unsigned char cmd);
void OLED_Write_Data(unsigned char datas);
void OLED_Init();
void OLED_Clear();
void OLED_Clear_Speed();
void OLED_Clear_Model();
void OLED_Show_Fixed_Word();
void OLED_Show_Char(char row,char col,char oledChar);
void OLED_Show_Str(char row,char col,char *str);
void OLED_Show_Init();

#endif
