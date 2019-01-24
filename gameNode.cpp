#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
	: _isSceneInit(false)
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::Init(void)
{
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::Init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{

		KEYMANAGER->Init();
		IMAGEMANAGER->Init();
		SOUNDMANAGER->Init();
		TIMEMANAGER->Init();
		PIXELCMANAGER->Init();
		EFFECTMANAGER->Init();
		SCENEMANAGER->Init();
		ACTIONMANAGER->Init();
		TXTDATA->Init();
		CAMERA->Init(WINSIZEX / 2, WINSIZEY / 2);
//		DATABASE->Init();
	}

	return S_OK;
}

void gameNode::Release(void)
{
	if (_managerInit)
	{
		KEYMANAGER->ReleaseSingleton();
		IMAGEMANAGER->ReleaseSingleton();
		SOUNDMANAGER->ReleaseSingleton();
		TIMEMANAGER->ReleaseSingleton();
		PIXELCMANAGER->ReleaseSingleton();
		EFFECTMANAGER->ReleaseSingleton();
		SCENEMANAGER->ReleaseSingleton();
		ACTIONMANAGER->ReleaseSingleton();
		TXTDATA->ReleaseSingleton();
		CAMERA->ReleaseSingleton();
	//	DATABASE->ReleaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::Update(void)
{


}

void gameNode::Render(void)
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;


	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);

	case WM_MOUSEWHEEL:
		_ptMouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}