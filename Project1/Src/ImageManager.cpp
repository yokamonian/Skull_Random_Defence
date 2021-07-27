#include "ImageManager.h"
#include "Image.h"



HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	DeleteAll();
}

Image* ImageManager::AddImage(string strKey, int width, int height)
{
	// 이미지 검색(기존의 이미지가 존재하는 경우) 후 반환
	Image* image = FindImage(strKey);
	if (image) return image;

	// 이미지 추가
	image = new Image();
	if (FAILED(image->Init(width, height)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}
	// 이미지 + 키워드 저장
	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image* ImageManager::AddImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image();
	if (FAILED(image->Init(fileName, width, height, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image* ImageManager::AddImage(string strKey, const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image();
	if (FAILED(image->Init(fileName, x, y, width, height, keyFrameX, keyFrameY, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image * ImageManager::FindImage(string strKey)
{
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end())
	{
		return iter->second;
	}

	return nullptr;
}

void ImageManager::DeleteImage(string strKey)
{
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end())
	{
		// second(value)를 메모리 해제
		(iter->second)->Release();
		SAFE_DELETE((iter->second));
		// key, value (pair) 를 메모리 해제
		mapImageDatas.erase(iter);
	}
}

void ImageManager::DeleteAll()
{
	map<string, Image*>::iterator iter;
	for (iter = mapImageDatas.begin(); iter != mapImageDatas.end(); /*iter++*/)
	{
		if (iter->second != nullptr)
		{
			// second(value)를 메모리 해제
			(iter->second)->Release();
			SAFE_DELETE((iter->second));
			// key, value (pair) 를 메모리 해제
			iter = mapImageDatas.erase(iter);
			// 지금 삭제하는 요소의 다음 요소를 자동으로 반환
		}
		else
		{
			iter++;
		}
	}

	// 맵을 메모리 해제
	mapImageDatas.clear();
}


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}
