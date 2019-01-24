#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
{
	m_vWorldPosition = cVector3(0, 10, -5);
	vLook = cVector3(0, 0, 1);
	m_Distance = -5;
}


cCamera::~cCamera()
{
}

cMatrix cCamera::GetViewMatrix(cCube cube)
{
	cMatrix matrixRet;
	cMatrix worldMatrix;
	cMatrix rightUpLookMatrix(4);

	worldMatrix = cMatrix().Identity(4);
	worldMatrix[3][0] = -m_vWorldPosition.x;
	worldMatrix[3][1] = -m_vWorldPosition.y;
	worldMatrix[3][2] = -m_vWorldPosition.z;

	rightUpLookMatrix[0][0] = vRight.x;
	rightUpLookMatrix[1][0] = vRight.y;
	rightUpLookMatrix[2][0] = vRight.z;

	rightUpLookMatrix[0][1] = vUp.x;
	rightUpLookMatrix[1][1] = vUp.y;
	rightUpLookMatrix[2][1] = vUp.z;

	rightUpLookMatrix[0][2] = vLook.x;
	rightUpLookMatrix[1][2] = vLook.y;
	rightUpLookMatrix[2][2] = vLook.z;

	rightUpLookMatrix[3][3] = 1;

	matrixRet = worldMatrix * rightUpLookMatrix;

	return matrixRet;
}

cMatrix cCamera::GetViewMatrix(cGround ground)
{
	cMatrix matrixRet;
	cMatrix worldMatrix;
	cMatrix rightUpLookMatrix(4);

	//vLook = (cube.m_vWorldPosition - m_vWorldPosition).Normalize();
	//vRight = cVector3().Cross(cVector3(0, 1, 0), vLook).Normalize();
	//vUp = cVector3().Cross(vLook, vRight).Normalize();

	worldMatrix = cMatrix().Identity(4);
	worldMatrix[3][0] = -m_vWorldPosition.x;
	worldMatrix[3][1] = -m_vWorldPosition.y;
	worldMatrix[3][2] = -m_vWorldPosition.z;

	rightUpLookMatrix[0][0] = vRight.x;
	rightUpLookMatrix[1][0] = vRight.y;
	rightUpLookMatrix[2][0] = vRight.z;

	rightUpLookMatrix[0][1] = vUp.x;
	rightUpLookMatrix[1][1] = vUp.y;
	rightUpLookMatrix[2][1] = vUp.z;

	rightUpLookMatrix[0][2] = vLook.x;
	rightUpLookMatrix[1][2] = vLook.y;
	rightUpLookMatrix[2][2] = vLook.z;

	rightUpLookMatrix[3][3] = 1;

	matrixRet = worldMatrix * rightUpLookMatrix;


	return matrixRet;
}

cMatrix cCamera::GetProjection()
{
	float m_fFovY = 45 * DEG_TO_RAD;
	float m_fAspect = ((float)WINSIZEX / (float)WINSIZEY);
	float m_fNearZ = 1;
	float m_fFarZ = 1000;

	cMatrix retMatrix(4);
	retMatrix[0][0] = (1.0f / tan(m_fFovY / 2.0f)) / m_fAspect;
	retMatrix[1][1] = (1.0f / tan(m_fFovY / 2.0f));
	retMatrix[2][2] = m_fFarZ / (m_fFarZ - m_fNearZ);
	retMatrix[2][3] = 1.0f;
	retMatrix[3][2] = -1.0f * ((m_fFarZ * m_fNearZ) / (m_fFarZ - m_fNearZ));
	
	return retMatrix;
}

cMatrix cCamera::GetViewPort()
{
	float fX = 0;
	float fY = 0;
	float fW = WINSIZEX;
	float fH = WINSIZEY;
	float fMinZ = 0;
	float fMaxZ = 1;

	cMatrix retMatrix(4);

	retMatrix[0][0] = fW / 2.f;
	retMatrix[1][1] = -1 * (fH / 2.f);
	retMatrix[2][2] = fMaxZ - fMinZ;	//MaxZ - MinZ
	retMatrix[3][3] = 1;

	retMatrix[3][0] = fX + (fW / 2.f);
	retMatrix[3][1] = fY + (fH / 2.f);
	retMatrix[3][2] = fMinZ;	//MinZ

	return retMatrix;
}

void cCamera::SetPosition(cCube cube)
{
	cVector3 vPosition;
	m_mRotate = RotateX() * RotateY() * RotateZ();
	vPosition = cVector3(0, 0, - m_Distance) * m_mRotate;
	m_vWorldPosition = cube.m_vWorldPosition - vPosition;

	vLook = (cube.m_vWorldPosition - m_vWorldPosition).Normalize();
	vRight = cVector3().Cross(cVector3(0, 1, 0), vLook).Normalize();
	vUp = cVector3().Cross(vLook, vRight).Normalize();

	//m_vWorldPosition = vPosition;
}

