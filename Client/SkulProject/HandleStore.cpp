#include "global_include.h"
#include "HandleStore.h"

HWND HandleStore::_mainHWnd = NULL;
HDC HandleStore::_mainHDC = NULL;

// 자주 사용하는 GID Object 미리 캐싱
HBRUSH HandleStore::_brushes[(UINT)BrushType::End] = { NULL };
HPEN HandleStore::_pens[(UINT)PenType::End] = { NULL };


void HandleStore::Initialize(HWND mainHWnd, HDC mainHDC)
{
	_brushes[(UINT)BrushType::Hollow] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	_pens[(UINT)PenType::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	_pens[(UINT)PenType::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	_pens[(UINT)PenType::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
