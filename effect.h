#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int				_x;					//이펙트 좌표위치 left
	int				_y;					//이펙트 좌표위치 top

	image*			_effectImage;		//이펙트 이미지
	animation*		_effectAnimation;	//이펙트 애니메이션
	BOOL			_isRunning;			//이펙트 활성화 여부
	float			_elapsedTime;		//이펙트 경과시간

public:
	effect();
	virtual ~effect();

	virtual HRESULT Init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	virtual HRESULT Init(image* effectImage, int frameW, int frameH, int fps);
	virtual void Release(void);
	virtual void Update(void);
	void Update(float elapsedTime);
	virtual void Render(HDC hdc);
	virtual void Render(HDC hdc, RECT cameraRc);

	void StartEffect(int x, int y);
	virtual void KillEffect(void);

	BOOL GetIsRunning(void) { return _isRunning; }
};

