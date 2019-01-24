#pragma once
#include "cVector3.h"
#include "cMatrix.h"

class cCube
{
public:
	cVector3 m_vVertex[8];		//ť�� ��
	cVector3 m_vRotation;		//ȸ����
	cVector3 m_vArrow;			//���� ����
	cVector3 m_vWorldPosition;


	cMatrix m_mRotateMatrix;	//ȸ�� ��Ʈ����

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

