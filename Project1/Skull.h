#pragma once
#include "GameObject.h"
#include "Storage.h"

enum class SKULLMode
{
	IDLE,
	ATTACK,
	SKILL
};


class AstarTile;
class Skull : public GameObject
{
private:
	int damage;
	int abilityPower;
	int attackSpeed;
	int skillCount;
	int growthDmg;
	int growthAp;
	int upgradeDmg;
	int upgradeAp;
	int upgradeAs;
	int upgradeSc;
	int idleFrame;
	int attackFrame;
	int skillFrame;
	Image* img;
	SkullData* info;
	AstarTile* nowTile;
	ISOTILE* nowSkullTile;
	bool isSelected = false;
	Storage* storage;
	SKULLMode skullMode;
	POINT prevPos;
	POINT fieldPos;
public:
	virtual HRESULT Init();
	void SetSkull(TILE_NUM_INFO buildPos, string* skullName);
	void SetSkull(POINT pos, string* skullName);
	void SetPrevPos(POINT _prevPos) { prevPos = _prevPos; }
	void SetPos(POINT _pos) { pos = _pos; }
	void SetPos(int posX, int posY) { pos.x = posX; pos.y = posY; }
	void SetSelected(bool _isSelected) { isSelected = _isSelected; }
	void SetFieldPos(POINT _pos) { fieldPos = _pos; }
	void SetStorage(Storage* _storage) 
	{ 
		if (_storage == nullptr && storage != nullptr) 
		{
			if (storage->GetSkullTile() == nullptr)
				storage->SetIsEmpty(true);
		}
		storage = _storage;
		storage->SetSkullTile(this);
		storage->SetIsEmpty(false);
	}
	Storage* GetStorage() { return storage; }
	POINT GetFieldPos() { return fieldPos; }
	POINT GetPrevPos() { return prevPos; }
	void SetNowTile(AstarTile* astar) { nowTile = astar; }
	AstarTile* GetSkullPos() { return nowTile; }
	void SetNowSkullTile(ISOTILE* _skull) { nowSkullTile = _skull; }
	ISOTILE* GetSkullTile() { return nowSkullTile; }
	bool GetIsSelected() { return isSelected; }
	virtual void Release();
	virtual	void Update();
	virtual	void Render(HDC hdc);
};

