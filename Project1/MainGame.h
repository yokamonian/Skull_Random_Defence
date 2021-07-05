#pragma once
#include "GameNode.h"



class MainGame : public GameNode
{
private:
	bool isInit;
	HANDLE hTimer;
	//Image* skullImg;
	Image* backBuffer;
	HDC hdc;
	GameNode* inGameScene;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);




	MainGame();
	virtual ~MainGame();
};

