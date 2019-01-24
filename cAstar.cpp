#include "stdafx.h"
#include "cAstar.h"
#include "cNode.h"

cAstar::cAstar():
	m_StartNode(NULL),
	m_EndNode(NULL)
{
}


cAstar::~cAstar()
{
}

void cAstar::Setup()
{
	for (int i = 0; i < 16 * 16; i++)
	{
		cNode* node;
		node = new cNode;
		node->SetXY(i % 16 * SIZE, i / 16 * SIZE);
		m_vecNode.push_back(node);
	}

	/*
	for (int i = 0; i < 16 * 16; i++)
	{
		int originalX = i % 16;
		int originalY = i / 16;
		
		int x;
		int y;

		x = originalX - 1; 
		y = originalY - 1;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}

		x = originalX + 0;
		y = originalY - 1;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}

		x = originalX + 1;
		y = originalY - 1;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}

		x = originalX - 1;
		y = originalY + 0;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}

		x = originalX + 1;
		y = originalY + 0;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}

		x = originalX - 1;
		y = originalY + 1;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}

		x = originalX + 0;
		y = originalY + 1;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}

		x = originalX + 1;
		y = originalY + 1;
		if (x >= 0 && y >= 0 && x <= 15 && y <= 15)
		{
			m_vecNode[i]->PushEdge(m_vecNode[y * 16 + x]);
		}
	}
	*/
}

