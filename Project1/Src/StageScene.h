#pragma once
#include "GameNode.h"
#include "pch.h"
#include <utility>

/// <summary>
/// StageScene : 게임 시작 시 등장하는 게임 스테이지 클래스.
/// </summary>


// 아이콘
typedef struct tagIcon
{
	POINT iconPos;
	Image* iconImg;
	int currframe;
}Icon;

// 버튼
typedef struct tagButton
{
	Icon	ButtIcon;
	RECT	ButtRect;
}Button;

class Skull;
class Card;
class AstarScene;
class Storage;
class Portal;
class EnemyManager;
class StageScene : public GameNode
{
private:
	// 스컬
	Skull* skull;					// 스컬
	Skull* selectSkull = nullptr;	// 선택된 스컬
	vector<Skull*> vecSkulls;		// 필드 위의 스컬(저장용)
	stack<Skull*> stSkulls;			// 오브젝트 풀(스컬)
	int skullLimitCount = 20;		// 스컬 수 제한
	string skullName;				// 스컬 타입(이름)
	Card* skullCard[4];				// 스컬 구매 카드
	POINT cardPos[4];				// 카드 위치값
	Storage** storage;				// 저장소
	Storage* prevStorage;			// (선택된 스컬의)이전 저장소

	// 타일
	ISOTILE** tiles;				// 모든 타일 정보
	TILE_NUM_INFO start;			// 시작점
	TILE_NUM_INFO end;				// 도착점
	POINT ptSelected;				// 선택된 타일맵

	bool isHide = false;			// 카드 구매 아이콘 숨김 여부
	bool isLock = false;			// 카드 구매 아이콘 잠김 여부
	bool isSelect = false;			// 선택 여부
	bool isWave = false;			// 웨이브 여부
	bool isTimer = false;			// 타이머 시작 여부
	bool isSpawn = false;			// 적 스폰 여부

	// UI
	Button cardLockB;				// 카드 구매 잠금 버튼
	Button startB;					// 시작 버튼
	Button cardB;					// 카드 구매 버튼
	Icon timer;						// 타이머 아이콘

	// 시간 관련
	float WaveTime;
	int waveDeltaTime;
	int frame;
	float elapsedTime = 0;
	float countTime = 5.0f;

	Image* inGameScreen;
	Image* enemyGate;
	Image* img;
	Image* effectImg;
	POINT gatePos;

	int currframeX;
	int currframeY;
	int elapsedSpawnTime = 0;
	bool isOpen;
	int totalGold;

	list<pair<int, int>>* astarPath;
	int ratioX, ratioY;
	int wave;
	int size;
	HPEN pen;
	HPEN pen1;

	Portal* portal;

	EnemyManager* enemymgr;
	int endflag;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	static StageScene* instance;
	void ShuffleDist();										// 카드 섞기
	void Start();											// 시작
	void CheckPercase();									// 구매 여부 확인
	void PerchaseCard(Card* skullCard, Storage* storage);	// 카드 구매
	void PerchaseShuffleCard(Card* shuffleCard);			// 섞기 버튼 구매
	void SelectSkull();
	void MoveSkull();										// (필드에) 스컬 이동
	void SetUpSkull();										// (필드에) 스컬 배치
	void SetStorage();
	void DrawPath(HDC hdc);
	void ClickButton();
	void SpawnEnemies();
	//void SpawnTime();
	Portal* GetPortal() { return portal; }

	StageScene();
	virtual ~StageScene();
};



