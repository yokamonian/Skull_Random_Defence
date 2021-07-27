#include "Card.h"
#include "pch.h"
#include "Image.h"

HRESULT Card::Init()
{
	return S_OK;
}

HRESULT Card::Init(POINT pos)
{
	pos = { pos.x, pos.y };
	card = { pos.x - 33, pos.y - 35, pos.x + 33, pos.y + 35 };


	currFrameX = 0;
	currFrameY = 0;

	return S_OK;
}

void Card::Release()
{
}

void Card::Render(HDC hdc)
{
	if(img)
	img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
}

void Card::PerchaseCard()
{
	if (currFrameY == 0)
		currFrameY = 1;
}

void Card::RerollCard()
{
	currFrameY = 0;
	int idx = rand() % 3;
	ShuffleCard(idx);
	skullId = idx;
}

void Card::ShuffleCard(int _skullId)
{

	switch (_skullId)
	{
	case 0:
		img = ImageManager::GetSingleton()->AddImage("지니카드", "Image/지니카드.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("지니카드");
		price = 110;
		skullId = 0;
		break;
	case 1:
		img = ImageManager::GetSingleton()->AddImage("약탈자카드", "Image/약탈자카드.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("약탈자카드");
		price = 130;
		skullId = 1;
		break;
	case 2:
		img = ImageManager::GetSingleton()->AddImage("그림리퍼카드", "Image/그림리퍼카드.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("그림리퍼카드");
		price = 150;
		skullId = 2;
		break;
	case 3:
		img = ImageManager::GetSingleton()->AddImage("카드", "Image/랜덤카드.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("카드");
		price = 30;
	}
}
