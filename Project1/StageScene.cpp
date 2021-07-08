#include "StageScene.h"
#include "pch.h"
#include "MapTileInfo.h"
#include "MacroFunction.h"
#include "Image.h"
#include "Storage.h"
#include "AstarScene.h"
#include "Card.h"
#include "Skull.h"
#include "UnitDataBase.h"
#include "MacroFunction.h"
#include "Portal.h"
#include <iostream>
#include "EnemyManager.h"

StageScene* StageScene::instance = 0;
HRESULT StageScene::Init()
{
	sceneType = 1;

	instance = this;
	// �ʱ� ��� ����
	totalGold = 3000;
	waveDeltaTime = 0;

	// ����� ����
	storage = new Storage*[9];
	for (int i = 0; i < 9; i++)
	{
		storage[i] = new Storage();
		storage[i]->SetStoragePos(40 + (55 * (i % 3)), 630 + (55 * (i / 3)));
		storage[i]->SetSkullTile(nullptr);
		storage[i]->SetIsEmpty(true);
		storage[i]->SetStorageId(-1);
		storage[i]->SetStorageRect(storage[i]->GetStoragePos().x, storage[i]->GetStoragePos().y, 55, 55);
	}

	// ���� ī�� ��� ����
	for (int i = 0; i < 4; i++)
	{
		int idx = rand() % 3;
		skullCard[i] = new Card();
		cardPos[i] = { 123 + (70 * i), 120 };
		skullCard[i]->Init(cardPos[i]);
		skullCard[i]->SetPos(cardPos[i]);
		skullCard[i]->ShuffleCard(idx);
		if (i == 3)
			skullCard[i]->ShuffleCard(3);
	}

	// ���� ������Ʈ Ǯ_���ÿ� ����
	for (int i = 0; i < skullLimitCount; i++)
	{
		skull = new Skull();
		skull->Init();
		stSkulls.push(skull);
	}

	// Ÿ�� �� ���� ����
	MapTileInfo::GetSingleton()->Init();
	tiles = MapTileInfo::GetSingleton()->GetTileMap();

	// Ÿ�ϸ� x, y �� �ʱ�ȭ
	ptSelected.x = 0;
	ptSelected.y = 0;

	// �ΰ��� �̹��� ����
	inGameScreen = ImageManager::GetSingleton()->AddImage("�ΰ���", "Image/����Ÿ��2.bmp", WINSIZE_X, WINSIZE_Y, false, RGB(255, 255, 255));
	enemyGate = ImageManager::GetSingleton()->AddImage("����Ʈ", "Image/Gate2.bmp", 0, 0, 240, 420, 2, 5, true, RGB(255, 255, 255));

	// ������ ����
	currframeX = 0;
	currframeY = 4;
	frame = 0;
	isOpen = false;

	// �⺻ ����� ����
	ShuffleDist();

	wave = 0;
	size = 0;

	portal = new Portal();
	portal->Init();
	portal->SetPos(tiles[5][2].x, tiles[5][2].y);
	gatePos = { tiles[start.idY][start.idX].x, tiles[start.idY][start.idX].y };


	pen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));

	// ���� ����+�ʱ�ȭ �� �˰��� �ʱ�ȭ
	UnitDataBase::GetSingleton()->Init();
	AstarScene::GetSingleton()->Init();
	astarPath = AstarScene::GetSingleton()->StartAstar(start);
	if (astarPath != NULL)
	{
		img = ImageManager::GetSingleton()->AddImage("����", "Image/����.bmp", 0, 0, 2700, 600, 9, 3, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->AddImage("��Ż��", "Image/��Ż��.bmp", 0, 0, 1540, 600, 7, 3, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->AddImage("�׸�����", "Image/�׸�����.bmp", 0, 0, 2640, 600, 12, 3, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->AddImage("��_����", "Image/����.bmp", 0, 0, 260, 320, 4, 4, true, RGB(255, 255, 255));
		effectImg = ImageManager::GetSingleton()->AddImage("��_����_��������Ʈ", "Image/��_����_����Ʈ.bmp", 0, 0, 318, 90, 6, 1, true, RGB(255, 255, 255));
	}

	// UI��ư ����
	startB.ButtIcon.iconPos = { 400, 630 };
	cardLockB.ButtIcon.iconPos = { 400, 685 };
	cardB.ButtIcon.iconPos = { 400, 740 };

	startB.ButtRect = GetRectToCenter(startB.ButtIcon.iconPos.x, startB.ButtIcon.iconPos.y, 54, 54);
	cardLockB.ButtRect = GetRectToCenter(cardLockB.ButtIcon.iconPos.x, cardLockB.ButtIcon.iconPos.y, 54, 54);
	cardB.ButtRect = GetRectToCenter(cardB.ButtIcon.iconPos.x, cardB.ButtIcon.iconPos.y, 54, 54);

	startB.ButtIcon.iconImg = ImageManager::GetSingleton()->AddImage("����", "Image/����.bmp", 0, 0, 48, 105, 1, 2, true, RGB(255, 255, 255));
	cardLockB.ButtIcon.iconImg = ImageManager::GetSingleton()->AddImage("���", "Image/��.bmp", 0, 0, 38, 105, 1, 2, true, RGB(255, 255, 255));
	cardB.ButtIcon.iconImg = ImageManager::GetSingleton()->AddImage("�����", "Image/�����.bmp", 0, 0, 48, 105, 1, 2, true, RGB(255, 255, 255));

	startB.ButtIcon.currframe = 0;
	cardLockB.ButtIcon.currframe = 0;
	cardB.ButtIcon.currframe = 0;

	timer.iconPos = { 45 , 120 };
	timer.iconImg = ImageManager::GetSingleton()->AddImage("Ÿ�̸�", "Image/Ÿ�̸�.bmp", 0, 0, 350, 73, 5, 1, true, RGB(255, 255, 255));
	timer.currframe = -1;

	enemymgr = new EnemyManager();
	enemymgr->Init();

	WaveTime = countTime + (float)enemymgr->GetEnemiesCount();
	return S_OK;
}

void StageScene::Release()
{
	for (int i = 0; i < 4; i++)
	{
		skullCard[i]->Release();
		SAFE_DELETE(skullCard[i]);
	}

	for (int i = 0; i < skullLimitCount; i++)
	{
		if (!vecSkulls.empty())
			vecSkulls.pop_back();
	}
	vecSkulls.clear();

	while (!stSkulls.empty())
	{
		stSkulls.pop();
	}

	DeleteObject(pen);
	DeleteObject(pen1);

	AstarScene::GetSingleton()->Release();
	AstarScene::GetSingleton()->ReleaseSingleton();

	MapTileInfo::GetSingleton()->Release();
	MapTileInfo::GetSingleton()->ReleaseSingleton();


}

void StageScene::Update()
{
	// ���� ���� ȭ�� ��
	if (isOpen)
	{
		// ���� �ð� üũ �� ���̺� ó��
		elapsedTime = TimeManager::GetSingleton()->GetWaveTime();

		float limitTime = WaveTime - elapsedTime;
		// ���̺� ����
		if (limitTime == WaveTime)
		{
			TimeManager::GetSingleton()->SetIsWaveTime(true);
			isWave = true;
			currframeY = 0;
		}
		// ���̺� ���� Ÿ�̸� ���� ó��
		else if (limitTime > 20 && limitTime <= 25)
		{
			timer.currframe = 25 - limitTime;
			if (timer.currframe < 0) timer.currframe = 0;
		}
		// ���̺� ���� ���� �� ���� ó��
		else if (limitTime > 0 && limitTime <= 20)
		{
			if (limitTime > 19 && isSpawn == false)
			{
				timer.currframe = -1;
				SpawnEnemies();
				isSpawn = true;
			}
			else if (limitTime <= 19)
			{
				if (19  - (limitTime + elapsedSpawnTime) >= 0)
				{
					elapsedSpawnTime++;
					SpawnEnemies();
					cout << limitTime << endl;
				}
			}
			
		}
		// ���̺� ���� �ƴҶ� ��Ż ����
		if (!isWave)
		{
			currframeX = 0;
			currframeY = 4;
			isSpawn = false;
		}
		// ���̺� ���� ��Ż ���� �ִϸ��̼�
		if (isWave)
		{
			frame++;
			if (frame % 3 == 2)
			{
				currframeX++;
				if (currframeX == 2)
				{
					currframeY++;
					currframeX = 0;
					if (currframeY == 4)
						currframeY = 0;
				}
			}
			enemymgr->Update();
		}
	}

	// ���� ���� ������Ʈ
	if (vecSkulls.size() > 0)
	{
		for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
		{
			(*it)->Update();
		}
	}

	// ī�� ����
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		ClickButton();
		if (!isLock)
		{
			CheckPercase();
		}
		SelectSkull();
	}

	// �巡�� �� ��ġ �� ����
	if ((KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON)))
	{
		if (!isWave)
		{
			if (isSelect == true)
			{
				MoveSkull();
			}
		}

	}

	// ���� ��ġ
	if ((KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON)))
	{
		if (!isWave)
		{
			if (isSelect == true)
			{
				SetStorage();
				SetUpSkull();
			}
		}
	}

	portal->Update();
}


void StageScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	inGameScreen->Render(hdc, 0, 0);
	for (int i = 0; i < 9; i++)
	{
		Rectangle(hdc, storage[i]->GetStorageRect().left, storage[i]->GetStorageRect().top,
			storage[i]->GetStorageRect().right, storage[i]->GetStorageRect().bottom);
	}
	SelectObject(hdc, pen1);

	// ��� ǥ�� ����
	if (astarPath != NULL)
		DrawPath(hdc);
	// UI ������ ����
	startB.ButtIcon.iconImg->FrameRender(hdc, startB.ButtIcon.iconPos.x, startB.ButtIcon.iconPos.y, 0, startB.ButtIcon.currframe);
	cardLockB.ButtIcon.iconImg->FrameRender(hdc, cardLockB.ButtIcon.iconPos.x, cardLockB.ButtIcon.iconPos.y, 0, cardLockB.ButtIcon.currframe);
	cardB.ButtIcon.iconImg->FrameRender(hdc, cardB.ButtIcon.iconPos.x, cardB.ButtIcon.iconPos.y, 0, cardB.ButtIcon.currframe);
	if (vecSkulls.size() > 0)
	{
		for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
		{
			if ((*it)->GetPos().y <= 332)
				(*it)->Render(hdc);
		}
	}
	
	portal->Render(hdc);


	enemyGate->FrameRender(hdc, gatePos.x, gatePos.y - 38, currframeX, currframeY);
	if (isWave)
	{
		enemymgr->Render(hdc);
	}
	if (timer.currframe >= 0)
		timer.iconImg->FrameRender(hdc, timer.iconPos.x, timer.iconPos.y, timer.currframe, 0);

	if (!isHide)
	{
		for (int i = 0; i < 4; i++)
		{
			skullCard[i]->Render(hdc);
		}
	}
	if (vecSkulls.size() > 0)
	{
		for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
		{
			if((*it)->GetPos().y >= 332)
			(*it)->Render(hdc);
		}
	}

}

