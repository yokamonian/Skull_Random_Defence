#include "AstarTile.h"

HRESULT AstarTile::Init()
{

	color = RGB(250, 100, 50);
	brush = CreateSolidBrush(color);

	pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	//pos.x

	pickSkull = nullptr;


	return S_OK;
}

HRESULT AstarTile::Init(int _idX, int _idY)
{
	parentTile = nullptr;
	// 경로 표기 선 색상 지정
	color = RGB(250, 100, 50);
	brush = CreateSolidBrush(color);

	pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	idX = _idX;
	idY = _idY;

	// 타일 초기화
	for (int i = 0; i < ISO_TILE_Y; i++)
	{
		if (i == idY)
		{
			if (i % 2 == 0)
				pos.x = ISO_START_X + (idX * ISO_TILE_SIZE_X);
			else if (i % 2 == 1)
				pos.x = ISO_START_X + (idX * ISO_TILE_SIZE_X) - ISO_TILE_HALF_SIZE_X;
			pos.y = ISO_START_Y + (i * ISO_TILE_SIZE_Y / 2);
		}
	}
	rc = GetRectToCenter(pos.x, pos.y, ISO_TILE_SIZE_X, ISO_TILE_SIZE_Y);


	return S_OK;
}

void AstarTile::Release()
{
	DeleteObject(brush);
	DeleteObject(pen);
}

void AstarTile::Update()
{
}

void AstarTile::Render(HDC hdc)
{
	SelectObject(hdc, brush);
	FillRect(hdc, &rc, brush);

	SelectObject(hdc, pen);
	RenderRect(hdc, pos.x - (ISO_TILE_HALF_SIZE_X), pos.y - (ISO_TILE_HALF_SIZE_Y), ISO_TILE_SIZE_X);
}

AstarTile::AstarTile()
{
}

AstarTile::~AstarTile()
{
}
