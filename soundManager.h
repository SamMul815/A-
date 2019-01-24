#pragma once
#include "singletonBase.h"
#include <vector>

//fmod.hpp 추가
#include "./inc/fmod.hpp"

//lib링크
#pragma comment(lib, "./lib/fmodex_vc.lib")

using namespace FMOD;

//채널 버퍼를 셋팅
#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef vector<pair<wstring, Sound**>> arrSounds;
	typedef vector<pair<wstring, Sound**>>::iterator arrSoundsIter;
	typedef vector<pair<wstring, Channel**>> arrChannels;
	typedef vector<pair<wstring, Channel**>>::iterator arrChannelsIter;
	
private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);

	void AddSound(wstring keyName, LPCWSTR soundName, bool bgm, bool loop);
	void Play(wstring keyName, float volume = 1.0f); // 0.0 ~ 1.0f  0 ~ 255
	void Stop(wstring keyName);
	void Pause(wstring keyName);
	void Resume(wstring keyName);

	bool IsPlaySound(wstring keyName);
	bool IsPauseSound(wstring keyName);

	int GetVolume(wstring keyName);
	void SetVolume(wstring keyName, float vol);

	int GetCurrentPlayTime(wstring keyName);
	void SetCurrentPlayTime(wstring keyName, unsigned int currentTime);

	int GetFinishPlayTime(wstring keyName);

	soundManager();
	~soundManager();
};

