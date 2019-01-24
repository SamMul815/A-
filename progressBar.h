#pragma once
#include "gameNode.h"

/*
===================== ���α׷��� �� ======================

���� Ŭ�������ο��� RectMake�� RectMakeCenter�� ȥ���ϼ̱⿡
RectMakeCenter�� �����Ͽ����� ���� _x, _y ������
��Ʈ�� �߽����� �ǹ��մϴ�.

_width���� ��� _currentWidth�� ����ϸ�, _maxWidth������ �߰��߽��ϴ�.
���� topbar�� ���̴� _currentWidth�� ���� ���� �����˴ϴ�.

_reverse ������ �߰��Ǿ����ϴ�. Init�Լ��� �Ű������� ���� �� ������
����Ʈ ���� false�Դϴ�. ���� true�� ��� �����ʿ��� �������� �������ϴ�.

=========================================================
*/

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _currentWidth, _maxWidth, _height;
	bool _reverse; // �������� ���������� ����

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	HRESULT Init(int x, int y, int width, int height, bool reverse = false);
	HRESULT Init(LPWSTR btnUpImageKeyName, LPWSTR btnDownImageKeyName,
		float x, float y, int width, int height, bool reverse = false);
	void Release(void);
	void Update(void);
	void Render(void);

	inline RECT GetRect() { return _rcProgress; }
	void SetGauge(float currentGauge, float maxGauge);

	//���α׷��� �� ��ǥ ���� �Ծ�
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }


	progressBar();
	~progressBar();
};

