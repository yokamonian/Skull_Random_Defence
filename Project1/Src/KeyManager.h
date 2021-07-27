#pragma once
#include "pch.h"
#include "SingletonBase.h"
#include <bitset>

using namespace std;

#define KEY_MAX_COUNT	256	

/// <summary>
/// KeyManager : 키 입력 관리 매니저 클래스
/// </summary>
class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEY_MAX_COUNT>	keyUp;
	bitset<KEY_MAX_COUNT>	keyDown;

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	// 키를 한번 눌렀을 때
	bool IsOnceKeyUp(int key);		// 키를 눌렀다 뗐을 때
	bool IsStayKeyDown(int key);	// 키를 누르고 있을 때

	// 판정
	bitset<KEY_MAX_COUNT> GetKeyUp() { return keyUp; }
	bitset<KEY_MAX_COUNT> GetKeyDown() { return keyDown; }

	void SetKeyUp(int key, bool state) { keyUp.set(key, state); }
	void SetKeyDown(int key, bool state) { keyDown.set(key, state); }

	KeyManager();
	~KeyManager();
};

