#include "stdafx.h"
#include "cNode.h"


cNode::cNode():
	m_pMother(NULL),
	m_nX(0),
	m_nY(0),
	m_fF(0),
	m_fG(0),
	m_fH(0),
	open(true),
	m_eType(E_NOMAL)
{
}


cNode::~cNode()
{
}

void cNode::Render(HDC hdc)
{
	HBRUSH brush;
	HPEN pen;

	pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	//brush = CreateSolidBrush(RGB(255, 0, 0));

	switch (m_eType)
	{
	case E_NOMAL:
		brush = CreateSolidBrush(RGB(255, 255, 0));
		break;
	case E_START:
		brush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case E_END:
		brush = CreateSolidBrush(RGB(0, 0, 255));
		break;
	case E_BLOCK:
		brush = CreateSolidBrush(RGB(0, 0, 0));
		break;
	case E_ROAD:
		brush = CreateSolidBrush(RGB(255, 0, 255));
		break;
	default:
		break;
	}

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, m_nX, m_nY, m_nX + SIZE, m_nY + SIZE);

	if (m_pMother)
	{
		float motherX = m_pMother->GetX();
		float motherY = m_pMother->GetY();

		float x1, y1;
		float x2, y2;
		

		float angle = GetAngle(motherX , motherY, m_nX, m_nY);
		
		x1 = m_nX + SIZE / 2;
		y1 = m_nY + SIZE / 2;

		x2 = x1 - cos(angle) * 20;
		y2 = y1 - -sin(angle) * 20;

		EllipseMakeCenter(hdc, x1, y1, 10, 10);
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);

		
		SetBkMode(hdc, TRANSPARENT);
		
		WCHAR arr[128];
		swprintf(arr, L"%.1f", GetF());
		TextOut(hdc, m_nX + 1, m_nY + 1, arr,lstrlenW(arr));

		swprintf(arr, L"%.1f", m_fG);
		TextOut(hdc, m_nX + 1, m_nY + 35, arr, lstrlenW(arr));

		swprintf(arr, L"%.1f", m_fH);
		TextOut(hdc, m_nX + 28, m_nY + 35, arr, lstrlenW(arr));

		if (!open)
		{
			swprintf(arr, L"c");
			TextOut(hdc, m_nX + 38, m_nY + 1, arr, lstrlenW(arr));
		}
	}



	DeleteObject(pen);
	DeleteObject(brush);


}
