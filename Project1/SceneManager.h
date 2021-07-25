#pragma once
#include "SingletonBase.h"
#include "pch.h"
#include <map>

using namespace std;

class GameNode;
/// <summary>
/// SceneManager : ��(scene)���� �Ŵ��� Ŭ����
/// </summary>
class SceneManager : public SingletonBase<SceneManager>
{
private:
	map<string, GameNode*> mapSceneDatas;
	map<string, GameNode*> mapLoadingSceneDatas;

public:
	static GameNode* currentScene; // ���� ��
	static GameNode* loadingScene; // �ε� ��
	static GameNode* readyScene;   // �ʱ�ȭ�� ���� ���� ��

public:

	HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	// �� �߰�
	GameNode* AddScene(string key, GameNode* scene);
	GameNode* AddLoadingScene(string key, GameNode* scene);
	

	// �� ü����
	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	SceneManager();
	virtual ~SceneManager();
};


