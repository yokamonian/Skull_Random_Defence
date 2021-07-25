#pragma once
#include "GameNode.h"

/// <summary>
/// GamaObject : ���� �� �����ϴ� ��� ������Ʈ�� ���� Ŭ����.
/// </summary>
class GameObject : public GameNode
{
protected:

	int currFrameX;
	int currFrameY;
	int frame;

public:
	virtual HRESULT Init() = 0;			// �ʱ�ȭ
	virtual void Release() = 0;			// ����
	virtual void Update() = 0;			// ������Ʈ
	virtual void Render(HDC hdc) = 0;	// ����

	GameObject();
	virtual~GameObject();
};

