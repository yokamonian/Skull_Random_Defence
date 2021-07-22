#pragma once
#include "GameObject.h"
#include "pch.h"
#include <utility>

// �� ������ ����
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
	int damage;				// ������
	int attackSpeed;		// ����
	int moveSpeed;			// �̼�
	int healthPoint;		// ü��
	int effectFrameX;		// ����Ʈ ������ ������
	float distX = 0;		// x�� �Ÿ�
	float distY = 0;		// y�� �Ÿ�
	int idleFrame;			// �⺻ ���� ������
	int attackFrame;		// ���� ���� ������
	int dieFrame;			// ��� ���� ������
	int EffectFrame;		// ����Ʈ ������ ��
	bool isRender;
	bool isFire = false;
	string effect;			// ����Ʈ �̸�
	float timeAmount;
	float time;
	Image* enemyImg;
	Image* attackImg;
	FPOINT destpos;			// ������
	FPOINT startpos;		// �����
	POINT PortalPos;		// ��Ż ��ġ
	FPOINT fPos;
	EnemyMode e_Mode;		// ���� ����
	RECT target;			// ���� ��ǥ
	ENEMYDATA* enemy;
	bool isSpawn = false;
	bool isAstar = false;	// �˰��� ���� ����
	bool isAttack = false;	// Ÿ�� ����
public:
	vector<pair<int, int>> destOrder; // ��ǥ ��ǥ
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetEnemy(POINT spawnPos, string* Name); // �� ���� ����
	void SetAstarPos(int posX, int posY)		 // ��ǥ ��� �˰��� ����
	{ pos.x = posX; pos.y = posY; destpos.x = posX; destpos.y = posY; }
	void SetPos(POINT _pos) { pos.x = _pos.x; pos.y = _pos.y; }; // ���� ��ġ��
	void SetIsRender(bool b) { isRender = b; }
	POINT GetPos() { return pos; }
	bool GetIsRender() { return isRender; }
	void SaveDestOrder(int X, int Y) { destOrder.push_back(make_pair(X, Y)); } // ������ ����
	float GetTime(FPOINT startpos, FPOINT destpos);
	void SetAttackMode(bool isAttack)
	{
		if (isAttack)
			e_Mode = EnemyMode::ATTACK;
		else
			e_Mode = EnemyMode::IDLE;
	}
	void frameByMode();		// ���� ���¿� ���� ������ ����
	void MoveAstar();		// �� �̵� ���� ����
	void EnemyBehavior();	// �� ���� ���� ����
	bool GetIsSpawn() { return isSpawn; }
	void SetIsSpawn(bool _isSpawn) { isSpawn = _isSpawn; }
	bool GetIsAstar() { return isAstar; }
	void SetIsAstar(bool _isAstar) { isAstar = _isAstar; }

};

