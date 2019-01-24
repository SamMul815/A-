#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase < timeManager >
{
private:
	timer* _timer;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(float lock = 0.0f);
	void Render(HDC hdc);

	//프레임 화면에 출력! 및 이제 가져다 쓸수있음
	inline float GetElapsedTime(void) const { return _timer->GetElapsedTime(); }
	inline float GetWorldTime(void) const { return _timer->GetWorldTime(); }

	timeManager();
	~timeManager();
};

