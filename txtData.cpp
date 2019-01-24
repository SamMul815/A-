#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::Init() { return S_OK; }
void txtData::Release() {}

//세이브
void txtData::TxtSave(LPCWSTR saveFileName, vector<wstring> vStr)
{
	HANDLE file;

	wchar_t str[128];
	DWORD write;
	unsigned short mark = 0xFEFF;

	_tcsncpy_s(str, 128, VectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, &mark, sizeof(mark), &write, NULL);
	WriteFile(file, str, wcslen(str)*sizeof(wchar_t), &write, NULL);

	CloseHandle(file);
}

LPWSTR txtData::VectorArrayCombine(vector<wstring> vArray)
{
	wchar_t str[128];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		_tcsncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) _tcscat(str, L",");
	}

	return str;
}

//로드
vector<wstring> txtData::TxtLoad(LPCWSTR loadFileName)
{
	HANDLE file;

	wchar_t str[128];
	DWORD read;
	unsigned short mark = 0xFEFF;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &mark, sizeof(mark), &read, NULL);
	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return CharArraySeparation(str);
}

vector<wstring> txtData::CharArraySeparation(wchar_t charArray[])
{
	vector<wstring> vArray;

	LPWSTR temp;
	LPWSTR separator = L",";
	LPWSTR token;

	token = _tcstok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = _tcstok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
