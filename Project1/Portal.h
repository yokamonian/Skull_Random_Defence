#pragma once
#include "GameObject.h"

class Portal : public GameObject
{
private:
	POINT pos;		// 위치
	Image* img;		// 이미지
	int hp;			// 체력

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void OnHit(int damage) { SetDamaged(damage); }					// 데미지 판정
	void SetDamaged(int damage) { hp -= damage; }					// 피격 처리
	void SetPos(int posX, int posY) { pos.x = posX; pos.y = posY; }	// 위치 조정
};

