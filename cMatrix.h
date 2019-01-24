#pragma once
class cMatrix
{
private:
	class cRow
	{
	private:
		std::vector<float> m_vecColumn;

	public:
		cRow() {}
		~cRow() {}

		float& operator [] (int nIndex)
		{
			return m_vecColumn[nIndex];
		}

		void Resize(int nDimension)
		{
			m_vecColumn.resize(nDimension);
		}

		void Print()
		{
			for (size_t i = 0; i < m_vecColumn.size(); ++i)
			{
				printf("%8.2f", m_vecColumn[i]);
			}
			printf("\n");
		}
	};

private:
	std::vector<cRow> m_vecRow;

public:
	cMatrix(void);
	cMatrix(int nDimension);
	~cMatrix(void);

	cRow& operator [] (int nIndex)
	{
		return m_vecRow[nIndex];
	}

	static cMatrix Identity(int nDimension);

	int Dimension();
	bool operator == (cMatrix& mat);
	bool operator != (cMatrix& mat);
	cMatrix operator + (cMatrix& mat);
	cMatrix operator - (cMatrix& mat);
	cMatrix operator * (float f);
	cMatrix operator * (cMatrix& mat);

	cMatrix Inverse(OUT float& fDeterminent);
	cMatrix Transpose();
	void Random(); // -5~5 사이의 소수이하 2자리까지 가지는 실수
	void Print();
	void Resize(int nDimension);
	float Determinant();
	cMatrix Adjoint();
	float Cofactor(int nRow, int nCol);
	float Minor(int nRow, int nCol);

	//static	cMatrix Translation(float x, float y, float z);
	//static	cMatrix RotateX(float fAngle);
	//static	cMatrix RotateY(float fAngle);
	//static	cMatrix RotateZ(float fAngle);
	//static	cMatrix Scale(float x, float y, float z);

	//static	cMatrix	View(cVector3* pEye/* 0, 0, -5 */, cVector3* pUp/* 0, 1, 0 */, cVector3* pLookAt /* 0, 0, 0 */);
	//static	cMatrix Projection(float fFovY /* 45도 */, float fAspect, float fNearZ /* 1 */, float fFarZ /* 1000 */);
	//static	cMatrix Viewport(float fX, float fY, float fW, float fH, float fMinZ, float fMaxZ);
};

