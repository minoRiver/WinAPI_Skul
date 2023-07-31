#pragma once

#define MAX_LOADSTRING 100

class Texture;

class Core
{
	SINGLETON(Core);

public:
	const POINT& GetResolution() const { return _resolution; }

public:
	int Initialize(HINSTANCE hInstance, int cmdShow);
	int Run();

private:
	void Update();
	void Render();

	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

private:
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];

	HINSTANCE _mainHInstance;
	HWND _mainHWnd;
	HDC _mainHDC;
	POINT _resolution;			// 메인 윈도우 해상도

	Texture* _backBufferTexture;
	HDC _backBufferDC;
};
