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

typedef struct SkullData
{
	int damage;
	int attackSpeed;
	int abilityPower;
	int skillCount;
	int growthDmg;
	int growthAp;
	int upgradeDmg;
	int upgradeAs;
	int upgradeSc;
	int upgradeAp;
	int idleFrame;
	int attackFrame;
	int skillFrame;
	string skullName;
	string EffectName;
}SKULLDATA;

typedef struct EnemyData
{
	int damage;
	int attackSpeed;
	int moveSpeed;
	int healthPoint;
	int idleFrame;
	int attackFrame;
	int dieFrame;
	string enemyName;
	string EffectName;
	int id;
}ENEMYDATA;

// enum, struct, .h, #define


#define WINSIZE_X	440
#define WINSIZE_Y	880
#define WINSTART_X	50
#define WINSTART_Y	50


#define ISO_TILE_X	5
#define ISO_TILE_Y	15


#define ISO_TILE_SIZE_X 84
#define ISO_TILE_SIZE_Y 42

#define ISO_TILE_HALF_SIZE_X (ISO_TILE_SIZE_X / 2)
#define ISO_TILE_HALF_SIZE_Y (ISO_TILE_SIZE_Y / 2)

#define ISO_START_X 12
#define ISO_START_Y 227	

#define INVEN_START_Y 590
#define INVEN_START_U 12
#define INVEN_START_I 190

typedef struct tagIsoTile
{
	int x, y;
	int tileNum;
	RECT rc;
	class Skull* skull = nullptr;
	bool isEmpty = true;
}ISOTILE;

typedef struct tileNumInfo
{
	int idX;
	int idY;
}TILE_NUM_INFO;

typedef struct tagStorage
{
	POINT storagePos;
	bool isEmpty;
	int Id;
	RECT storageRc;
	class Skull* skullTile;
}STORAGE;



#define PI         3.141592

#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}

#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#include "MacroFunction.h"
#include "UnitDataBase.h"
