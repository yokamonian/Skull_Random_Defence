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
	Image* image = FindImage(strKey);
	if (image) return image;

	image = new Image();
	if (FAILED(image->Init(width, height)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

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
		(iter->second)->Release();
		SAFE_DELETE((iter->second));

		mapImageDatas.erase(iter);	// 맵이 가지고 있던 데이터중 해당 이터레이터를 삭제 예를 들면 10개였던게 9개가 됨
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