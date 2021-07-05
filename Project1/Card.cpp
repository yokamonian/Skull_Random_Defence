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
		img = ImageManager::GetSingleton()->AddImage("����ī��", "Image/����ī��.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("����ī��");
		price = 110;
		skullId = 0;
		break;
	case 1:
		img = ImageManager::GetSingleton()->AddImage("��Ż��ī��", "Image/��Ż��ī��.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("��Ż��ī��");
		price = 130;
		skullId = 1;
		break;
	case 2:
		img = ImageManager::GetSingleton()->AddImage("�׸�����ī��", "Image/�׸�����ī��.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("�׸�����ī��");
		price = 150;
		skullId = 2;
		break;
	case 3:
		img = ImageManager::GetSingleton()->AddImage("ī��", "Image/����ī��.bmp", 0, 0, 61, 160, 1, 2, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->FindImage("ī��");
		price = 30;
	}
}
