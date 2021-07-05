#pragma once
#include "GameNode.h"
#include "pch.h"
#include <utility>

typedef struct tagIcon
{
	POINT iconPos;
	Image* iconImg;
	int currframe;
}Icon;

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
	Skull* skull;
	Skull* selectSkull = nullptr;
	vector<Skull*> vecSkulls;
	stack<Skull*> stSkulls;
	int skullLimitCount = 20;
	string skullName;
	// 타일
	ISOTILE** tiles;
	TILE_NUM_INFO start;
	TILE_NUM_INFO end;

	bool isHide = false;
	bool isLock = false;
	bool isSelect = false;
	bool isWave = false;
	bool isTimer = false;
	bool isSpawn = false;
	Button cardLockB;
	Button startB;
	Button cardB;
	Icon timer;

	float WaveTime;
	float elapsedTime = 0;
	float countTime = 5.0f;
	Image* inGameScreen;
	Image* enemyGate;
	Image* img;
	Image* effectImg;
	POINT gatePos;
	int currframeX;
	int currframeY;
	int waveDeltaTime;
	int frame;
	int elapsedSpawnTime = 0;
	bool isOpen;
	int totalGold;

	list<pair<int, int>>* astarPath;
	int ratioX, ratioY;
	int wave;
	int size;
	HPEN pen;
	HPEN pen1;

	Card* skullCard[4];
	POINT cardPos[4];
	POINT ptSelected;
	Storage** storage;
	Storage* prevStorage;
	Portal* portal;

	EnemyManager* enemymgr;
	int endflag;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	static StageScene* instance;
	void ShuffleDist();
	void Start();
	void CheckPercase();
	void PerchaseCard(Card* skullCard, Storage* storage);
	void PerchaseShuffleCard(Card* shuffleCard);
	void SelectSkull();
	void MoveSkull();
	void SetUpSkull();
	void SetStorage();
	void DrawPath(HDC hdc);
	void ClickButton();
	void SpawnEnemies();
	//void SpawnTime();
	Portal* GetPortal() { return portal; }

	StageScene();
	virtual ~StageScene();
};



