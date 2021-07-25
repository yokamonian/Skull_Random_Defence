#pragma once
#include "GameObject.h"
#include "Storage.h"

// ���� ���۱���
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
	int damage;			        // ������
	int abilityPower;	        // ����
	int attackSpeed;	        // ��ų ������
	int skillCount;		        // ��ų�� �ʿ��� Ÿ�ݼ�
	int growthDmg;		        // ���� ������(ų)
	int growthAp;		        // ���� ��ų ������(ų)
	int upgradeDmg;		        // ���޾� ������
	int upgradeAp;		        // ���޾� ����
	int upgradeAs;		        // ���޾� ��ų�� �ʿ��� Ÿ�ݼ�
	int upgradeSc;		        // ���޾� ��ų������
	int idleFrame;		        // �⺻ ���� �ִϸ��̼� ������
	int attackFrame;	        // ���� ���� �ִϸ��̼� ������
	int skillFrame;		        // ��ų ���� �ִϸ��̼� ������
	Image* img;			        // ���� �̹��� �̸�
	SkullData* info;	        // ���� ����
	AstarTile* nowTile;         // ���� ���� ��ġ
	ISOTILE* nowSkullTile;	    // ������ �����ϴ� Ÿ�� ��ġ
	bool isSelected = false;	// (������)���õǾ�����
	Storage* storage;			// ���� �������
	SKULLMode skullMode;		// ������ ���ۻ���
	POINT prevPos;				// ������ ���� ��ġ
	POINT fieldPos;				// �ʵ� ��ġ
public:
	virtual HRESULT Init();
	// ���� ���� ����
	void SetSkull(TILE_NUM_INFO buildPos, string* skullName);
	void SetSkull(POINT pos, string* skullName);
	// ���� ��ġ ���� �� �̵�
	void SetPrevPos(POINT _prevPos) { prevPos = _prevPos; }
	void SetPos(POINT _pos) { pos = _pos; }
	void SetPos(int posX, int posY) { pos.x = posX; pos.y = posY; }
	void SetSelected(bool _isSelected) { isSelected = _isSelected; }
	void SetFieldPos(POINT _pos) { fieldPos = _pos; }
	// ��������� ����
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

