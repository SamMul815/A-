#include "stdafx.h"
#include "cGround.h"


cMatrix cGround::GetWorldMatrix()
{

	cMatrix matrixRet;

	matrixRet = cMatrix().Identity(4);
	matrixRet[3][0] = m_vWorldPosition.x;
	matrixRet[3][1] = m_vWorldPosition.y;
	matrixRet[3][2] = m_vWorldPosition.z;

	return matrixRet;
}

cGround::cGround()
{
	for (int i = 0; i < 8; i++)
	{
		m_vVertexX[i][0] = cVector3(i , 0, 0);
		m_vVertexZ[i][0] = cVector3(0, 0,  i);

		m_vVertexX[i][1] = cVector3(i, 0, 7);
		m_vVertexZ[i][1] = cVector3(7, 0, i);
	}
	m_vWorldPosition = cVector3(0, 0, 0);	//큐브의 월드 좌표
}

cGround::~cGround()
{
}
