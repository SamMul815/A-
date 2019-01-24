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
	//���࿡ ����Ʈ �̹����� ������ ����
	if (!effectImage) return E_FAIL;

	//����Ʈ Ȱ��ȭ���� �ʱ�ȭ
	_isRunning = false;

	//����Ʈ �̹��� ����
	_effectImage = effectImage;

	//����Ʈ ��� �ð� ����
	_elapsedTime = elapsedTime;

	//animation�� ���ٸ� ���� ����
	if (!_effectAnimation) _effectAnimation = new animation;

	//�ִϸ��̼� ����
	_effectAnimation->Init(_effectImage->GetWidth(), _effectImage->GetHeight(), frameW, frameH);
	_effectAnimation->SetDefPlayFrame(false, false);
	_effectAnimation->SetFPS(fps);
	_effectAnimation->Stop();

	return S_OK;
}

HRESULT effect::Init(image * effectImage, int frameW, int frameH, int fps)
{
	//���࿡ ����Ʈ �̹����� ������ ����
	if (!effectImage) return E_FAIL;

	//����Ʈ Ȱ��ȭ���� �ʱ�ȭ
	_isRunning = false;

	//����Ʈ �̹��� ����
	_effectImage = effectImage;

	//animation�� ���ٸ� ���� ����
	if (!_effectAnimation) _effectAnimation = new animation;

	//�ִϸ��̼� ����
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
	//�ִϸ��̼��� Ȱ��ȭ ���� �ʾҴٸ�? ������� ����
	if (!_isRunning) return;
	_effectAnimation->FrameUpdate(_elapsedTime);

	//����Ʈ �ִϸ��̼��� ���ᰡ �Ǹ� ����
	if (!_effectAnimation->IsPlay()) KillEffect();
}

void effect::Update(float elapsedTime)
{
	//�ִϸ��̼��� Ȱ��ȭ ���� �ʾҴٸ�? ������� ����
	if (!_isRunning) return;
	_effectAnimation->FrameUpdate(elapsedTime);

	//����Ʈ �ִϸ��̼��� ���ᰡ �Ǹ� ����
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
	//�̹����� �ִϸ��̼� �� �� �ϳ��� ������ ������������
	if (!_effectImage || !_effectAnimation) return;

	//left top -> center��~
	_x = x - (_effectAnimation->GetFrameWidth() / 2);
	_y = y - (_effectAnimation->GetFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->Start();


}

void effect::KillEffect(void)
{
	_isRunning = false;
}
