#pragma once
#include "GameNode.h"

class Image;


class TitleScene : public GameNode
{
private:
	Image* bg;
	Image* tank;
	FPOINT menuPointer;
	FPOINT pos;
	int elapsedTime;
	int currFrameX;
	bool isRender = false;
	FPOINT menuPos[3] = { {480.0f, 425.0f}, {480.0f, 475.0f} ,{480.0f, 525.0f} };
	int menuNum;
	int addFrameX;

public:

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	
	/*static void click1();
	static void click2();*/

	TitleScene();
	virtual ~TitleScene();
};