void StageScene::ShuffleDist()
{
	int a = rand() % 22;
	switch (a)
	{
	case 0: start = { 0 , 0 };
			break;
	case 1: start = { 1 , 0 };
			break;
	case 2: start = { 2 , 0 };
			break;
	case 3: start = { 3 , 0 };
			break;
	case 4: start = { 0 , 1 };
			break;
	case 5: start = { 4 , 1 };
			break;
	case 6: start = { 0 , 3 };
			break;
	case 7: start = { 4 , 3 };
			break;
	case 8: start = { 0 , 5 };
			break;
	case 9: start = { 4 , 5 };
			break;
	case 10: start = { 0 , 7 };
			 break;
	case 11: start = { 4 , 7 };
			 break;
	case 12: start = { 0 , 9 };
			 break;
	case 13: start = { 4 , 9 };
			 break;
	case 14: start = { 0 , 11 };
			 break;
	case 15: start = { 4 , 11 };
			 break;
	case 16: start = { 4 , 13 };
			 break;
	case 17: start = { 0 , 14 };
			 break;
	case 18: start = { 1 , 14 };
			 break;
	case 19: start = { 2 , 14 };
			 break;
	case 20: start = { 3 , 14 };
			 break;
	}
}

void StageScene::Start()
{
	if (!isOpen)
	{
		isOpen = true;
		wave++;
		timer.currframe = 0;
	}
}

