#pragma once

#include "globalDef.h"

void nomal_botton(int left, int top, int right, int bottom, const char* text, int size);//��������

void abnomal_botton(int left, int top, int right, int bottom, int flag);//�Ƿ����ֱ߿�

int pop_up_window(int pat, HWND handle);//��������

int select(int winds);//�����λ���ж�

void menu(int choice, HWND handle);//�˵���ת(�����λ�õĲ���)

void mainInterface(int flag);//������

void gameLevel();//�ؿ���ת����

void finishTheGame();//ͨ�ؽ���

void endInterface();//��Ϸ��������

void gameInterface();//��Ϸ����->����ģʽ

void gameRecord();//��Ϸ��¼����

void gameSetting();//��Ϸ���ý���

