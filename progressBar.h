#pragma once
#include "gameNode.h"

/*
===================== 프로그레스 바 ======================

쌤이 클래스내부에서 RectMake와 RectMakeCenter를 혼용하셨기에
RectMakeCenter로 통일하였으며 따라서 _x, _y 변수는
렉트의 중심점을 의미합니다.

_width변수 대신 _currentWidth를 사용하며, _maxWidth변수를 추가했습니다.
따라서 topbar의 길이는 _currentWidth의 값에 따라 조정됩니다.

_reverse 변수가 추가되었습니다. Init함수에 매개변수로 받을 수 있으며
디폴트 값은 false입니다. 값이 true일 경우 오른쪽에서 왼쪽으로 차오릅니다.

=========================================================
*/

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _currentWidth, _maxWidth, _height;
	bool _reverse; // 기준점을 오른쪽으로 삼음

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

	//프로그레스 바 좌표 조종 함쑤
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }


	progressBar();
	~progressBar();
};

