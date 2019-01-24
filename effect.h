#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int				_x;					//����Ʈ ��ǥ��ġ left
	int				_y;					//����Ʈ ��ǥ��ġ top

	image*			_effectImage;		//����Ʈ �̹���
	animation*		_effectAnimation;	//����Ʈ �ִϸ��̼�
	BOOL			_isRunning;			//����Ʈ Ȱ��ȭ ����
	float			_elapsedTime;		//����Ʈ ����ð�

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

