#pragma once
#include "SingletonBase.h"
#include "AstarTile.h"
#include <vector>

class AstarTile;
/// <summary>
/// AstarScene : Astar알고리즘 클래스.
///				 게임 스테이지 타일 정보를 통해 목적지(Portal)까지 경로를 만들어주는 
///				 알고리즘 기반 클래스.
/// </summary>
class AstarScene : public SingletonBase<AstarScene>
{
private:
	vector<AstarTile*> vecTiles;		// 모든 타일
	AstarTile* startTile;				// 시작 타일
	AstarTile* endTile;					// 도착 타일
	AstarTile* currTile;				// 현재 타일

	bool isWall[ISO_TILE_X*ISO_TILE_Y]; // 타일속성이 '벽'인지
	vector<AstarTile*>  openList;		// 탐색리스트
	vector<AstarTile*>  closeList;		// 지나온 타일리스트

	list<pair<int, int>> Route;			// 확정된 경로의 번호
	bool isFinish;						// 도착여부
	int routeNum;						// 도착까지 지나온 타일 수

public:
	HRESULT Init();						// 멤버 변수 초기화, 메모리 할당
	HRESULT Init(TILE_NUM_INFO start);	// 지정된 시작점으로부터의 Init
	void Release();						// 메모리 해제

	void FindPath(AstarTile* currTile);	// 경로 탐색 함수
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