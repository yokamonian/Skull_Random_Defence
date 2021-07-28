#pragma once
#include "pch.h"

/// <summary>
/// 게임 내 프레임에 관련된 클래스.
/// </summary>
class Timer
{
private:
	bool			isHardware;				// 하드웨어에서 제공하는 고성능 타이머를 쓸 수 있는 지 여부
	float			timeScale;				// (고성능 타이머가 제공하는 경과 진동수를 초당 진동수로 나누어서) 진동수를 시간단위로 변환
	float			timeElapsed;			// 마지막 시간과 현재 시간의 경과량DT(Delta Time)				
	__int64			currTime;				// 현재 시간(고성능 타이머 값)
	__int64			lastTime;				// 이전 시간(고성능 타이머 값)
	__int64			periodFrequency;		// 고성능 타이머의 주파수(초당 진동수), 지원하지 않으면 0 반환

	unsigned long	frameRate;				// 프레임 수
	unsigned long	FPSFrameCount;			// 초당 프레임
	float			FPSTimeElapsed;			// 프레임 경과량
	float			worldTime;				// 월드 타임
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

