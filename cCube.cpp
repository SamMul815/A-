#include "stdafx.h"
#include "cCube.h"


cMatrix cCube::GetWorldMatrix()
{
	cMatrix matrixRet;

	matrixRet = cMatrix().Identity(4);
	matrixRet[3][0] = m_vWorldPosition.x ;
	matrixRet[3][1] = m_vWorldPosition.y ;
	matrixRet[3][2] = m_vWorldPosition.z;

	return RotateX() * RotateY() * RotateZ() *  matrixRet;
}

void cCube::Rotation(cVector3 vAngle)
{
	m_vRotation = m_vRotation + vAngle;
	m_vArrow = cVector3(0, 0, 1).TransformNormal(&(RotateX() * RotateY() * RotateZ())).Normalize();
}

cCube::cCube()
{
	//위쪽 4개의 꼭짓점
	m_vVertex[0] = cVector3(-0.5, 0.5, 0.5);
	m_vVertex[1] = cVector3( 0.5, 0.5, 0.5);
	m_vVertex[2] = cVector3(-0.5, 0.5,-0.5);
	m_vVertex[3] = cVector3( 0.5, 0.5,-0.5);

	//아래쪽 4개의 꼭짓점
	m_vVertex[4] = cVector3(-0.5, -0.5, 0.5);
	m_vVertex[5] = cVector3( 0.5, -0.5, 0.5);
	m_vVertex[6] = cVector3(-0.5, -0.5,-0.5);
	m_vVertex[7] = cVector3( 0.5, -0.5,-0.5);


	////위쪽 4개의 꼭짓점
	//m_vVertex[0] = cVector3(-0.5, 1, 0);
	//m_vVertex[1] = cVector3(0.5, 1, 0);
	//m_vVertex[2] = cVector3(-0.5, 1, -1);
	//m_vVertex[3] = cVector3(0.5, 1, -1);


	////아래쪽 4개의 꼭짓점
	//m_vVertex[4] = cVector3(-0.5, 0, 0);
	//m_vVertex[5] = cVector3(0.5, 0, 0);
	//m_vVertex[6] = cVector3(-0.5, 0, -1);
	//m_vVertex[7] = cVector3(0.5, 0, -1);


	m_vWorldPosition = cVector3(0, 0, 0);	//큐브의 월드 좌표
	m_vRotation = cVector3(0, 0, 0);
	m_vArrow = cVector3(0, 0, 1);


}

cCube::~cCube()
{

}

cMatrix cCube::RotateX()
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[1][1] = cosf(m_vRotation.x);
	matRet[1][2] = sinf(m_vRotation.x);
	matRet[2][1] = -sinf(m_vRotation.x);
	matRet[2][2] = cosf(m_vRotation.x);

	return matRet;
}

cMatrix cCube::RotateY()
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(m_vRotation.y);
	matRet[0][2] = -sinf(m_vRotation.y);
	matRet[2][0] = sinf(m_vRotation.y);
	matRet[2][2] = cosf(m_vRotation.y);

	return matRet;
}

cMatrix cCube::RotateZ()
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(m_vRotation.z);
	matRet[0][1] = sinf(m_vRotation.z);
	matRet[1][0] = -sinf(m_vRotation.z);
	matRet[1][1] = cosf(m_vRotation.z);

	return matRet;
}

cMatrix cCube::RotateXYZ()
{
	return RotateX() * RotateY() * RotateZ();
}


cMatrix cCube::RotateMatrix(cMatrix _x, cMatrix _y, cMatrix _z)
{
	return _x * _y * _z;
}

void cCube::Move(float speed)
{
	m_vWorldPosition = m_vWorldPosition + (m_vArrow * speed);
}

