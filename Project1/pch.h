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

// �Ʊ� ���� ������ ���̽�
typedef struct SkullData
{
	int damage;			// ������
	int attackSpeed;	// ����
	int abilityPower;	// ��ų ������
	int skillCount;		// ��ų�� �ʿ��� Ÿ�ݼ�
	int growthDmg;		// ���� ������(ų)
	int growthAp;		// ���� ��ų ������(ų)
	int upgradeDmg;		// ���޾� ������
	int upgradeAs;		// ���޾� ����
	int upgradeSc;		// ���޾� ��ų�� �ʿ��� Ÿ�ݼ�
	int upgradeAp;		// ���޾� ��ų������
	int idleFrame;		// �⺻ ���� �ִϸ��̼� ������
	int attackFrame;	// ���� ���� �ִϸ��̼� ������
	int skillFrame;		// ��ų ���� �ִϸ��̼� ������
	string skullName;	// ���� �̸�
	string EffectName;	// ��ų ����Ʈ �̸�
}SKULLDATA;

// ���� ���� ������ ���̽�
typedef struct EnemyData
{
	int damage;			// ������
	int attackSpeed;	// ����
	int moveSpeed;		// �̼�
	int healthPoint;	// ü��
	int idleFrame;		// �⺻ ���� �ִϸ��̼� ������
	int attackFrame;	// ���� ���� �ִϸ��̼� ������
	int dieFrame;		// ��� ���� �ִϸ��̼� ������
	string enemyName;	// �� �̸�
	string EffectName;	// �� ��ų ����Ʈ �̸�
	int id;				// id��
}ENEMYDATA;

// enum, struct, .h, #define

// �ܼ� â ũ��
#define WINSIZE_X	440
#define WINSIZE_Y	880
#define WINSTART_X	50
#define WINSTART_Y	50

// Ÿ�� ���� ���� ����
#define ISO_TILE_X	5
#define ISO_TILE_Y	15

// Ÿ�� ���� ���� ũ��
#define ISO_TILE_SIZE_X 84
#define ISO_TILE_SIZE_Y 42
#define ISO_TILE_HALF_SIZE_X (ISO_TILE_SIZE_X / 2)
#define ISO_TILE_HALF_SIZE_Y (ISO_TILE_SIZE_Y / 2)

// Ÿ�� ���� ��ǥ
#define ISO_START_X 12
#define ISO_START_Y 227	

// �κ� ���� ��ǥ
#define INVEN_START_Y 590
#define INVEN_START_U 12
#define INVEN_START_I 190

// ����(Ÿ��) �̹��� ����
typedef struct tagIsoTile
{
	int x, y;
	int tileNum;
	RECT rc;
	class Skull* skull = nullptr;
	bool isEmpty = true;
}ISOTILE;

// Ÿ�� ��ǥ
typedef struct tileNumInfo
{
	int idX;
	int idY;
}TILE_NUM_INFO;

// �κ��丮 ����
typedef struct tagStorage
{
	POINT storagePos;
	bool isEmpty;
	int Id;
	RECT storageRc;
	class Skull* skullTile;
}STORAGE;


// �̹��� ���� ����
#define PI         3.141592
#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}
#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

// ��������ȭ
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#include "MacroFunction.h"
#include "UnitDataBase.h"
