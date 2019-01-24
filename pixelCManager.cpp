#include "stdafx.h"
#include "pixelCManager.h"


pixelCManager::pixelCManager()
{
}


pixelCManager::~pixelCManager()
{
}


HRESULT pixelCManager::Init(void)
{

	return S_OK;
}

void pixelCManager::Release(void)
{

}

image* pixelCManager::AddPixelCLayer(wstring strKey, COLORREF pixelColor)
{
	image* originImg = IMAGEMANAGER->FindImage(strKey);
	
	if (!originImg) return NULL;

	image* pixelCImg = FindPixelCLayer(strKey);

	if (pixelCImg) return pixelCImg;

	pixelCImg = new image;
	pixelCImg->Init(originImg->GetWidth(), originImg->GetHeight());

	for (int y = 0; y < pixelCImg->GetHeight(); y++)
	{
		for (int x = 0; x < pixelCImg->GetWidth(); x++)
		{
			if (GetPixel(originImg->GetMemDC(), x, y) != originImg->GetTransColor())
			{
				SetPixel(pixelCImg->GetMemDC(), x, y, pixelColor);
			}
		}
	}

	_mPixelCLayerList.insert(make_pair(strKey, pixelCImg));

	return pixelCImg;
}

image* pixelCManager::FindPixelCLayer(wstring strKey)
{
	mapPixelCLayerIter key = _mPixelCLayerList.find(strKey);

	//이미지가 있으면
	if (key != _mPixelCLayerList.end())
	{
		return key->second;
	}

	return NULL;
}

void pixelCManager::ErasePixel(wstring strKey, int x, int y, int width, int height, SHAPETYPE type)
{
	image* originImg = IMAGEMANAGER->FindImage(strKey);
	image* pixelLayer = FindPixelCLayer(strKey);

	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	RECT tempRc = RectMakeCenter(x, y, width, height);

	myBrush = CreateSolidBrush(originImg->GetTransColor());
	myPen = CreatePen(PS_SOLID, 1, originImg->GetTransColor());

	SelectObject(pixelLayer->GetMemDC(), myBrush);
	SelectObject(pixelLayer->GetMemDC(), myPen);
	SelectObject(originImg->GetMemDC(), myBrush);
	SelectObject(originImg->GetMemDC(), myPen);

	switch (type)
	{
	case RECTANGLE:
		Rectangle(pixelLayer->GetMemDC(), tempRc.left, tempRc.top, tempRc.right, tempRc.bottom);
		Rectangle(originImg->GetMemDC(), tempRc.left, tempRc.top, tempRc.right, tempRc.bottom);
		break;
	case CIRCLE:
		Ellipse(pixelLayer->GetMemDC(), tempRc.left, tempRc.top, tempRc.right, tempRc.bottom);
		Ellipse(originImg->GetMemDC(), tempRc.left, tempRc.top, tempRc.right, tempRc.bottom);
		break;
	}
}