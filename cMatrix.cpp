#include "StdAfx.h"
#include "cMatrix.h"


cMatrix::cMatrix(void)
{
}

cMatrix::cMatrix(int nDimension)
{
	Resize(nDimension);
	for (int i = 0; i < nDimension; i++)
	{
		for (int j = 0; j < nDimension; j++)
		{
			m_vecRow[i][j] = 0;
		}
	}
}

cMatrix::~cMatrix(void)
{
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix matRet(nDimension);

	for (int i = 0; i < nDimension; ++i)
	{
		for (int j = 0; j < nDimension; ++j)
		{
			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}

	return matRet;
}

void cMatrix::Resize(int nDimension)
{
	m_vecRow.resize(nDimension);
	for (int i = 0; i < nDimension; ++i)
	{
		m_vecRow[i].Resize(nDimension);
	}
}

int cMatrix::Dimension()
{
	return m_vecRow.size();
}

bool cMatrix::operator==(cMatrix& mat)
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if (fabs((*this)[i][j] - mat[i][j]) > FLOAT_EPSILON)
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix& mat)
{
	return !((*this) == mat);
}

cMatrix cMatrix::operator+(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}

	return matRet;
}

cMatrix cMatrix::operator-(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}

	return matRet;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] * f;
		}
	}

	return matRet;
}

cMatrix cMatrix::operator*(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = 0;
			for (int k = 0; k < Dimension(); ++k)
			{
				matRet[i][j] += ((*this)[i][k] * mat[k][j]);
			}
		}
	}

	return matRet;
}

cMatrix cMatrix::Transpose()
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}

	return matRet;
}

void cMatrix::Random()
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			(*this)[i][j] = ((rand() % 1000) - 500) / 100.f;
		}
	}
}

void cMatrix::Print()
{
	printf("===== Matrix\n");
	for (int i = 0; i < Dimension(); ++i)
	{
		m_vecRow[i].Print();
	}
}

cMatrix cMatrix::Inverse(OUT float& fDeterminent)
{
	fDeterminent = Determinant();
	if (fabs(fDeterminent) < FLOAT_EPSILON)
	{
		return cMatrix::Identity(Dimension());
	}
	return Adjoint() * (1 / fDeterminent);
}

float cMatrix::Determinant()
{
	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
	}

	float fDeterminant = 0;
	for (size_t i = 0; i < Dimension(); ++i)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}
	return fDeterminant;
}

cMatrix cMatrix::Adjoint()
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}

	return matRet;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;
	if ((nRow + nCol) % 2 == 1)
	{
		nConst = -1;
	}
	return nConst * Minor(nRow, nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{
	int nMinorRow = 0;
	int nMinorCol = 0;

	cMatrix mat(Dimension() - 1);
	for (int i = 0; i < Dimension(); ++i)
	{
		if (i == nRow)
			continue;
		nMinorCol = 0;
		for (int j = 0; j < Dimension(); ++j)
		{
			if (j == nCol)
				continue;
			mat[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}

	return mat.Determinant();
}
