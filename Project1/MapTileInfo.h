#pragma once
#include "SingletonBase.h"
#include "pch.h"

/// <summary>
/// MapTileInfo : 게임 내 타워 배치가 가능한 구역 간 타워 배치가 가능한 타일들을 배치해주는 클래스.
/// </summary>
class MapTileInfo : public SingletonBase<MapTileInfo>
{
private:
	ISOTILE** tiles;
public:
	HRESULT Init();
	void Release();

	ISOTILE** GetTileMap() { return tiles; }
};

