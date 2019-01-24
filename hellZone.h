#pragma once
#include "gameNode.h"
#include <vector>


class cAstar;

class hellZone : public gameNode
{
private:
	cAstar* m_pAstar;
	int _mouseX;
	int _mouseY;
public:
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

	hellZone();
	~hellZone();
};

