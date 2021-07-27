#pragma once
#include "pch.h"

/// <summary>
/// Image : 각종 이미지 정보를 담는 클래스.
/// </summary>
class Image
{
public:
	// 이미지 정보 타입
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,
		FILE,
		EMPTY,
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// 리소스의 고유한 아이디
		HDC		hMemDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int		width;		// 이미지 가로 크기
		int		height;		// 이미지 세로 크기
		BYTE	loadType;	// 로드 타입

		HDC		hBlendDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hBlendBitmap;	// 이미지 정보
		HBITMAP hBlendOldBit;	// 기존 이미지 정보
		int		blendMaxSize;

		HDC		hRotateDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hRotateBitmap;	// 이미지 정보
		HBITMAP hRotateOldBit;	// 기존 이미지 정보
		int		rotateMaxSize;

		float	x;					// 출력 위치 좌표
		float	y;					// 출력 위치 좌표
		int		currentKeyFrameX;	// 현재 키프레임 인덱스
		int		currentKeyFrameY;
		int		maxKeyFrameX;		// 최대 키프레임 수
		int		maxKeyFrameY;
		int		keyFrameWidth;		// 키프레임 당 크기
		int		keyFrameHeight;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			x = 0.0f;
			y = 0.0f;
			currentKeyFrameX = 0;
			currentKeyFrameY = 0;
			maxKeyFrameX = 0;
			maxKeyFrameY = 0;
			keyFrameWidth = 0;
			keyFrameHeight = 0;
		}
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;			// 이미지정보 구조체 포인터
	char* fileName;			// 파일경로 + 이름
	bool		isTrans;			// 투명화 여부
	COLORREF	transColor;			// 투명화할 색
	BLENDFUNCTION	blendFunc;
	RECT		rt;
	double		dblAngle;
	int			ixRotateAxis;
	int			iyRotateAxis;
	int			ixDisplay;
	int			iyDisplay;
	double		dlbSizeRatio;
	HBITMAP		hMaskBmp;
	int			ixMask;
	int			iyMask;
public:
	// 빈 비트맵 이미지를 만든다.
	HRESULT Init(int width, int height);

	// 리소스로부터 데이터를 읽어서 만든다.
	HRESULT Init(const DWORD resID, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 데이터를 읽어서 만든다.
	HRESULT Init(const char* fileName, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// 이미지 + 키프레임 초기화
	HRESULT Init(const char* fileName, float x, float y,
		int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);
	void Release();

	void Render(HDC hdc, int destX, int destY);
	void BlankRender(HDC hdc, int destX, int destY);
	void GageRender(HDC hdc, int destX, int destY, int gage);

	void Render(HDC hdc, int destX, int destY, int sourceX, int sourceY);

	void BGRender(HDC hdc, int destX, int destY, int sourceX, int sourceY);

	void FrameRender(HDC hdc, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, float scale = 1.0f);

	//알파 랜더
	void AlphaRender(HDC hdc, BYTE alpha, int destX, int destY, bool isTrans);
	void AlphaFrameRender(HDC hdc, BYTE alpha, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, bool isTrans, float scale = 1.0f);
	void RotateRender(HDC hdc, double dblAngle,
		int destX, int destY, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);
	// 회전 & 알파
	void RotateAlphaRender(HDC hdc, double dblAngle,
		int destX, int destY, BYTE alpha = 255, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);
	void RotateFrameRender(HDC hdc, double dblAngle,
		int currentKeyFrameX, int currentKeyFrameY,
		int destX, int destY, float scale = 1.0f,
		double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);
	void RotateAlphaFrameRender(HDC hdc, int destX, int destY, double dblAngle,
		int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, float scale = 1.0f, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);


	HDC GetMemDC() { return imageInfo->hMemDC; }

	int GetMaxKeyFrameX() { return imageInfo->maxKeyFrameX; }
	int GetMaxKeyFrameY() { return imageInfo->maxKeyFrameY; }


	Image();
	~Image();
};

