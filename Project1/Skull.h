#pragma once
#include "GameObject.h"
#include "Storage.h"

// 스컬 동작구분
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
	int damage;			        // 데미지
	int abilityPower;	        // 공속
	int attackSpeed;	        // 스킬 데미지
	int skillCount;		        // 스킬에 필요한 타격수
	int growthDmg;		        // 성장 데미지(킬)
	int growthAp;		        // 성장 스킬 데미지(킬)
	int upgradeDmg;		        // 성급업 데미지
	int upgradeAp;		        // 성급업 공속
	int upgradeAs;		        // 성급업 스킬에 필요한 타격수
	int upgradeSc;		        // 성급업 스킬데미지
	int idleFrame;		        // 기본 동작 애니메이션 프레임
	int attackFrame;	        // 공격 동작 애니메이션 프레임
	int skillFrame;		        // 스킬 동작 애니메이션 프레임
	Image* img;			        // 스컬 이미지 이름
	SkullData* info;	        // 스컬 정보
	AstarTile* nowTile;         // 스컬 현재 위치
	ISOTILE* nowSkullTile;	    // 스컬이 존재하는 타일 위치
	bool isSelected = false;	// (스컬이)선택되었는지
	Storage* storage;			// 스컬 저장공간
	SKULLMode skullMode;		// 스컬의 동작상태
	POINT prevPos;				// 스컬의 이전 위치
	POINT fieldPos;				// 필드 위치
public:
	virtual HRESULT Init();
	// 유닛 정보 세팅
	void SetSkull(TILE_NUM_INFO buildPos, string* skullName);
	void SetSkull(POINT pos, string* skullName);
	// 유닛 위치 세팅 및 이동
	void SetPrevPos(POINT _prevPos) { prevPos = _prevPos; }
	void SetPos(POINT _pos) { pos = _pos; }
	void SetPos(int posX, int posY) { pos.x = posX; pos.y = posY; }
	void SetSelected(bool _isSelected) { isSelected = _isSelected; }
	void SetFieldPos(POINT _pos) { fieldPos = _pos; }
	// 유닛저장소 세팅
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

