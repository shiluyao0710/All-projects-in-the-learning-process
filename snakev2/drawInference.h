#pragma once

#include "globalDef.h"

void nomal_botton(int left, int top, int right, int bottom, const char* text, int size);//文字设置

void abnomal_botton(int left, int top, int right, int bottom, int flag);//是否文字边框

int pop_up_window(int pat, HWND handle);//弹窗提醒

int select(int winds);//鼠标点击位置判断

void menu(int choice, HWND handle);//菜单中转(鼠标点击位置的操作)

void mainInterface(int flag);//主界面

void gameLevel();//关卡跳转界面

void finishTheGame();//通关界面

void endInterface();//游戏结束界面

void gameInterface();//游戏界面->单人模式

void gameRecord();//游戏记录界面

void gameSetting();//游戏设置界面

