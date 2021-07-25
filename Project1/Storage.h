#pragma once
#include "pch.h"

class Skull;
/// <summary>
/// Storage : 게임 내 스컬의 보관소 클래스.
/// </summary>
class Storage
{
private:
	POINT storagePos;	// 저장소 위치
	bool isEmpty;		// 비어있는 지 여부
	int id;				// 칸 번호
	RECT storageRc;		// 저장소 칸의 판정 범위
	Skull* skullTile;	// 스컬
public:
	void SetIsEmpty(bool _isEmpty) { isEmpty = _isEmpty; }
	bool GetIsEmpty() { return isEmpty; }
	void SetStoragePos(int posX, int posY) { storagePos = { posX, posY }; }
	POINT GetStoragePos() { return storagePos; }
	void SetStorageRect(int posX, int posY, int width, int height)
	{
		storageRc = GetRectToCenter(posX, posY, width, height);
	}
	void SetStorageId(int idX) { id = idX; }
	int GetStorageId() { return id; }
	RECT GetStorageRect() { return storageRc; }
	void SetSkullTile(Skull* skull) 
	{ 
		skullTile = skull; 
		if (skull == nullptr)
			isEmpty = true;
		else
			isEmpty = false;
	}
	Skull* GetSkullTile() { return skullTile; }
	bool CheckTile()
	{
		if (skullTile == nullptr)
			return false;
		return true;
	}
	Storage();
	~Storage();
};

