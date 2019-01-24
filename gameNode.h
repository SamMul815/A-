#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->AddImage(L"backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

	bool _isSceneInit;			// SceneManager에서 init을 했는가 안했는가
public:
	//HRESULT  마소가 만든건데
	//성공, 실패 등등 출력란에 알려줌

	virtual HRESULT Init(void);		//초기화 함수
	virtual HRESULT Init(bool managerInit);
	virtual void Release(void);		//메모리 해제 함수
	virtual void Update(void);		//연산 함수
	virtual void Render(void);	//그리기 함수
	
	image* GetBackBuffer(void) { return _backBuffer; }

	HDC GetMemDC() { return _backBuffer->GetMemDC(); }
	HDC GetHDC() { return _hdc; }
	HDC* GetTopHDC() { return &_hdc; }
	bool GetIsSceneInit() { return _isSceneInit; }

	void SetIsSceneInit(bool is) { _isSceneInit = is; }
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


	gameNode();
	virtual ~gameNode();
};

