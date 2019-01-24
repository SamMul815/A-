#pragma once
#include "gameNode.h"

typedef void(*CALLBACK_FUNCTION)(void);

class action : public gameNode
{
private:
	image* _image;
	float _startX, _startY;
	float _endX, _endY;

	float _angle;
	float _travelRange;
	float _worldTimeCount;
	float _time;

	bool _isMoving;

	CALLBACK_FUNCTION _callbackFunction;

public:
	action();
	~action();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void MoveTo(image* image, float endX, float endY, float time);
	void MoveTo(image* image, float endX, float endY,
		float time, CALLBACK_FUNCTION cbFunction);

	void Moving(void);

	bool GetIsMoving(void) { return _isMoving; }
};

