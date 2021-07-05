#include "Portal.h"
#include "Image.h"


HRESULT Portal::Init()
{
	img = ImageManager::GetSingleton()->AddImage("Æ÷Å»", "Image/Æ÷Å».bmp", 0, 0, 720, 80, 9, 1, true, RGB(0, 0, 0));
	hp = 10;
	frame = 0;
	currFrameX = currFrameY = 0;
	return S_OK;
}

void Portal::Release()
{
}

void Portal::Update()
{
	frame++;
	if (frame % 5 == 4)
	{ 
		currFrameX++;
		frame = 0;
	}
	if (currFrameX == 9)
		currFrameX = 0;
}

void Portal::Render(HDC hdc)
{
	if (img)
		img->FrameRender(hdc, pos.x, pos.y - 21, currFrameX, 0);
}
