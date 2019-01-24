#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<wstring, image*> mapImageList;
	typedef map<wstring, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	HRESULT Init(void);
	void Release(void);

	image* AddImage(wstring strKey, int width, int height);
	image* AddImage(wstring strKey, int width, int height,
		BOOL trans, COLORREF transColor, BOOL blend = FALSE, BOOL rotate = FALSE);


	image* AddImage(wstring strKey, LPCWSTR fileName, int width, int height, bool trans, COLORREF transColor, bool blend = false, bool rotate = false);
	image* AddImage(wstring strKey, const DWORD resID, int width, int height, bool trans, COLORREF transColor, bool blend = false, bool rotate = false);
	image* AddImage(wstring strKey, LPCWSTR fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, bool blend = false, bool rotate = false);

	//프레임 이미지 추가
	image* AddFrameImage(wstring strKey, LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool blend = false, bool rotate = false);
	image* AddFrameImage(wstring strKey, LPCWSTR fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool blend = false, bool rotate = false);

	//이미지 키 값으로 찾는 함수
	image* FindImage(wstring strKey);

	BOOL DeleteImage(wstring strKey);

	BOOL DeleteAll(void);

	//렌더 함수
	void Render(wstring strKey, HDC hdc);
	void Render(wstring strKey, HDC hdc, int destX, int destY);
	void Render(wstring strKey, HDC hdc, int destX, int destY, int width, int height);
	void Render(wstring strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int sourWidth, int sourHeight);

	//프레임 렌더는 니들이 구현해볼 것.
	void FrameRender(wstring strKey, HDC hdc, int destX, int destY);
	void FrameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);
	// 루프 렌더
	void LoopRender(wstring strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void AniRender(wstring strKey, HDC hdc, int destX, int destY, animation* ani);

	// 알파 렌더
	void AlphaRender(wstring strKey, HDC hdc, BYTE alpha);
	void AlphaRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(wstring strKey, HDC hdc, int destX, int destY, float resizeX, float resizeY, BYTE alpha);
	void AlphaRender(wstring strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	
	void FrameAlphaRender(wstring strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void FrameAlphaRender(wstring strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void AniAlphaRender(wstring strKey, HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	// Rotate Render
	void RotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle = 0.0f);
	void RotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle, BYTE alpha);

	void FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle = 0.0f);
	void FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, float angle, BYTE alpha);

	void FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle = 0.0f);
	void FrameRotateRender(wstring strKey,HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle, BYTE alpha);

	void FrameRotateRender(wstring strKey,HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle);
	void FrameRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle, BYTE alpha);


	void AniRotateRender(wstring strKey, HDC hdc, float centerX, float centerY, animation* ani, float angle = 0.0f);


	imageManager();
	~imageManager();
};

