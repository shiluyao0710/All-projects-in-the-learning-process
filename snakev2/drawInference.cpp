#include "globalDef.h"
#include "drawInference.h"
#include "backgroundMusic.h"
#include "food.h"
#include "scoreAccess.h"
#include "gameLogic.h"
#include "snakeAction.h"
#include "globalVar.h"

//�������ֿ���
extern int songONorOFF;
//��ǰ�ؿ�����߹ؿ�
extern int levelMax;
extern int localLevel;
//�Ƿ����ʳ��
extern int foodFlag;
//�Ƿ�����β
extern int reserveSnake;
extern struct Snake* tail;
//�ߵ���ɫ
extern int snakeColor;

void nomal_botton(int left, int top, int right, int bottom, const char* text, int size )//����״̬��ť
{
	setbkmode(TRANSPARENT);//�������屳��͸��
	char lingshi_text[50] = { 0 };//��ť����
	strcpy(lingshi_text, text);//��ȡ����
	settextstyle(size, 0, "����");//��������
	settextcolor(WHITE);
	int text_x = left + (right - left - textwidth(lingshi_text)) / 2;//���ݺ�����
	int text_y = top + (bottom - top - textheight(lingshi_text)) / 2;//����������
	outtextxy(text_x, text_y, lingshi_text);
}

void abnomal_botton(int left, int top, int right, int bottom, int flag)//ѡ��״̬��ť
{
	BeginBatchDraw();
	if (flag == YES) 
	{
		setlinecolor(WHITE);//����������ɫ
	}
	else {
		setlinecolor(BLACK);//����������ɫ
	}
	setlinestyle(PS_SOLID, 1);//������������
	roundrect(left, top, right, bottom, 10, 10);//���ð�ť
	FlushBatchDraw();
}

