#include "AStarScene.h"
#include "AstarTile.h"
#include "pch.h"

HRESULT AstarScene::Init()
{
	// 시작점
	startTile = new AstarTile();
	startTile->Init(0, 0);
	startTile->SetAttribute("start");
	// 도착지점
	endTile = new AstarTile();
	endTile->Init(2, 5);
	endTile->SetAttribute("end");

	// 초기세팅
	currTile = startTile;
	routeNum = 0;
	isFinish = false;
	vecTiles.reserve(ISO_TILE_X*ISO_TILE_Y);

	for (int i = 0; i < ISO_TILE_Y; i++)
	{
		for (int j = 0; j < ISO_TILE_X; j++)
		{
			// 시작 타일인지
			if (j == startTile->GetIdX() && i == startTile->GetIdY())
			{
				vecTiles.push_back(startTile);
				continue;
			}

			// 도착 타일인지
			if (j == endTile->GetIdX() && i == endTile->GetIdY())
			{
				vecTiles.push_back(endTile);
				continue;
			}

			AstarTile* tile = new AstarTile();
			tile->Init(j, i);
			tile->SetAttribute("");
			//CheckWall();
			vecTiles.push_back(tile);
			if (i % 2 == 0)
			{
				if (j == 4)
				{
					tile->SetAttribute("wall");
				}
			}
		}
	}
	return S_OK;
}

HRESULT AstarScene::Init(TILE_NUM_INFO start)
{
	startTile = new AstarTile();
	startTile->Init(start.idX, start.idY);
	startTile->SetAttribute("start");

	endTile = new AstarTile();
	endTile->Init(2, 5);
	endTile->SetAttribute("end");

	currTile = startTile;
	routeNum = 0;
	isFinish = false;
	vecTiles.reserve(ISO_TILE_X*ISO_TILE_Y);

	for (int i = 0; i < ISO_TILE_Y; i++)
	{
		for (int j = 0; j < ISO_TILE_X; j++)
		{
			// 시작 타일인지
			if (j == startTile->GetIdX() && i == startTile->GetIdY())
			{
				vecTiles.push_back(startTile);
				continue;
			}

			// 도착 타일인지
			if (j == endTile->GetIdX() && i == endTile->GetIdY())
			{
				vecTiles.push_back(endTile);
				continue;
			}

			AstarTile* tile = new AstarTile();
			tile->Init(j, i);
			tile->SetAttribute("");
			vecTiles.push_back(tile);
			if (i % 2 == 0)
			{
				if (j == 4)
				{
					tile->SetAttribute("wall");
					isWall[j + (j * i)] = true;
				}
			}
		}

	}
	for (int i = 0; i < ISO_TILE_X * ISO_TILE_Y; i++)
	{
		isWall[i] = false;
	}
	return S_OK;
}

void AstarScene::Release()
{
	if (endTile)
	{
		endTile->Release();
		SAFE_DELETE(endTile);
	}

	if (startTile)
	{
		startTile->Release();
		SAFE_DELETE(startTile);
	}

	for (auto it : openList)
	{
		delete(it);
	}
	openList.clear();

	for (auto it : closeList)
	{
		delete(it);
	}
	closeList.clear();

	Route.clear();
}

void AstarScene::FindPath(AstarTile* currTile)
{
	// 현재 타일에서 이동가능한 모든 타일을 오픈리스트에 넣는다.
	AddOpenList(currTile);

	float minF = 99999;
	AstarTile* minTile = nullptr;
	int F, G, H;
	for (int i = 0; i < openList.size(); i++)
	{
		//도착지점까지의 예상 비용 계산
		H = (abs(endTile->GetIdX() - openList[i]->GetIdX()) + abs(endTile->GetIdY() - openList[i]->GetIdY())) * 10;

		openList[i]->SetCostToGoal(H);

		// 시작 타일부터 현재 타일까지의 비용 계산
		// 부모 타일의 G + 타일 하나의 이동 비용s
		AstarTile* parent = openList[i]->GetParentTile();
		if (parent)
		{
			G = parent->GetCostFromStart() +
				(GetDistance(parent->GetPos().x, parent->GetPos().y,
					openList[i]->GetPos().x, openList[i]->GetPos().y) > ISO_TILE_SIZE_X ? 10 : 10);
		}
		else
		{
			G = GetDistance(parent->GetPos().x, parent->GetPos().y,
				openList[i]->GetPos().x, openList[i]->GetPos().y) > ISO_TILE_SIZE_X ? 10 : 10;
		}

		openList[i]->SetCostFromStart(G);

		F = G + H;
		openList[i]->SetTotalCost(F);

		// 가장 비용이 적게 드는 타일을 선택한다.
		if (minF > F)
		{
			minF = F;
			minTile = openList[i];
		}
	}

	// 가장 적은 비용이 드는 타일이 도착지점일 경우
	if (minTile->GetAttribute() == "end")
	{
		AstarTile* curr = minTile;

		while (curr->GetParentTile() != nullptr)
		{
			Route.push_back(make_pair(curr->GetIdX(), curr->GetIdY()));
			curr = curr->GetParentTile();
		}
		Route.push_back(make_pair(startTile->GetIdX(), startTile->GetIdY()));
		Route.reverse();
		routeNum = Route.size();
		isFinish = true;
		openList.clear();
		closeList.clear();
		return;
	}

	// 지나온 타일을 클로즈리스트에 추가한다.
	closeList.push_back(minTile);

	// 오픈리스트에서 제거한다.
	for (vector<AstarTile*>::iterator it = openList.begin(); it != openList.end(); it++)
	{
		if ((*it) == minTile)
		{
			openList.erase(it);
			break;
		}
	}

	// 제일 가까운 타일을 기준으로 알고리즘을 반복한다.
	currTile = minTile;

	FindPath(currTile);
}

