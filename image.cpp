#include "stdafx.h"
#include "image.h"
//8��Ʈ? 16��Ʈ? 24��Ʈ? 32��Ʈ?
#pragma comment (lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

//�� ��Ʈ�� �̹��� ���� ����� ���
HRESULT image::Init(int width, int height)
{

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//����Į�� �ʱ�ȭ
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���� �ʱ�ȭ
	_blend = FALSE;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (_blend)
	{

		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	_rotate = FALSE;

	if (_rotate)
	{
		int size;
		(width > height ? size = width : size = height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::Init(int width, int height,
	BOOL trans, COLORREF transColor, BOOL blend, BOOL rotate)
{

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���� �ʱ�ȭ
	_blend = blend;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (_blend)
	{

		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	_rotate = rotate;

	if (_rotate)
	{
		int size;
		(width > height ? size = width : size = height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


//���ҽ����� �о�ͼ� ����� ���
HRESULT image::Init(const DWORD resID, int width, int height,
	BOOL trans, COLORREF transColor, BOOL blend, BOOL rotate)
{
	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���� �ʱ�ȭ
	_blend = blend;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (_blend)
	{
		int size;
		(width > height ? size = width : size = height);
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = size;
		_blendImage->height = size;
	}

	_rotate = rotate;

	if (_rotate)
	{
		int size;
		(width > height ? size = width : size = height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//���Ϸκ��� �о�ͼ� ����� ���
HRESULT image::Init(LPCWSTR fileName, int width, int height,
	BOOL trans, COLORREF transColor, BOOL blend, BOOL rotate)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���ϰ�� �̸� �����ؼ� ������
	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���� �ʱ�ȭ
	_blend = blend;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (_blend)
	{
		int size;
		(width > height ? size = width : size = height);
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = size;
		_blendImage->height = size;
	}

	_rotate = rotate;

	if (_rotate)
	{
		int size;
		(width > height ? size = width : size = height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::Init(LPCWSTR fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor, BOOL blend, BOOL rotate)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���ϰ�� �̸� �����ؼ� ������
	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���� �ʱ�ȭ
	_blend = blend;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (_blend)
	{
		int size;
		(width > height ? size = width : size = height);
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = size;
		_blendImage->height = size;
	}

	_rotate = rotate;

	if (_rotate)
	{
		int size;
		(width > height ? size = width : size = height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

// ������ �̹���
HRESULT image::Init(LPCWSTR fileName, int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor, BOOL blend, BOOL rotate)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���ϰ�� �̸� �����ؼ� ������
	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���� �ʱ�ȭ
	_blend = blend;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (_blend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
	}

	_rotate = rotate;

	if (_rotate)
	{
		int size;
		(_imageInfo->frameWidth > _imageInfo->frameHeight ? size = _imageInfo->frameWidth : size = _imageInfo->frameHeight);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
		
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::Init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY,
	BOOL trans, COLORREF transColor, BOOL blend, BOOL rotate)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) Release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//���ϰ�� �̸� �����ؼ� ������
	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	//����Į�� �ʱ�ȭ
	_trans = trans;
	_transColor = transColor;

	//���� �ʱ�ȭ
	_blend = blend;

	if (_imageInfo->hBit == 0)
	{
		Release();

		return E_FAIL;
	}

	if (_blend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
	}

	_rotate = rotate;

	if (_rotate)
	{
		int size;
		(_imageInfo->frameWidth > _imageInfo->frameHeight ? size = _imageInfo->frameWidth : size = _imageInfo->frameHeight);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->resID = 0;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::Release(void)
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//�����͵� ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//���� �ʱ�ȭ
		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		//�̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//�����͵� ����
		SAFE_DELETE(_blendImage);

		// ���� �ʱ�ȭ
		_blend = false;
	}
}

void image::SetTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::Render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			_imageInfo->x,				//����� ��ǥ ������ X
			_imageInfo->y,				//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			0, 0,				//����� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//			HDC		�ѷ��� ��ǥX, �ѷ��� ��ǥY
void image::Render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ũ�� width
			_imageInfo->height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			0, 0,				//����� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::Render(HDC hdc, int destX, int destY, int width, int height)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			width,	//����� ũ�� width
			height,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			0, 0,				//����� ��������
			_imageInfo->width,	//����� �������� width
			_imageInfo->height,	//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		// ��� ũ�⸦ �����Ͽ� ����
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, destX, destY,
			width, height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY);
	}
}

void image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			sourWidth,			//����� ũ�� width
			sourHeight,			//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			sourX, sourY,		//����� ��������
			sourWidth,			//����� �������� width
			sourHeight,			//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}


void image::FrameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->frameWidth,	//����� ũ�� width
			_imageInfo->frameHeight,	//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,				//����� ��������
			_imageInfo->frameWidth,	//����� �������� width
			_imageInfo->frameHeight,	//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->frameWidth,			//����� ũ�� width
			_imageInfo->frameHeight,			//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,		//����� ��������
			_imageInfo->frameWidth,			//����� �������� width
			_imageInfo->frameHeight,			//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,	//����� ��� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			width,			//����� ũ�� width
			height,			//����� ũ�� height
			_imageInfo->hMemDC,	//������ DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,		//����� ��������
			_imageInfo->frameWidth,			//����� �������� width
			_imageInfo->frameHeight,			//����� �������� height
			_transColor);		//���翡�� ���ܵ� ����
	}
	else
	{
		//DC �������� ��Ӻ��� ���
		BitBlt(hdc, destX, destY,
			width,
			height,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::LoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���) ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� ����
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�̹����� ���� ���
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ ��ο� ����(�׷��ִ� ����) ������ ������!
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �κ��� �ٽ� �׷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//x������!
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			Render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}


	}
}

void image::AniRender(HDC hdc, int destX, int destY, animation* ani)
{
	Render(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight());
}

void image::AlphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc,
			(int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}
void image::AlphaRender(HDC hdc, int destX, int destY, float resizeX, float resizeY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			resizeX,
			resizeY,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			resizeX, resizeY,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}
void image::AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_blendImage->hMemDC,
			0, 0,
			sourWidth,
			sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight, _blendFunc);
	}
}

void image::FrameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::FrameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;


	if (_trans)
	{
		BitBlt(_blendImage->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::AniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha)
{
	AlphaRender(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight(), alpha);
}

void image::RotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2)*(_imageInfo->width / 2) + (_imageInfo->height / 2)*(_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	if (_trans)
	{
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::RotateRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2)*(_imageInfo->width / 2) + (_imageInfo->height / 2)*(_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}

	if (_trans)
	{
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
			
		AlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height, _blendFunc);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}
void image::FrameRotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2)*(_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2)*(_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	if (_trans)
	{

		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->frameWidth, _rotateImage->frameHeight,
			hdc,
			0, 0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

	
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::FrameRotateRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2)*(_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2)*(_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	if (_trans)
	{

		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		AlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height, _blendFunc);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2)*(_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2)*(_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	
	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	if (_trans)
	{
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->frameWidth, _rotateImage->frameHeight,
			hdc,
			0,0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0,0,0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		
		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2)*(_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2)*(_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	if (_trans)
	{
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		AlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height, _blendFunc);


	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

void image::FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((resizeX / 2)*(resizeX / 2) + (resizeY / 2)*(resizeY / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)resizeY / 2) / ((float)resizeX / 2));
	baseAngle[1] = atanf(((float)resizeY / 2) / ((float)resizeX / 2));
	baseAngle[2] = PI + atanf(((float)resizeY / 2) / ((float)resizeX / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	if (_trans)
	{
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}
void image::FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	POINT rPoint[3];
	int dist = sqrt((resizeX / 2)*(resizeX / 2) + (resizeY / 2)*(resizeY / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)resizeY / 2) / ((float)resizeX / 2));
	baseAngle[1] = atanf(((float)resizeY / 2) / ((float)resizeX / 2));
	baseAngle[2] = PI + atanf(((float)resizeY / 2) / ((float)resizeX / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	if (_trans)
	{
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);
		BitBlt(_blendImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2, SRCCOPY);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
		AlphaBlend(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_blendImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height, _blendFunc);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}
void image::AniRotateRender(HDC hdc, float centerX, float centerY, animation * ani, float angle)
{
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2)*(_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2)*(_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));


	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle)*dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)*dist);
	}
	if (_trans)
	{
		// ���� ������ ä���
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc,
			0, 0, BLACKNESS);

		// �������� 1,1 ���� ������ ���� �귯����(transColor)���� ä���
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 0, 0, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);


		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			ani->GetFramePos().x, ani->GetFramePos().y,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);

	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			ani->GetFramePos().x, ani->GetFramePos().y,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}
