#include "AStarScene.h"
#include "AstarTile.h"
#include "pch.h"

HRESULT AstarScene::Init()
{
	// ������
	startTile = new AstarTile();
	startTile->Init(0, 0);
	startTile->SetAttribute("start");
	// ��������
	endTile = new AstarTile();
	endTile->Init(2, 5);
	endTile->SetAttribute("end");

	// �ʱ⼼��
	currTile = startTile;
	routeNum = 0;
	isFinish = false;
	vecTiles.reserve(ISO_TILE_X*ISO_TILE_Y);

	for (int i = 0; i < ISO_TILE_Y; i++)
	{
		for (int j = 0; j < ISO_TILE_X; j++)
		{
			// ���� Ÿ������
			if (j == startTile->GetIdX() && i == startTile->GetIdY())
			{
				vecTiles.push_back(startTile);
				continue;
			}

			// ���� Ÿ������
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
			// ���� Ÿ������
			if (j == startTile->GetIdX() && i == startTile->GetIdY())
			{
				vecTiles.push_back(startTile);
				continue;
			}

			// ���� Ÿ������
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
	// ���� Ÿ�Ͽ��� �̵������� ��� Ÿ���� ���¸���Ʈ�� �ִ´�.
	AddOpenList(currTile);

	float minF = 99999;
	AstarTile* minTile = nullptr;
	int F, G, H;
	for (int i = 0; i < openList.size(); i++)
	{
		//�������������� ���� ��� ���
		H = (abs(endTile->GetIdX() - openList[i]->GetIdX()) + abs(endTile->GetIdY() - openList[i]->GetIdY())) * 10;

		openList[i]->SetCostToGoal(H);

		// ���� Ÿ�Ϻ��� ���� Ÿ�ϱ����� ��� ���
		// �θ� Ÿ���� G + Ÿ�� �ϳ��� �̵� ���s
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

		// ���� ����� ���� ��� Ÿ���� �����Ѵ�.
		if (minF > F)
		{
			minF = F;
			minTile = openList[i];
		}
	}

	// ���� ���� ����� ��� Ÿ���� ���������� ���
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

	// ������ Ÿ���� Ŭ�����Ʈ�� �߰��Ѵ�.
	closeList.push_back(minTile);

	// ���¸���Ʈ���� �����Ѵ�.
	for (vector<AstarTile*>::iterator it = openList.begin(); it != openList.end(); it++)
	{
		if ((*it) == minTile)
		{
			openList.erase(it);
			break;
		}
	}

	// ���� ����� Ÿ���� �������� �˰����� �ݺ��Ѵ�.
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

	// ���� Ÿ�� ������ ��� Ÿ���� Ȯ���Ѵ�.
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

			// Ÿ�ϸ� ������ ����� ��
			if (sideX < 0 || sideX >= ISO_TILE_X ||
				sideY < 0 || sideY >= ISO_TILE_Y)
			{
				continue;
			}

			AstarTile* tile = vecTiles[sideY * ISO_TILE_X + sideX];

			// ���� ����Ʈ�� ���� �ʴ� ���
			/*
				start, wall, openList,�̹� closeList�� ����ִ� ���
			*/

			if (tile->GetAttribute() == "start" ||
				tile->GetAttribute() == "wall")
				continue;



			// �̹� ���¸���Ʈ�� ���� �� ����ó��
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

			// Ŭ�����Ʈ�� ���� �� ����ó��
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
