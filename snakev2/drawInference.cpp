#include "globalDef.h"
#include "drawInference.h"
#include "backgroundMusic.h"
#include "food.h"
#include "scoreAccess.h"
#include "gameLogic.h"
#include "snakeAction.h"
#include "globalVar.h"

//声明音乐开关
extern int songONorOFF;
//当前关卡和最高关卡
extern int levelMax;
extern int localLevel;
//是否产生食物
extern int foodFlag;
//是否保留蛇尾
extern int reserveSnake;
extern struct Snake* tail;
//蛇的颜色
extern int snakeColor;

void nomal_botton(int left, int top, int right, int bottom, const char* text, int size )//正常状态按钮
{
	setbkmode(TRANSPARENT);//设置字体背景透明
	char lingshi_text[50] = { 0 };//按钮内容
	strcpy(lingshi_text, text);//获取内容
	settextstyle(size, 0, "宋体");//设置字体
	settextcolor(WHITE);
	int text_x = left + (right - left - textwidth(lingshi_text)) / 2;//内容横坐标
	int text_y = top + (bottom - top - textheight(lingshi_text)) / 2;//内容纵坐标
	outtextxy(text_x, text_y, lingshi_text);
}

void abnomal_botton(int left, int top, int right, int bottom, int flag)//选中状态按钮
{
	BeginBatchDraw();
	if (flag == YES) 
	{
		setlinecolor(WHITE);//设置线条颜色
	}
	else {
		setlinecolor(BLACK);//设置线条颜色
	}
	setlinestyle(PS_SOLID, 1);//设置线条类型
	roundrect(left, top, right, bottom, 10, 10);//设置按钮
	FlushBatchDraw();
}

