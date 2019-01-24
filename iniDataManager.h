//#pragma once
//#include "singletonBase.h"
//#include <vector>
//
//struct tagIniData
//{
//	LPCWSTR subject;	//브랜드
//	LPCWSTR title;		//HP
//	LPCWSTR body;		//500
//};
//
//class iniDataManager : public singletonBase < iniDataManager >
//{
//private:
//	typedef vector<tagIniData> arrIniData;
//	typedef vector<tagIniData>::iterator arrIniDataIter;
//
//	typedef vector<arrIniData> arrIniDatas;
//	typedef vector<arrIniData>::iterator arrIniDatasIter;
//
//private:
//	arrIniDatas _vIniData;
//
//public:
//	HRESULT Init();
//	void Release();
//
//	//저장
//	void AddData(LPCWSTR subject, LPCWSTR title, LPCWSTR body);
//	void IniSave(wchar_t* fileName);
//
//	//로드
//	wchar_t* LoadDataString(LPCWSTR fileName, LPCWSTR subject, LPCWSTR title);
//	wchar_t* LoadDataString(LPCWSTR fileName, LPCWSTR subject, LPCWSTR title, int size);
//	int LoadDataInteger(LPCWSTR fileName, LPCWSTR subject, LPCWSTR title);
//
//	wchar_t* replaceAll(wchar_t* s, const wchar_t *olds, const wchar_t* news);
//
//	iniDataManager();
//	~iniDataManager();
//};
//
