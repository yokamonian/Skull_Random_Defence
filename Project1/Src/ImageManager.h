#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Image;
/// <summary>
/// ImageManager : 이미지 파일을 관리하기 위한 매니저 클래스
/// </summary>
class ImageManager : public SingletonBase<ImageManager>
{
private:
	map<string, Image*> mapImageDatas;
public:
	// 초기화 & 해제
	virtual HRESULT Init();
	virtual void Release();
	// 이미지 추가
	Image* AddImage(string strKey, int width, int height);
	Image* AddImage(string strKey, const char* fileName, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);
	Image* AddImage(string strKey, const char * fileName,
		float x, float y, int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans, COLORREF transColor);
	// 이미지 찾기
	Image* FindImage(string strKey);

	void DeleteImage(string strKey);
	void DeleteAll();
	ImageManager();
	~ImageManager();
};

