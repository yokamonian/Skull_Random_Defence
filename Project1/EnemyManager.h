#pragma once
#include "GameNode.h"
#include "AstarScene.h"


class Enemy;
class EnemyManager : public GameNode
{
private:
	ISOTILE** tiles;			// 적 위치 타일
	vector<Enemy*> enemies;		// 적 유닛 집합
	Enemy* enemy;				// 적 유닛
	stack<Enemy*> stEnemies;
	list<pair<int, int>>* astar;
	TILE_NUM_INFO spawnPos;
	int enemyCount = 20;
	int waveId;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void SetAstarPath(list<pair<int, int>>* _astar);

	//void SetSpawnPos(TILE_NUM_INFO _pos) { spawnPos = _pos; }
	void SetEnemy(int id, TILE_NUM_INFO _pos);
	int GetEnemiesCount() { return enemyCount; }
	void WaveStart();
};

