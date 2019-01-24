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
	static gameNode* _currentScene;		//ÇöÀç ¾À
	static gameNode* _loadingScene;		//·Îµù ¾À
	static gameNode* _readyScene;		//´ë±â ¾À

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

	//¾À Ãß°¡
	gameNode* AddScene(wstring sceneName, gameNode* scene);

	gameNode* FindScene(wstring sceneName);

	//·Îµù ¾À Ãß°¡
	gameNode* AddLoadingScene(wstring loadingSceneName, gameNode* scene);

	HRESULT ChangeScene(wstring sceneName);
	HRESULT ChangeScene(wstring sceneName, wstring loadingSceneName);

	//privateµµ °Á publicÃ³·³ Á¢±Ù°¡´ÉÄÉ ÇØÁÜ Ä¸½¶È­ ¹«½Ã
	friend DWORD CALLBACK LoadingThread(LPVOID prc);

};

