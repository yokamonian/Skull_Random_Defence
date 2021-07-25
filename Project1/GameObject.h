#pragma once
#include "GameNode.h"

/// <summary>
/// GamaObject : 게임 내 등장하는 모든 오브젝트의 상위 클래스.
/// </summary>
class GameObject : public GameNode
{
protected:

	int currFrameX;
	int currFrameY;
	int frame;

public:
	virtual HRESULT Init() = 0;			// 초기화
	virtual void Release() = 0;			// 해제
	virtual void Update() = 0;			// 업데이트
	virtual void Render(HDC hdc) = 0;	// 랜더

	GameObject();
	virtual~GameObject();
};

