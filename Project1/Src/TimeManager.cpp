#include "TimeManager.h"
#include "Timer.h"


HRESULT TimeManager::Init()
{
	timer = new Timer();
	timer->Init();

	testTime = 0.0f;
	waveTime = 0.0f;
	isTestStart = false;
	return S_OK;
}

void TimeManager::Release()
{
	SAFE_DELETE(timer);
}

void TimeManager::Update(float lockFPS)
{
	// 타이머 함수 실행
	if (timer)
	{
		timer->Tick(lockFPS);
	}
	// 알고리즘 시작시 실행
	if (isTestStart)
	{
		testTime += timer->GetDeltaTime();
	}
	// 웨이브 시작 시 실행
	if (isWaveStart)
	{
		waveTime += timer->GetDeltaTime();
	}
}

void TimeManager::Render(HDC hdc)
{
	// 프레임 및 월드타임 표기
#ifdef _DEBUG
	if (timer)
	{
		SetBkMode(hdc, TRANSPARENT);

		wsprintf(strText, "FPS : %d", timer->GetFrameRate());
		TextOut(hdc, 10, 10, strText, strlen(strText));

		sprintf_s(strText, "WorldTime : %.2f", timer->GetWorldTime());
		TextOut(hdc, 10, 30, strText, strlen(strText));
	}
#endif
}

float TimeManager::GetWorldCount()
{
	return timer->GetWorldTime();
}

float TimeManager::GetCurrTime()
{
	return timer->GetCurrTime();
}

float TimeManager::GetDeltaTime()
{
	if (timer)
	{
		return timer->GetDeltaTime();
	}
	return 0.0f;
}

void TimeManager::ResetWt()
{
	timer->ResetWt();
}



