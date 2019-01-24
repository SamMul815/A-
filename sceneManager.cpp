#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//private�� �� publicó�� ���ٰ����� ���� ĸ��ȭ ����
DWORD CALLBACK LoadingThread(LPVOID prc)
{
	//��ü�� init �Լ� ����
	sceneManager::_readyScene->Init();

	//���� ���� ��ü�� ������ �ٲ�
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε����� ����
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

//�� �߰�
gameNode* sceneManager::AddScene(wstring sceneName, gameNode* scene)
{
	if (!scene) return NULL;
	//scene->Init();
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//�ε� �� �߰�
gameNode* sceneManager::AddLoadingScene(wstring loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT sceneManager::ChangeScene(wstring sceneName)
{
	//ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	//// �����ҽ�
	////�ٲٷ��� ������ �ʱ�Ȳ
	//if (SUCCEEDED(find->second->Init()))
	//{
	//	if (_currentScene) _currentScene->Release();
	//	_currentScene = find->second;

	//	return S_OK;
	//}

	//�ٲٷ��� ������ �ʱ�Ȳ
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
	//ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return NULL;
	else return find->second;
	
}

HRESULT sceneManager::ChangeScene(wstring sceneName, wstring loadingSceneName)
{
	//ã�´�
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (find == _mLoadingSceneList.end()) return ChangeScene(loadingSceneName);


	//�ٲٷ��� ������ �ʱ�Ȳ
	if (SUCCEEDED(find->second->Init()))
	{
		//���� ������ ������
		if (_currentScene) _currentScene->Release();

		//�ε��� Ʋ��
		_loadingScene = findLoading->second;

		//�غ�� ���� �ٲܷ��� �� �־��� ����
		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &_loadThreadID));
	}

	return E_FAIL;
}
