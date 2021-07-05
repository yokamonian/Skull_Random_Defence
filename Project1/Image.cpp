#include "Image.h"
#pragma comment(lib, "msimg32.lib")




HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	int maxSize = width > height ? width : height;

	// Blend
	imageInfo->blendMaxSize = maxSize * 2;
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate

	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool trans, COLORREF transColor)
{
	return E_NOTIMPL;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	int maxSize = width > height ? width : height;

	isTrans = trans;
	this->transColor = transColor;

	// Blend
	imageInfo->blendMaxSize = maxSize * 2;
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const char* fileName,
	float x, float y, int width, int height,
	int keyFrameX, int keyFrameY,
	bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	// 추가
	imageInfo->x = x - (width / 2);
	imageInfo->y = y - (height / 2);
	imageInfo->currentKeyFrameX = 0;
	imageInfo->currentKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;
	imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->keyFrameWidth = width / keyFrameX;
	imageInfo->keyFrameHeight = height / keyFrameY;
	int maxSize = (width / keyFrameX) > imageInfo->keyFrameHeight ? (width / keyFrameX) : imageInfo->keyFrameHeight;
	isTrans = trans;
	this->transColor = transColor;

	// Blend
	imageInfo->blendMaxSize = maxSize * 2;
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		delete imageInfo;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2), destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		// 메모리에 있는 데이터를 화면에 고속복사한다.
		BitBlt(hdc,				// 복사 목적지 DC
			destX,
			destY, 		// 복사 시작 위치
			imageInfo->width,	// 원본에서 복사될 가로 크기
			imageInfo->height,	// 원본에서 복사될 세로 크기
			imageInfo->hMemDC,	// 원본 DC
			0, 0,				// 원본에서 복사 시작 위치
			SRCCOPY);			// 복사 옵션
	}
}

void Image::BlankRender(HDC hdc, int destX, int destY)
{
	GdiTransparentBlt(
		hdc,
		destX, destY,
		imageInfo->width, imageInfo->height,

		imageInfo->hMemDC,
		0, 0,
		imageInfo->width, imageInfo->height,
		transColor
	);
}

void Image::GageRender(HDC hdc, int destX, int destY, int gage)
{
	GdiTransparentBlt(
		hdc,
		destX, destY,
		gage,
		imageInfo->height,

		imageInfo->hMemDC,
		0, 0,
		gage, imageInfo->height,
		transColor
	);
}

void Image::Render(HDC hdc, int destX, int destY, int sourceX, int sourceY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2), destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		// 메모리에 있는 데이터를 화면에 고속복사한다.
		BitBlt(hdc,				// 복사 목적지 DC
			destX,
			destY, 		// 복사 시작 위치
			imageInfo->width - sourceX,	// 원본에서 복사될 가로 크기
			imageInfo->height,	// 원본에서 복사될 세로 크기
			imageInfo->hMemDC,	// 원본 DC
			sourceX, 0,				// 원본에서 복사 시작 위치
			SRCCOPY);			// 복사 옵션

		BitBlt(hdc,				// 복사 목적지 DC
			imageInfo->width - sourceX,
			destY, 		// 복사 시작 위치
			sourceX,	// 원본에서 복사될 가로 크기
			imageInfo->height,	// 원본에서 복사될 세로 크기
			imageInfo->hMemDC,	// 원본 DC
			0, 0,				// 원본에서 복사 시작 위치
			SRCCOPY);			// 복사 옵션

	}
}

void Image::BGRender(HDC hdc, int destX, int destY, int sourceX, int sourceY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX, destY,
			WINSIZE_X, WINSIZE_Y,

			imageInfo->hMemDC,
			sourceX, 0,
			WINSIZE_X, WINSIZE_Y,
			transColor
		);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, float scale)
{
	// 현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->keyFrameWidth * scale / 2), destY - (imageInfo->keyFrameHeight * scale / 2),
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);
	}

}