void StageScene::CheckPercase()
{
	// ���� ī�� ���
	for (int i = 0; i < 4; i++)
	{
		// ī�� �� �ϳ��� ���콺 ����Ʈ ���� ��ĥ��
		if (PtInRect(&(skullCard[i]->GetCardRect()), g_ptMouse))
		{
			// 3���� �����
			for (int j = 0; j < 9; j++)
			{
				// 0~2���� ī���� ��� &&	����ҿ� ������� �����Ҷ�
				if (i < 3 && storage[j]->GetIsEmpty())
				{
					// ī���� ���ݺ��� ���� �ݾ��� ���� ���϶�
					if (skullCard[i]->GetPrice() <= totalGold && skullCard[i]->GetCurrFrameY() == 0)
					{
						PerchaseCard(skullCard[i], storage[j]);
						break;
					}
				}
				// ���� ���� ī���� ���
				else if (i == 3 && skullCard[i]->GetPrice() <= totalGold)
				{
					PerchaseShuffleCard(skullCard[i]);
					break;

				}
			}
		}
	}
}

void StageScene::PerchaseCard(Card* skullCard, Storage* storage)
{
	// ī�尪 ����
	totalGold -= skullCard->GetPrice();
	// ���Ű��� ���๮
	skullCard->PerchaseCard();
	// Ÿ���� ���� ����
	string* skullName = UnitDataBase::GetSingleton()->GetSkullIdInfo(skullCard->GetSkullId());
	// ������Ʈ Ǯ ����
	Skull* skull = stSkulls.top();
	stSkulls.pop();
	skull->SetSkull(storage->GetStoragePos(), skullName);
	vecSkulls.push_back(skull);
	// Ÿ�Ͽ��� Ÿ������ ����
	storage->SetSkullTile(skull);
	// Ÿ������ Ÿ������ ����
	skull->SetStorage(storage);
}

void StageScene::PerchaseShuffleCard(Card* shuffleCard)
{
	totalGold -= shuffleCard->GetPrice();
	for (int k = 0; k < 3; k++)
		skullCard[k]->RerollCard();
}

