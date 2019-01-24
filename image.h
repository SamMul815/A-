#pragma once
#include "animation.h"
//========================================================
// 2015. 12. 04 ## image Class ## - Tango Team -
//========================================================
#define MAGENTA RGB(255, 0 , 255)
#define CYAN RGB(0, 255, 255)
#define SKYBLUE RGB(0, 172, 255)
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	//리소스 파일로부터 pk3. pak
		LOAD_FILE,		//파일로부터
		LOAD_EMPTY,		//빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;
		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		BYTE loadType;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
		//같은 구조체지만 IMAGE_INFO, 그 구조체 변수에 접근하기 위한 포인터 LPIMAGE_INFO
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 구조체
	TCHAR*			_fileName;		//뽜일 이름
	BOOL			_trans;			//특정 픽셀값을 날릴꺼니?
	COLORREF		_transColor;	//날릴꺼면 뭘날릴래?

	BOOL			_blend;
	BLENDFUNCTION	_blendFunc;		//알파블렌드를 사용하기 위한 정보
	LPIMAGE_INFO	_blendImage;	//알파블렌드를 사용하기 위한 이미지 정보
	BOOL			_rotate;
	LPIMAGE_INFO	_rotateImage;

public:
	image();
	~image();

	//빈 비트맵 이미지 만들어서 사용할 경우
	HRESULT Init(int width, int height);
	HRESULT Init(int width, int height,
		BOOL trans, COLORREF transColor, BOOL blend = FALSE, BOOL rotate = FALSE);
	
	//리소스부터 읽어와서 사용할 경우
	HRESULT Init(const DWORD resID, int width, int height,
		BOOL trans, COLORREF transColor , BOOL blend , BOOL rotat);

	//파일로부터 읽어와서 사용할 경우
	HRESULT Init(LPCWSTR fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE, BOOL rotate = FALSE);

	HRESULT Init(LPCWSTR fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE, BOOL rotate = FALSE);

	// 프레임단위로 움직일 이미지일 경우
	HRESULT Init(LPCWSTR fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE, BOOL rotate = FALSE);

	HRESULT Init(LPCWSTR fileName, float x, float y, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE, BOOL rotate = FALSE);

	void Release(void);

	void SetTransColor(BOOL trans, COLORREF transColor);

	void Render(HDC hdc);

	//			HDC		뿌려줄 좌표X, 뿌려줄 좌표Y
	void Render(HDC hdc, int destX, int destY);

	void Render(HDC hdc, int destX, int destY, int width, int height);

	//			HDC		뿌려줄 좌표X  뿌려줄 좌표Y 가져올 X   가져올 Y	 가져올 그림width, 가져올 그림 height
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void FrameRender(HDC hdc, int destX, int destY);

	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int width, int height);

	void LoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//애니메이션 렌더
	void AniRender(HDC hdc, int destX, int destY, animation* ani);

	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, float resizeX, float resizeY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void FrameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void FrameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void AniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	void RotateRender(HDC hdc, float centerX, float centerY, float angle);
	void RotateRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha);

	void FrameRotateRender(HDC hdc, float centerX, float centerY, float angle);
	void FrameRotateRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle);
	void FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle, BYTE alpha);
	void FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle);
	void FrameRotateRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float resizeX, float resizeY, float angle, BYTE alpha);

	void AniRotateRender(HDC hdc, float centerX, float centerY, animation* ani, float angle);

	inline HDC GetMemDC(void) { return _imageInfo->hMemDC; }

	//=============================
	// 이미지 관련 Getter, Setter //
	//=============================

	inline COLORREF GetTransColor() { return _transColor; }

	inline void SetX(float x) { _imageInfo->x = x; }
	inline float GetX() { return _imageInfo->x; }

	inline void SetY(float y) { _imageInfo->y = y; }
	inline float GetY() { return _imageInfo->y; }

	//이미지 중점좌표
	inline void SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//중점 X
	inline float GetCenterX(void)
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	//중점 Y
	inline float GetCenterY(void)
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	//가로 해상도
	inline int GetWidth(void) { return _imageInfo->width; }

	//세로 해상도
	inline int GetHeight(void) { return _imageInfo->height; }

	//프레임 관련 
	inline void SetCurrentFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void SetCurrentFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY(void) { return _imageInfo->maxFrameY; }
			   
	inline int GetCurrentFrameX(void) { return _imageInfo->currentFrameX; }
	inline int GetCurrentFrameY(void) { return _imageInfo->currentFrameY; }
			   
	inline int GetFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int GetFrameHeight(void) { return _imageInfo->frameHeight; }

};