void Image::AlphaRender(HDC hdc, BYTE alpha, int destX, int destY, bool isTrans)
{
	// 1. 출력해야 되는 DC에 그려져 있는 내용을 blendDC에 복사
	// 2. 출력할 이미지를 blendDC에 지정한 색상을 제외해서 복사
	// 3. blendDC에 내용을 목적지 DC에 복사
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		Image* blendDC = ImageManager::GetSingleton()->AddImage("Key", imageInfo->width, imageInfo->height);

		/*HBITMAP hBitmap = CreateCompatibleBitmap(hdc, imageInfo->width, imageInfo->height);
		SelectObject(blendDC, hBitmap);*/

		BitBlt(blendDC->GetMemDC(), 0, 0, imageInfo->width, imageInfo->height, hdc, destX - (imageInfo->width / 2), destY - (imageInfo->height / 2), SRCCOPY);
		GdiTransparentBlt(blendDC->GetMemDC(), 0, 0, imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, RGB(255, 0, 255));

		AlphaBlend(hdc, destX - (imageInfo->width / 2), destY - (imageInfo->height / 2), imageInfo->width, imageInfo->height, blendDC->GetMemDC(), 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}

	else
	{
		AlphaBlend(hdc, destX, destY, imageInfo->width, imageInfo->height, imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}
}

void Image::AlphaFrameRender(HDC hdc, BYTE alpha, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, bool isTrans, float scale)
{
	blendFunc.SourceConstantAlpha = alpha;
	// 현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	if (isTrans)
	{
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), SRCCOPY);
		GdiTransparentBlt(
			imageInfo->hBlendDC,
			0, 0, imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor);
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);

	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);
	}

}

void Image::RotateRender(HDC hdc, double dblAngle,
	int destX, int destY, double dblSizeRatio/* = 1*/,
	HBITMAP hMaskBmp/* = NULL*/, int ixMask/* = 0*/, int iyMask/* = 0*/)
{
	int i;
	POINT apt[3] = { 0 };
	double dblWidth = (double)imageInfo->width * dblSizeRatio;
	double dblHeight = (double)imageInfo->height * dblSizeRatio;
	double ixRotate = (int)((double)(imageInfo->width / 2) * dblSizeRatio); // 크기가 변하는 것 고려
	double iyRotate = (int)((double)(imageInfo->height / 2) * dblSizeRatio);
	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. 회전축을 기준으로 상대좌표를 구하고
	// 2. 회전후 위치좌표(상대좌표)를 얻은 후
	// 3. 얻은 값을 원래의 좌표에 적용.
	for (i = 0; i < 3; i++)
	{
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  꼭지점 부분
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up 꼭지점 부분
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low 꼭지점 부분
		dblxDest = dblx * cosVal - dbly * sinVal;
		dblyDest = dblx * sinVal + dbly * cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = destX - (long)ixRotate + (long)dblxDest;
		apt[i].y = destY - (long)iyRotate + (long)dblyDest;
	}

	PlgBlt(hdc, apt, imageInfo->hMemDC, 0, 0,
		imageInfo->width, imageInfo->height, hMaskBmp, ixMask, iyMask);
}

