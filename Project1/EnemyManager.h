#pragma once
#include "GameNode.h"
#include "AstarScene.h"


class Enemy;
class EnemyManager : public GameNode
{
private:
	ISOTILE** tiles;			// �� ��ġ Ÿ��
	vector<Enemy*> enemies;		// �� ���� ����
	Enemy* enemy;				// �� ����
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

