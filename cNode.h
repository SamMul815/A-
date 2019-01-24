#pragma once
#define SIZE 50
enum ENODETYPE {
	E_NOMAL,
	E_START,
	E_END,
	E_BLOCK,
	E_ROAD
};

class cNode
{
private:
	cNode* m_pMother;
	vector<cNode*> m_vecEdge;
	int m_nX;
	int m_nY;
	float m_fF;
	float m_fG;
	float m_fH;

	bool open;

	ENODETYPE m_eType;


public:
	cNode();
	~cNode();


	void SetXY(int x, int y) { m_nX = x; m_nY = y; }
	int GetX() { return m_nX; }
	int GetY() { return m_nY; }
	int GetAX() { return m_nX / SIZE; }
	int GetAY() { return m_nY / SIZE; }
	ENODETYPE GetType() { return m_eType; }
	void SetType(ENODETYPE type) { m_eType = type; }
		
	void PushEdge(cNode* node) { m_vecEdge.push_back(node); }
	vector<cNode*> GetEdge() { return m_vecEdge; }

	//void SetF(float f){m_fF = f;}
	void SetG(float g){m_fG = g;}
	void SetH(float h){m_fH = h;}

	float GetF() { return m_fG + m_fH; }
	float GetG() { return m_fG; }
	float GetH() { return m_fH; }

	void close() { open = false; }
	void Open() { open = true; }
	bool isOpen() { return open; }
	cNode* GetMother() { return m_pMother; }
	void SetMother(cNode* node) { m_pMother = node; }
	void Render(HDC hdc);
};

