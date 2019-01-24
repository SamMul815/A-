#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class txtData : public singletonBase<txtData>
{
public:
	HRESULT Init();
	void Release();

	//���̺�
	void TxtSave(LPCWSTR saveFileName, vector<wstring> vStr);
	LPWSTR VectorArrayCombine(vector<wstring> vArray);

	//�ε�
	vector<wstring> TxtLoad(LPCWSTR loadFileName);
	vector<wstring> CharArraySeparation(wchar_t charArray[]);


	txtData();
	~txtData();
};

