#include "Enemy.h"
#include "GameObject.h"
#include "Image.h"
#include "StageScene.h"
#include "pch.h"
#include <iostream>
#include <math.h>
#include "Portal.h"

HRESULT Enemy::Init()
{
	pos = { 0, 0 };
	destOrder.reserve(50);
	frame = 0;
	EffectFrame = 0;
	currFrameX = 0;
	currFrameY = 0;
	timeAmount = 1.0f;
	PortalPos = { 222, 332 };
	isRender = false;
	e_Mode = EnemyMode::IDLE;
	effectFrameX = -1;
	time = 0.0f;
	return S_OK;
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	frameByMode();
	EnemyBehavior();

}

void Enemy::Render(HDC hdc)
{
	if (isRender)
	{
		if (enemyImg)
		{
			enemyImg->FrameRender(hdc, pos.x, pos.y - 38, currFrameX, currFrameY);
			if (isFire)
			{
				attackImg->FrameRender(hdc, PortalPos.x, PortalPos.y - 15, effectFrameX, 0);
			}
		}
	}
}

// 적 유닛 세팅
void Enemy::SetEnemy(POINT spawnPos, string* enemyName)
{
	EnemyData* enemy = UnitDataBase().GetSingleton()->GetEnemyInfo(*(enemyName));
	pos = { spawnPos.x, spawnPos.y };
	this->damage = enemy->damage;
	this->attackSpeed = enemy->attackSpeed;
	this->moveSpeed = enemy->moveSpeed;
	this->healthPoint = enemy->healthPoint;
	this->idleFrame = enemy->idleFrame;
	this->attackFrame = enemy->attackFrame;
	this->dieFrame = enemy->dieFrame;
	this->effect = enemy->EffectName;
	enemyImg = ImageManager::GetSingleton()->FindImage(enemy->enemyName);
	attackImg = ImageManager::GetSingleton()->FindImage(enemy->EffectName);
	fPos = { (float)pos.x, (float)pos.y };
	destpos = fPos;
}

float Enemy::GetTime(FPOINT startpos, FPOINT destpos)
{
	float distance = sqrt(((destpos.x - startpos.x) * (destpos.x - startpos.x)) +
		((destpos.y - startpos.y) * (destpos.y - startpos.y)));
	float Time = distance / moveSpeed;

	return Time;
}

// 동작 프레임 지정
void Enemy::frameByMode()
{
	frame++;
	int actionFrame = 8;
	switch (e_Mode)
	{
	case EnemyMode::IDLE:
		currFrameY = 0;
		actionFrame = 10;
		if (currFrameX == idleFrame)
			currFrameX = 0;
		break;
	case EnemyMode::ATTACK:
		currFrameY = 1;
		actionFrame = attackSpeed * 2 / 3;
		if (currFrameX == attackFrame)
		{
			currFrameX = 0;
		}
		else if (currFrameX == attackFrame - 2)
		{
			isFire = true;
		}
		if (isFire)
		{
			EffectFrame++;
			if (EffectFrame % 3 == 2)
			{
				effectFrameX++;
				if (effectFrameX == 7)
				{
					effectFrameX = -1;
					isFire = false;

					if (SceneManager::GetSingleton()->currentScene->GetSceneType() == 1)
					{
						StageScene* scene = (StageScene*)(SceneManager::GetSingleton()->currentScene);
						scene->GetPortal()->SetDamaged(damage);
					}

					//StageScene::instance->GetPortal()->SetDamaged(damage);
				}
			}
		}
		break;
	case EnemyMode::DIE:
		currFrameY = 2;
		if (currFrameX == dieFrame)
			currFrameX = idleFrame;
		break;
	}
	if (frame % actionFrame == actionFrame - 1)
	{
		frame = 0;
		currFrameX++;
	}
}
	// 적 이동 관련 설정
	void Enemy::MoveAstar()
	{
		// 도착지까지 이동(이동 시작 전)
		if (timeAmount >= 1.0f)
		{
			// 이동 경로가 비어있지 않은경우
			if (!destOrder.empty())
			{
				// 도착시간 리셋
				TimeManager::GetSingleton()->ResetTestTime();
				// 다음 도착 지점 갱신
				destpos = { (float)destOrder.back().first, (float)destOrder.back().second };
				destOrder.pop_back();
				startpos = { (float)pos.x, (float)pos.y };
				time = GetTime(startpos, destpos);
				if (TimeManager::GetSingleton()->GetIsTestStart() == false)
					TimeManager::GetSingleton()->SetIsTestStart(true);
				timeAmount = TimeManager::GetSingleton()->GetTestTime() / time;
			}
		}
		// 도착지까지 이동(이동 중)
		else if (timeAmount < 1.0f)
		{
			timeAmount = TimeManager::GetSingleton()->GetTestTime() / time;
			pos.x = startpos.x + ((destpos.x - startpos.x) * timeAmount);
			pos.y = startpos.y + ((destpos.y - startpos.y) * timeAmount);
		}
	}

	// 적 유닛 상태 판정
	void Enemy::EnemyBehavior()
	{
		if (healthPoint > 0)
		{
			if (abs(pos.x - PortalPos.x) < 30 && abs(pos.y - PortalPos.y) < 15)
			{
				e_Mode = EnemyMode::ATTACK;
				isAttack = true;
			}
			else
			{
				MoveAstar();
				isAttack = false;
			}



		}
		else if (healthPoint <= 0)
		{
			e_Mode = EnemyMode::DIE;
		}
	}



