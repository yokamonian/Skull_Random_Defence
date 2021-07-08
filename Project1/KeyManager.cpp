#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	// 초기화
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		SetKeyDown(i, false);
		SetKeyUp(i, true);
	}

	return S_OK;
}

void KeyManager::Release()
{
}

// 키를 한번 눌렀을 때
bool KeyManager::IsOnceKeyDown(int key)
{
	// GetAsyncKeyState(VK_...)	
	/*
		1. 0x0000 => 이전 프레임에 누른 적이 없고 호출시점에도 눌려있지 않음
		2. 0x0001 => 이전 프레임에 누른 적이 있고 호출시점에는 눌려있지 않음
		3. 0x8000 => 이전 프레임에 누른 적이 없고 호출시점에는 눌려있는 상태
		4. 0x8001 => 이전 프레임에 누른 적이 있고 호출시점에도 눌려있는 상태
	*/
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// 누른 판정이 없다면
		if (!this->GetKeyDown()[key])
		{
			this->SetKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->SetKeyDown(key, false);
	}

	return false;
}

// 키를 눌렀다 뗐을 때
bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->SetKeyUp(key, false);
	}
	else
	{
		if (!this->GetKeyUp()[key])
		{
			this->SetKeyUp(key, true);
			return true;
		}
	}

	return false;
}

// 키를 누르고 있을 때
bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}
