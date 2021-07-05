#pragma once
#include "GameObject.h"
#include "pch.h"
#include <utility>

enum class EnemyMode
{
	IDLE,
	ATTACK,
	DIE
};


class StageScene;
class Portal;
class Enemy : protected GameObject
{
private:
	int damage;
	int attackSpeed;
	int moveSpeed;
	int healthPoint;
	int effectFrameX;
	float distX = 0;
	float distY = 0;
	int idleFrame;
	int attackFrame;
	int dieFrame;
	int EffectFrame;
	bool isRender;
	bool isFire = false;
	string effect;
	float timeAmount;
	float time;
	Image* enemyImg;
	Image* attackImg;
	FPOINT destpos;
	FPOINT startpos;
	POINT PortalPos;
	FPOINT fPos;
	EnemyMode e_Mode;
	RECT target;
	ENEMYDATA* enemy;
	bool isSpawn = false;
	bool isAstar = false;
	bool isAttack = false;
public:
	vector<pair<int, int>> destOrder;
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetEnemy(POINT spawnPos, string* Name);
	void SetAstarPos(int posX, int posY) { pos.x = posX; pos.y = posY; destpos.x = posX; destpos.y = posY; }
	void SetPos(POINT _pos) { pos.x = _pos.x; pos.y = _pos.y; };
	void SetIsRender(bool b) { isRender = b; }
	POINT GetPos() { return pos; }
	bool GetIsRender() { return isRender; }
	void SaveDestOrder(int X, int Y) { destOrder.push_back(make_pair(X, Y)); }
	float GetTime(FPOINT startpos, FPOINT destpos);
	void SetAttackMode(bool isAttack)
	{
		if (isAttack)
			e_Mode = EnemyMode::ATTACK;
		else
			e_Mode = EnemyMode::IDLE;
	}
	void frameByMode();
	void MoveAstar();
	void EnemyBehavior();
	bool GetIsSpawn() { return isSpawn; }
	void SetIsSpawn(bool _isSpawn) { isSpawn = _isSpawn; }
	bool GetIsAstar() { return isAstar; }
	void SetIsAstar(bool _isAstar) { isAstar = _isAstar; }

};

