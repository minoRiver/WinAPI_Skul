#include "global_include.h"
#include "Texture.h"

#include "HandleStore.h"

Texture::Texture()
	: _hDC(0)
	, _hBitmap(0)
	, _bitmapInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(_hDC);
	DeleteObject(_hBitmap);
}

void Texture::Create(UINT width, UINT height, HDC mainDC)
{
	HDC hDC = HandleStore::GetMainDC();

	_hBitmap = CreateCompatibleBitmap(hDC, (int)width, (int)height);
	_hDC = CreateCompatibleDC(hDC);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(_hDC, _hBitmap);
	DeleteObject(hOldBitmap);

	_bitmapInfo.bmWidth = width;
	_bitmapInfo.bmHeight = height;
}

void Texture::Load(const wstring& filePath, HDC mainDC)
{
	// 설명 : https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagew
	// hInst 에 nullptr 을 넣는 이유는 MSDN에 "사전 정의된 이미지 또는 독립 실행형 리소스(아이콘, 커서 또는 비트맵 파일)를 로드하려면 NULL 로 설정하라" 라고 써있어서
	// name : 파일 경로
	// type : 로드할 이미지 유형, 비트 연산으로 판단함(IMAGE_BITMAP, IMAGE_ICON, IMAGE_CURSOR 있음)
	// cx, cy : 로드할 비트맵 크기(픽셀), 값이 0일 경우 default size를 사용함
	// fuLoad : 파일의 추가적인 플래그 같은 느낌(MSDN 들어가서 확인)
	// LR_CREATEDIBSECTION | LR_LOADFROMFILE <<-- 강의에서는 이게 가장 기본적인 플래그라고 설명하긴 함
	_hBitmap = (HBITMAP)LoadImage(nullptr, filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(_hBitmap);

	// 비트맵과 연결할 DC 생성
	_hDC = CreateCompatibleDC(mainDC);

	// 비트맵과 DC 연결
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(_hDC, _hBitmap);
	DeleteObject(hPrevBitmap);

	// 비트맵 정보 가져오기(가로 세로 길이 등등의 정보가 있음)
	GetObject(_hBitmap, sizeof(BITMAP), &_bitmapInfo);
}