int select(int winds)//点击选项模块
{
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))//获取鼠标点击信息
		{
			switch (msg.message)//判断点击信息
			{
			case WM_LBUTTONDOWN:
				if (winds == MAINWIND && msg.x > 200 && msg.x < 360 && msg.y>220 && msg.y < 260)//点击单人模式
				{
					abnomal_botton(200, 220, 360, 260, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(200, 220, 360, 260, NO);//取消按钮状态
					return SINGLEMODE;
				}
				else if (winds == MAINWIND && msg.x > 200 && msg.x < 360 && msg.y>280 && msg.y < 320)//点击双人模式
				{
					abnomal_botton(200, 280, 360, 320, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(200, 280, 360, 320, NO);//取消按钮状态
					return DOUBLEMODE;
				}
				else if (winds == MAINWIND &&  msg.x > 200&& msg.x < 360 && msg.y>340 && msg.y < 380)//点击游戏设置
				{
					abnomal_botton(200, 340, 360, 380, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(200, 340, 360, 380, NO);//取消按钮状态
					return GAMEPLAY;
				}
				else if (winds == GSETUPWIND && msg.x > 400 && msg.x < 420 && msg.y>240 && msg.y < 260) {//点击音乐开
					abnomal_botton(400, 240, 420, 260, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(400, 240, 420, 260, NO);//取消按钮状态
					return MUSICON;
				}
				else if (winds == GSETUPWIND && msg.x > 460 && msg.x < 480 && msg.y>240 && msg.y < 260) {//点击音乐关
					abnomal_botton(460, 240, 480, 260, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(460, 240, 480, 260, NO);//取消按钮状态
					return MUSICOFF;
				}
				else if (winds == GSETUPWIND && msg.x > 400 && msg.x < 420 && msg.y>300 && msg.y < 320) {//点击初始速度慢
					abnomal_botton(400, 300, 420, 320, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(400, 300, 420, 320, NO);//取消按钮状态
					return SPEEDSLOW;
				}
				else if (winds == GSETUPWIND && msg.x > 450 && msg.x < 470 && msg.y>300 && msg.y < 320) {//点击初始速度中
					abnomal_botton(450, 300, 470, 320, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(450, 300, 470, 320, NO);//取消按钮状态
					return SPEEDMIDDLE;
				}
				else if (winds == GSETUPWIND && msg.x > 500 && msg.x < 520 && msg.y>300 && msg.y < 320) {//点击初始速度快
					abnomal_botton(500, 300, 520, 320, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(500, 300, 520, 320, NO);//取消按钮状态
					return SPEEDFAST;
				}
				else if (winds == GSETUPWIND && msg.x > 400 && msg.x < 420 && msg.y>360 && msg.y < 380) {//点击蛇的颜色红
					abnomal_botton(400, 360, 420, 380, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(400, 360, 420, 380, NO);//取消按钮状态
					return SNAKERED;
				}
				else if (winds == GSETUPWIND && msg.x > 450 && msg.x < 470 && msg.y>360 && msg.y < 380) {//点击蛇的颜色绿
					abnomal_botton(450, 360, 470, 380, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(450, 360, 470, 380, NO);//取消按钮状态
					return SNAKEGREEN;
				}
				else if (winds == GSETUPWIND && msg.x > 500 && msg.x < 520 && msg.y>360 && msg.y < 380) {//点击蛇的颜色蓝
					abnomal_botton(500, 360, 520, 380, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(500, 360, 520, 380, NO);//取消按钮状态
					return SNAKEBLUE;
				}
				else if (winds == GSETUPWIND && msg.x > 310 && msg.x < 460 && msg.y>420 && msg.y < 450) {//点击游戏设置中返回主界面
					abnomal_botton(310, 420, 460, 450, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(310, 420, 460, 450, NO);//取消按钮状态
					return SETUPBUTTON;
				}
				else if (winds == MAINWIND &&  msg.x > 200 && msg.x < 360 && msg.y>400 && msg.y < 440)//点击游戏记录
				{
					abnomal_botton(200, 400, 360, 440, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(200, 400, 360, 440, NO);//取消按钮状态
					return GAMERECORD;
				}
				else if (winds == GRECORDWIND &&  msg.x > 280 && msg.x < 480 && msg.y>350 && msg.y < 390)//点击游戏记录中返回主界面
				{
					abnomal_botton(280, 350, 480, 390, YES);//显示按钮状态
					Sleep(500);
					abnomal_botton(280, 350, 480, 390, NO);//取消按钮状态
					return GRECORDBUTTON;
				}
			default:
				return INSIGNIFICANCE;
			}
		}
	}
}

int pop_up_window(int popup, HWND handle) //弹窗提醒
{ 
	if (popup == SINGLEPOPUP) //单人模式游戏开始弹窗
	{
		backMusic(PAUSEMUSIC);
		int i = MessageBox(handle, "是否开始游戏?", "提示", MB_OKCANCEL);
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
	else if (popup == DOUBLEPOPUP)//双人模式弹窗
	{
		backMusic(PAUSEMUSIC);
		int j = MessageBox(handle, "敬请期待！", "提示", MB_OKCANCEL);
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
	else if (popup == ENDPOPUP)//游戏结束，是否再来一局弹窗
	{
		if (songONorOFF != NO)
		{
			backMusic(CLOSEMUSIC);
		}
		int k = MessageBox(handle, "再来一局！", "提示", MB_OKCANCEL);
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

void menu(int choice, HWND handle)//菜单中转(执行鼠标点击坐标的具体操作)
{
	int yes_or_no;
	switch (choice)
	{
	case SINGLEMODE://单人模式
		yes_or_no = pop_up_window(SINGLEPOPUP, handle);
		if (yes_or_no == NO) 
		{
			localLevel = 1;
			mainInterface(NO);
		}
		closegraph();
		singlePlayerMode();
		return;
	case DOUBLEMODE://双人模式
		yes_or_no = pop_up_window(DOUBLEPOPUP, handle);
		mainInterface(NO);
		return;
	case GAMEPLAY://游戏设置
		closegraph();
		gameSetting();
		return;
	case GAMERECORD://游戏记录
		closegraph();
		gameRecord();
		return;
	case GRECORDBUTTON://游戏记录返回主界面
		closegraph();
		mainInterface(YES);
		return;
	case MUSICON://音乐打开按钮
		if (songONorOFF != YES) 
		{
			backMusic(OPENMUSIC);
			backMusic(PLAYMUSIC);
			songONorOFF = YES;
		}
		return;
	case MUSICOFF://音乐关闭按钮
		if (songONorOFF != NO) 
		{
			backMusic(CLOSEMUSIC);
			songONorOFF = NO;
		}
		return;
	case SETUPBUTTON://游戏设置返回主界面
		closegraph();
		mainInterface(YES);
		return;
	case SPEEDSLOW://速度慢按钮
		snakeSpeed = SPEEDSLOW;
		return;
	case SPEEDMIDDLE://速度中按钮
		snakeSpeed = SPEEDMIDDLE;
		return;
	case SPEEDFAST://速度快按钮
		snakeSpeed = SPEEDFAST;
		return;
	case SNAKERED://红色按钮
		snakeColor = SNAKERED;
		return;
	case SNAKEGREEN://绿色按钮
		snakeColor = SNAKEGREEN;
		return;
	case SNAKEBLUE://蓝色按钮
		snakeColor = SNAKEBLUE;
		return;
	default :
		return;
	}
}

void mainInterface(int flag)//主界面
{
	if (songONorOFF != NO) 
	{
		backMusic(OPENMUSIC);
		backMusic(PLAYMUSIC);
	}
	if (flag == YES)
	{
		initgraph(window_length, window_width);//启动窗口
	}
	HWND startwindow = GetHWnd();//获取窗口句柄
	SetWindowText(startwindow, "贪吃蛇");//设置窗口标题
	while (1)//选项循环模式
	{
		BeginBatchDraw();
		IMAGE start_bk;
		loadimage(&start_bk, _T("snake1.png"));//设置背景
		putimage(550, 150, &start_bk); //x,y为左上角顶点放置图片
		//设置按钮
		nomal_botton(50, 100, 450, 180, "Snake Game", 80);//游戏名称
		nomal_botton(200, 220, 360, 260, "单人模式", 40);//第一个按钮
		nomal_botton(200, 280, 360, 320, "双人模式", 40);//第二个按钮
		nomal_botton(200, 340, 360, 380, "游戏设置", 40);//第三个按钮
		nomal_botton(200, 400, 360, 440, "游戏记录", 40);//第四个按钮
		FlushBatchDraw();
		int choice = select(MAINWIND);//选择选项
		menu(choice, startwindow);//加载选项
	}
}

void gameInterface() //游戏关卡界面
{
	initgraph(window_length, window_width);//启动窗口
	HWND gameInterfacewindow = GetHWnd();//获取窗口句柄
	SetWindowText(gameInterfacewindow, "游戏界面");//设置窗口标题
	snakeInit();
	//初始化画布
	cleardevice();
	BeginBatchDraw();
	produceWall();
	produceFood();
	snakePrint();
	FlushBatchDraw();
	//开始移动
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

void gameLevel() //关卡跳转界面
{
	initgraph(window_length, window_width);//启动窗口
	HWND gameLevelwindow = GetHWnd();//获取窗口句柄
	SetWindowText(gameLevelwindow, "游戏关卡");//设置窗口标题
	cleardevice();
	BeginBatchDraw();
	IMAGE gameLevelwindow_bk;
	loadimage(&gameLevelwindow_bk, _T("snake2.png"));//设置背景
	putimage(650, 350, &gameLevelwindow_bk); //x,y为左上角顶点放置图片
	nomal_botton(200, 100, 600, 180, "Snake Game！", 80);//设置文字位置
	char s[50];
	sprintf(s, "关卡:%d", localLevel);
	nomal_botton(330, 250, 450, 290, s, 40);
	FlushBatchDraw();
	Sleep(500);
	closegraph();//关闭窗口
}

void endInterface() //游戏结束界面
{
	initgraph(window_length, window_width);//启动窗口
	HWND gameLevelwindow = GetHWnd();//获取窗口句柄
	SetWindowText(gameLevelwindow, "游戏结束");//设置窗口标题
	cleardevice();
	BeginBatchDraw();
	char str[100];
	char* s = (char*)malloc(sizeof(char) * 100);
	s = recordHighScore();
	strcpy(str, s);
	IMAGE gameLevelwindow_bk;
	loadimage(&gameLevelwindow_bk, _T("snake2.png"));//设置背景
	putimage(650, 350, &gameLevelwindow_bk); //x,y为左上角顶点放置图片
	nomal_botton(200, 100, 600, 180, "Game Over！", 80);
	nomal_botton(310, 250, 490, 290, "再来一局？", 40);
	nomal_botton(200, 350, 590, 380, str , 30);
	FlushBatchDraw();
	int result = pop_up_window(ENDPOPUP, gameLevelwindow);//获取弹窗结果
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

void finishTheGame() //游戏通关界面
{
	initgraph(window_length, window_width);//启动窗口
	HWND finishTheGamewindow = GetHWnd();//获取窗口句柄
	SetWindowText(finishTheGamewindow, "游戏通关");//设置窗口标题
	cleardevice();
	BeginBatchDraw();
	IMAGE finishTheGame_bk;
	loadimage(&finishTheGame_bk, _T("snake2.png"));//设置背景
	putimage(650, 350, &finishTheGame_bk); //x,y为左上角顶点放置图片
	nomal_botton(300, 100, 550, 180, "恭喜您！", 80);
	nomal_botton(330, 250, 490, 290, "完美通关", 40);
	//nomal_botton(330, 350, 490, 370, "按任意键结束...", 20);
	FlushBatchDraw();
	Sleep(500);
	closegraph();
	mainInterface(YES);
}

void gameSetting() //游戏设置界面
{
	initgraph(window_length, window_width);//启动窗口
	HWND gameSettingwindow = GetHWnd();//获取窗口句柄
	SetWindowText(gameSettingwindow, "游戏设置");//设置窗口标题
	while (1) {
		cleardevice();
		BeginBatchDraw();
		nomal_botton(220, 100, 540, 180, "游戏设置", 80);
		nomal_botton(240, 240, 380, 260, "背景音乐：", 20);
		nomal_botton(400, 240, 420, 260, "开", 20);
		nomal_botton(460, 240, 480, 260, "关", 20);
		nomal_botton(240, 300, 380, 320, "初始速度：", 20);
		nomal_botton(400, 300, 420, 320, "慢", 20);
		nomal_botton(450, 300, 470, 320, "中", 20);
		nomal_botton(500, 300, 520, 320, "快", 20);
		nomal_botton(240, 360, 380, 380, "蛇的颜色：", 20);
		nomal_botton(400, 360, 420, 380, "红", 20);
		nomal_botton(450, 360, 470, 380, "绿", 20);
		nomal_botton(500, 360, 520, 380, "蓝", 20);
		//nomal_botton(280, 250, 480, 290, "最高关卡:1", 20);
		nomal_botton(310, 420, 460, 450, "返回主界面", 30);
		FlushBatchDraw();
		int choice = select(GSETUPWIND);
		menu(choice, gameSettingwindow);
	}
}

void gameRecord() //游戏记录界面
{
	initgraph(window_length, window_width);//启动窗口
	HWND recordwindow = GetHWnd();//获取窗口句柄
	SetWindowText(recordwindow, "游戏记录");//设置窗口标题
	while (1) {
		cleardevice();
		BeginBatchDraw();
		nomal_botton(220, 100, 540, 180, "游戏记录", 80);
		char s[50];
		sprintf(s, "最高关卡:%d", levelMax);
		nomal_botton(280, 250, 480, 290, s, 40);
		nomal_botton(280, 350, 480, 390, "返回主界面", 40);
		FlushBatchDraw();
		int choice = select(GRECORDWIND);
		menu(choice, recordwindow);
	}
}
