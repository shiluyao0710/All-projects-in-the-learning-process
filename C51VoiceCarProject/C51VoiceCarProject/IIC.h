#ifndef _IIC_H
#define _IIC_H

/********************************ͷ�ļ�****************************************/
#include <reg52.h>
#include <intrins.h>
#include "TTLDefine.h"

/********************************λ����****************************************/
sbit IIC_SCL = P2^0;
sbit IIC_SDA = P2^1;

/********************************��������****************************************/
void IIC_Init();
void IIC_Start();
void IIC_Stop();
void IIC_Ack();
void IIC_NAck();
unsigned char IIC_Wait_Ack();
void IIC_Write_Data(unsigned char dat);

#endif
