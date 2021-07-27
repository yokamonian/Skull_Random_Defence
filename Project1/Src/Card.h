 #pragma once
#include "GameNode.h"
class Card : public GameNode
{
	
	/// <summary>
	/// Card : 게임 내 스컬을 구매하기 위한 UI 중 하나의 클래스.
	///			인게임 재화인 골드를 통해 구매하거나 섞는 등의 함수가 담겨있다.
	/// </summary>
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

