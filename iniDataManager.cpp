#include "stdafx.h"
//#include "iniDataManager.h"
//
//
//iniDataManager::iniDataManager()
//{
//}
//
//
//iniDataManager::~iniDataManager()
//{
//}
//
//HRESULT iniDataManager::Init()
//{
//
//	return S_OK;
//}
//
//void iniDataManager::Release()
//{
//
//}
//
////저장
//void iniDataManager::AddData(LPCWSTR subject, LPCWSTR title, LPCWSTR body)
//{
//	tagIniData iniData;
//	iniData.subject = subject;
//	iniData.title = title;
//	iniData.body = body;
//
//	arrIniData vIniData;
//	vIniData.push_back(iniData);
//
//	_vIniData.push_back(vIniData);
//}
//
//void iniDataManager::IniSave(wchar_t* fileName)
//{
//	wchar_t str[256];
//	wchar_t dir[256];
//
//	ZeroMemory(dir, sizeof(dir));
//	swprintf(dir, L"\\%s.ini", fileName);
//
//	//현재 경로에 저장한다
//	GetCurrentDirectory(256, str);
//	_tcsncat_s(str, 256, dir, 254);
//
//	for (int i = 0; i < _vIniData.size(); i++)
//	{
//		arrIniData vData = _vIniData[i];
//		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);
//
//		vData.clear();
//	}
//
//	_vIniData.clear();
//}
//
////로드
//wchar_t* iniDataManager::LoadDataString(LPCWSTR fileName, LPCWSTR subject, LPCWSTR title)
//{
//	wchar_t str[256];
//	wchar_t dir[256];
//
//	ZeroMemory(dir, sizeof(dir));
//	swprintf(dir, L"\\%s.ini", fileName);
//
//	GetCurrentDirectory(256, str);
//	_tcsncat_s(str, 256, dir, 254);
//
//	//wchar_t* data = new wchar_t[64];
//	wchar_t data[64];
//	GetPrivateProfileString(subject, title, L"", data, 64, str);
//
//	wchar_t* str_t = new wchar_t[64];
//	str_t = replaceAll(data, L"name", DATABASE->GetName());
//
//	return str_t;
//}
//
//wchar_t* iniDataManager::LoadDataString(LPCWSTR fileName, LPCWSTR subject, LPCWSTR title, int size)
//{
//	wchar_t str[256];
//	wchar_t dir[256];
//
//	ZeroMemory(dir, sizeof(dir));
//	swprintf(dir, L"\\%s.ini", fileName);
//
//	GetCurrentDirectory(256, str);
//	_tcsncat_s(str, 256, dir, 254);
//
//	//wchar_t* data = new wchar_t[64];
//	wchar_t data[64];
//	GetPrivateProfileString(subject, title, L"", data, size, str);
//
//	wchar_t* str_t = new wchar_t[64];
//	str_t = replaceAll(data, L"name", DATABASE->GetName());
//
//	return str_t;
//}
//
//int iniDataManager::LoadDataInteger(LPCWSTR fileName, LPCWSTR subject, LPCWSTR title)
//{
//	wchar_t str[256];
//	wchar_t dir[256];
//
//	ZeroMemory(dir, sizeof(dir));
//	swprintf(dir, L"\\%s.ini", fileName);
//
//	GetCurrentDirectory(256, str);
//	_tcsncat_s(str, 256, dir, 254);
//
//	return GetPrivateProfileInt(subject, title, 0, str);
//}
//
//wchar_t* iniDataManager::replaceAll(wchar_t* s, const wchar_t *olds, const wchar_t* news)
//{
//	wchar_t* result, *sr;
//	size_t i, count = 0;
//	size_t oldlen = wcslen(olds); if (oldlen < 1) return s;
//	size_t newlen = wcslen(news);
//
//
//	if (newlen != oldlen) {
//		for (i = 0; s[i] != '\0';) {
//			if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
//			else i++;
//		}
//	}
//	else i = wcslen(s);
//
//
//	result = (wchar_t*)malloc((i + 1 + count * (newlen - oldlen)) * sizeof(TCHAR));
//
//	if (result == NULL) return NULL;
//
//
//	sr = result;
//	while (*s) {
//		if (memcmp(s, olds, oldlen) == 0) {
//			memcpy(sr, news, newlen * sizeof(TCHAR));
//			sr += newlen;
//			s += oldlen;
//		}
//		else *sr++ = *s++;
//	}
//	*sr = '\0';
//
//	return result;
//}