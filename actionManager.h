#pragma once
#include "singletonBase.h"
#include <vector>

class action;

class actionManager : public singletonBase<actionManager>
{
private:
	typedef vector<action*> arrAction;
	typedef vector<action*>::iterator iterAction;

private:
	arrAction _vAction;
	iterAction _viAction;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void MoveTo(image* image, float endX, float endY, float time);
	void MoveTo(image* image, float endX, float endY, float time, void* cbFunction);


	actionManager();
	~actionManager();
};

