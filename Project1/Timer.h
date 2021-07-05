#pragma once
#include "pch.h"


class Timer
{
private:
	bool			isHardware;				// �ϵ����� �����ϴ� ���� Ÿ�̸Ӹ� �� �� �ִ� �� ����
	float			timeScale;				// (���� Ÿ�̸Ӱ� �����ϴ� ��� �������� �ʴ� �������� �����) �������� �ð������� ��ȯ
	float			timeElapsed;			// ������ �ð��� ���� �ð��� �����DT(Delta Time)				
	__int64			currTime;				// ���� �ð�(���� Ÿ�̸� ��)
	__int64			lastTime;				// ���� �ð�(���� Ÿ�̸� ��)
	__int64			periodFrequency;		// ���� Ÿ�̸��� ���ļ�(�ʴ� ������), �������� ������ 0 ��ȯ

	unsigned long	frameRate;
	unsigned long	FPSFrameCount;
	float			FPSTimeElapsed;
	float			worldTime;
	bool			isGameStart;

public:
	HRESULT Init();
	void Tick(float lockFPS = 0.0f);
	unsigned long GetFrameRate() { return frameRate; }
	float GetWorldTime() { return worldTime; }
	__int64 GetCurrTime() { return currTime; }
	float GetDeltaTime() { return timeElapsed; }

	void SetGameStart(bool _isGameStart) { isGameStart = _isGameStart; }
	void ResetWt() { worldTime = 0; }

	Timer();
	~Timer();
};