void cCamera::DrawTriangle(HDC hdc,cVector3 cameraVlook, cMatrix matrix, cMatrix cubeRotate, cVector3 _v1, cVector3 _v2, cVector3 _v3)
{
	cVector3 v1 = _v1 * matrix;
	cVector3 v2 = _v2 * matrix;
	cVector3 v3 = _v3 * matrix;

	cVector3 vCross1, vCross2;	//ÈÄ¸éÃ³¸® ÇØÁÙ º¤ÅÍ
	vCross1 = v2 - v1;
	vCross2 = v3 - v2;

	cVector3 vTemp;
	vTemp = cVector3().Cross(vCross1, vCross2) * m_mRotate;

	if (cVector3().Dot(vTemp, cameraVlook) > 0)
	{
		MoveToEx(hdc, v1.x, v1.y, NULL);
		LineTo(hdc, v2.x, v2.y);
		LineTo(hdc, v3.x, v3.y);
		LineTo(hdc, v1.x, v1.y);
	}
}

void cCamera::Render(HDC hdc, cCube cube)
{
	cMatrix drawMatrix;
	drawMatrix = cube.GetWorldMatrix() * GetViewMatrix(cube) * GetProjection() * GetViewPort();
	//drawMatrix.Print();

	//À§
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(), cube.m_vVertex[0], cube.m_vVertex[1], cube.m_vVertex[3]);
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(), cube.m_vVertex[0], cube.m_vVertex[3], cube.m_vVertex[2]);

	//¾Õ
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[2], cube.m_vVertex[3], cube.m_vVertex[7]);
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[2], cube.m_vVertex[7], cube.m_vVertex[6]);

	//¿Þ¿·
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[0], cube.m_vVertex[2], cube.m_vVertex[4]);
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[4], cube.m_vVertex[2], cube.m_vVertex[6]);

	//¿À¿·
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[3], cube.m_vVertex[1], cube.m_vVertex[5]);
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[3], cube.m_vVertex[5], cube.m_vVertex[7]);

	//µÚ
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[1], cube.m_vVertex[0], cube.m_vVertex[4]);
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[1], cube.m_vVertex[4], cube.m_vVertex[5]);

	//¾Æ·¡
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[6], cube.m_vVertex[7], cube.m_vVertex[5]);
	DrawTriangle(hdc, vLook, drawMatrix, cube.RotateXYZ(),cube.m_vVertex[6], cube.m_vVertex[5], cube.m_vVertex[4]);
}

void cCamera::Render(HDC hdc, cGround ground)
{
	cMatrix drawMatrix;
	cVector3 cameraVLook;
	drawMatrix = ground.GetWorldMatrix() * GetViewMatrix(ground) * GetProjection() * GetViewPort();

	for (int i = 0; i < 8; i++)
	{
		cVector3 v1, v2;
		v1 = ground.m_vVertexX[i][0] * drawMatrix;
		v2 = ground.m_vVertexX[i][1] * drawMatrix;

		MoveToEx(hdc, v1.x, v1.y, NULL);
		LineTo(hdc, v2.x, v2.y);

		TextOut(hdc, v1.x, v1.y, L"x", sizeof(char));
	}

	for (int i = 0; i < 8; i++)
	{
		cVector3 v1, v2;
		v1 = ground.m_vVertexZ[i][0] * drawMatrix;
		v2 = ground.m_vVertexZ[i][1] * drawMatrix;

		MoveToEx(hdc, v1.x, v1.y, NULL);
		LineTo(hdc, v2.x, v2.y);
	
		TextOut(hdc, v1.x, v1.y, L"z", sizeof(char));
	}
}

cMatrix cCamera::RotateX()
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[1][1] = cosf(m_vRotate.x);
	matRet[1][2] = sinf(m_vRotate.x);
	matRet[2][1] = -sinf(m_vRotate.x);
	matRet[2][2] = cosf(m_vRotate.x);

	return matRet;
}

cMatrix cCamera::RotateY()
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(m_vRotate.y);
	matRet[0][2] = -sinf(m_vRotate.y);
	matRet[2][0] = sinf(m_vRotate.y);
	matRet[2][2] = cosf(m_vRotate.y);

	return matRet;
}

cMatrix cCamera::RotateZ()
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(m_vRotate.z);
	matRet[0][1] = sinf(m_vRotate.z);
	matRet[1][0] = -sinf(m_vRotate.z);
	matRet[1][1] = cosf(m_vRotate.z);

	return matRet;
}

void cCamera::Rotation(cVector3 rotate)
{
	m_vRotate = m_vRotate + rotate;

	if (m_vRotate.x >= PI / 2)
	{
		m_vRotate.x = PI / 2 - (1*DEG_TO_RAD);
	}

	if (m_vRotate.x <= -( PI / 2))
	{
		m_vRotate.x = -(PI / 2) + (1 * DEG_TO_RAD);
	}

	if (m_vRotate.y > PI * 2)
		m_vRotate.y -= PI *2;

	if (m_vRotate.y < -PI * 2)
		m_vRotate.y += PI * 2;

}
