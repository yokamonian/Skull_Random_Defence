#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Timer;
/// <summary>
/// TimeManager : Time 클래스를 활용. 게임 내 각종 타이머 매니저 클래스.
/// </summary>
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* timer;		// 타이머
	char strText[256];
	float testTime;		// 알고리즘 내 시간측정 변수
	float waveTime;		// 웨이브 시간
	bool isTestStart;	// 알고리즘 시작 여부
	bool isGameStart;	// 게임 시작 여부
	bool isWaveStart;	// 웨이브 시작여부

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

