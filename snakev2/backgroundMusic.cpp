#include "globalDef.h"
#include "backgroundMusic.h"

//����������Ŀ
extern int songTrack;

void backMusic(int flag) //��������������
{
	int nowSongTrack = songTrack;
	switch (flag) 
	{
	case OPENMUSIC:	
		openMusic(nowSongTrack);
		return;
	case PLAYMUSIC:
		playMusic(nowSongTrack);
		return;
	case PAUSEMUSIC:
		pauseMusic(nowSongTrack);
		return;
	case RESUMEMUSIC:
		resumeMusic(nowSongTrack);
		return;
	case VOLUMEMUSIC:
		oppVolumeMusic(nowSongTrack, 800);
		return;
	case CLOSEMUSIC:
		closeMusic(nowSongTrack);
		return;
	default:
		return;
	}
}

void openMusic(int nowSongTrack) //������
{
	switch (nowSongTrack)
	{
	case MUSICISY:
		mciSendString("open isy.mp3 alias music_isy", 0, 0, 0);//alias�Ǳ�������˼����music������isy.mp3
		return;
	case MUSICZYN:
		mciSendString("open zyn.mp3 alias music_zyn", 0, 0, 0);
		return;
	case MUSICNDYS:
		mciSendString("open ndys.mp3 alias music_ndys", 0, 0, 0);
		return;
	default:
		return;
	}
}

void playMusic(int nowSongTrack)//��������
{
	switch (nowSongTrack)
	{
	case MUSICISY:
		mciSendString("play music_isy", 0, 0, 0);
		return;
	case MUSICZYN:
		mciSendString("play music_zyn", 0, 0, 0);
		return;
	case MUSICNDYS:
		mciSendString("play music_ndys", 0, 0, 0);
		return;
	default:
		return;
	}
}

void pauseMusic(int nowSongTrack) //��ͣ��ǰ���ŵ�����
{
	switch (nowSongTrack)
	{
	case MUSICISY:
		mciSendString("pause music_isy", 0, 0, 0);
		return;
	case MUSICZYN:
		mciSendString("pause music_zyn", 0, 0, 0);
		return;
	case MUSICNDYS:
		mciSendString("pause music_ndys", 0, 0, 0);
		return;
	default:
		return;
	}
}

void resumeMusic(int nowSongTrack) //�ָ���ͣ���ŵ�����
{
	switch (nowSongTrack)
	{
	case MUSICISY:
		mciSendString("resume music_isy", 0, 0, 0);
		return;
	case MUSICZYN:
		mciSendString("resume music_zyn", 0, 0, 0);
		return;
	case MUSICNDYS:
		mciSendString("resume music_ndys", 0, 0, 0);
		return;
	default:
		return;
	}
}

void oppVolumeMusic(int nowSongTrack, int volumeSize) //�������������С
{
	char s[100];
	memset(s, 0, sizeof(s));
	switch (nowSongTrack)
	{
	case MUSICISY:
		sprintf(s, "setaudio music_isy volume to %d", volumeSize);
		mciSendString(s, 0, 0, 0);	//�������ڵ���ǰý��������volumeSize
		return;
	case MUSICZYN:
		sprintf(s, "setaudio music_zyn volume to %d", volumeSize);
		mciSendString(s, 0, 0, 0);	
		return;
	case MUSICNDYS:
		sprintf(s, "setaudio music_ndys volume to %d", volumeSize);
		mciSendString(s, 0, 0, 0);	
		return;
	default:
		return;
	}
}

void closeMusic(int nowSongTrack)//�ر�����
{
	switch (nowSongTrack)
	{
	case MUSICISY:
		mciSendString("close music_isy", 0, 0, 0);
		return;
	case MUSICZYN:
		mciSendString("close music_zyn", 0, 0, 0);
		return;
	case MUSICNDYS:
		mciSendString("close music_ndys", 0, 0, 0);
		return;
	default:
		return;
	}
}