void StageScene::SelectSkull()
{
	if (isSelect == false)
	{
		selectSkull = nullptr;

		// ����� ���� 0~2�� �߿�
		for (int i = 0; i < 9; i++)
		{
			// ����� i�� ����ְ�, �װ��� ���콺 ����Ʈ ���� ����������
			if (PtInRect(&(storage[i]->GetStorageRect()), g_ptMouse))
			{
				for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
				{
					// ����� i�� ��ġ�� Ÿ���� ������
					if (PtInRect(&(storage[i]->GetStorageRect()), (*it)->GetPos()))
					{
						// �ش� Ÿ���� ���õǰ� ���� ����Ʈ���� ���� Ÿ�� ��ġ�� ����ȴ�.
						isSelect = true;
						(*it)->SetPrevPos((*it)->GetPos());
						selectSkull = (*it);
						storage[i]->SetSkullTile(nullptr);
						break;
					}
				}
			}
		}

		if (selectSkull == nullptr)
		{
			// ���� Ÿ��
			for (int i = 0; i < ISO_TILE_Y; i++)
			{
				endflag = -1;
				for (int j = 0; j < ISO_TILE_X; j++)
				{
					if (i % 2 == 0)
					{
						if (j == 4)
							continue;
					}

					// ����Ÿ�� �� �ϳ��� ���콺 ����Ʈ���� ��ĥ���
					if (PtInRect(&tiles[i][j].rc, g_ptMouse))
					{
						float xx = (float)abs(g_ptMouse.x - tiles[i][j].x) / ISO_TILE_HALF_SIZE_X;
						float yy = (float)abs(g_ptMouse.y - tiles[i][j].y) / ISO_TILE_HALF_SIZE_Y;
						// ���̼Ҹ�Ʈ�� Ÿ�� ���� ���ǹ�
						if (xx + yy < 1)
						{
							for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
							{
								// �� Ÿ�� ���� �ִ� Ÿ���� ���� ���
								if (PtInRect(&tiles[i][j].rc, (*it)->GetPos()))
								{
									// �ش� Ÿ���� ���û��·� �ٲٰ�, ���� ��ġ���� ���� ��ġ���� ����
									isSelect = true;
									(*it)->SetPrevPos((*it)->GetPos());
									selectSkull = (*it);
									tiles[i][j].skull = (*it);
									endflag = 1;
									break;

								}
							}
						}
					}
				}
				if (endflag == 1)
					break;
			}
		}
	}
}

void StageScene::MoveSkull()
{
	selectSkull->SetPos(g_ptMouse.x, g_ptMouse.y - 21);
}

void StageScene::SetUpSkull()
{
	for (int k = 0; k < ISO_TILE_Y; k++)
	{
		for (int j = 0; j < ISO_TILE_X; j++)
		{
			if (k % 2 == 0)
			{
				if (j == 4)
					continue;
			}

			if (PtInRect(&tiles[k][j].rc, g_ptMouse))
			{
				for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
				{
					float xx = (float)abs(g_ptMouse.x - tiles[k][j].x) / ISO_TILE_HALF_SIZE_X;
					float yy = (float)abs(g_ptMouse.y - tiles[k][j].y) / ISO_TILE_HALF_SIZE_Y;
					// ���̼Ҹ�Ʈ�� Ÿ�� ���� ���ǹ�
					if (xx + yy < 1)
					{
						// Ÿ�� ��ġ�� ����
						POINT tilePos = { tiles[k][j].x, tiles[k][j].y - 21 };
						selectSkull->SetPos(tilePos);
						// �ش� Ÿ������ ������ ���� ���
						if (tiles[k][j].skull == nullptr)
						{
							// ���° Ÿ������
							int idx = j + (5 * k);
							tiles[k][j].skull = selectSkull;

							////cout << "���콺��ǥ : " << idx << endl;
							if (selectSkull->GetSkullTile() != nullptr)
							{
								selectSkull->GetSkullTile()->skull = nullptr;
								int a = selectSkull->GetSkullTile()->tileNum;
								selectSkull->GetSkullTile()->isEmpty = true;
								selectSkull->SetNowSkullTile(&tiles[k][j]);
								AstarScene::GetSingleton()->MoveWall(a, idx);
								astarPath = NULL;
								astarPath = AstarScene::GetSingleton()->StartAstar(start);
								isSelect = false;
								break;
							}
							tiles[k][j].isEmpty = false;

							selectSkull->SetNowSkullTile(&tiles[k][j]);
							AstarScene::GetSingleton()->AddWall(idx);
							astarPath = NULL;
							astarPath = AstarScene::GetSingleton()->StartAstar(start);
							//cout << (*it)->GetPos().x << ", " << (*it)->GetPos().y << endl;
							isSelect = false;
							break;
						}
					}
				}
			}
		}
	}
}

