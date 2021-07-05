#include "Animation.h"

Animation::Animation()
	: frameCount(0)
	, frameWidth(0)
	, frameHeight(0)
	, isLoop(false)
	, nowPlayIdx(0)
	, isPlaying(false)
	, keyFrameUpdateTime(0.0f)
	, accumulateTime(0.0f)
	
{
}

Animation::~Animation()
{
}

HRESULT Animation::Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight)
{
	// ���� ������ ��
	int frameWidthCount = totalWidth / frameWidth;

	// ���� ������ �� 
	int frameHeightCount = totalHeight / frameHeight;

	// ��ü ������ ��
	frameCount = frameWidthCount * frameHeightCount;

	// ������ ��ġ ����Ʈ ����
	vecFrameList.clear();
	vecFrameList.resize(frameCount);

	for (int i = 0; i < frameHeightCount; i++)
	{
		for (int j = 0; j < frameWidthCount; j++)
		{
			//POINT framePos = {i * frameHeight, j * frameWidth};

			vecFrameList[i * frameWidthCount + j].x = j * frameWidth;
			vecFrameList[i * frameWidthCount + j].y = i * frameHeight;

			//vecFrameList[i*frameWidthCount + j] = framePos;
		}
	}


	// �⺻ �÷��� ����Ʈ ����
	SetPlayFrame();


	return S_OK;
}

void Animation::SetPlayFrame(bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		//������
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);
		}

		//������
		for (int i = frameCount-1; i > 0; i--)
		{
			vecPlayList.push_back(i);
		}
	}
	else
	{
		//������
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i); 
		}
	}


}

void Animation::SetPlayFrame(int startFrame, int endFrame, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	// startFrame�� 0���� ũ�ų� ���� endFrame�� ������ frame���� �۰ų� ���� ��

	if (startFrame == endFrame)
	{
		Stop();
		return;
	}

	if (startFrame > endFrame)
	{
		if (isReverse)
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = 0; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = endFrame-1; i >- 1; i--)
			{
				vecPlayList.push_back(i);
			}

			for (int i = frameCount - 1; i >= startFrame; i--)
			{
				vecPlayList.push_back(i);
			}


		}
		else
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = 0; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
	else
	{
		if (isReverse)
		{
			//������
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}

			//������
			for (int i = endFrame - 1; i > startFrame; i--)
			{
				vecPlayList.push_back(i);
			}
		}
		else
		{
			//������
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
}

void Animation::SetPlayFrame(int * arr, int arrLength, bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}

		for (int i = arrLength - 1; i >= 0; i--)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrLength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
}

void Animation::UpdateKeyFrame(float dt)
{
	if (isPlaying)
	{
		accumulateTime += dt;

		if (accumulateTime >= keyFrameUpdateTime)
		{
			nowPlayIdx++;

			if (nowPlayIdx >= vecPlayList.size())
			{
				// ������ ��
				if (isLoop)
				{
					nowPlayIdx = 0;
				}
				else
				{
					nowPlayIdx--;
					isPlaying = false;
				}
			}

			accumulateTime -= keyFrameUpdateTime;
			/*accumulateTime = 0.0f;*/ //���� �� ��Ȯ�ϴ�
		}
	}

	
}

void Animation::Start()
{
	nowPlayIdx = 0;
	isPlaying = true;
}

void Animation::Stop()
{
	nowPlayIdx = 0;
	isPlaying = false;

}

void Animation::Pause()
{
	isPlaying = false;
}

void Animation::Resume()
{
	isPlaying = true;
}
