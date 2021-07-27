#pragma once
#include "GameNode.h"


class Skull;
/// <summary>
/// AstarTile : MapTileInfo의 타일 정보를 기반으로 Astar알고리즘 실행을 위한 타일 각개 정보를 담는 클래스.
///				단일 타일 정보를 담고 있다.
/// </summary>
class AstarTile : public GameNode
{
private:
	int idX, idY;
	RECT rc;

	float totalCost;//F
	float costFromStart;//G, 시작점에서 련재 노드까지의 비용 
	float costToGoal;//H현재 노드에서 도착 노드까지의 예상 경로 비용
	POINT pos;
	AstarTile* parentTile;
	
	string attribute;// 속성의 정보 
	COLORREF color;
	HBRUSH	brush;
	HPEN pen;


	Skull* pickSkull = nullptr;


public:
	virtual HRESULT Init();
	HRESULT Init(int _idX, int _idY);// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		   // 메모리 해제
	virtual void Update();		   // 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	void SetTotalCost(float cost) { totalCost = cost; }
	void SetCostFromStart(float cost) { costFromStart = cost; }
	void SetCostToGoal(float cost) { costToGoal = cost; }

	void SetAttribute(string _attribute) { attribute = _attribute; }
	void SetColor(COLORREF _color) {
		DeleteObject(brush);

		color = _color;
		brush = CreateSolidBrush(color);
	}
	int GetIdX() { return idX; }
	int GetIdY() { return idY; }

	RECT GetRect() { return rc; }
	string GetAttribute() { return attribute; }
	void SetParentTile(AstarTile* _parentTile) { parentTile = _parentTile; }
	AstarTile* GetParentTile() { return parentTile; }
	float GetCostFromStart() { return costFromStart; }

	void SetSkull(Skull* _skull) { pickSkull = _skull; }
	Skull* GetSkullInfo() { return pickSkull; }

	AstarTile();
	virtual~AstarTile();
};

