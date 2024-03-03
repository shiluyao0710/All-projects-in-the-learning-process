#include "globalDef.h"
#include "backgroundMusic.h"

//声明音乐曲目
extern int songTrack;

void backMusic(int flag) //背景音乐主函数
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

void openMusic(int nowSongTrack) //打开音乐
{
	switch (nowSongTrack)
	{
	case MUSICISY:
		mciSendString("open isy.mp3 alias music_isy", 0, 0, 0);//alias是别名的意思，用music来代替isy.mp3
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

void playMusic(int nowSongTrack)//播放音乐
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

void pauseMusic(int nowSongTrack) //暂停当前播放的音乐
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

void resumeMusic(int nowSongTrack) //恢复暂停播放的音乐
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

void oppVolumeMusic(int nowSongTrack, int volumeSize) //调节相对音量大小
{
	char s[100];
	memset(s, 0, sizeof(s));
	switch (nowSongTrack)
	{
	case MUSICISY:
		sprintf(s, "setaudio music_isy volume to %d", volumeSize);
		mciSendString(s, 0, 0, 0);	//音量调节到当前媒体音量的volumeSize
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

void closeMusic(int nowSongTrack)//关闭音乐
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

