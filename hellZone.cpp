#include "stdafx.h"
#include "hellZone.h"
#include "cAstar.h"

#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
hellZone::hellZone(){}
hellZone::~hellZone(){}


HRESULT hellZone::Init(void)
{
	gameNode::Init(true);
	
	m_pAstar = new cAstar;
	m_pAstar->Setup();

	return S_OK;
}

void hellZone::Release(void)
{
	gameNode::Release();
}

void hellZone::Update(void)
{
	gameNode::Update();
	m_pAstar->Update();
}

void hellZone::Render()
{
	HDC backDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);


	m_pAstar->Render(GetMemDC());

	//EllipseMakeCenter(GetMemDC(), 20, 20, 20, 20);
	//MoveToEx(GetMemDC(),0,0, NULL);
	//LineTo(	 GetMemDC(),10,10);

	//TIMEMANAGER->Render(GetMemDC());
	this->GetBackBuffer()->Render(GetHDC(), 0, 0);
}
