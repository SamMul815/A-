#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{

}

HRESULT keyAniManager::Init(void)
{

	return S_OK;
}

void keyAniManager::Release(void)
{
	DeleteAll();
}

void keyAniManager::Update(void)
{
	iterAnimations iter = _mTotalAnimations.begin();

	for (iter; iter != _mTotalAnimations.end(); ++iter)
	{
		//애니메이션이 재생되고 있으면 넘어간다
		if (!iter->second->IsPlay()) continue;

		//초당 60프레임 얍얍!
		iter->second->FrameUpdate(TIMEMANAGER->GetElapsedTime() * 1.0f);
	}
}
void keyAniManager::Render(void)
{

}

void keyAniManager::AddDefaultFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetDefPlayFrame(reverse, loop);
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));

}
void keyAniManager::AddDefaultFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}
void keyAniManager::AddDefaultFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}

//배열 키애니메이션																																								   
void keyAniManager::AddArrayFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int* arr, int arrLen, int fps, bool loop)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(arr, arrLen, loop);
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}
void keyAniManager::AddArrayFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}
void keyAniManager::AddArrayFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}

//구간 키애니메이션																																								   
void keyAniManager::AddCoordinateFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(start, end, reverse, loop);
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}
void keyAniManager::AddCoordinateFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}
void keyAniManager::AddCoordinateFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj)
{
	image* img = IMAGEMANAGER->FindImage(imageKeyName);
	animation* ani = new animation;

	ani->Init(img->GetWidth(), img->GetHeight(), img->GetFrameWidth(), img->GetFrameHeight());
	ani->SetPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->SetFPS(fps);

	_mTotalAnimations.insert(pair<wstring, animation*>(animationKeyName, ani));
}

void keyAniManager::Start(wstring animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->Start();
}
void keyAniManager::Stop(wstring animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->Stop();
}
void keyAniManager::Pause(wstring animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->Pause();
}
void keyAniManager::Resume(wstring animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);
	iter->second->Resume();
}

animation* keyAniManager::FindAnimation(wstring animationKeyName)
{
	iterAnimations iter = _mTotalAnimations.find(animationKeyName);

	if (iter != _mTotalAnimations.end())
	{
		return iter->second;
	}

	return NULL;
}

void keyAniManager::DeleteAll(void)
{
	for (iterAnimations iter = _mTotalAnimations.begin(); iter != _mTotalAnimations.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = _mTotalAnimations.erase(iter);
		}
		else ++iter;
	}

	_mTotalAnimations.clear();
}