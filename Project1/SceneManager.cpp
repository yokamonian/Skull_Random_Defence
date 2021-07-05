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

	mapSceneDatas.insert(pair<string, GameNode*>(key, scene)); // 씬을 초기화 후 맵에 insert

	return scene;
}

GameNode * SceneManager::AddLoadingScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapLoadingSceneDatas.insert(pair<string, GameNode*>(key, scene)); // 씬을 초기화 후 맵에 insert
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

	if (it->second == currentScene) return S_OK; //씬 체인지 동작 없이 S_OK를 리턴해주자.

	if (SUCCEEDED(it->second->Init())) //바꿀려고 하는 씬
	{
		if (currentScene) //현재 씬은 릴리즈를 해주고
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

	if (it == mapSceneDatas.end()) //없으면 SceneChange에 실패했다를 알려주고.
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK; //씬 체인지 동작 없이 S_OK를 리턴해주자.

	// change 중간에 들어갈 로딩씬
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())
	{
		return ChangeScene(sceneName);
	}

	if (SUCCEEDED(itLoading->second->Init())) //바꿀려고 하는 씬
	{
		if (currentScene) //현재 씬은 릴리즈를 해주고
		{
			currentScene->Release();
		}

		readyScene = it->second;
		loadingScene = itLoading->second;

		currentScene = loadingScene;

		// 멀티쓰레드로 체인지할 메인씬을 초기화한다.   // 멀티쓰레드가 처리할 함수의 주소
		HANDLE hThread;
		DWORD loadThredID;
		//hThread= CreateThread(NULL, 0, func, NULL, 0, &loadThredID);
		//CloseHandle(hThread);
		// 함수이름이 곧 함수의 포인터니까
		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThredID));  //쓰레드를 다시 닫아준다.

		return S_OK;
	}

	return E_FAIL;
}

