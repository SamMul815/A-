#pragma once
#include "gameNode.h"
//�Լ������� ������
typedef void(*CALLBACK_FUNCTION)(void);

//�ݹ��Լ��� ���ε� �� ���Ͽ� �����Ͻÿ�

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;

	LPCWSTR _imageName;
	image* _image;
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;

public:
	HRESULT Init(LPCWSTR imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);

	void Release(void);
	void Update(void);
	void Render(void);

	button();
	~button();
};

