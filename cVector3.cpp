#include "StdAfx.h"
#include "cVector3.h"


cVector3::cVector3(void)
	: x(0), y(0), z(0)
{
}

cVector3::cVector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}


cVector3::~cVector3(void)
{
}

bool cVector3::operator==(cVector3& v)
{
	if (fabs(x - v.x) >= FLOAT_EPSILON)
		return false;

	if (fabs(y - v.y) >= FLOAT_EPSILON)
		return false;

	if (fabs(z - v.z) >= FLOAT_EPSILON)
		return false;

	return true;
}

bool cVector3::operator!=(cVector3& v)
{
	return !(*this == v);
}

cVector3 cVector3::operator+(cVector3& v)
{
	return cVector3(x + v.x, y + v.y, z + v.z);
}

cVector3 cVector3::operator-(cVector3& v)
{
	return cVector3(x - v.x, y - v.y, z - v.z);
}

cVector3 cVector3::operator*(float f)
{
	return cVector3(x * f, y * f, z * f);
}
cVector3 cVector3::operator*(cMatrix & matrix)
{
	float fVector[4];
	for (int i = 0; i < matrix.Dimension(); i++)
	{
		fVector[i] = 0;
		fVector[i] += matrix[0][i] * x;
		fVector[i] += matrix[1][i] * y;
		fVector[i] += matrix[2][i] * z;
		fVector[i] += matrix[3][i] * 1;
	}
	return cVector3(fVector[0] / fVector[3],fVector[1] / fVector[3],fVector[2] / fVector[3]);
}

cVector3 cVector3::TransformNormal(cMatrix* pmat)
{
	cMatrix mat = *pmat;
	cVector3 v;
	v.x = x * mat[0][0] + y * mat[1][0] + z * mat[2][0];
	v.y = x * mat[0][1] + y * mat[1][1] + z * mat[2][1];
	v.z = x * mat[0][2] + y * mat[1][2] + z * mat[2][2];
	return v;
}

float cVector3::Length()
{
	return sqrt(LengthSq());
}

float cVector3::LengthSq()
{
	return x * x + y * y + z * z;
}

cVector3 cVector3::Normalize()
{
	float l = Length();
	return cVector3(x / l, y / l, z / l);
}

float cVector3::Dot(cVector3& v1, cVector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector3 cVector3::Cross(cVector3& v1, cVector3& v2)
{
	return cVector3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

cVector3 operator*(float f, cVector3& v)
{
	return v * f;
}
