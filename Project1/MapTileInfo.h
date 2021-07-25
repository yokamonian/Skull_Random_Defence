#pragma once
#include "SingletonBase.h"
#include "pch.h"

/// <summary>
/// MapTileInfo : ���� �� Ÿ�� ��ġ�� ������ ���� �� Ÿ�� ��ġ�� ������ Ÿ�ϵ��� ��ġ���ִ� Ŭ����.
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

