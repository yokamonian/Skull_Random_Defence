#pragma once
#include "SingletonBase.h"
#include "pch.h"
#include <map>

using namespace std;

class GameNode;
/// <summary>
/// SceneManager : 씬(scene)관리 매니저 클래스
/// </summary>
class SceneManager : public SingletonBase<SceneManager>
{
private:
	map<string, GameNode*> mapSceneDatas;
	map<string, GameNode*> mapLoadingSceneDatas;

public:
	static GameNode* currentScene; // 현재 씬
	static GameNode* loadingScene; // 로딩 씬
	static GameNode* readyScene;   // 초기화를 위한 예비 씬

public:

	HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	// 씬 추가
	GameNode* AddScene(string key, GameNode* scene);
	GameNode* AddLoadingScene(string key, GameNode* scene);
	

	// 씬 체인지
	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	SceneManager();
	virtual ~SceneManager();
};


