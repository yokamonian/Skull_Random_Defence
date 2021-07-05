 #pragma once
#include "GameNode.h"
class Card : public GameNode
{
private:
	RECT card;
	POINT pos;
	int skullId;
	int price;
	int currFrameX;
	int currFrameY;

	Image* img;
public:
	virtual HRESULT Init();
	HRESULT Init(POINT pos);
	virtual void Release();
	virtual	void Render(HDC hdc);

	int GetPrice() { return price; }
	RECT GetCardRect() { return card; }
	void PerchaseCard();
	void RerollCard();
	void SetCurrFrameY(int _currFrameY) { currFrameY = _currFrameY; }
	void SetPos(POINT _pos) { pos.x = _pos.x; pos.y = _pos.y; }
	void ShuffleCard(int skullId);
	int GetSkullId() { return skullId; }
	int GetCurrFrameY() { return currFrameY; }
};

