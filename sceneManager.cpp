#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//private도 걍 public처럼 접근가능케 해줌 캡슐화 무시
DWORD CALLBACK LoadingThread(LPVOID prc)
{
	//교체될 init 함수 실행
	sceneManager::_readyScene->Init();

	//현재 씬을 교체될 씬으로 바꿈
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩씬을 해제
	sceneManager::_loadingScene->Release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

HRESULT sceneManager::Init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::Release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->Release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else
		{
			++miSceneList;
		}
	}

	_mSceneList.clear();

}

void sceneManager::Update(void)
{
	if (_currentScene) _currentScene->Update();
}

void sceneManager::Render(void)
{
	if (_currentScene) _currentScene->Render();
}

//씬 추가
gameNode* sceneManager::AddScene(wstring sceneName, gameNode* scene)
{
	if (!scene) return NULL;
	//scene->Init();
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//로딩 씬 추가
gameNode* sceneManager::AddLoadingScene(wstring loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT sceneManager::ChangeScene(wstring sceneName)
{
	//찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	//// 원래소스
	////바꾸려는 씬으로 초기황
	//if (SUCCEEDED(find->second->Init()))
	//{
	//	if (_currentScene) _currentScene->Release();
	//	_currentScene = find->second;

	//	return S_OK;
	//}

	//바꾸려는 씬으로 초기황
	if (!find->second->GetIsSceneInit())
	{
		if (SUCCEEDED(find->second->Init()))
		{
			find->second->SetIsSceneInit(true);
			_currentScene = find->second;
		}
		return S_OK;
	}
	else
	{
		_currentScene = find->second;
		return S_OK;
	}



	return S_OK;
}

gameNode* sceneManager::FindScene(wstring sceneName)
{
	//찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return NULL;
	else return find->second;
	
}

HRESULT sceneManager::ChangeScene(wstring sceneName, wstring loadingSceneName)
{
	//찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (find == _mLoadingSceneList.end()) return ChangeScene(loadingSceneName);


	//바꾸려는 씬으로 초기황
	if (SUCCEEDED(find->second->Init()))
	{
		//씬이 있으면 릴리즈
		if (_currentScene) _currentScene->Release();

		//로딩씬 틀고
		_loadingScene = findLoading->second;

		//준비된 씬에 바꿀려는 씬 넣어줌 ㅇㅇ
		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &_loadThreadID));
	}

	return E_FAIL;
}
