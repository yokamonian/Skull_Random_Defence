#pragma once
#include "pch.h"

/// <summary>
/// GameNode : 게임의 모든 오브젝트 기반 클래스의 상위 클래스.
/// </summary>
class GameNode
{
protected:
	POINT pos;

	int sceneType;

public:
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	POINT GetPos() { return pos; }
	int GetSceneType() { return sceneType; }
	GameNode();
	virtual ~GameNode();
};

