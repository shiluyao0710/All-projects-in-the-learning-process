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

//���ڴ�С
#define window_length 800
#define window_width 500
//�߼��ж�
#define YES 1
#define NO 0
//���������洰�ڲ�
#define MAINWIND 1000
#define GRECORDWIND 1001
#define GSETUPWIND 1002
//���ؽ��水ť
#define GRECORDBUTTON 1003
#define SETUPBUTTON 1004
//�����涨��
#define SINGLEMODE 2000
#define DOUBLEMODE 2001
#define GAMEPLAY 2002
#define GAMERECORD 2003
//��Ϸ����->��������
#define MUSICON 3000
#define MUSICOFF 3001
//��Ϸ����->�ߵ��ٶ�
#define SPEEDSLOW 10000
#define SPEEDMIDDLE 7000
#define SPEEDFAST 4000
//��Ϸ����->�ߵ���ɫ
#define SNAKERED 5001
#define SNAKEGREEN 5002
#define SNAKEBLUE 5003
//����������
#define INSIGNIFICANCE 6000
//��������
#define SINGLEPOPUP 7000
#define DOUBLEPOPUP 7001
#define ENDPOPUP 7002
//��������
#define OPENMUSIC 8000
#define PLAYMUSIC 8001
#define PAUSEMUSIC 8002
#define RESUMEMUSIC 8003
#define VOLUMEMUSIC 8004
#define CLOSEMUSIC 8005
//������
#define MUSICISY 8006
#define MUSICZYN 8007
#define MUSICNDYS 8008
//ʳ���С
#define FOODWIDTH 10
#define FOODHEIGHT 10
//ͨ��Ҫ��
#define FIRSTLEVEL 200
#define SECONDLEVEL 300
#define THIRDLEVEL 400
#define FOURTHLEVEL 1000
//�����
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
