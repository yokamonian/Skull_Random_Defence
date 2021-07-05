#pragma once
#include "GameNode.h"


class GameObject : public GameNode
{
protected:

	int currFrameX;
	int currFrameY;
	int frame;

public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	GameObject();
	virtual~GameObject();
};

