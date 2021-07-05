#pragma once
#include "SingletonBase.h"
#include "pch.h"
#include <map>

using namespace std;

class GameNode;
class SceneManager : public SingletonBase<SceneManager>
{
private:
	map<string, GameNode*> mapSceneDatas;
	map<string, GameNode*> mapLoadingSceneDatas;

public:
	static GameNode* currentScene; //��� ������ �Ǿ��ֱ� ������ ������ �� ���������� �������� �ִ�.
	static GameNode* loadingScene;
	static GameNode* readyScene;	

public:

	HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	// �� �߰�
	GameNode* AddScene(string key, GameNode* scene); //Ű�� scene�� ������ map�� ������ �Լ�
	GameNode* AddLoadingScene(string key, GameNode* scene); //Ű�� scene�� ������ map�� ������ �Լ�
	

	// �� ü����
	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	SceneManager();
	virtual ~SceneManager();
};


