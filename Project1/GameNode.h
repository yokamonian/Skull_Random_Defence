#pragma once
#include "pch.h"

/// <summary>
/// GameNode : ������ ��� ������Ʈ ��� Ŭ������ ���� Ŭ����.
/// </summary>
class GameNode
{
protected:
	POINT pos;

	int sceneType;

public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	POINT GetPos() { return pos; }
	int GetSceneType() { return sceneType; }
	GameNode();
	virtual ~GameNode();
};

