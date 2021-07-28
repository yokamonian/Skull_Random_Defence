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
	// 초기 골드 세팅
	totalGold = 3000;
	waveDeltaTime = 0;

	// 저장소 세팅
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

	// 구매 카드 목록 세팅
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

	// 스컬 오브젝트 풀_스택에 저장
	for (int i = 0; i < skullLimitCount; i++)
	{
		skull = new Skull();
		skull->Init();
		stSkulls.push(skull);
	}

	// 타일 맵 정보 세팅
	MapTileInfo::GetSingleton()->Init();
	tiles = MapTileInfo::GetSingleton()->GetTileMap();

	// 타일맵 x, y 값 초기화
	ptSelected.x = 0;
	ptSelected.y = 0;

	// 인게임 이미지 세팅
	inGameScreen = ImageManager::GetSingleton()->AddImage("인게임", "Image/스컬타워2.bmp", WINSIZE_X, WINSIZE_Y, false, RGB(255, 255, 255));
	enemyGate = ImageManager::GetSingleton()->AddImage("게이트", "Image/Gate2.bmp", 0, 0, 240, 420, 2, 5, true, RGB(255, 255, 255));

	// 프레임 세팅
	currframeX = 0;
	currframeY = 4;
	frame = 0;
	isOpen = false;

	// 기본 출발지 세팅
	ShuffleDist();

	wave = 0;
	size = 0;

	portal = new Portal();
	portal->Init();
	portal->SetPos(tiles[5][2].x, tiles[5][2].y);
	gatePos = { tiles[start.idY][start.idX].x, tiles[start.idY][start.idX].y };


	pen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));

	// 유닛 세팅+초기화 및 알고리즘 초기화
	UnitDataBase::GetSingleton()->Init();
	AstarScene::GetSingleton()->Init();
	astarPath = AstarScene::GetSingleton()->StartAstar(start);
	if (astarPath != NULL)
	{
		img = ImageManager::GetSingleton()->AddImage("지니", "Image/지니.bmp", 0, 0, 2700, 600, 9, 3, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->AddImage("약탈자", "Image/약탈자.bmp", 0, 0, 1540, 600, 7, 3, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->AddImage("그림리퍼", "Image/그림리퍼.bmp", 0, 0, 2640, 600, 12, 3, true, RGB(255, 255, 255));
		img = ImageManager::GetSingleton()->AddImage("적_법사", "Image/법사.bmp", 0, 0, 260, 320, 4, 4, true, RGB(255, 255, 255));
		effectImg = ImageManager::GetSingleton()->AddImage("적_법사_공격이펙트", "Image/적_법사_이펙트.bmp", 0, 0, 318, 90, 6, 1, true, RGB(255, 255, 255));
	}

	// UI버튼 세팅
	startB.ButtIcon.iconPos = { 400, 630 };
	cardLockB.ButtIcon.iconPos = { 400, 685 };
	cardB.ButtIcon.iconPos = { 400, 740 };

	startB.ButtRect = GetRectToCenter(startB.ButtIcon.iconPos.x, startB.ButtIcon.iconPos.y, 54, 54);
	cardLockB.ButtRect = GetRectToCenter(cardLockB.ButtIcon.iconPos.x, cardLockB.ButtIcon.iconPos.y, 54, 54);
	cardB.ButtRect = GetRectToCenter(cardB.ButtIcon.iconPos.x, cardB.ButtIcon.iconPos.y, 54, 54);

	startB.ButtIcon.iconImg = ImageManager::GetSingleton()->AddImage("시작", "Image/시작.bmp", 0, 0, 48, 105, 1, 2, true, RGB(255, 255, 255));
	cardLockB.ButtIcon.iconImg = ImageManager::GetSingleton()->AddImage("잠금", "Image/락.bmp", 0, 0, 38, 105, 1, 2, true, RGB(255, 255, 255));
	cardB.ButtIcon.iconImg = ImageManager::GetSingleton()->AddImage("숨기기", "Image/숨기기.bmp", 0, 0, 48, 105, 1, 2, true, RGB(255, 255, 255));

	startB.ButtIcon.currframe = 0;
	cardLockB.ButtIcon.currframe = 0;
	cardB.ButtIcon.currframe = 0;

	timer.iconPos = { 45 , 120 };
	timer.iconImg = ImageManager::GetSingleton()->AddImage("타이머", "Image/타이머.bmp", 0, 0, 350, 73, 5, 1, true, RGB(255, 255, 255));
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
	// 게임 시작 화면 시
	if (isOpen)
	{
		// 남은 시간 체크 및 웨이브 처리
		elapsedTime = TimeManager::GetSingleton()->GetWaveTime();

		float limitTime = WaveTime - elapsedTime;
		// 웨이브 시작
		if (limitTime == WaveTime)
		{
			TimeManager::GetSingleton()->SetIsWaveTime(true);
			isWave = true;
			currframeY = 0;
		}
		// 웨이브 시작 타이머 구간 처리
		else if (limitTime > 20 && limitTime <= 25)
		{
			timer.currframe = 25 - limitTime;
			if (timer.currframe < 0) timer.currframe = 0;
		}
		// 웨이브 라운드 시작 및 스폰 처리
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
		// 웨이브 중이 아닐때 포탈 상태
		if (!isWave)
		{
			currframeX = 0;
			currframeY = 4;
			isSpawn = false;
		}
		// 웨이브 중의 포탈 상태 애니메이션
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

	// 스컬 상태 업데이트
	if (vecSkulls.size() > 0)
	{
		for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
		{
			(*it)->Update();
		}
	}

	// 카드 구매
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		ClickButton();
		if (!isLock)
		{
			CheckPercase();
		}
		SelectSkull();
	}

	// 드래그 시 위치 값 조정
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

	// 스컬 배치
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

	// 경로 표시 랜더
	if (astarPath != NULL)
		DrawPath(hdc);
	// UI 아이콘 랜더
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
	// 구매 카드 목록
	for (int i = 0; i < 4; i++)
	{
		// 카드 중 하나와 마우스 포인트 값이 겹칠때
		if (PtInRect(&(skullCard[i]->GetCardRect()), g_ptMouse))
		{
			// 3개의 저장소
			for (int j = 0; j < 9; j++)
			{
				// 0~2번의 카드일 경우 &&	저장소에 빈공간이 존재할때
				if (i < 3 && storage[j]->GetIsEmpty())
				{
					// 카드의 가격보다 많은 금액을 소지 중일때
					if (skullCard[i]->GetPrice() <= totalGold && skullCard[i]->GetCurrFrameY() == 0)
					{
						PerchaseCard(skullCard[i], storage[j]);
						break;
					}
				}
				// 랜덤 셔플 카드일 경우
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
	// 카드값 차감
	totalGold -= skullCard->GetPrice();
	// 구매관련 실행문
	skullCard->PerchaseCard();
	// 타워의 정보 전달
	string* skullName = UnitDataBase::GetSingleton()->GetSkullIdInfo(skullCard->GetSkullId());
	// 오브젝트 풀 과정
	Skull* skull = stSkulls.top();
	stSkulls.pop();
	skull->SetSkull(storage->GetStoragePos(), skullName);
	vecSkulls.push_back(skull);
	// 타일에게 타워정보 전달
	storage->SetSkullTile(skull);
	// 타워에게 타일정보 전달
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

		// 저장소 공간 0~2번 중에
		for (int i = 0; i < 9; i++)
		{
			// 저장소 i가 비어있고, 그곳에 마우스 포인트 값이 겹쳐있을때
			if (PtInRect(&(storage[i]->GetStorageRect()), g_ptMouse))
			{
				for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
				{
					// 저장소 i에 위치한 타워가 있을때
					if (PtInRect(&(storage[i]->GetStorageRect()), (*it)->GetPos()))
					{
						// 해당 타워는 선택되고 이전 포인트값에 현재 타일 위치가 저장된다.
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
			// 메인 타일
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

					// 메인타일 중 하나에 마우스 포인트값이 겹칠경우
					if (PtInRect(&tiles[i][j].rc, g_ptMouse))
					{
						float xx = (float)abs(g_ptMouse.x - tiles[i][j].x) / ISO_TILE_HALF_SIZE_X;
						float yy = (float)abs(g_ptMouse.y - tiles[i][j].y) / ISO_TILE_HALF_SIZE_Y;
						// 아이소메트릭 타워 선택 조건문
						if (xx + yy < 1)
						{
							for (vector<Skull*>::iterator it = vecSkulls.begin(); it != vecSkulls.end(); it++)
							{
								// 그 타일 위에 있는 타워가 있을 경우
								if (PtInRect(&tiles[i][j].rc, (*it)->GetPos()))
								{
									// 해당 타워를 선택상태로 바꾸고, 이전 위치값에 현재 위치값을 저장
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
					// 아이소메트릭 타워 선택 조건문
					if (xx + yy < 1)
					{
						// 타워 위치값 설정
						POINT tilePos = { tiles[k][j].x, tiles[k][j].y - 21 };
						selectSkull->SetPos(tilePos);
						// 해당 타일위에 스컬이 없는 경우
						if (tiles[k][j].skull == nullptr)
						{
							// 몇번째 타일인지
							int idx = j + (5 * k);
							tiles[k][j].skull = selectSkull;

							////cout << "마우스좌표 : " << idx << endl;
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
	// 저장소 위치에 속해있지 않으며, 메인타일들의 위치에 속해있지 않은경우 이전 위치값으로 되돌린다.
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
		// 저장소와 겹치는 위치의 타워가 있는 경우
		if (PtInRect(&(storage[j]->GetStorageRect()), selectSkull->GetPos()))
		{
			if (storage[j]->GetSkullTile() != nullptr)
			{
				selectSkull->SetPos(selectSkull->GetPrevPos());
				selectSkull->GetStorage()->SetSkullTile(selectSkull);
				isSelect = false;
				break;
			}
			// 타워의 위치를 현재 겹치는 타일의 위치로 조정
			selectSkull->SetPos(storage[j]->GetStoragePos());
			// 타워가 속한 타일값을 현재 타일로 조정
			selectSkull->SetStorage(storage[j]);
			// 타워의 선택여부 해제
			storage[j]->SetSkullTile(selectSkull);
			isSelect = false;
			break;
		}
	}
}

// 경로 그리기
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
