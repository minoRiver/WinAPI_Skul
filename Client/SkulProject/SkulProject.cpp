﻿// SkulProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "SkulProject.h"

#include "Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    Core* core = Core::GetInstance();
    if (FAILED(core->Initialize(hInstance, nCmdShow)))
    {
        return -1;
    }

    int result = core->Run();

    return result;
}