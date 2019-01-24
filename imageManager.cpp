#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::Init(void)
{
	return S_OK;
}

void imageManager::Release(void)
{
	DeleteAll();
}


image* imageManager::AddImage(wstring strKey, int width, int height)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	image* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new image;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
image* imageManager::AddImage(wstring strKey, int width, int height,
	BOOL trans, COLORREF transColor, BOOL blend, BOOL rotate)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	image* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new image;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(width, height, trans, transColor, blend, rotate)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::AddImage(wstring strKey, const DWORD resID, int width, int height, bool trans, COLORREF transColor, bool blend, bool rotate)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	image* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new image;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(resID, width, height, trans, transColor, blend, rotate)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::AddImage(wstring strKey, LPCWSTR fileName, int width, int height, bool trans, COLORREF transColor, bool blend, bool rotate)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	image* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new image;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(fileName, width, height, trans, transColor, blend, rotate)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::AddImage(wstring strKey, LPCWSTR fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, bool blend, bool rotate)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	image* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new image;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(fileName, x, y, width, height, trans, transColor, blend, rotate)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//������ �̹��� �߰�
image* imageManager::AddFrameImage(wstring strKey, LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool blend, bool rotate)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	image* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new image;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(fileName, x, y, width, height, frameX, frameY, trans, transColor, blend, rotate)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::AddFrameImage(wstring strKey, LPCWSTR fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool blend, bool rotate)
{
	//������ Ű ���� �ִ°�? ������ �װ� �׳� �������ش�
	image* img = FindImage(strKey);

	if (img) return img;

	//������� ������ �Դٸ� Ű ���� ����
	img = new image;

	//�̹��� �ʱ�ȭ�� �����ϸ� NULL������ �ʱ�ȭ
	if (FAILED(img->Init(fileName, width, height, frameX, frameY, trans, transColor, blend, rotate)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������� ������ �Դٸ� �ʱ�ȭ�� �� �� ��Ȳ
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//�̹��� Ű ������ ã�� �Լ�
image* imageManager::FindImage(wstring strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//�̹����� ������
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


BOOL imageManager::DeleteImage(wstring strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->Release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}


BOOL imageManager::DeleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return TRUE;
}


//���� �Լ�
void imageManager::Render(wstring strKey, HDC hdc)
{
	image* img = FindImage(strKey);

	if (img) img->Render(hdc);
}

void imageManager::Render(wstring strKey, HDC hdc, int destX, int destY)
{
	image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY);
}
void imageManager::Render(wstring strKey, HDC hdc, int destX, int destY, int width, int height)
{
	image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY, width, height);
}
void imageManager::Render(wstring strKey, HDC hdc, int destX, int destY,
	int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);

}


void imageManager::FrameRender(wstring strKey, HDC hdc, int destX, int destY)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRender(hdc, destX, destY);
}

void imageManager::FrameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::FrameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY, width, height);
}

void imageManager::LoopRender(wstring strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = FindImage(strKey);

	if (img) img->LoopRender(hdc, drawArea, offSetX, offSetY);
}

void imageManager::AniRender(wstring strKey, HDC hdc, int destX, int destY, animation* ani)
{
	image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight());
}

//���� ����
void imageManager::AlphaRender(wstring strKey, HDC hdc, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, alpha);
}

void imageManager::AlphaRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, destX, destY, alpha);
}
void imageManager::AlphaRender(wstring strKey, HDC hdc, int destX, int destY, float resizeX, float resizeY, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, destX, destY, resizeX, resizeY, alpha);
}
void imageManager::AlphaRender(wstring strKey, HDC hdc, int destX, int destY,
	int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::FrameAlphaRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->FrameAlphaRender(hdc, destX, destY, alpha);
}

void imageManager::FrameAlphaRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->FrameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void imageManager::AniAlphaRender(wstring strKey, HDC hdc, int destX, int destY, animation * ani, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight(), alpha);
}


void imageManager::RotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle)
{
	image* img = FindImage(strKey);

	if (img) img->RotateRender(hdc, centerX, centerY, angle);
}
void imageManager::RotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->RotateRender(hdc, centerX, centerY, angle, alpha);
}
void imageManager::FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle)									  
{
	image* img = FindImage(strKey);

	if (img) img->FrameRotateRender(hdc, centerX, centerY, angle);
}
void imageManager::FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRotateRender(hdc, centerX, centerY, angle, alpha);
}
void imageManager::FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRotateRender(hdc, centerX, centerY, currentFrameX, currentFrameY, angle);
}
void imageManager::FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRotateRender(hdc, centerX, centerY, currentFrameX, currentFrameY, angle, alpha);
}
void imageManager::FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRotateRender(hdc, centerX, centerY, currentFrameX, currentFrameY, resizeX, resizeY, angle);
}
void imageManager::FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle, BYTE alpha)
{
	image* img = FindImage(strKey);

	if (img) img->FrameRotateRender(hdc, centerX, centerY, currentFrameX, currentFrameY, resizeX, resizeY, angle, alpha);
}
void imageManager::AniRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, animation* ani, float angle)						  
{
	image* img = FindImage(strKey);

	if (img) img->AniRotateRender(hdc, centerX, centerY, ani, angle);
}