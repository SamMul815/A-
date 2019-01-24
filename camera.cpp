#include "stdafx.h"
#include "camera.h"

camera::camera() {}

camera::~camera() {}

HRESULT camera::Init(int focusX, int focusY)
{
	_cameraBuffer = new image;
	_cameraBuffer->Init(WINSIZEX, WINSIZEY);

	_playBuffer = new image;
	_playBuffer->Init(600*3, 600*3);

	_alphaImage = new image;
	_alphaImage->Init(WINSIZEX, WINSIZEY, false, NULL, true, false); //,false, NULL, true, false
	_alphaRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	_cameraSpeed = 7.0f;

	_focus.x = focusX;
	_focus.y = focusY;
	_destFocus = { NULL, NULL };
	_cameraRc = RectMakeCenter(_focus.x, _focus.y, WINSIZEX, WINSIZEY);
	_cameraRangeRc = RectMakeCenter(WINSIZEX, WINSIZEY, WINSIZEX * 2, WINSIZEY * 2);

//	_playRc = RectMake(0, 0, VIEWSIZEHALF, VIEWSIZEHALF);
	

	_shakeCam = false;
	_shakeCount = 0;


	_fadeIn	= false;
	_fadeOut = false;
	_alphaValue_fadeIn = 255;
	_alphaValue_fadeOut = 0; 

	_showDebugMode = false;

	return S_OK;
}

void camera::Release()
{
	SAFE_DELETE(_cameraBuffer);
	SAFE_DELETE(_playBuffer);
}

void camera::Update()
{
	//=== ī�޶� �̵� (��ǥ���� ���� ���) ===//
	if (_destFocus.x != NULL && _destFocus.y != NULL)
		MoveCamera();

	//====ī�޶� ���� ����====//

	CameraCorrection();

	//======================//

	// ī�޶� ��鸲
	if (_shakeCam)
	{
		ShakeCamera();
	}

	// ī�޶� DC ���� ��ǥ ����(cameraRc�� ��ġ�� ���� ��� ��ǥ ����)
	SetViewportOrgEx(_cameraBuffer->GetMemDC(), -(_cameraRc.left), -(_cameraRc.top), NULL);


	// ���̵� ��
	if (_fadeIn)
	{
		_alphaValue_fadeIn -= 2;

		if (_alphaValue_fadeIn <= 0)
		{
			_alphaValue_fadeIn = 0;
			_fadeIn = false;
		}
	}
	// ���̵� �ƿ�
	if (_fadeOut)
	{
		_alphaValue_fadeOut += 2;

		if (_alphaValue_fadeOut >= 255)
		{
			_alphaValue_fadeOut = 255;
			_fadeOut = true;
		}
	}
	
	// ����� �¿���
	if (KEYMANAGER->IsToggleKey(VK_TAB))
	{
		_showDebugMode = true;
	}
	else _showDebugMode = false;

}

void camera::Update(RECT rangeRc)
{
	int centerX = 0;
	int centerY = 0;

	//if (rangeRc.right >= VIEWSIZEHALF)
	//{
	//	if (_focus.x < VIEWSIZEHALF / 2)
	//		centerX = VIEWSIZEHALF / 2;
	//	else if (_focus.x > rangeRc.right - VIEWSIZEHALF / 2)
	//		centerX = rangeRc.right - VIEWSIZEHALF / 2;
	//	else
	//		centerX = _focus.x;
	//}
	//else
	//{
	//	centerX = VIEWSIZEHALF / 2;
	//}

	//if (rangeRc.bottom >= VIEWSIZEHALF)
	//{
	//	if (_focus.y < VIEWSIZEHALF / 2)
	//		centerY = VIEWSIZEHALF / 2;
	//	else if (_focus.y > rangeRc.bottom - VIEWSIZEHALF / 2)
	//		centerY = rangeRc.bottom - VIEWSIZEHALF / 2;
	//	else
	//		centerY = _focus.y;
	//}
	//else
	//{
	//	centerY = VIEWSIZEHALF / 2;
	//}

	//_playRc = RectMakeCenter(centerX, centerY, VIEWSIZEHALF, VIEWSIZEHALF);


	//// ���̵� ��
	//if (_fadeIn)
	//{
	//	_alphaValue_fadeIn -= 2;

	//	if (_alphaValue_fadeIn <= 0)
	//	{
	//		_alphaValue_fadeIn = 255;
	//		_fadeIn = false;
	//	}
	//}
	//// ���̵� �ƿ�
	//if (_fadeOut)
	//{
	//	_alphaValue_fadeOut += 2;

	//	if (_alphaValue_fadeOut >= 255)
	//	{
	//		_alphaValue_fadeOut = 0;
	//		_fadeOut = false;
	//	}
	//}

}

