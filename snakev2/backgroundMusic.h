#pragma once

#include "globalDef.h"

void backMusic(int flag);//控制接口

void openMusic(int nowSongTrack);//打开音乐

void playMusic(int nowSongTrack);//播放音乐

void pauseMusic(int nowSongTrack);//暂停音乐

void resumeMusic(int nowSongTrack);//恢复被暂停的音乐

void oppVolumeMusic(int nowSongTrack, int volumeSize);//调节音乐相对音量

void closeMusic(int nowSongTrack);//关闭音乐

