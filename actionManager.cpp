#include "stdafx.h"
#include "actionManager.h"
#include "action.h"

actionManager::actionManager()
{
}


actionManager::~actionManager()
{

}

HRESULT actionManager::Init(void)
{

	return S_OK;
}

void actionManager::Release(void)
{
	for (_viAction = _vAction.begin(); _viAction != _vAction.end(); )
	{
		if (_vAction.size() != 0)
		{
			SAFE_DELETE(*_viAction);
			_viAction = _vAction.erase(_viAction);
		}
		else ++_viAction;
	}

	_vAction.clear();
}

void actionManager::Update(void)
{
	for (int i = 0; i < _vAction.size(); i++)
	{
		_vAction[i]->Update();
		if (!_vAction[i]->GetIsMoving())
		{
			SAFE_DELETE(_vAction[i]);
			_vAction.erase(_vAction.begin() + i);
			break;
		}
	}
}

void actionManager::Render(void)
{

}

void actionManager::MoveTo(image* image, float endX, float endY, float time)
{
	action* moveAction;
	moveAction = new action;
	moveAction->Init();
	moveAction->MoveTo(image, endX, endY, time);
	_vAction.push_back(moveAction);
}
void actionManager::MoveTo(image* image, float endX, float endY, float time, void* cbFunction)
{
	action* moveAction;
	moveAction = new action;
	moveAction->Init();
	moveAction->MoveTo(image, endX, endY, time, (CALLBACK_FUNCTION)cbFunction);
	_vAction.push_back(moveAction);
}