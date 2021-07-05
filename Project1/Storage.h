#pragma once
#include "pch.h"

class Skull;
class Storage
{
private:
	POINT storagePos;
	bool isEmpty;
	int id;
	RECT storageRc;
	Skull* skullTile;
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

