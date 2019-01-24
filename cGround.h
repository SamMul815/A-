#pragma once
#include "cVector3.h"
#include "cMatrix.h"

class cGround
{
public:
	cVector3 m_vVertexX[8][2];
	cVector3 m_vVertexZ[8][2];
	cVector3 m_vWorldPosition;

	cMatrix GetWorldMatrix();

	cGround();
	~cGround();
};