void StageScene::SetStorage()
{
	// ����� ��ġ�� �������� ������, ����Ÿ�ϵ��� ��ġ�� �������� ������� ���� ��ġ������ �ǵ�����.
	for (int j = 0; j < 9; j++)
	{
		if (!(g_ptMouse.x >= storage[0]->GetStorageRect().left &&
			g_ptMouse.x <= storage[2]->GetStorageRect().right &&
			g_ptMouse.y >= storage[0]->GetStorageRect().top &&
			g_ptMouse.y <= storage[8]->GetStorageRect().bottom))
		{
			if (g_ptMouse.x >= ISO_START_X &&
				g_ptMouse.x <= ISO_START_X + (ISO_TILE_SIZE_X * ISO_TILE_X) &&
				g_ptMouse.y >= ISO_START_Y &&
				g_ptMouse.y <= ISO_START_Y + (ISO_TILE_HALF_SIZE_Y * ISO_TILE_Y))
				continue;
			selectSkull->SetPos(selectSkull->GetPrevPos());
			isSelect = false;
		}
		// ����ҿ� ��ġ�� ��ġ�� Ÿ���� �ִ� ���
		if (PtInRect(&(storage[j]->GetStorageRect()), selectSkull->GetPos()))
		{
			if (storage[j]->GetSkullTile() != nullptr)
			{
				selectSkull->SetPos(selectSkull->GetPrevPos());
				selectSkull->GetStorage()->SetSkullTile(selectSkull);
				isSelect = false;
				break;
			}
			// Ÿ���� ��ġ�� ���� ��ġ�� Ÿ���� ��ġ�� ����
			selectSkull->SetPos(storage[j]->GetStoragePos());
			// Ÿ���� ���� Ÿ�ϰ��� ���� Ÿ�Ϸ� ����
			selectSkull->SetStorage(storage[j]);
			// Ÿ���� ���ÿ��� ����
			storage[j]->SetSkullTile(selectSkull);
			isSelect = false;
			break;
		}
	}
}

// ��� �׸���
void StageScene::DrawPath(HDC hdc)
{
	SelectObject(hdc, pen);
	int idX;// = new int();
	int idY;// = new int();
	size = astarPath->size();

	int i = 0;
	for (auto it = astarPath->begin(), end = astarPath->end(); it != end; it++)
	{
		idX = it->first;
		idY = it->second;

		if (i == 0)
		{
			MoveToEx(hdc, tiles[idY][idX].x, tiles[idY][idX].y, NULL);
		}
		else if (i > 0)
		{
			LineTo(hdc, tiles[idY][idX].x, tiles[idY][idX].y);
		}
		i++;
	}
}

void StageScene::ClickButton()
{
	if (PtInRect(&startB.ButtRect, g_ptMouse))
	{
		if (!isWave)
			Start();
	}
	else if (PtInRect(&cardLockB.ButtRect, g_ptMouse))
	{
		if (isLock)
		{
			isLock = false;
			cardLockB.ButtIcon.currframe = 0;
		}
		else
		{
			isLock = true;
			cardLockB.ButtIcon.currframe = 1;

		}
	}
	else if (PtInRect(&cardB.ButtRect, g_ptMouse))
	{
		if (isHide)
		{
			isHide = false;
			cardB.ButtIcon.currframe = 0;
		}
		else
		{
			isHide = true;
			cardB.ButtIcon.currframe = 1;
		}
	}
}

void StageScene::SpawnEnemies()
{
	enemymgr->SetEnemy(0, start);
	enemymgr->SetAstarPath(astarPath);
	enemymgr->WaveStart();
}

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
}