void Image::RotateAlphaRender(HDC hdc, double dblAngle, int destX, int destY, BYTE alpha, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	// 투명도
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. 목적지 DC에 그려져 있는 내용을 blend DC에 복사
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->blendMaxSize, imageInfo->blendMaxSize,
			hdc,
			destX - (imageInfo->blendMaxSize / 2),
			destY - (imageInfo->blendMaxSize / 2), SRCCOPY);

		// 2. 이미지를 회전시켜서 Rotate DC에 복사
		RECT rc = { 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize };
		HBRUSH hBrush = CreateSolidBrush(transColor);
		FillRect(imageInfo->hRotateDC, &rc, hBrush);
		DeleteObject(hBrush);

		RotateRender(imageInfo->hRotateDC, dblAngle,
			imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);
		//RotateFrameRender(imageInfo->hRotateDC, dblAngle, imageInfo->rotateMaxSize /2, imageInfo->rotateMaxSize / 2,
		//	imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);


		// 3. Rotate DC 이미지를 blend DC에 지정한 색상을 제외해서 복사
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			imageInfo->blendMaxSize, imageInfo->blendMaxSize,

			imageInfo->hRotateDC,
			0, 0,
			imageInfo->blendMaxSize, imageInfo->blendMaxSize,
			transColor);

		// 4. blend DC에 내용을 목적지 DC에 복사
		AlphaBlend(hdc,
			destX - (imageInfo->blendMaxSize / 2),
			destY - (imageInfo->blendMaxSize / 2),
			imageInfo->blendMaxSize, imageInfo->blendMaxSize,
			imageInfo->hBlendDC, 0, 0, imageInfo->blendMaxSize, imageInfo->blendMaxSize,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::RotateFrameRender(HDC hdc, double dblAngle, int currentKeyFrameX, int currentKeyFrameY, int destX, int destY, float scale, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	// 현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	int i;
	POINT apt[3] = { 0 };
	double dblWidth = (double)imageInfo->keyFrameWidth * dblSizeRatio;
	double dblHeight = (double)imageInfo->keyFrameHeight * dblSizeRatio;
	double ixRotate = (int)((double)(imageInfo->keyFrameWidth / 2) * dblSizeRatio); // 크기가 변하는 것 고려
	double iyRotate = (int)((double)(imageInfo->keyFrameHeight / 2) * dblSizeRatio);
	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. 회전축을 기준으로 상대좌표를 구하고
	// 2. 회전후 위치좌표(상대좌표)를 얻은 후
	// 3. 얻은 값을 원래의 좌표에 적용.
	for (i = 0; i < 3; i++)
	{
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  꼭지점 부분
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up 꼭지점 부분
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low 꼭지점 부분
		dblxDest = dblx * cosVal - dbly * sinVal;
		dblyDest = dblx * sinVal + dbly * cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = destX - (long)ixRotate + (long)dblxDest;
		apt[i].y = destY - (long)iyRotate + (long)dblyDest;
	}

	PlgBlt(hdc, apt, imageInfo->hMemDC, imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX, imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
		imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, hMaskBmp, ixMask, iyMask);

}

void Image::RotateAlphaFrameRender(HDC hdc, int destX, int destY, double dblAngle, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, float scale, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. 목적지 DC에 그려져 있는 내용을 blend DC에 복사
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->blendMaxSize, imageInfo->blendMaxSize,
			hdc,
			destX - (imageInfo->blendMaxSize / 2),
			destY - (imageInfo->blendMaxSize / 2), SRCCOPY);

		// 2. 이미지를 회전시켜서 Rotate DC에 복사
		RECT rc = { 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize };
		HBRUSH hBrush = CreateSolidBrush(transColor);
		FillRect(imageInfo->hRotateDC, &rc, hBrush);
		DeleteObject(hBrush);
		
		//RotateRender(imageInfo->hRotateDC, dblAngle,
			//imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);
		RotateFrameRender(imageInfo->hRotateDC, dblAngle, imageInfo->currentKeyFrameX, imageInfo->currentKeyFrameY,
			imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);


		// 3. Rotate DC 이미지를 blend DC에 지정한 색상을 제외해서 복사
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			imageInfo->blendMaxSize * scale, imageInfo->blendMaxSize * scale,

			imageInfo->hRotateDC,
			0, 0,
			imageInfo->blendMaxSize * scale, imageInfo->blendMaxSize * scale,
			transColor);

		// 4. blend DC에 내용을 목적지 DC에 복사
		AlphaBlend(hdc,
			destX - (imageInfo->blendMaxSize / 2),
			destY - (imageInfo->blendMaxSize / 2),
			imageInfo->blendMaxSize, imageInfo->blendMaxSize,
			imageInfo->hBlendDC, 0, 0, imageInfo->blendMaxSize, imageInfo->blendMaxSize,
			blendFunc);
	}
}



Image::Image()
{
}


Image::~Image()
{
}
