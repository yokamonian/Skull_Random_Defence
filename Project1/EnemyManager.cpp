#include "EnemyManager.h"
#include "Enemy.h"
#include "MapTileInfo.h"

HRESULT EnemyManager::Init()
{
	for (int i = 0; i < 1; i++)
	{
		Enemy* enemy = new Enemy();
		enemy->Init();
		stEnemies.push(enemy);
	}
	tiles = MapTileInfo::GetSingleton()->GetTileMap();
	return S_OK;
}

void EnemyManager::Release()
{
	for (auto& it : enemies)
	{
		it->Release();
		SAFE_DELETE(it);
	}
	enemies.clear();
	for (int i = 0; i < enemyCount; i++)
	{
		if (stEnemies.empty())
			break;
		stEnemies.pop();
	}
}

void EnemyManager::Update()
{
	if (enemies.size() > 0)
	{
		for (auto& it : enemies)
		{
			it->Update();
		}
	}
}

void EnemyManager::Render(HDC hdc)
{
	if (enemies.size() > 0)
	{
		for (auto& it : enemies)
		{
			it->Render(hdc);
		}
	}
}

// A_Star 경로 설정
void EnemyManager::SetAstarPath(list<pair<int, int>>* _astar)
{
	for (auto it = enemies.begin(), end = enemies.end(); it != end; it++)
	{
		if ((*it)->GetIsSpawn() == false)
		{
			astar = _astar;
			astar->push_back(astar->back());
			astar->reverse();
			(*it)->SetIsSpawn(true);
		}
	}
}

void EnemyManager::SetEnemy(int id, TILE_NUM_INFO _pos)
{
	if (!stEnemies.empty())
	{
		string* enemyName = UnitDataBase::GetSingleton()->GetEnemyIdInfo(id);
		Enemy* spawneEnemy = stEnemies.top();
		stEnemies.pop();
		POINT pos = { tiles[_pos.idY][_pos.idX].x, tiles[_pos.idY][_pos.idX].y };
		spawneEnemy->SetEnemy(pos, enemyName);
		spawneEnemy->SetIsRender(true);
		enemies.push_back(spawneEnemy);
	}
}

void EnemyManager::WaveStart()
{

	for (auto it = enemies.begin(), end = enemies.end(); it != end; it++)
	{
		if ((*it)->GetIsAstar() == false)
		{
			for (auto astarIt = astar->begin(), end = astar->end(); astarIt != end; astarIt++)
			{
				int idX = astarIt->first;
				int idY = astarIt->second;

				(*it)->SaveDestOrder(tiles[idY][idX].x, tiles[idY][idX].y);
				if ((*it)->GetIsRender() == false)
				{
					(*it)->SetIsRender(true);
				}
			}
			(*it)->destOrder.pop_back();
			(*it)->SetIsAstar(true);
		}
	}
}

