#pragma once
#include "pch.h"

class Animation
{
private:
	// key frame ��ġ ����Ʈ->   //�����ϴ� ��ġ�� ������ �� �ִ� �ε���.
	vector<POINT> vecFrameList;	

	// �÷��� ����Ʈ -> //�� �� Ű �������� ������ �� �ִ°� 0�� 5�� �ְ� 1,2,3,4,5,6 ���� ������ �̷��� ����ǰ� -->�÷��� ����Ʈ�� �����.
	vector<int> vecPlayList;

	int frameCount;		// ��ü ������ ��
	int frameWidth;		// ������ ����ũ��
	int frameHeight;	// ������ ���� ũ��

	bool isLoop;		// �ݺ� �Ǵ��� ����
	int nowPlayIdx;		// ���� �÷��� ������ �ε���
	bool isPlaying;		// ���� �÷��� ������ ����

	float keyFrameUpdateTime;   // ������Ʈ ���� �ð� //������ ���� �긦 �ʰ��ϸ� ���� ���������� �ѱ���
	float accumulateTime;		//���� �ð�

public:
	Animation();
	~Animation();

	HRESULT Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight);
	void SetPlayFrame(bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int startFrame, int endFrame, bool isReverse = FALSE, bool isLoop = FALSE);
	void SetPlayFrame(int* arr, int arrLength, bool isReverse = FALSE, bool isLoop = FALSE);
	void UpdateKeyFrame(float dt); //�갡 ������Ʈ�� �Ǵ� ����(TimeManager�� elapsedTime), 

	void SetUpdateTime(int fps) { keyFrameUpdateTime = 1.0f / fps; } // �ɸ��͵鸶�� ����Ǵ� �ӵ��� �ٸ��� �� �� �ִ�.

	POINT GetFramePos() { return vecFrameList[vecPlayList[nowPlayIdx]]; }

	void Start();
	void Stop();
	void Pause();
	void Resume();
};

