#include "StageUI.h"
#include "pch.h"

//HRESULT StageUI::Init()
//{
//	totalGold = 1000;
//
//	for (int i = 0; i < 3; i++)
//	{
//		storage[i].storagePos = storagePos[i];
//		storage[i].isEmpty = true;
//		storage[i].Id = -1;
//	}
//
//	for (int i = 0; i < 4; i++)
//	{
//		int idx = rand() % 3;
//		skullCard[i] = new Card();
//		cardPos[i] = { 123 + (70 * i), 155 };
//		skullCard[i]->Init(cardPos[i]);
//		skullCard[i]->SetPos(cardPos[i]);
//		skullCard[i]->ShuffleCard(idx);
//		if (i == 3)
//			skullCard[i]->ShuffleCard(3);
//	}
//	return S_OK;
//}
//
//void StageUI::Release()
//{
//}
//
//void StageUI::Update()
//{
//	for (int i = 0; i < 4; i++)
//	{
//		if (PtInRect(&(skullCard[i]->GetCardRect()), g_ptMouse))
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
//				{
//					if (i < 3)
//					{
//						if (storage[j].isEmpty = true)
//						{
//							if (skullCard[i]->GetPrice() <= totalGold)
//							{
//								totalGold -= skullCard[i]->GetPrice();
//								skullCard[i]->PerchaseCard();
//
//
//								storage[j].Id = skullCard[i]->GetSkullId();
//								storage[j].isEmpty = false;
//
//								break;
//							}
//						}
//					}
//
//					else if (i == 3)
//					{
//						if (skullCard[i]->GetPrice() <= totalGold)
//						{
//							for(int k = 0; k < 3; k++)
//								skullCard[k]->RerollCard();
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//void StageUI::Render(HDC hdc)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		skullCard[i]->Render(hdc);
//	}
//
//}
//

