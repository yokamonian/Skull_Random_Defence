#pragma once
#include "pch.h"
#include "SingletonBase.h"
#include <bitset>

using namespace std;

#define KEY_MAX_COUNT	256	

class KeyManager : public SingletonBase<KeyManager>
{
	//protected:
	//	static KeyManager* instance;
	//
	//	SingletonBase() {};
	//	~SingletonBase() {};
	//
	//public:
	//	static KeyManager* GetSingleton();	// instance�� �ܺο� ����
	//	void ReleaseSingleton();	// �޸� �Ҵ�� instance ����
private:
	bitset<KEY_MAX_COUNT>	keyUp;
	bitset<KEY_MAX_COUNT>	keyDown;

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyDown(int key);	// Ű�� �ѹ� ������ ��
	bool IsOnceKeyUp(int key);		// Ű�� ������ ���� ��
	bool IsStayKeyDown(int key);	// Ű�� ������ ���� ��

	bitset<KEY_MAX_COUNT> GetKeyUp() { return keyUp; }
	bitset<KEY_MAX_COUNT> GetKeyDown() { return keyDown; }

	void SetKeyUp(int key, bool state) { keyUp.set(key, state); }
	void SetKeyDown(int key, bool state) { keyDown.set(key, state); }

	KeyManager();
	~KeyManager();
};

