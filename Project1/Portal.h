#pragma once
#include "GameObject.h"

class Portal : public GameObject
{
private:
	POINT pos;
	Image* img;
	int hp;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void OnHit(int damage) { SetDamaged(damage); }
	void SetDamaged(int damage) { hp -= damage; }
	void SetPos(int posX, int posY) { pos.x = posX; pos.y = posY; }
};