list<pair<int, int>>* AstarScene::StartAstar(TILE_NUM_INFO start)
{
	Route.clear();
	startTile->Init(start.idX, start.idY);

	currTile = startTile;
	routeNum = 0;
	isFinish = false;


	for (int i = 0; i < ISO_TILE_X*ISO_TILE_Y; i++)
	{
		if (isWall[i] == true)
		{
			(*vecTiles[i]).SetAttribute("wall");
		}
	}

	FindPath(currTile);
	return &Route;
}

void AstarScene::AddOpenList(AstarTile * currentTile)
{

	// 현재 타일 주위의 모든 타일을 확인한다.
	int startX = currentTile->GetIdX();
	int startY = currentTile->GetIdY() - 1;
	int sideX, sideY;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i == 1)
			{
				continue;
			}
			if (startY % 2 == 0)
			{
				sideX = (startX - 1) + j;
			}
			else if (abs(startY % 2) == 1)
			{
				sideX = startX + j;
			}
			sideY = startY + i;

			// 타일맵 영역을 벗어났을 때
			if (sideX < 0 || sideX >= ISO_TILE_X ||
				sideY < 0 || sideY >= ISO_TILE_Y)
			{
				continue;
			}

			AstarTile* tile = vecTiles[sideY * ISO_TILE_X + sideX];

			// 오픈 리스트에 넣지 않는 경우
			/*
				start, wall, openList,이미 closeList에 들어있는 경우
			*/

			if (tile->GetAttribute() == "start" ||
				tile->GetAttribute() == "wall")
				continue;



			// 이미 오픈리스트에 있을 때 예외처리
			bool isExist = false;
			for (vector<AstarTile*>::iterator it = openList.begin(); it != openList.end(); it++)
			{
				if ((*it) == tile)
				{
					isExist = true;
					break;
				}
			}

			if (isExist) continue;

			// 클로즈리스트에 있을 때 예외처리
			isExist = false;
			for (vector<AstarTile*>::iterator it = closeList.begin(); it != closeList.end(); it++)
			{
				if ((*it) == tile)
				{
					isExist = true;
					break;
				}
			}

			if (isExist) continue;

			openList.push_back(tile);

			tile->SetParentTile(currentTile);
		}
	}

}

void AstarScene::AddWall(int idx)
{
	for (int i = 0; i < vecTiles.size(); i++)
	{
		if (i == idx)
		{
			if (vecTiles[i]->GetAttribute() == "start" ||
				vecTiles[i]->GetAttribute() == "end")
				continue;

			vecTiles[i]->SetAttribute("wall");
			isWall[i] = true;
			break;
		}
	}
}

void AstarScene::AddWall(AstarTile * _currtile)
{
	for (int i = 0; i < vecTiles.size(); i++)
	{
		if (vecTiles[i]->GetIdX() == _currtile->GetIdX() && vecTiles[i]->GetIdY() == _currtile->GetIdY())
			if (vecTiles[i]->GetAttribute() == "start" ||
				vecTiles[i]->GetAttribute() == "end")
				continue;

		vecTiles[i]->SetAttribute("wall");
		isWall[i] = true;
		break;
	}
}

void AstarScene::MoveWall(int idx, int moveIdx)
{
	for (int i = 0; i < vecTiles.size(); i++)
	{
		if (i == idx || i == moveIdx)
		{
			if (vecTiles[i]->GetAttribute() == "start" ||
				vecTiles[i]->GetAttribute() == "end")
				continue;


			vecTiles[idx]->SetAttribute("");
			vecTiles[moveIdx]->SetAttribute("wall");
			isWall[idx] = false;
			isWall[moveIdx] = true;
		}
		int a = idx > i ? idx : i;
		if (i == a)
			break;
	}
}

void AstarScene::MoveWall(AstarTile * _currtile, AstarTile * _moveTile)
{
	for (int i = 0; i < vecTiles.size(); i++)
	{
		for (int j = 0; j < vecTiles.size(); j++)
			if ((vecTiles[i]->GetIdX() == _currtile->GetIdX() && vecTiles[i]->GetIdY() == _currtile->GetIdY()) &&
				(vecTiles[j]->GetIdX() == _moveTile->GetIdX() && vecTiles[j]->GetIdY() == _moveTile->GetIdY()))
			{
				if ((vecTiles[i]->GetAttribute() == "start" ||
					vecTiles[i]->GetAttribute() == "end") ||
					(vecTiles[j]->GetAttribute() == "start" ||
						vecTiles[j]->GetAttribute() == "end"))
					continue;


				vecTiles[i]->SetAttribute("");
				vecTiles[j]->SetAttribute("wall");
				isWall[i] = false;
				isWall[j] = true;
			}
		break;
	}
}

void AstarScene::CheckWall()
{

}



AstarScene::AstarScene()
{
}


AstarScene::~AstarScene()
{
}
