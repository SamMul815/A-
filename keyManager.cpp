#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::Init(void)
{
	//처음에 모든 키는 하나도 안눌려진 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		this->GetKeyUp().set(i, false);
		this->GetKeyUp().set(i, false);
	}


	return S_OK;
}

void keyManager::Release(void)
{

}

bool keyManager::IsOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->GetKeyDown()[key])
		{
			this->SetKeyDown(key, true);
			return true;
		}
	}
	else this->SetKeyDown(key, false);

	return false;
}

bool keyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->SetKeyUp(key, true);
	else
	{
		if (this->GetKeyUp()[key])
		{
			this->SetKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool keyManager::IsToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
