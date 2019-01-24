#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	typedef vector<effect*> arrEffects;
	typedef vector<effect*>::iterator iterEffects;

	typedef map<wstring, arrEffects> arrEffect;
	typedef map<wstring, arrEffects>::iterator iterEffect;

	typedef vector<map<wstring, arrEffects>> arrTotalEffect;
	typedef vector<map<wstring, arrEffects>>::iterator iterTotalEffect;

private:
	arrTotalEffect _vTotalEffects;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(HDC hdc);
	void Render(HDC hdc, RECT cameraRc);

	void AddEffect(wstring effectName, LPCWSTR imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsedTime, int buffer);

	void Play(wstring effectName, int x, int y);


	effectManager();
	~effectManager();
};

