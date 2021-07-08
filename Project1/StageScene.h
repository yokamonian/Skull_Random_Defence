#pragma once
#include "GameNode.h"
#include "pch.h"
#include <utility>

// ������
typedef struct tagIcon
{
	POINT iconPos;
	Image* iconImg;
	int currframe;
}Icon;

// ��ư
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
	// ����
	Skull* skull;					// ����
	Skull* selectSkull = nullptr;	// ���õ� ����
	vector<Skull*> vecSkulls;		// �ʵ� ���� ����(�����)
	stack<Skull*> stSkulls;			// ������Ʈ Ǯ(����)
	int skullLimitCount = 20;		// ���� �� ����
	string skullName;				// ���� Ÿ��(�̸�)
	Card* skullCard[4];				// ���� ���� ī��
	POINT cardPos[4];				// ī�� ��ġ��
	Storage** storage;				// �����
	Storage* prevStorage;			// (���õ� ������)���� �����

	// Ÿ��
	ISOTILE** tiles;				// ��� Ÿ�� ����
	TILE_NUM_INFO start;			// ������
	TILE_NUM_INFO end;				// ������
	POINT ptSelected;				// ���õ� Ÿ�ϸ�

	bool isHide = false;			// ī�� ���� ������ ���� ����
	bool isLock = false;			// ī�� ���� ������ ��� ����
	bool isSelect = false;			// ���� ����
	bool isWave = false;			// ���̺� ����
	bool isTimer = false;			// Ÿ�̸� ���� ����
	bool isSpawn = false;			// �� ���� ����

	// UI
	Button cardLockB;
	Button startB;
	Button cardB;
	Icon timer;

	// �ð� ����
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



