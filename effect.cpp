#include "stdafx.h"
#include "effect.h"
#include "animation.h"


effect::effect()
	: _effectImage(NULL),
	_effectAnimation(NULL),
	_isRunning(false),
	_x(0),
	_y(0)
{
}


effect::~effect()
{
}

HRESULT effect::Init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	//만약에 이펙트 이미지가 없으면 리턴
	if (!effectImage) return E_FAIL;

	//이펙트 활성화여부 초기화
	_isRunning = false;

	//이펙트 이미지 대입
	_effectImage = effectImage;

	//이펙트 경과 시간 셋팅
	_elapsedTime = elapsedTime;

	//animation이 없다면 새로 생성
	if (!_effectAnimation) _effectAnimation = new animation;

	//애니메이션 셋팅
	_effectAnimation->Init(_effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH);
	_effectAnimation->SetDefPlayFrame(false, false);
	_effectAnimation->SetFPS(fps);
	_effectAnimation->Stop();

	return S_OK;
}

HRESULT effect::Init(image * effectImage, int frameW, int frameH, int fps)
{
	//만약에 이펙트 이미지가 없으면 리턴
	if (!effectImage) return E_FAIL;

	//이펙트 활성화여부 초기화
	_isRunning = false;

	//이펙트 이미지 대입
	_effectImage = effectImage;

	//animation이 없다면 새로 생성
	if (!_effectAnimation) _effectAnimation = new animation;

	//애니메이션 셋팅
	_effectAnimation->Init(_effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH);
	_effectAnimation->SetDefPlayFrame(false, false);
	_effectAnimation->SetFPS(fps);
	_effectAnimation->Stop();

	return S_OK;
}

void effect::Release(void)
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::Update(void)
{
	//애니메이션이 활성화 되지 않았다면? 재생하지 마라
	if (!_isRunning) return;
	_effectAnimation->FrameUpdate(_elapsedTime);

	//이펙트 애니메이션이 종료가 되면 꺼라
	if (!_effectAnimation->IsPlay()) KillEffect();
}

void effect::Update(float elapsedTime)
{
	//애니메이션이 활성화 되지 않았다면? 재생하지 마라
	if (!_isRunning) return;
	_effectAnimation->FrameUpdate(elapsedTime);

	//이펙트 애니메이션이 종료가 되면 꺼라
	if (!_effectAnimation->IsPlay()) KillEffect();
}

void effect::Render(HDC hdc)
{
	if (!_isRunning) return;

	_effectImage->AniRender(hdc, _x, _y, _effectAnimation);
}

void effect::Render(HDC hdc, RECT cameraRc)
{
	if (!_isRunning) return;

	RECT temp;
	RECT tempEffect = RectMakeCenter(_x, _y, _effectImage->GetFrameWidth(), _effectImage->GetFrameHeight());

	//if (IntersectRect(&temp, &tempEffect, &cameraRc))
	//{
		_effectImage->AniRender(hdc, _x - cameraRc.left, _y - cameraRc.top, _effectAnimation);
	//}
}

void effect::StartEffect(int x, int y)
{
	//이미지나 애니메이션 둘 중 하나라도 없으면 실행하지마라
	if (!_effectImage || !_effectAnimation) return;

	//left top -> center로~
	_x = x - (_effectAnimation->GetFrameWidth() / 2);
	_y = y - (_effectAnimation->GetFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->Start();


}

void effect::KillEffect(void)
{
	_isRunning = false;
}
