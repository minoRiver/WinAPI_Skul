#include "global_include.h"
#include "Resource.h"
#include "Core.h"

#include "Time.h"
#include "Input.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "HandleStore.h"

#include "Texture.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

Core::Core()
	: _mainHWnd(0)
	, _resolution{}
	, _mainHDC(0)
{
}

Core::~Core()
{
	// GetDC로 만든 DC는 ReleaseDC로 지워야함
	ReleaseDC(_mainHWnd, _mainHDC);
}

int Core::Initialize(HINSTANCE hInstance, int cmdShow)
{
    // 메모리 릭(누수) 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SKULPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, cmdShow))
    {
        return FALSE;
    }

	// 해상도에 맞게 윈도우 크기 조정
    _resolution = POINT{ WINDOW_WIDTH, WINDOW_HEIGHT };

	RECT rt = { 0, 0, _resolution.x, _resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(_mainHWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// 이중 버퍼링 용도의 텍스처를 만들고 DC를 가져온다.
	_backBufferTexture = ResourceManager::GetInstance()->CreateTexture(L"BackBuffer", _resolution.x, _resolution.y);
	_backBufferDC = _backBufferTexture->GetDC();

	// Manager 초기화
    HandleStore::Initialize(_mainHWnd, _mainHDC);
	PathManager::Initialize();
	Time::Initialize();
	Input::Initialize();

	return S_OK;
}

int Core::Run()
{
    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Update();
            Render();
        }
    }

    return (int)msg.wParam;
}

void Core::Update()
{
	Time::Update();
	Input::Update();
	//Camera::GetInst()->Update();
	//SceneManager::GetInst()->Update();
	//ColliderManager::GetInst()->Update();
	//UIManager::GetInst()->Update();
}

void Core::Render()
{
	// 화면 Clear
	Rectangle(_backBufferDC, -1, -1, _resolution.x + 1, _resolution.y + 1);

	//SceneManager::GetInst()->Render(_backBufferDC);
	//Camera::GetInst()->Render(_backBufferDC);

	// 메인 DC에 그린 것들을 옮긴다.
	BitBlt(_mainHDC, 0, 0, _resolution.x, _resolution.y, _backBufferDC, 0, 0, SRCCOPY);
}

ATOM Core::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SKULPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SKULPROJECT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL Core::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    _mainHInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    _mainHWnd = hWnd;
    _mainHDC = GetDC(_mainHWnd);

    return TRUE;
}
