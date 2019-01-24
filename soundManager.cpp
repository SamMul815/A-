#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	: _system(NULL),
	_sound(NULL),
	_channel(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::Init(void)
{
	//사운드 시스템사용할 거라고 셋팅
	System_Create(&_system);
	
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//채널과 사운드는 꼭 꼭 꼭 동적할당(필쑤)
	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));

	return S_OK;
}

void soundManager::Release(void)
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 닫기 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

//Fmod 시스템을 갱신
void soundManager::Update(void)
{
	//사운드 System 계속적으로 업데이트
	_system->update();

	//볼륨이 바뀌거나 
	//재생이 끝난 사운드를 채널에서 빼내는등의 다양한
	//작업을 자동으로 해준다

	//촬리 얘드라 꼭 포폴 완성하거라
}


void soundManager::AddSound(wstring keyName, LPCWSTR soundName, bool bgm, bool loop)
{
	//루프여부
	if (loop)
	{
		if (bgm)
		{
			_system->createStream((const char*)soundName, FMOD_LOOP_NORMAL | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound((const char*)soundName, FMOD_LOOP_NORMAL | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream((const char*)soundName, FMOD_DEFAULT | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound((const char*)soundName, FMOD_DEFAULT | FMOD_UNICODE, 0, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.push_back(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void soundManager::Play(wstring keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::Stop(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::Pause(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::Resume(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::IsPlaySound(wstring keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::IsPauseSound(wstring keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

int soundManager::GetVolume(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	float vol;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getVolume(&vol);
			break;
		}
	}

	return vol;
}

void soundManager::SetVolume(wstring keyName, float vol)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(vol);
			break;
		}
	}
}

int soundManager::GetCurrentPlayTime(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	unsigned int currentTime;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&currentTime, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return currentTime;
}

void soundManager::SetCurrentPlayTime(wstring keyName, unsigned int currentTime)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(currentTime, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}

int soundManager::GetFinishPlayTime(wstring keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	unsigned int finishTime;

	for (iter; iter != _mTotalSounds.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			(*iter->second)->getLength(&finishTime, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return finishTime;
}