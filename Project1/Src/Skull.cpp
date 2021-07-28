#include "Skull.h"
#include "Image.h"

HRESULT Skull::Init()
{
	nowSkullTile = nullptr;
	storage = nullptr;
	return S_OK;
}

void Skull::SetSkull(TILE_NUM_INFO buildPos, string* skullName)
{
	// 유닛 데이터 베이스에서 스컬 정보 불러오기
	SkullData* skullInfo = UnitDataBase::GetSingleton()->GetSkullInfo(*(skullName));

	// 타일 위치에 유닛 좌표 설정
	int posX, posY;
	if(buildPos.idX % 2 == 0)
		posX = ISO_START_X + ((buildPos.idX + 1) * ISO_TILE_SIZE_X);
	else if(buildPos.idX % 2 == 1)
		posX = ISO_START_X + ((buildPos.idX + 1) * ISO_TILE_SIZE_X) - ISO_TILE_HALF_SIZE_X;
	posY = ISO_START_Y + (buildPos.idY * ISO_TILE_HALF_SIZE_Y);
	pos = { posX, posY };

	// 스컬 세팅
	img = ImageManager::GetSingleton()->FindImage(skullInfo->skullName);
	this->damage = skullInfo->damage;
	this->abilityPower = skullInfo->abilityPower;
	this->attackSpeed = skullInfo->attackSpeed;
	this->skillCount = skullInfo->skillCount;
	this->growthAp = skullInfo->growthAp;
	this->growthDmg = skullInfo->growthDmg;
	this->upgradeAp = skullInfo->upgradeAp;
	this->upgradeAs = skullInfo->upgradeAs;
	this->upgradeDmg = skullInfo->upgradeDmg;
	this->upgradeSc = skullInfo->upgradeSc;
	this->idleFrame = skullInfo->idleFrame;
	this->attackFrame = skullInfo->attackFrame;
	this->skillFrame = skullInfo->skillFrame;
	currFrameX = 0;
	currFrameY = 0;
	frame = 0;

	skullMode = SKULLMode::IDLE;
}

void Skull::SetSkull(POINT pos, string* skullName)
{
	SkullData* skullInfo = UnitDataBase::GetSingleton()->GetSkullInfo(*(skullName));
	this->pos = { pos.x, pos.y };
	img = ImageManager::GetSingleton()->FindImage(skullInfo->skullName);

	this->damage = skullInfo->damage;
	this->abilityPower = skullInfo->abilityPower;
	this->attackSpeed = skullInfo->attackSpeed;
	this->skillCount = skullInfo->skillCount;
	this->growthAp = skullInfo->growthAp;
	this->growthDmg = skullInfo->growthDmg;
	this->upgradeAp = skullInfo->upgradeAp;
	this->upgradeAs = skullInfo->upgradeAs;
	this->upgradeDmg = skullInfo->upgradeDmg;
	this->upgradeSc = skullInfo->upgradeSc;
	this->idleFrame = skullInfo->idleFrame;
	this->attackFrame = skullInfo->attackFrame;
	this->skillFrame = skullInfo->skillFrame;
	currFrameX = 0;
	currFrameY = 0;
	frame = 0;

	skullMode = SKULLMode::IDLE;
}

void Skull::Release()
{
}

void Skull::Update()
{
	// 상태에 다른 애니메이션 설정 업데이트
	frame++;
	if (frame % 7 == 6)
	{
		frame = 0;
		currFrameX++;
		switch (skullMode)
		{
		case SKULLMode::IDLE :
			currFrameY = 0;
			if (currFrameX == idleFrame)
				currFrameX = 0;
			break;
		case SKULLMode::ATTACK :
			currFrameY = 1;
			if (currFrameX == attackFrame)
				currFrameX = 0;
			break;
		case SKULLMode::SKILL :
			currFrameY = 2;
			if (currFrameX == skillFrame)
				currFrameX = 0;
			break;
		}

	}
}

void Skull::Render(HDC hdc)
{
	if(img)
	img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
}
