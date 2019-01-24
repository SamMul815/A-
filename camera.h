#pragma once
#include "singletonBase.h"
#define ZOOMSIZE 200
#define ZOOMFOCUSDC_X 200
#define ZOOMFOCUSDC_Y 150

class camera : public singletonBase <camera>
{
private:
	image*	_cameraBuffer;		// winsize 이미지
	image*	_playBuffer;		// 플레이 화면만 보여줄 이미지
	image*	_alphaImage;		// 알파블랜드 위한 이미지
	HDC*	_topDc;				// 최종적으로 더블버퍼링 될 DC

	POINT	_focus;				// 카메라 포커스
	POINT	_destFocus;			// 포커스 목표점

	RECT	_playRc;			// 플레이카메라 rc
	//RECT	_playRangeRc;		// 플레이카메라 범위 rc
	RECT	_cameraRc;			// 전체카메라 rect
	RECT	_cameraRangeRc;		// 카메라 이동 가능 범위
	RECT	_alphaRc;			// 알파블랜드 이미지의 렉트

	float	_cameraSpeed;		// 카메라 이동 속도   

	bool	_shakeCam;			// 카메라가 흔들리냐?
	float	_shakeStrength;		// 카메라 흔들림 강도
	int		_shakeCount;		// 흔들림을 위한 카운트

	bool	_fadeIn;			// 풰이드 인이냐~?
	bool	_fadeOut;			// 풰이드 아웃이냐~?
	int		_alphaValue_fadeIn;	// 페이드 인을 위한 알파블랜드 값
	int		_alphaValue_fadeOut;// 페이드 아웃을 위한 알파블랜드 값

	bool	_showDebugMode;		// 디버그모드냐~?

	wchar_t _systemMsg[128];

public:
	HRESULT Init(int focusX, int focusY);
	void Release();
	void Update();
	void Render(HDC hdc);
	void RenderPlayBuffer(HDC hdc);

	void Update(RECT rangeRc);				// 카메라의 이동범위를 받아 조정

	void MoveCamera();
	void CameraCorrection();
	void ShakeCamera();
	void ShakingCameraRectLeft();
	void ShakingCameraRectRight();

	//======= GET 함수 =======//

	image* GetPlayBuffer() { return _playBuffer; }
	RECT GetPlayRect() { return _playRc; }
	image* GetCameraBuffer() { return _cameraBuffer; }
	image* GetAlphaImage() { return _alphaImage; }
	RECT GetCameraRect() { return _cameraRc; }
	RECT GetCamRangeRc() { return _cameraRangeRc; }
	bool GetShowDebugMode() { return _showDebugMode; }
	HDC* GetTopDC() { return _topDc; }

	//======= SET 함수 =======//

	void SetCamRangeRc(int left, int top, int width, int height)
	{
		_cameraRangeRc = RectMake(left, top, width, height);
	}
	void SetTopDC(HDC* dc) { _topDc = dc; }

	void SetFadeIn(bool fadeIn) { _fadeIn = fadeIn; }
	void SetFadeOut(bool fadeOut) { _fadeOut = fadeOut; }
	void SetCameraFocus(int x, int y) { _focus = { x, y }; }
	void SetDestFocus(int x, int y) { _destFocus = { x, y }; }
	void SetShowDebugMode(bool showDebug) { _showDebugMode = showDebug; }

	//=======================//

	camera();
	~camera();
};

