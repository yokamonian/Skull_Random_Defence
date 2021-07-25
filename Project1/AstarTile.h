#pragma once
#include "GameNode.h"


class Skull;
/// <summary>
/// AstarTile : MapTileInfo�� Ÿ�� ������ ������� Astar�˰��� ������ ���� Ÿ�� ���� ������ ��� Ŭ����.
///				���� Ÿ�� ������ ��� �ִ�.
/// </summary>
class AstarTile : public GameNode
{
private:
	int idX, idY;
	RECT rc;

	float totalCost;//F
	float costFromStart;//G, ���������� ���� �������� ��� 
	float costToGoal;//H���� ��忡�� ���� �������� ���� ��� ���
	POINT pos;
	AstarTile* parentTile;
	
	string attribute;// �Ӽ��� ���� 
	COLORREF color;
	HBRUSH	brush;
	HPEN pen;


	Skull* pickSkull = nullptr;


public:
	virtual HRESULT Init();
	HRESULT Init(int _idX, int _idY);// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		   // �޸� ����
	virtual void Update();		   // ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

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

