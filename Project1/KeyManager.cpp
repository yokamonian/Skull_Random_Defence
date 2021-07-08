#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	// �ʱ�ȭ
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

// Ű�� �ѹ� ������ ��
bool KeyManager::IsOnceKeyDown(int key)
{
	// GetAsyncKeyState(VK_...)	
	/*
		1. 0x0000 => ���� �����ӿ� ���� ���� ���� ȣ��������� �������� ����
		2. 0x0001 => ���� �����ӿ� ���� ���� �ְ� ȣ��������� �������� ����
		3. 0x8000 => ���� �����ӿ� ���� ���� ���� ȣ��������� �����ִ� ����
		4. 0x8001 => ���� �����ӿ� ���� ���� �ְ� ȣ��������� �����ִ� ����
	*/
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// ���� ������ ���ٸ�
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

// Ű�� ������ ���� ��
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

// Ű�� ������ ���� ��
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
