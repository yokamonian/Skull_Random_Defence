#pragma once

#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <list>
#include <stack>


using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SceneManager.h"


typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

// 아군 유닛 데이터 베이스
typedef struct SkullData
{
	int damage;			// 데미지
	int attackSpeed;	// 공속
	int abilityPower;	// 스킬 데미지
	int skillCount;		// 스킬에 필요한 타격수
	int growthDmg;		// 성장 데미지(킬)
	int growthAp;		// 성장 스킬 데미지(킬)
	int upgradeDmg;		// 성급업 데미지
	int upgradeAs;		// 성급업 공속
	int upgradeSc;		// 성급업 스킬에 필요한 타격수
	int upgradeAp;		// 성급업 스킬데미지
	int idleFrame;		// 기본 동작 애니메이션 프레임
	int attackFrame;	// 공격 동작 애니메이션 프레임
	int skillFrame;		// 스킬 동작 애니메이션 프레임
	string skullName;	// 스컬 이름
	string EffectName;	// 스킬 이펙트 이름
}SKULLDATA;

// 적군 유닛 데이터 베이스
typedef struct EnemyData
{
	int damage;			// 데미지
	int attackSpeed;	// 공속
	int moveSpeed;		// 이속
	int healthPoint;	// 체력
	int idleFrame;		// 기본 동작 애니메이션 프레임
	int attackFrame;	// 공격 동작 애니메이션 프레임
	int dieFrame;		// 사망 동작 애니메이션 프레임
	string enemyName;	// 적 이름
	string EffectName;	// 적 스킬 이펙트 이름
	int id;				// id값
}ENEMYDATA;

// enum, struct, .h, #define

// 콘솔 창 크기
#define WINSIZE_X	440
#define WINSIZE_Y	880
#define WINSTART_X	50
#define WINSTART_Y	50

// 타일 가로 세로 개수
#define ISO_TILE_X	5
#define ISO_TILE_Y	15

// 타일 가로 세로 크기
#define ISO_TILE_SIZE_X 84
#define ISO_TILE_SIZE_Y 42
#define ISO_TILE_HALF_SIZE_X (ISO_TILE_SIZE_X / 2)
#define ISO_TILE_HALF_SIZE_Y (ISO_TILE_SIZE_Y / 2)

// 타일 시작 좌표
#define ISO_START_X 12
#define ISO_START_Y 227	

// 인벤 시작 좌표
#define INVEN_START_Y 590
#define INVEN_START_U 12
#define INVEN_START_I 190

// 스컬(타워) 이미지 정보
typedef struct tagIsoTile
{
	int x, y;
	int tileNum;
	RECT rc;
	class Skull* skull = nullptr;
	bool isEmpty = true;
}ISOTILE;

// 타일 좌표
typedef struct tileNumInfo
{
	int idX;
	int idY;
}TILE_NUM_INFO;

// 인벤토리 정보
typedef struct tagStorage
{
	POINT storagePos;
	bool isEmpty;
	int Id;
	RECT storageRc;
	class Skull* skullTile;
}STORAGE;


// 이미지 랜더 관련
#define PI         3.141592
#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}
#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

// 전역변수화
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#include "MacroFunction.h"
#include "UnitDataBase.h"
