#pragma once
#include "singletonBase.h"
#include <map>

class image;
class animation;

class keyAniManager : public singletonBase < keyAniManager >
{
private:
	typedef map<wstring, animation*> arrAnimation;
	typedef map<wstring, animation*>::iterator iterAnimations;

private:
	arrAnimation _mTotalAnimations;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	//����Ʈ Ű�ִϸ��̼�
	void AddDefaultFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int fps, bool reverse, bool loop);
	void AddDefaultFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction);
	void AddDefaultFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	//�迭 Ű�ִϸ��̼�
	void AddArrayFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int* arr, int arrLen, int fps, bool loop);
	void AddArrayFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void AddArrayFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);

	//���� Ű�ִϸ��̼�
	void AddCoordinateFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
	void AddCoordinateFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj);
	void AddCoordinateFrameAnimation(wstring animationKeyName, wchar_t* imageKeyName, int start, int end, int fps, bool reverse, bool loop);

	void Start(wstring animationKeyName);
	void Stop(wstring animationKeyName);
	void Pause(wstring animationKeyName);
	void Resume(wstring animationKeyName);

	animation* FindAnimation(wstring animationKeyName);

	void DeleteAll(void);

	keyAniManager();
	~keyAniManager();
};

