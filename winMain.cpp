//������� ���
#include "stdafx.h"
#include "hellZone.h"

//��������
HINSTANCE _hInstance;
HWND _hWnd;

LPTSTR _lpszClass = TEXT("Tango API");

POINT _ptMouse;
long  _ptMouseWheel;

hellZone _hz;

//�Լ� ������Ÿ��(����)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//�޴� �̸�	
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ������~

	//������ ���� ���
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 800;
	dm.dmPelsHeight = 600;
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//���� �ػ󵵷�!
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//������ â ����
	_hWnd = CreateWindow(
		WINNAME,						//������ Ŭ���� �̸�
		WINNAME,						//������ Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�
		WS_POPUPWINDOW | WS_MAXIMIZE,	//������ ������
		WINSTARTX,						//������ â ���� X��ǥ
		WINSTARTY,						//������ â ���� Y��ǥ
		GetSystemMetrics(SM_CXSCREEN),	//������ â ����ũ��
		GetSystemMetrics(SM_CYSCREEN),	//������ â ����ũ��
		NULL,							//�θ� ������ ����
		(HMENU)NULL,					//�޴� �ڵ�
		hInstance,						//�ν��Ͻ� ������ ����
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, GetSystemMetrics(SM_CXSCREEN),	//������ â ����ũ��
		GetSystemMetrics(SM_CYSCREEN));
#else
	//������ â ����
	_hWnd = CreateWindow(
		WINNAME,			//������ Ŭ���� �̸�
		WINNAME,			//������ Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW,//������ ������
		WINSTARTX,			//������ â ���� X��ǥ
		WINSTARTY,			//������ â ���� Y��ǥ
		WINSIZEX,			//������ â ����ũ��
		WINSIZEY,			//������ â ����ũ��
		NULL,				//�θ� ������ ����
		(HMENU)NULL,		//�޴� �ڵ�
		hInstance,			//�ν��Ͻ� ������ ����
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#endif

	//������ â�� ������ ���Բ� ��Ÿ���ش�
	ShowWindow(_hWnd, cmdShow);

	if (FAILED(_hz.Init()))
	{
		//���� ���н� �ΰ��ְ� ����

		return 0;
	}

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->Update(60.0f);
			_hz.Update();
			_hz.Render();
		}
	}

	

	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//Ű���� �Է� �޽��� ó�� ���
		DispatchMessage(&message);	//������ ������� �޽��� ����
	}*/

	//�޽��� �� ��������
	_hz.Release();

	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _hz.MainProc(hWnd, iMessage, wParam, lParam);
}

//===============================================
// - 2015. 11. 17 ## Ŭ���̾�Ʈ ���� ������ ##
//===============================================

void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//���۾� ������ ������ �۾� �������� ũ�⸸ ������
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);


}