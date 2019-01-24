#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::Init(void)
{
	_timer = new timer;
	_timer->Init();

	return S_OK;
}

void timeManager::Release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

void timeManager::Update(float lock)
{
	if (_timer != NULL)
	{
		_timer->Tick(lock);
	}
}

void timeManager::Render(HDC hdc)
{
	wchar_t str[256];
	string strFrame;

	SetBkMode(hdc, TRANSPARENT);

#ifdef _DEBUG
	if (_timer != NULL)
	{
		//FPS
		swprintf(str, L"framePerSec(FPS) : %d", _timer->GetFrameRate());
		TextOutW(hdc, 0, 0, str, _tcslen(str));

		//월드타임
		swprintf(str, L"worldTime : %f", _timer->GetWorldTime());
		TextOutW(hdc, 0, 20, str, _tcslen(str));

		//갱신 Tick
		swprintf(str, L"elapsedTime : %f", _timer->GetElapsedTime());
		TextOutW(hdc, 0, 40, str, _tcslen(str));
	}
#else
	{
		//FPS
		swprintf(str, L"framePerSec(FPS) : %d", _timer->GetFrameRate());
		TextOut(hdc, 0, 0, str, _tcslen(str));
	}
#endif
}