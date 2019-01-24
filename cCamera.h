#pragma once
#include "cCube.h"
#include "cGround.h"
class cCamera
{
public:
	cVector3 m_vWorldPosition;	//월드 좌표
	cVector3 m_vRotate;			//카메라 회전값
	cMatrix  m_mRotate;			//회전된 매트릭스값

	cVector3 vUp;
	cVector3 vRight;
	cVector3 vLook;
	float m_Distance;		//카메라 거리값

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

