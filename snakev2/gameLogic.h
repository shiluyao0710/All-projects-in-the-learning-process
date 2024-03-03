#pragma once

#include "globalDef.h"
#include "drawInference.h"
#include "food.h"

void singlePlayerMode();//单人模式

int getKey(int tmpdir);//捕获按键

int ifKbhit(int tmpdir);//判断是否有按键

void ExecuteKey(int left, int top, int right, int bottom);//执行按键操作