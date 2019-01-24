#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->AddImage(L"backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

	bool _isSceneInit;			// SceneManager���� init�� �ߴ°� ���ߴ°�
public:
	//HRESULT  ���Ұ� ����ǵ�
	//����, ���� ��� ��¶��� �˷���

	virtual HRESULT Init(void);		//�ʱ�ȭ �Լ�
	virtual HRESULT Init(bool managerInit);
	virtual void Release(void);		//�޸� ���� �Լ�
	virtual void Update(void);		//���� �Լ�
	virtual void Render(void);	//�׸��� �Լ�
	
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

