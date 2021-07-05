#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Timer;
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* timer;
	char strText[256];
	float testTime;
	float waveTime;
	bool isTestStart;
	bool isGameStart;
	bool isWaveStart;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float lockFPS = 0.0f);
	virtual void Render(HDC hdc);


	float GetWorldCount();
	float GetCurrTime();

	bool GetIsTestStart() { return isTestStart; }
	float GetDeltaTime();
	void SetIsTestStart(bool b) { isTestStart = b; }
	void SetIsGameStart(bool _isGameStart) { isGameStart = _isGameStart; }
	float GetTestTime() { return testTime; }
	void ResetTestTime() { testTime = 0; }
	float GetWaveTime() { return waveTime; }
	void SetIsWaveTime(bool _isWaveTime) { isWaveStart = _isWaveTime; }
	void ResetWaveTime() { waveTime = 0; }

	void ResetWt();
	Timer* GetTimer() { return timer; }
};

