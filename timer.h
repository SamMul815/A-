#pragma once


class timer
{
private:
	bool _isHardware;
	float _timeScale;
	float _timeElapsed;
	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT Init(void);
	void Tick(float lockFPS = 0.0f);
	unsigned long GetFrameRate(wchar_t* str = NULL) const;
	inline float GetElapsedTime(void) const { return _timeElapsed; }
	inline float GetWorldTime(void) const { return _worldTime; }

	timer();
	~timer();
};

