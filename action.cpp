#include "stdafx.h"
#include "action.h"


action::action()
{
}


action::~action()
{
}

HRESULT action::Init(void)
{

	_callbackFunction = NULL;
	_worldTimeCount = 0.0f;
	_isMoving = false;

	return S_OK;
}

void action::Release(void)
{

}

void action::Update(void)
{
	Moving();
}

void action::Render(void)
{

}


void action::MoveTo(image* image, float endX, float endY, float time)
{
	if (!_isMoving)
	{
		_callbackFunction = NULL;

		_image = image;

		_startX = image->GetX();
		_startY = image->GetY();

		_endX = endX;
		_endY = endY;

		_travelRange = GetDistance(_startX, _startY, _endX, _endY);

		_angle = GetAngle(_startX, _startY, _endX, _endY);

		_worldTimeCount = TIMEMANAGER->GetWorldTime();

		_time = time;

		_isMoving = true;


	}
}

void action::MoveTo(image* image, float endX, float endY, float time, CALLBACK_FUNCTION cbFunction)
{
	if (!_isMoving)
	{
		_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

		_image = image;

		_startX = image->GetX();
		_startY = image->GetY();

		_endX = endX;
		_endY = endY;

		_travelRange = GetDistance(_startX, _startY, _endX, _endY);

		_angle = GetAngle(_startX, _startY, _endX, _endY);

		_worldTimeCount = TIMEMANAGER->GetWorldTime();

		_time = time;

		_isMoving = true;
	}
}

void action::Moving(void)
{
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->GetElapsedTime();

	float moveSpeed = (elapsedTime / _time) * _travelRange;

	_image->SetX(_image->GetX() + cosf(_angle) * moveSpeed);
	_image->SetY(_image->GetY() + (-sinf(_angle)) * moveSpeed);

	if (_time + _worldTimeCount <= TIMEMANAGER->GetWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->GetWorldTime();

		_isMoving = false;

		if (_callbackFunction != NULL)
		{
			_callbackFunction();
		}
	}
}
