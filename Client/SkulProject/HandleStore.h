#pragma once

class HandleStore
{
public:
	static HWND GetMainHWnd() { return _mainHWnd; }
	static HDC GetMainDC() { return _mainHDC; }
	static HBRUSH GetBrush(BrushType type) { return _brushes[(UINT)type]; }
	static HPEN GetPen(PenType type) { return _pens[(UINT)type]; }

public:
	static void Initialize(HWND mainHWnd, HDC mainHDC);

private:
	static HWND _mainHWnd;
	static HDC _mainHDC;

	// 자주 사용하는 GID Object 미리 캐싱
	static HBRUSH _brushes[(UINT)BrushType::End];
	static HPEN _pens[(UINT)PenType::End];
};