void cAstar::Update()
{
	if (KEYMANAGER->IsStayKeyDown(VK_MBUTTON))
	{
		int x = _ptMouse.x / SIZE;
		int y = _ptMouse.y / SIZE;


		m_vecNode[y * 16 + x]->SetType(E_BLOCK);
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
	{
		int x = _ptMouse.x / SIZE;
		int y = _ptMouse.y / SIZE;

		if (m_StartNode)
			m_StartNode->SetType(E_NOMAL);


		m_StartNode = m_vecNode[y * 16 + x];
		m_vecNode[y * 16 + x]->SetType(E_START);
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RBUTTON))
	{
		int x = _ptMouse.x / SIZE;
		int y = _ptMouse.y / SIZE;


		if (m_EndNode)
			m_EndNode->SetType(E_NOMAL);

		m_EndNode = m_vecNode[y * 16 + x];
		m_vecNode[y * 16 + x]->SetType(E_END);
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
	{
		for (int i = 0; i < 16 * 16; i++)
		{
			m_vecNode[i]->SetMother(NULL);
			m_vecNode[i]->GetEdge().clear();
			m_vecNode[i]->SetG(0);
			m_vecNode[i]->SetH(0);
			m_vecNode[i]->Open();
			m_vecOpenList.clear();
	
		}
		for (int i = 0; i < 16 * 16; i++)
		{
			int originalX = i % 16;
			int originalY = i / 16;
			int orignalN = originalY * 16 + originalX;
			for (int j = 0; j < 9; j++)
			{
				int x = originalX + (j % 3) - 1;
				int y = originalY + (j / 3) - 1;
				int n = y * 16 + x;

			if(originalX -1 >= 0) if (m_vecNode[orignalN - 1]->GetType() == E_BLOCK && j == 0) continue;
			if(originalX -1 >= 0) if (m_vecNode[orignalN - 1]->GetType() == E_BLOCK && j == 6) continue;

			if(originalX + 1 <= 15)	if (m_vecNode[orignalN + 1]->GetType() == E_BLOCK && j == 2) continue;
			if(originalX + 1 <= 15)	if (m_vecNode[orignalN + 1]->GetType() == E_BLOCK && j == 8) continue;


			if(originalY - 1 >= 0)	if (m_vecNode[orignalN - 16]->GetType() == E_BLOCK && j == 0) continue;
			if(originalY - 1 >= 0) if (m_vecNode[orignalN - 16]->GetType() == E_BLOCK && j == 2) continue;

			if(originalY + 1 <= 15)	if (m_vecNode[orignalN + 16]->GetType() == E_BLOCK && j == 6) continue;
			if(originalY + 1 <= 15)	if (m_vecNode[orignalN + 16]->GetType() == E_BLOCK && j == 8) continue;


				if (x >= 0 && y >= 0 && x <= 15 && y <= 15 && j != 4)
				{
					if(m_vecNode[n]->GetType() != E_BLOCK)
						m_vecNode[orignalN]->PushEdge(m_vecNode[n]);
				}

			}
		}
		Find();
	}
	if (KEYMANAGER->IsOnceKeyDown('A'))
	{
		ifstream inFile;
		inFile.open("data.txt");
		int i = 0;
		while (!inFile.eof())
		{
			char a;
			inFile.get(a);
			switch (a)
			{
			case 'e':
				m_vecNode[i]->SetType(E_NOMAL);
				break;
			case 'b':
				m_vecNode[i]->SetType(E_BLOCK);
				break;
			case 's':
				m_vecNode[i]->SetType(E_START);
				m_StartNode = m_vecNode[i];
				break;
			case 'd':
				m_vecNode[i]->SetType(E_END);
				m_EndNode = m_vecNode[i];
				break;
			}
			i++;
			if (i >= 16 * 16) break;
		}

	}
}

void cAstar::Find()
{
	bool roof = TRUE;
	cNode* smallNode;

	int x = abs(m_StartNode->GetAX() - m_EndNode->GetAX());
	int y = abs(m_StartNode->GetAY() - m_EndNode->GetAY());

	m_StartNode->SetG(0);
	m_StartNode->SetH(x + y);

	m_vecOpenList.push_back(m_StartNode);


	while (!m_vecOpenList.empty() && roof)
	{
		int eraseNumber = 0;	//확장하고 지울 벡터값
		smallNode = m_vecOpenList[0];
		for (int i = 0; i < m_vecOpenList.size(); i++)		//가장 f값이 작은 노드를 찾음
		{
			if (smallNode->GetF() > m_vecOpenList[i]->GetF())
			{
				smallNode = m_vecOpenList[i];
				eraseNumber = i;
			}
		}

		int originalX = smallNode->GetAX();
		int originalY = smallNode->GetAY();

		for (int i = 0; i < smallNode->GetEdge().size(); i++)
		{
			if (smallNode->GetEdge()[i]->GetMother())	//엄마 있을경우
			{
				int gX = abs(smallNode->GetAX() - smallNode->GetEdge()[i]->GetAX());
				int gY = abs(smallNode->GetAY() - smallNode->GetEdge()[i]->GetAY());
				float g;
				if (gX == 1 && gY == 1)
					g = smallNode->GetG() + ROOT2;
				else
					g = smallNode->GetG() + 1;

				if (smallNode->GetEdge()[i]->GetG() > g)
				{
					if (smallNode->GetEdge()[i] == m_StartNode)
						int k = 0;

					smallNode->GetEdge()[i]->SetMother(smallNode);
					smallNode->GetEdge()[i]->SetG(g);
				}

			}
			else
			{
				int hx = abs(smallNode->GetEdge()[i]->GetAX() - m_EndNode->GetAX());
				int hy = abs(smallNode->GetEdge()[i]->GetAY() - m_EndNode->GetAY());

				int gX = abs(smallNode->GetAX() - smallNode->GetEdge()[i]->GetAX());
				int gY = abs(smallNode->GetAY() - smallNode->GetEdge()[i]->GetAY());

				if (gX == 1 && gY == 1)
					smallNode->GetEdge()[i]->SetG(smallNode->GetG() + ROOT2);
				else
					smallNode->GetEdge()[i]->SetG(smallNode->GetG() + 1);


				if(smallNode->GetEdge()[i]->isOpen())
				smallNode->GetEdge()[i]->SetMother(smallNode);

				if (smallNode->GetEdge()[i] == m_EndNode)
				{
					smallNode->GetEdge()[i]->close();
					roof = false;
					break;
				}


				smallNode->GetEdge()[i]->SetH(hx + hy);
				m_vecOpenList.push_back(smallNode->GetEdge()[i]);
			}
		}

	
		smallNode->close();
		m_vecOpenList.erase(m_vecOpenList.begin() + eraseNumber);
	}


	cNode* node = m_EndNode->GetMother();

	while (true)
	{
		if (node == m_StartNode) break;
			
		node->SetType(E_ROAD);
		node = node->GetMother();

	}

}

void cAstar::Render(HDC hdc)
{
	for each (auto v in m_vecNode)
	{
		v->Render(hdc);
	}
}