void camera::Render(HDC hdc)
{
	/*swprintf(_systemMsg, L"%d %d %d %d", _cameraRc.left, _cameraRc.top, _cameraRc.right, _cameraRc.bottom);
	TextOut(_cameraBuffer->GetMemDC(), _cameraRc.right - 100, _cameraRc.top + 10, _systemMsg, _tcslen(_systemMsg));*/
	BitBlt(hdc,							// ���� �� DC (�� ��ȭ��)
		0,								// �߶�� X
		0,								// �߶�� Y
		WINSIZEX,						// ���� �� �̹����� width
		WINSIZEY,						// ���� �� �̹����� height
		_cameraBuffer->GetMemDC(),		// ���� �� �̹����� ������ DC
		_cameraRc.left,					// ���� �� �̹����� left
		_cameraRc.top,					// ���� �� �̹����� top
		SRCCOPY);						// �� ! �� !

	if (_fadeIn)
	{
		_alphaImage->AlphaRender(hdc, 0, 0, _alphaValue_fadeIn);
	}
	
	if (_fadeOut)
	{
		_alphaImage->AlphaRender(hdc, 0, 0, _alphaValue_fadeOut);
	}	
	 
}
void camera::RenderPlayBuffer(HDC hdc)
{
	//BitBlt(hdc,							// ���� �� DC (�� ��ȭ��)
	//	0,								// �߶�� X
	//	0,								// �߶�� Y
	//	600,						// ���� �� �̹����� width
	//	600,						// ���� �� �̹����� height
	//	_playBuffer->GetMemDC(),		// ���� �� �̹����� ������ DC
	//	0,					// ���� �� �̹����� left
	//	0,					// ���� �� �̹����� top
	//	SRCCOPY);						// �� ! �� !
	/*SetStretchBltMode(hdc, HALFTONE);
	StretchBlt(hdc, 101, 0,
		VIEWSIZE, VIEWSIZE,
		_playBuffer->GetMemDC(),
		0, 0,
		VIEWSIZEHALF,
		VIEWSIZEHALF,
		SRCCOPY);*/
}

void camera::MoveCamera()
{
	int angle = GetAngle(_focus.x, _focus.y, _destFocus.x, _destFocus.y);
	int distance = GetDistance(_focus.x, _focus.y, _destFocus.x, _destFocus.y);
	_focus.x += cos(angle) * distance + 1;
	_focus.y += -sin(angle) * distance + 1;
	
	if (distance <= 1)
		_destFocus = { NULL, NULL };
}

void camera::CameraCorrection()
{
	// ���� �׽�Ʈ
	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD8))
	{
		_focus.y -= _cameraSpeed;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD2))
	{
		_focus.y += _cameraSpeed;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD4))
	{
		_focus.x -= _cameraSpeed;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_NUMPAD6))
	{
		_focus.x += _cameraSpeed;
	}
	_cameraRc = RectMakeCenter(_focus.x, _focus.y, WINSIZEX, WINSIZEY);

	if (_cameraRc.left <= _cameraRangeRc.left)
	{
		_focus.x = _cameraRangeRc.left + WINSIZEX / 2;
	}

	if (_cameraRc.top <= _cameraRangeRc.top)
	{
		_focus.y = _cameraRangeRc.top + WINSIZEY / 2;
	}

	if (_cameraRc.right >= _cameraRangeRc.right)
	{
		_focus.x = _cameraRangeRc.right - WINSIZEX / 2;
	}

	if (_cameraRc.bottom >= _cameraRangeRc.bottom)
	{
		_focus.y = _cameraRangeRc.bottom - WINSIZEY / 2;
	}
	

	_cameraRc = RectMakeCenter(_focus.x, _focus.y, WINSIZEX, WINSIZEY);
}

void camera::ShakeCamera()
{
	_shakeCount++;

	if (_shakeCount % 2 != 0) ShakingCameraRectLeft();
	else ShakingCameraRectRight();

	if (_shakeCount >= 20)
	{
		_shakeCam = false;
		_shakeCount = 0;
	}
}

void camera::ShakingCameraRectLeft()
{
	_cameraRc.top -= _shakeStrength;
	_cameraRc.bottom -= _shakeStrength;
}

void camera::ShakingCameraRectRight()
{
	_cameraRc.top += _shakeStrength;
	_cameraRc.bottom += _shakeStrength;
}