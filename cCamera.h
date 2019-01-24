#pragma once
#include "cCube.h"
#include "cGround.h"
class cCamera
{
public:
	cVector3 m_vWorldPosition;	//���� ��ǥ
	cVector3 m_vRotate;			//ī�޶� ȸ����
	cMatrix  m_mRotate;			//ȸ���� ��Ʈ������

	cVector3 vUp;
	cVector3 vRight;
	cVector3 vLook;
	float m_Distance;		//ī�޶� �Ÿ���

	cCamera();
	~cCamera();

	cMatrix GetViewMatrix(cCube cube);
	cMatrix GetViewMatrix(cGround ground);

	cMatrix GetProjection();
	cMatrix GetViewPort();

	cMatrix RotateX();
	cMatrix RotateY();
	cMatrix RotateZ();
	void	Rotation(cVector3 rotate);

	void SetPosition(cCube cube);
	void DrawTriangle(HDC hdc,cVector3 cameraVlook, cMatrix matrix, cMatrix cubeRotate, cVector3 _v1, cVector3 _v2, cVector3 _v3);
	void Render(HDC hdc, cCube cube);
	void Render(HDC hdc, cGround ground);

};

