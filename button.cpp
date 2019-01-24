#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{
}

HRESULT button::Init(LPCWSTR imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	CALLBACK_FUNCTION cbFunction)
{
	//ฤÝน้วิพฅ
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;


	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->FindImage(imageName);

	_rc = RectMakeCenter(x, y, _image->GetFrameWidth(), _image->GetFrameHeight());


	return S_OK;
}

void button::Release(void)
{

}

void button::Update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->IsOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
}

void button::Render(void)
{
	switch (_direction)
	{
	case BUTTONDIRECTION_UP: case BUTTONDIRECTION_NULL:
		_image->FrameRender(GetMemDC(), _rc.left, _rc.top,
			_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
	case BUTTONDIRECTION_DOWN:
		_image->FrameRender(GetMemDC(), _rc.left, _rc.top,
			_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;

	}
}