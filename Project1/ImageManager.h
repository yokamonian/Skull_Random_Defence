#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Image;
class ImageManager : public SingletonBase<ImageManager>
{
private:
	map<string, Image*> mapImageDatas;
public:
	// �ʱ�ȭ & ����
	virtual HRESULT Init();
	virtual void Release();
	// �̹��� �߰�
	Image* AddImage(string strKey, int width, int height);
	Image* AddImage(string strKey, const char* fileName, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);
	Image* AddImage(string strKey, const char * fileName,
		float x, float y, int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans, COLORREF transColor);
	// �̹��� ã��
	Image* FindImage(string strKey);

	void DeleteImage(string strKey);
	void DeleteAll();
	ImageManager();
	~ImageManager();
};

