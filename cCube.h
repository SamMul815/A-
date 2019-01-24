#pragma once
#include "cVector3.h"
#include "cMatrix.h"

class cCube
{
public:
	cVector3 m_vVertex[8];		//큐브 점
	cVector3 m_vRotation;		//회전값
	cVector3 m_vArrow;			//정면 벡터
	cVector3 m_vWorldPosition;


	cMatrix m_mRotateMatrix;	//회전 매트릭스

	cMatrix GetWorldMatrix();
	cMatrix RotateX();
	cMatrix RotateY();
	cMatrix RotateZ();
	cMatrix RotateXYZ();

	//cMatrix RotateX(cVector3 _centerVertex);
	cMatrix RotateMatrix(cMatrix _x, cMatrix _y, cMatrix _z);

	void Move(float speed);
	void Rotation(cVector3 vAngle);
	cCube();
	~cCube();
};

