#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;


DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	SceneManager::readyScene->Init();
	SceneManager::currentScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	return 0;
}

SceneManager::SceneManager()
{

}
SceneManager::~SceneManager()
{

}

HRESULT SceneManager::Init()
{
	return S_OK;
}

void SceneManager::Release()
{
}

void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
	{
		currentScene->Render(hdc);
	}
}

GameNode * SceneManager::AddScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapSceneDatas.insert(pair<string, GameNode*>(key, scene)); // (초기화 후) insert

	return scene;
}

GameNode * SceneManager::AddLoadingScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapLoadingSceneDatas.insert(pair<string, GameNode*>(key, scene));
	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	map<string, GameNode*>::iterator it;

	it = mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end()) // 없을 시
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK; 

	if (SUCCEEDED(it->second->Init())) // 바꿀려고 하는 씬
	{
		if (currentScene) //(현재 씬)릴리즈
		{
			currentScene->Release();
		}


		currentScene = it->second;
		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	map<string, GameNode*>::iterator it;

	it = mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end()) // 맵이 없을 시
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK;

	// change 중간에 들어갈 로딩씬
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())
	{
		return ChangeScene(sceneName);
	}

	if (SUCCEEDED(itLoading->second->Init())) //바꿀려고 하는 씬
	{
		if (currentScene) //현재 씬 해제
		{
			currentScene->Release();
		}

		readyScene = it->second;
		loadingScene = itLoading->second;

		currentScene = loadingScene;

		// 멀티쓰레드로 체인지할 메인씬 초기화
		HANDLE hThread;
		DWORD loadThredID;
		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThredID));  //쓰레드 닫기

		return S_OK;
	}

	return E_FAIL;
}

