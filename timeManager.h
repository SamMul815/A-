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

	//������ ȭ�鿡 ���! �� ���� ������ ��������
	inline float GetElapsedTime(void) const { return _timer->GetElapsedTime(); }
	inline float GetWorldTime(void) const { return _timer->GetWorldTime(); }

	timeManager();
	~timeManager();
};

