#pragma once
#include "SingletonBase.h"
#include "AstarTile.h"
#include <vector>

class AstarTile;
/// <summary>
/// AstarScene : Astar�˰��� Ŭ����.
///				 ���� �������� Ÿ�� ������ ���� ������(Portal)���� ��θ� ������ִ� 
///				 �˰��� ��� Ŭ����.
/// </summary>
class AstarScene : public SingletonBase<AstarScene>
{
private:
	vector<AstarTile*> vecTiles;		// ��� Ÿ��
	AstarTile* startTile;				// ���� Ÿ��
	AstarTile* endTile;					// ���� Ÿ��
	AstarTile* currTile;				// ���� Ÿ��

	bool isWall[ISO_TILE_X*ISO_TILE_Y]; // Ÿ�ϼӼ��� '��'����
	vector<AstarTile*>  openList;		// Ž������Ʈ
	vector<AstarTile*>  closeList;		// ������ Ÿ�ϸ���Ʈ

	list<pair<int, int>> Route;			// Ȯ���� ����� ��ȣ
	bool isFinish;						// ��������
	int routeNum;						// �������� ������ Ÿ�� ��

public:
	HRESULT Init();						// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	HRESULT Init(TILE_NUM_INFO start);	// ������ ���������κ����� Init
	void Release();						// �޸� ����

	void FindPath(AstarTile* currTile);	// ��� Ž�� �Լ�
	list<pair<int, int>>* StartAstar(TILE_NUM_INFO start); 
	void AddOpenList(AstarTile* _currtile);
	void AddWall(int idx);
	void AddWall(AstarTile* _currtile);
	void MoveWall(int idx, int moveIdx);
	void MoveWall(AstarTile* _currtile, AstarTile* _moveTile);
	void CheckWall();
	list<pair<int, int>>* GetDestOrder() { return &Route; }

	AstarScene();
	virtual ~AstarScene();
};