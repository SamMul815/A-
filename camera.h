#pragma once
#include "singletonBase.h"
#define ZOOMSIZE 200
#define ZOOMFOCUSDC_X 200
#define ZOOMFOCUSDC_Y 150

class camera : public singletonBase <camera>
{
private:
	image*	_cameraBuffer;		// winsize �̹���
	image*	_playBuffer;		// �÷��� ȭ�鸸 ������ �̹���
	image*	_alphaImage;		// ���ĺ��� ���� �̹���
	HDC*	_topDc;				// ���������� ������۸� �� DC

	POINT	_focus;				// ī�޶� ��Ŀ��
	POINT	_destFocus;			// ��Ŀ�� ��ǥ��

	RECT	_playRc;			// �÷���ī�޶� rc
	//RECT	_playRangeRc;		// �÷���ī�޶� ���� rc
	RECT	_cameraRc;			// ��üī�޶� rect
	RECT	_cameraRangeRc;		// ī�޶� �̵� ���� ����
	RECT	_alphaRc;			// ���ĺ��� �̹����� ��Ʈ

	float	_cameraSpeed;		// ī�޶� �̵� �ӵ�   

	bool	_shakeCam;			// ī�޶� ��鸮��?
	float	_shakeStrength;		// ī�޶� ��鸲 ����
	int		_shakeCount;		// ��鸲�� ���� ī��Ʈ

	bool	_fadeIn;			// �R�̵� ���̳�~?
	bool	_fadeOut;			// �R�̵� �ƿ��̳�~?
	int		_alphaValue_fadeIn;	// ���̵� ���� ���� ���ĺ��� ��
	int		_alphaValue_fadeOut;// ���̵� �ƿ��� ���� ���ĺ��� ��

	bool	_showDebugMode;		// ����׸���~?

	wchar_t _systemMsg[128];

public:
	HRESULT Init(int focusX, int focusY);
	void Release();
	void Update();
	void Render(HDC hdc);
	void RenderPlayBuffer(HDC hdc);

	void Update(RECT rangeRc);				// ī�޶��� �̵������� �޾� ����

	void MoveCamera();
	void CameraCorrection();
	void ShakeCamera();
	void ShakingCameraRectLeft();
	void ShakingCameraRectRight();

	//======= GET �Լ� =======//

	image* GetPlayBuffer() { return _playBuffer; }
	RECT GetPlayRect() { return _playRc; }
	image* GetCameraBuffer() { return _cameraBuffer; }
	image* GetAlphaImage() { return _alphaImage; }
	RECT GetCameraRect() { return _cameraRc; }
	RECT GetCamRangeRc() { return _cameraRangeRc; }
	bool GetShowDebugMode() { return _showDebugMode; }
	HDC* GetTopDC() { return _topDc; }

	//======= SET �Լ� =======//

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

