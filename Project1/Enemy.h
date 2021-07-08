#pragma once
#include "GameObject.h"
#include "pch.h"
#include <utility>

// 적 유닛의 상태
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
	int damage;				// 데미지
	int attackSpeed;		// 공속
	int moveSpeed;			// 이속
	int healthPoint;		// 체력
	int effectFrameX;		// 이펙트 프레임 시작점
	float distX = 0;		// x축 거리
	float distY = 0;		// y축 거리
	int idleFrame;			// 기본 동작 프레임
	int attackFrame;		// 공격 동작 프레임
	int dieFrame;			// 사망 동작 프레임
	int EffectFrame;		// 이펙트 프레임 수
	bool isRender;
	bool isFire = false;
	string effect;			// 이펙트 이름
	float timeAmount;
	float time;
	Image* enemyImg;
	Image* attackImg;
	FPOINT destpos;			// 도착점
	FPOINT startpos;		// 출발점
	POINT PortalPos;		// 포탈 위치
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

