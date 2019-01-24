#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <fstream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "XinputManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "pixelCManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "actionManager.h"
#include "keyAniManager.h"
#include "utils.h"
#include "collision.h"
#include "txtData.h"
//#include "iniDataManager.h"
#include "camera.h"

using namespace std;
using namespace TANGO_UTIL;

//===============================================
// - 2015. 11. 17 ## �����ι� ##
//===============================================

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINNAME (LPTSTR)(TEXT("Tango Team"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
#else
#define WINNAME (LPTSTR)(TEXT("Tango Team"))
#define WINSTARTX 20
#define WINSTARTY 20
#define WINSIZEX 800	
#define WINSIZEY 800

#endif

#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::GetSingleton()
#define KEYMANAGER keyManager::GetSingleton()
#define IMAGEMANAGER imageManager::GetSingleton()
#define SOUNDMANAGER soundManager::GetSingleton()
#define PIXELCMANAGER pixelCManager::GetSingleton()
#define TIMEMANAGER timeManager::GetSingleton()
#define EFFECTMANAGER effectManager::GetSingleton()
#define SCENEMANAGER sceneManager::GetSingleton()
#define ACTIONMANAGER actionManager::GetSingleton()
#define KEYANIMANAGER keyAniManager::GetSingleton()
#define TXTDATA txtData::GetSingleton()
//#define INIDATAMANAGER iniDataManager::GetSingleton()
#define CAMERA camera::GetSingleton()
#define TEXTRENDER textRender::GetSingleton()

//===============================================
// - 2015. 11. 17 ## ��ũ�� �Լ� ##
//===============================================

#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p)=NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->Release(); (p) = NULL;}}

//===============================================
// - 2015. 11. 17 ## ���� ���� ##
//===============================================


extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
extern long _ptMouseWheel;