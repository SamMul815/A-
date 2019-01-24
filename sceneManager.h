#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

using namespace std;

class sceneManager : public singletonBase < sceneManager >
{
public:
	typedef map<wstring, gameNode*> mapSceneList;
	typedef map<wstring, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;		//���� ��
	static gameNode* _loadingScene;		//�ε� ��
	static gameNode* _readyScene;		//��� ��

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadThreadID;

public:
	sceneManager();
	~sceneManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	//�� �߰�
	gameNode* AddScene(wstring sceneName, gameNode* scene);

	gameNode* FindScene(wstring sceneName);

	//�ε� �� �߰�
	gameNode* AddLoadingScene(wstring loadingSceneName, gameNode* scene);

	HRESULT ChangeScene(wstring sceneName);
	HRESULT ChangeScene(wstring sceneName, wstring loadingSceneName);

	//private�� �� publicó�� ���ٰ����� ���� ĸ��ȭ ����
	friend DWORD CALLBACK LoadingThread(LPVOID prc);

};

