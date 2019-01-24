#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::Init(int x, int y, int width, int height, bool reverse)
{
	_x = x;
	_y = y;

	_rcProgress = RectMakeCenter(x, y, width, height);

	//���α׷��� �� �̹���
	_progressBarTop = IMAGEMANAGER->AddImage(L"topBar", L"./image/progressBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255), false);
	_progressBarBottom = IMAGEMANAGER->AddImage(L"backBar", L"./image/progressBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255), false);


	_currentWidth = _maxWidth = width;
	_height = height;
	_reverse = reverse;

	return S_OK;
}

HRESULT progressBar::Init(LPWSTR btnUpImageKeyName, LPWSTR btnDownImageKeyName,
	float x, float y, int width, int height, bool reverse)
{
	_x = x;
	_y = y;

	_rcProgress = RectMakeCenter(x, y, width, height);

	wchar_t strUpName[128];
	wchar_t strDownName[128];

	ZeroMemory(strUpName, sizeof(strUpName));
	ZeroMemory(strDownName, sizeof(strDownName));

	swprintf(strUpName, L"./image/%s.bmp", btnUpImageKeyName);
	swprintf(strDownName, L"./image/%s.bmp", btnDownImageKeyName);

	_progressBarBottom = IMAGEMANAGER->AddImage(btnDownImageKeyName, strDownName, x, y,
		width, height, true, RGB(255, 0, 255));
	_progressBarTop = IMAGEMANAGER->AddImage(btnUpImageKeyName, strUpName, x, y,
		width, height, true, RGB(255, 0, 255));

	_currentWidth = _maxWidth = width;
	_height = height;
	_reverse = reverse;

	//1. ���� == �����Ҵ��ؼ� ���α׷����� �̹��� ������ �ٷ� ����� �� �ְ� �����

	return S_OK;
}

void progressBar::Release(void)
{

}

void progressBar::Update(void)
{
	_rcProgress = RectMakeCenter(_x, _y, _maxWidth, _height);
}

void progressBar::Render(void)
{
	_progressBarBottom->Render(CAMERA->GetCameraBuffer()->GetMemDC(),
		_rcProgress.left, _rcProgress.top,
		0, 0,
		_maxWidth, _height);

	if (!_reverse)
	{
		_progressBarTop->Render(CAMERA->GetCameraBuffer()->GetMemDC(),
			_rcProgress.left, _rcProgress.top,
			0, 0,
			_currentWidth, _height);
	}
	else
	{
		_progressBarTop->Render(CAMERA->GetCameraBuffer()->GetMemDC(),
			_rcProgress.left + (_maxWidth - _currentWidth), _rcProgress.top,
			0, 0,
			_currentWidth, _height);
	}
}

void progressBar::SetGauge(float currentGauge, float maxGauge)
{
	_currentWidth = (currentGauge / maxGauge) * _maxWidth;
}
