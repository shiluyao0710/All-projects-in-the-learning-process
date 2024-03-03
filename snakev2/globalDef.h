#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <iostream>
#include <mmsystem.h>

//窗口大小
#define window_length 800
#define window_width 500
//逻辑判断
#define YES 1
#define NO 0
//返回主界面窗口层
#define MAINWIND 1000
#define GRECORDWIND 1001
#define GSETUPWIND 1002
//返回界面按钮
#define GRECORDBUTTON 1003
#define SETUPBUTTON 1004
//主界面定义
#define SINGLEMODE 2000
#define DOUBLEMODE 2001
#define GAMEPLAY 2002
#define GAMERECORD 2003
//游戏设置->背景音乐
#define MUSICON 3000
#define MUSICOFF 3001
//游戏设置->蛇的速度
#define SPEEDSLOW 10000
#define SPEEDMIDDLE 7000
#define SPEEDFAST 4000
//游戏设置->蛇的颜色
#define SNAKERED 5001
#define SNAKEGREEN 5002
#define SNAKEBLUE 5003
//无意义设置
#define INSIGNIFICANCE 6000
//弹窗设置
#define SINGLEPOPUP 7000
#define DOUBLEPOPUP 7001
#define ENDPOPUP 7002
//音乐设置
#define OPENMUSIC 8000
#define PLAYMUSIC 8001
#define PAUSEMUSIC 8002
#define RESUMEMUSIC 8003
#define VOLUMEMUSIC 8004
#define CLOSEMUSIC 8005
//歌曲名
#define MUSICISY 8006
#define MUSICZYN 8007
#define MUSICNDYS 8008
//食物大小
#define FOODWIDTH 10
#define FOODHEIGHT 10
//通关要求
#define FIRSTLEVEL 200
#define SECONDLEVEL 300
#define THIRDLEVEL 400
#define FOURTHLEVEL 1000
//方向键
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
