#include "UnitDataBase.h"
#include <utility>

HRESULT UnitDataBase::Init()
{
	AddSkullInfo(5, 2, 10, 5, 1, 1, 7, 1, 15, 1, 4, 7, 9, "지니", 0);
	AddSkullInfo(15, 3, 20, 6, 2, 3, 12, 2, 30, 1, 6, 6, 7, "약탈자", 1);
	AddSkullInfo(35, 4, 50, 7, 3, 5, 20, 3, 70, 2, 5, 9, 12, "그림리퍼", 2);
	AddEnemyInfo(5, 20, 100, 100, 4, 4, 2, "적_법사", 0, "적_법사_공격이펙트");
	return S_OK;
}

void UnitDataBase::Release()
{

}

void UnitDataBase::AddSkullInfo(int damage, int attackSpeed, int abilityPower, int skillCount, int growthDmg,
	int growthAp, int upgradeDmg, int upgradeAs, int upgradeSc, int upgradeAp, 
	int idleFrame, int attackFrame, int skillFrame, string skullName , int skullId)
{
	/*SkullData* skull = { damage, attackSpeed, abilityPower, skillCount, growthDmg, growthAp, upgradeDmg, upgradeAs,
		upgradeSc, upgradeAp, idleFrame, attackFrame, skillFrame, skullName};*/
	SkullData* skull = new SkullData();
	skull->damage = damage;
	skull->attackSpeed = attackSpeed;
	skull->abilityPower = abilityPower;
	skull->skillCount = skillCount;
	skull->growthDmg = growthDmg;
	skull->growthAp = growthAp;
	skull->upgradeDmg = upgradeDmg;
	skull->upgradeAs = upgradeAs;
	skull->upgradeSc = upgradeSc;
	skull->upgradeAp = upgradeAp;
	skull->idleFrame = idleFrame;
	skull->attackFrame = attackFrame;
	skull->skillFrame = skillFrame;
	skull->skullName = skullName;

	Skulls.insert(make_pair(skullName, skull));
	SkullIds.insert(make_pair(skullId, skullName));
}

void UnitDataBase::AddEnemyInfo(int damage, int attackSpeed, int moveSpeed, int healthPoint,
	int idleFrame, int attackFrame, int dieFrame, string enemyName, int id, string effectName)
{
	EnemyData* enemy = new EnemyData();
	enemy->damage = damage;
	enemy->attackSpeed = attackSpeed;
	enemy->moveSpeed = moveSpeed;
	enemy->healthPoint = healthPoint;
	enemy->idleFrame = idleFrame;
	enemy->attackFrame = attackFrame;
	enemy->dieFrame = dieFrame;
	enemy->enemyName = enemyName;
	enemy->id = id;
	enemy->EffectName = effectName;
	Enemies.insert(make_pair(enemyName, enemy));
	EnemyIds.insert(make_pair(id, enemyName));

}

SkullData * UnitDataBase::GetSkullInfo(string skullName)
{
	SkullData* skull = Skulls.find(skullName)->second;
	return skull;
}

ENEMYDATA * UnitDataBase::GetEnemyInfo(string enemyName)
{
	ENEMYDATA* enemy = Enemies.find(enemyName)->second;
	return enemy;
}

string * UnitDataBase::GetSkullImgInfo(string skullName)
{
	SKULLDATA* skull = Skulls.find(skullName)->second;
	return &(skull->skullName);
}

string * UnitDataBase::GetSkullIdInfo(int id)
{
	return &(SkullIds.find(id)->second);
}

string * UnitDataBase::GetEnemyIdInfo(int id)
{
	return &(EnemyIds.find(id)->second);
}
