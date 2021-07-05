#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

//�ݹ� �Լ�
// ������ ���ξ��� �ʱ�ȭ �ϴ� ��.
DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	// ������ ���� ���� (���)
	/*
		1. ȣ��� �Լ��� ��ȯ�� �� �� (�츮�� ����� ���)
		2. ȣ��� �Լ� ���ο��� ExitThread()�� ȣ������ ��
		3. ������ ���μ����� �ٸ� ���μ������� TerminateThread()�� ȣ������ ��
		4. ���� �����尡 ���Ե� ���μ����� ����� ��
	*/

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

	mapSceneDatas.insert(pair<string, GameNode*>(key, scene)); // <string, GameNode*Ÿ���̰�,> ( key, scene ) ���� �ʱ�ȭ �ؼ� �ʿ��ٰ� insert�� �Ѵ�.

	return scene;
}

GameNode * SceneManager::AddLoadingScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapLoadingSceneDatas.insert(pair<string, GameNode*>(key, scene)); // <string, GameNode*Ÿ���̰�,> ( key, scene ) ���� �ʱ�ȭ �ؼ� �ʿ��ٰ� insert�� �Ѵ�.

	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName) //Ű�� ���ͼ�
{
	map<string, GameNode*>::iterator it;

	it = mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end()) //������ SceneChange�� �����ߴٸ� �˷��ְ�.
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK; //�� ü���� ���� ���� S_OK�� ����������.

	if (SUCCEEDED(it->second->Init())) //�ٲܷ��� �ϴ� ��
	{
		if (currentScene) //���� ���� ����� ���ְ�
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

	if (it == mapSceneDatas.end()) //������ SceneChange�� �����ߴٸ� �˷��ְ�.
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK; //�� ü���� ���� ���� S_OK�� ����������.

	// change �߰��� �� �ε���
	map<string, GameNode*>::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())
	{
		return ChangeScene(sceneName);
	}

	if (SUCCEEDED(itLoading->second->Init())) //�ٲܷ��� �ϴ� ��
	{
		if (currentScene) //���� ���� ����� ���ְ�
		{
			currentScene->Release();
		}

		readyScene = it->second;
		loadingScene = itLoading->second;

		currentScene = loadingScene;

		// ��Ƽ������� ü������ ���ξ��� �ʱ�ȭ�Ѵ�.   // ��Ƽ�����尡 ó���� �Լ��� �ּ�
		HANDLE hThread;
		DWORD loadThredID;
		//hThread= CreateThread(NULL, 0, func, NULL, 0, &loadThredID);
		//CloseHandle(hThread);
		// �Լ��̸��� �� �Լ��� �����ʹϱ�
		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThredID));  //�����带 �ٽ� �ݾ��ش�.

		return S_OK;
	}

	return E_FAIL;
}

