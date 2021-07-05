#define _CRT_SECURE_NO_WARNINGS

#include "MainGame.h"
#include "pch.h"



// ��������
HINSTANCE	g_hInstance;	// ���α׷� �ν��Ͻ� �ڵ�
HWND		g_hWnd;			// ������ �ڵ�
LPSTR		g_lpszClass = (LPSTR)TEXT("�������� ����");

POINT		g_ptMouse;

MainGame mainGame;



void SetWindowSize(int x, int y, int width, int height);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// �����츦 �����ϱ� ���� �Լ�
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	srand(time(NULL));

	// ������ ������ ���� �⺻����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;	// ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X, WINSTART_Y,
		WINSIZE_X, WINSIZE_Y,
		NULL,
		NULL,
		g_hInstance,
		NULL);

	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	// ������ �۾����� ����
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	// ���ΰ��� �ʱ�ȭ
	if (mainGame.Init())
	{
		return 0;
	}

	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TimeManager::GetSingleton()->Update(30);


			mainGame.Update();
			mainGame.Render();
		}
	}
	// ����
	mainGame.Release();

	return message.wParam;
}


void SetWindowSize(int x, int y, int width, int height)
{
	// ������ �۾����� ����
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = width; rc.bottom = height;

	// ���� ������ ũ�� �޾ƿ´�.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// �̵�
	MoveWindow(g_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	return mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}