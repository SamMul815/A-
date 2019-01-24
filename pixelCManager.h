#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

enum SHAPETYPE
{
	RECTANGLE,
	CIRCLE
};

class pixelCManager : public singletonBase<pixelCManager>
{
private:
	typedef map<wstring, image*> mapPixelCLayerList;
	typedef map<wstring, image*>::iterator mapPixelCLayerIter;
	
private:
	mapPixelCLayerList _mPixelCLayerList;

public:
	HRESULT Init(void);
	void Release(void);

	image* AddPixelCLayer(wstring strKey, COLORREF pixelColor);
	image* FindPixelCLayer(wstring strKey);

	void ErasePixel(wstring strKey, int x, int y, int width, int height, SHAPETYPE type);

	pixelCManager();
	~pixelCManager();
};