int select(int winds)//���ѡ��ģ��
{
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))//��ȡ�������Ϣ
		{
			switch (msg.message)//�жϵ����Ϣ
			{
			case WM_LBUTTONDOWN:
				if (winds == MAINWIND && msg.x > 200 && msg.x < 360 && msg.y>220 && msg.y < 260)//�������ģʽ
				{
					abnomal_botton(200, 220, 360, 260, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(200, 220, 360, 260, NO);//ȡ����ť״̬
					return SINGLEMODE;
				}
				else if (winds == MAINWIND && msg.x > 200 && msg.x < 360 && msg.y>280 && msg.y < 320)//���˫��ģʽ
				{
					abnomal_botton(200, 280, 360, 320, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(200, 280, 360, 320, NO);//ȡ����ť״̬
					return DOUBLEMODE;
				}
				else if (winds == MAINWIND &&  msg.x > 200&& msg.x < 360 && msg.y>340 && msg.y < 380)//�����Ϸ����
				{
					abnomal_botton(200, 340, 360, 380, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(200, 340, 360, 380, NO);//ȡ����ť״̬
					return GAMEPLAY;
				}
				else if (winds == GSETUPWIND && msg.x > 400 && msg.x < 420 && msg.y>240 && msg.y < 260) {//������ֿ�
					abnomal_botton(400, 240, 420, 260, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(400, 240, 420, 260, NO);//ȡ����ť״̬
					return MUSICON;
				}
				else if (winds == GSETUPWIND && msg.x > 460 && msg.x < 480 && msg.y>240 && msg.y < 260) {//������ֹ�
					abnomal_botton(460, 240, 480, 260, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(460, 240, 480, 260, NO);//ȡ����ť״̬
					return MUSICOFF;
				}
				else if (winds == GSETUPWIND && msg.x > 400 && msg.x < 420 && msg.y>300 && msg.y < 320) {//�����ʼ�ٶ���
					abnomal_botton(400, 300, 420, 320, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(400, 300, 420, 320, NO);//ȡ����ť״̬
					return SPEEDSLOW;
				}
				else if (winds == GSETUPWIND && msg.x > 450 && msg.x < 470 && msg.y>300 && msg.y < 320) {//�����ʼ�ٶ���
					abnomal_botton(450, 300, 470, 320, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(450, 300, 470, 320, NO);//ȡ����ť״̬
					return SPEEDMIDDLE;
				}
				else if (winds == GSETUPWIND && msg.x > 500 && msg.x < 520 && msg.y>300 && msg.y < 320) {//�����ʼ�ٶȿ�
					abnomal_botton(500, 300, 520, 320, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(500, 300, 520, 320, NO);//ȡ����ť״̬
					return SPEEDFAST;
				}
				else if (winds == GSETUPWIND && msg.x > 400 && msg.x < 420 && msg.y>360 && msg.y < 380) {//����ߵ���ɫ��
					abnomal_botton(400, 360, 420, 380, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(400, 360, 420, 380, NO);//ȡ����ť״̬
					return SNAKERED;
				}
				else if (winds == GSETUPWIND && msg.x > 450 && msg.x < 470 && msg.y>360 && msg.y < 380) {//����ߵ���ɫ��
					abnomal_botton(450, 360, 470, 380, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(450, 360, 470, 380, NO);//ȡ����ť״̬
					return SNAKEGREEN;
				}
				else if (winds == GSETUPWIND && msg.x > 500 && msg.x < 520 && msg.y>360 && msg.y < 380) {//����ߵ���ɫ��
					abnomal_botton(500, 360, 520, 380, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(500, 360, 520, 380, NO);//ȡ����ť״̬
					return SNAKEBLUE;
				}
				else if (winds == GSETUPWIND && msg.x > 310 && msg.x < 460 && msg.y>420 && msg.y < 450) {//�����Ϸ�����з���������
					abnomal_botton(310, 420, 460, 450, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(310, 420, 460, 450, NO);//ȡ����ť״̬
					return SETUPBUTTON;
				}
				else if (winds == MAINWIND &&  msg.x > 200 && msg.x < 360 && msg.y>400 && msg.y < 440)//�����Ϸ��¼
				{
					abnomal_botton(200, 400, 360, 440, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(200, 400, 360, 440, NO);//ȡ����ť״̬
					return GAMERECORD;
				}
				else if (winds == GRECORDWIND &&  msg.x > 280 && msg.x < 480 && msg.y>350 && msg.y < 390)//�����Ϸ��¼�з���������
				{
					abnomal_botton(280, 350, 480, 390, YES);//��ʾ��ť״̬
					Sleep(500);
					abnomal_botton(280, 350, 480, 390, NO);//ȡ����ť״̬
					return GRECORDBUTTON;
				}
			default:
				return INSIGNIFICANCE;
			}
		}
	}
}

int pop_up_window(int popup, HWND handle) //��������
{ 
	if (popup == SINGLEPOPUP) //����ģʽ��Ϸ��ʼ����
	{
		backMusic(PAUSEMUSIC);
		int i = MessageBox(handle, "�Ƿ�ʼ��Ϸ?", "��ʾ", MB_OKCANCEL);
		backMusic(RESUMEMUSIC);
		if (IDOK == i)
		{
			return YES;
		}
		else if (IDCANCEL == i)
		{
			return NO;
		}
	}
	else if (popup == DOUBLEPOPUP)//˫��ģʽ����
	{
		backMusic(PAUSEMUSIC);
		int j = MessageBox(handle, "�����ڴ���", "��ʾ", MB_OKCANCEL);
		backMusic(RESUMEMUSIC);
		if (IDOK == j)
		{
			return YES;
		}
		else if (IDCANCEL == j)
		{
			return NO;
		}
	}
	else if (popup == ENDPOPUP)//��Ϸ�������Ƿ�����һ�ֵ���
	{
		if (songONorOFF != NO)
		{
			backMusic(CLOSEMUSIC);
		}
		int k = MessageBox(handle, "����һ�֣�", "��ʾ", MB_OKCANCEL);
		foodFlag = YES;
		if (songONorOFF != NO) 
		{
			backMusic(OPENMUSIC);
			backMusic(PLAYMUSIC);
		}
		if (IDOK == k)
		{
			return YES;
		}
		else if (IDCANCEL == k)
		{
			return NO;
		}
	}
}

void menu(int choice, HWND handle)//�˵���ת(ִ�����������ľ������)
{
	int yes_or_no;
	switch (choice)
	{
	case SINGLEMODE://����ģʽ
		yes_or_no = pop_up_window(SINGLEPOPUP, handle);
		if (yes_or_no == NO) 
		{
			localLevel = 1;
			mainInterface(NO);
		}
		closegraph();
		singlePlayerMode();
		return;
	case DOUBLEMODE://˫��ģʽ
		yes_or_no = pop_up_window(DOUBLEPOPUP, handle);
		mainInterface(NO);
		return;
	case GAMEPLAY://��Ϸ����
		closegraph();
		gameSetting();
		return;
	case GAMERECORD://��Ϸ��¼
		closegraph();
		gameRecord();
		return;
	case GRECORDBUTTON://��Ϸ��¼����������
		closegraph();
		mainInterface(YES);
		return;
	case MUSICON://���ִ򿪰�ť
		if (songONorOFF != YES) 
		{
			backMusic(OPENMUSIC);
			backMusic(PLAYMUSIC);
			songONorOFF = YES;
		}
		return;
	case MUSICOFF://���ֹرհ�ť
		if (songONorOFF != NO) 
		{
			backMusic(CLOSEMUSIC);
			songONorOFF = NO;
		}
		return;
	case SETUPBUTTON://��Ϸ���÷���������
		closegraph();
		mainInterface(YES);
		return;
	case SPEEDSLOW://�ٶ�����ť
		snakeSpeed = SPEEDSLOW;
		return;
	case SPEEDMIDDLE://�ٶ��а�ť
		snakeSpeed = SPEEDMIDDLE;
		return;
	case SPEEDFAST://�ٶȿ찴ť
		snakeSpeed = SPEEDFAST;
		return;
	case SNAKERED://��ɫ��ť
		snakeColor = SNAKERED;
		return;
	case SNAKEGREEN://��ɫ��ť
		snakeColor = SNAKEGREEN;
		return;
	case SNAKEBLUE://��ɫ��ť
		snakeColor = SNAKEBLUE;
		return;
	default :
		return;
	}
}

void mainInterface(int flag)//������
{
	if (songONorOFF != NO) 
	{
		backMusic(OPENMUSIC);
		backMusic(PLAYMUSIC);
	}
	if (flag == YES)
	{
		initgraph(window_length, window_width);//��������
	}
	HWND startwindow = GetHWnd();//��ȡ���ھ��
	SetWindowText(startwindow, "̰����");//���ô��ڱ���
	while (1)//ѡ��ѭ��ģʽ
	{
		BeginBatchDraw();
		IMAGE start_bk;
		loadimage(&start_bk, _T("snake1.png"));//���ñ���
		putimage(550, 150, &start_bk); //x,yΪ���ϽǶ������ͼƬ
		//���ð�ť
		nomal_botton(50, 100, 450, 180, "Snake Game", 80);//��Ϸ����
		nomal_botton(200, 220, 360, 260, "����ģʽ", 40);//��һ����ť
		nomal_botton(200, 280, 360, 320, "˫��ģʽ", 40);//�ڶ�����ť
		nomal_botton(200, 340, 360, 380, "��Ϸ����", 40);//��������ť
		nomal_botton(200, 400, 360, 440, "��Ϸ��¼", 40);//���ĸ���ť
		FlushBatchDraw();
		int choice = select(MAINWIND);//ѡ��ѡ��
		menu(choice, startwindow);//����ѡ��
	}
}

void gameInterface() //��Ϸ�ؿ�����
{
	initgraph(window_length, window_width);//��������
	HWND gameInterfacewindow = GetHWnd();//��ȡ���ھ��
	SetWindowText(gameInterfacewindow, "��Ϸ����");//���ô��ڱ���
	snakeInit();
	//��ʼ������
	cleardevice();
	BeginBatchDraw();
	produceWall();
	produceFood();
	snakePrint();
	FlushBatchDraw();
	//��ʼ�ƶ�
	int dir = KEY_RIGHT;
	int tmpdir = KEY_RIGHT;
	cleardevice();
	BeginBatchDraw();
	produceWall();
	produceFood();
	goto first;
	while (1)
	{	
		reserveSnake = NO;
		cleardevice();
		BeginBatchDraw();
		produceWall();
		produceFood();
		dir = ifKbhit(tmpdir);
		first:
		switch (dir)
		{
		case KEY_UP:
			ExecuteKey(tail->left, tail->top - 10, tail->right, tail->bottom - 10);
			tmpdir = KEY_UP;
			break;
		case KEY_DOWN:
			ExecuteKey(tail->left, tail->top + 10, tail->right, tail->bottom + 10);
			tmpdir = KEY_DOWN;
			break;
		case KEY_LEFT:
			ExecuteKey(tail->left - 10, tail->top, tail->right - 10, tail->bottom);
			tmpdir = KEY_LEFT;
			break;
		case KEY_RIGHT:
			ExecuteKey(tail->left + 10, tail->top, tail->right + 10, tail->bottom);
			tmpdir = KEY_RIGHT;
			break;
		}
		FlushBatchDraw();
	}
	closegraph();
}

void gameLevel() //�ؿ���ת����
{
	initgraph(window_length, window_width);//��������
	HWND gameLevelwindow = GetHWnd();//��ȡ���ھ��
	SetWindowText(gameLevelwindow, "��Ϸ�ؿ�");//���ô��ڱ���
	cleardevice();
	BeginBatchDraw();
	IMAGE gameLevelwindow_bk;
	loadimage(&gameLevelwindow_bk, _T("snake2.png"));//���ñ���
	putimage(650, 350, &gameLevelwindow_bk); //x,yΪ���ϽǶ������ͼƬ
	nomal_botton(200, 100, 600, 180, "Snake Game��", 80);//��������λ��
	char s[50];
	sprintf(s, "�ؿ�:%d", localLevel);
	nomal_botton(330, 250, 450, 290, s, 40);
	FlushBatchDraw();
	Sleep(500);
	closegraph();//�رմ���
}

void endInterface() //��Ϸ��������
{
	initgraph(window_length, window_width);//��������
	HWND gameLevelwindow = GetHWnd();//��ȡ���ھ��
	SetWindowText(gameLevelwindow, "��Ϸ����");//���ô��ڱ���
	cleardevice();
	BeginBatchDraw();
	char str[100];
	char* s = (char*)malloc(sizeof(char) * 100);
	s = recordHighScore();
	strcpy(str, s);
	IMAGE gameLevelwindow_bk;
	loadimage(&gameLevelwindow_bk, _T("snake2.png"));//���ñ���
	putimage(650, 350, &gameLevelwindow_bk); //x,yΪ���ϽǶ������ͼƬ
	nomal_botton(200, 100, 600, 180, "Game Over��", 80);
	nomal_botton(310, 250, 490, 290, "����һ�֣�", 40);
	nomal_botton(200, 350, 590, 380, str , 30);
	FlushBatchDraw();
	int result = pop_up_window(ENDPOPUP, gameLevelwindow);//��ȡ�������
	closegraph();
	getScore = 0;
	if (result == YES) 
	{
		snakeSpeed = snakeSpeed;
		localLevel = localLevel;
		leftObstacleOne = leftObstacleOne;
		topObstacleOne = topObstacleOne;
		rightObstacleOne = rightObstacleOne;
		bottomObstacleOne = bottomObstacleOne;
		leftObstacleTwo = leftObstacleTwo;
		topObstacleTwo = topObstacleTwo;
		rightObstacleTwo = rightObstacleTwo;
		bottomObstacleTwo = bottomObstacleTwo;
		singlePlayerMode();
	}
	else 
	{
		snakeSpeed = SPEEDSLOW;
		localLevel = 1;
		leftObstacleOne = 0;
		topObstacleOne = 0;
		rightObstacleOne = 0;
		bottomObstacleOne = 0;
		leftObstacleTwo = 0;
		topObstacleTwo = 0;
		rightObstacleTwo = 0;
		bottomObstacleTwo = 0;
		mainInterface(YES);
	}
}

void finishTheGame() //��Ϸͨ�ؽ���
{
	initgraph(window_length, window_width);//��������
	HWND finishTheGamewindow = GetHWnd();//��ȡ���ھ��
	SetWindowText(finishTheGamewindow, "��Ϸͨ��");//���ô��ڱ���
	cleardevice();
	BeginBatchDraw();
	IMAGE finishTheGame_bk;
	loadimage(&finishTheGame_bk, _T("snake2.png"));//���ñ���
	putimage(650, 350, &finishTheGame_bk); //x,yΪ���ϽǶ������ͼƬ
	nomal_botton(300, 100, 550, 180, "��ϲ����", 80);
	nomal_botton(330, 250, 490, 290, "����ͨ��", 40);
	//nomal_botton(330, 350, 490, 370, "�����������...", 20);
	FlushBatchDraw();
	Sleep(500);
	closegraph();
	mainInterface(YES);
}

void gameSetting() //��Ϸ���ý���
{
	initgraph(window_length, window_width);//��������
	HWND gameSettingwindow = GetHWnd();//��ȡ���ھ��
	SetWindowText(gameSettingwindow, "��Ϸ����");//���ô��ڱ���
	while (1) {
		cleardevice();
		BeginBatchDraw();
		nomal_botton(220, 100, 540, 180, "��Ϸ����", 80);
		nomal_botton(240, 240, 380, 260, "�������֣�", 20);
		nomal_botton(400, 240, 420, 260, "��", 20);
		nomal_botton(460, 240, 480, 260, "��", 20);
		nomal_botton(240, 300, 380, 320, "��ʼ�ٶȣ�", 20);
		nomal_botton(400, 300, 420, 320, "��", 20);
		nomal_botton(450, 300, 470, 320, "��", 20);
		nomal_botton(500, 300, 520, 320, "��", 20);
		nomal_botton(240, 360, 380, 380, "�ߵ���ɫ��", 20);
		nomal_botton(400, 360, 420, 380, "��", 20);
		nomal_botton(450, 360, 470, 380, "��", 20);
		nomal_botton(500, 360, 520, 380, "��", 20);
		//nomal_botton(280, 250, 480, 290, "��߹ؿ�:1", 20);
		nomal_botton(310, 420, 460, 450, "����������", 30);
		FlushBatchDraw();
		int choice = select(GSETUPWIND);
		menu(choice, gameSettingwindow);
	}
}

void gameRecord() //��Ϸ��¼����
{
	initgraph(window_length, window_width);//��������
	HWND recordwindow = GetHWnd();//��ȡ���ھ��
	SetWindowText(recordwindow, "��Ϸ��¼");//���ô��ڱ���
	while (1) {
		cleardevice();
		BeginBatchDraw();
		nomal_botton(220, 100, 540, 180, "��Ϸ��¼", 80);
		char s[50];
		sprintf(s, "��߹ؿ�:%d", levelMax);
		nomal_botton(280, 250, 480, 290, s, 40);
		nomal_botton(280, 350, 480, 390, "����������", 40);
		FlushBatchDraw();
		int choice = select(GRECORDWIND);
		menu(choice, recordwindow);
	}
}
