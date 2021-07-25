#pragma once
#include "GameObject.h"

/// <summary>
/// Portal : ���� �� ������ ���� ������Ʈ Ŭ����.
/// </summary>
class Portal : public GameObject
{
private:
	POINT pos;		// ��ġ
	Image* img;		// �̹���
	int hp;			// ü��

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void OnHit(int damage) { SetDamaged(damage); }					// ������ ����
	void SetDamaged(int damage) { hp -= damage; }					// �ǰ� ó��
	void SetPos(int posX, int posY) { pos.x = posX; pos.y = posY; }	// ��ġ ����
};

