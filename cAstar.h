#pragma once
class cNode;
#define ROOT2 1.4142135
class cAstar
{
private:
	cNode*			m_StartNode;
	cNode*			m_EndNode;

	vector<cNode*> m_vecNode;
	vector<cNode*> m_vecOpenList;
public:
	cAstar();
	~cAstar();

	void Setup();
	void Update();
	void Find();
	void Render(HDC hdc);

};

