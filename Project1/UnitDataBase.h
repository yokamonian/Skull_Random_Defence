#pragma once
#include "SingletonBase.h"
#include "pch.h"

/// <summary>
/// UnitDataBase : ���� �� �����ϴ� ��� ������ �Ʊ��� ������ �����ϴ� Ŭ����.
/// </summary>
class Image;
class UnitDataBase : public SingletonBase <UnitDataBase>
{
private:
	map<string, SkullData*> Skulls;
	map<string, EnemyData*> Enemies;
	map<int, string> SkullIds;
	map<int, string> EnemyIds;
public: 
	HRESULT Init();
	void Release();
	void AddSkullInfo(int damage, int attackSpeed, int abilityPower, int skillCount, int growthDmg,
		int growthAp, int upgradeDmg, int upgradeAs, int upgradeSc, int upgradeAp, int idleFrame, int attackFrame,
		int skillFrame, string skullName, int skullId);
	void AddEnemyInfo(int damage, int attackSpeed, int moveSpeed, int healthPoint, int idleFrame, int attackFrame,
		int dieFrame, string EnemyName, int id, string effectName);
	SKULLDATA* GetSkullInfo(string skullName);
	ENEMYDATA* GetEnemyInfo(string enemyName);
	string* GetSkullImgInfo(string skullName);
	string* GetSkullIdInfo(int id);
	string* GetEnemyIdInfo(int id);
};

