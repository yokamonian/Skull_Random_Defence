#include "MapTileInfo.h"


HRESULT MapTileInfo::Init()
{

	tiles = new ISOTILE*[ISO_TILE_Y];


	for (int i = 0; i < ISO_TILE_Y; i++)
	{
		tiles[i] = new ISOTILE[ISO_TILE_X];
	}

	for (int i = 0; i < ISO_TILE_Y; i++)
	{
		for (int j = 0; j < ISO_TILE_X; j++)
		{
			if (i % 2 == 0)
			{
				tiles[i][j].x = ISO_START_X + ((j + 1) * ISO_TILE_SIZE_X);

			}
			else if ((i % 2 == 1))
			{
				tiles[i][j].x = ISO_START_X + ((j + 1) * ISO_TILE_SIZE_X) - ISO_TILE_HALF_SIZE_X;
			}

			tiles[i][j].y = ISO_START_Y + (i * ISO_TILE_HALF_SIZE_Y);
			tiles[i][j].rc = { tiles[i][j].x - ISO_TILE_HALF_SIZE_X, tiles[i][j].y - ISO_TILE_HALF_SIZE_Y,
			 tiles[i][j].x + ISO_TILE_HALF_SIZE_X, tiles[i][j].y + ISO_TILE_HALF_SIZE_Y };
			tiles[i][j].tileNum = j + (i * 5);
		}
	}
	return S_OK;
}

void MapTileInfo::Release()
{
	for (int i = 0; i < ISO_TILE_X; i++)
	{
		delete[] tiles[i];
	}
	delete [] tiles;
}
