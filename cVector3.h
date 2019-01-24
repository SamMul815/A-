#pragma once
#include "cMatrix.h"
class cVector3
{
public:
	cVector3(void);
	cVector3(float _x, float _y, float _z);
	~cVector3(void);

public:
	float x, y, z;

	bool operator == (cVector3& v);
	bool operator != (cVector3& v);
	cVector3 operator + (cVector3& v);
	cVector3 operator - (cVector3& v);
	cVector3 operator * (float f);
	cVector3 operator * (cMatrix& matrix);
	float Length();
	float LengthSq(); // ±æÀÌ Á¦°ö
	cVector3 Normalize();
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	 cVector3 TransformNormal(cMatrix* pmat);

};

cVector3 operator * (float f, cVector3& v);

