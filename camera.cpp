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
	//=== 카메라 이동 (목표점이 있을 경우) ===//
	if (_destFocus.x != NULL && _destFocus.y != NULL)
		MoveCamera();

	//====카메라 범위 보정====//

	CameraCorrection();

	//======================//

	// 카메라 흔들림
	if (_shakeCam)
	{
		ShakeCamera();
	}

	// 카메라 DC 원점 좌표 조정(cameraRc의 위치에 따라 출력 좌표 보정)
	SetViewportOrgEx(_cameraBuffer->GetMemDC(), -(_cameraRc.left), -(_cameraRc.top), NULL);


	// 페이드 인
	if (_fadeIn)
	{
		_alphaValue_fadeIn -= 2;

		if (_alphaValue_fadeIn <= 0)
		{
			_alphaValue_fadeIn = 0;
			_fadeIn = false;
		}
	}
	// 페이드 아웃
	if (_fadeOut)
	{
		_alphaValue_fadeOut += 2;

		if (_alphaValue_fadeOut >= 255)
		{
			_alphaValue_fadeOut = 255;
			_fadeOut = true;
		}
	}
	
	// 디버그 온오프
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


	//// 페이드 인
	//if (_fadeIn)
	//{
	//	_alphaValue_fadeIn -= 2;

	//	if (_alphaValue_fadeIn <= 0)
	//	{
	//		_alphaValue_fadeIn = 255;
	//		_fadeIn = false;
	//	}
	//}
	//// 페이드 아웃
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
	BitBlt(hdc,							// 복사 될 DC (새 도화지)
		0,								// 잘라올 X
		0,								// 잘라올 Y
		WINSIZEX,						// 복사 할 이미지의 width
		WINSIZEY,						// 복사 할 이미지의 height
		_cameraBuffer->GetMemDC(),		// 복사 한 이미지가 존재할 DC
		_cameraRc.left,					// 복사 한 이미지의 left
		_cameraRc.top,					// 복사 한 이미지의 top
		SRCCOPY);						// 복 ! 사 !

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
	//BitBlt(hdc,							// 복사 될 DC (새 도화지)
	//	0,								// 잘라올 X
	//	0,								// 잘라올 Y
	//	600,						// 복사 할 이미지의 width
	//	600,						// 복사 할 이미지의 height
	//	_playBuffer->GetMemDC(),		// 복사 한 이미지가 존재할 DC
	//	0,					// 복사 한 이미지의 left
	//	0,					// 복사 한 이미지의 top
	//	SRCCOPY);						// 복 ! 사 !
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
	// 조작 테스트
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