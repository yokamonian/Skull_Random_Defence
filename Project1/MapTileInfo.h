#pragma once
#include "SingletonBase.h"
#include "pch.h"

class MapTileInfo : public SingletonBase<MapTileInfo>
{
private:
	ISOTILE** tiles;
public:
	HRESULT Init();
	void Release();

	ISOTILE** GetTileMap() { return tiles; }
};

