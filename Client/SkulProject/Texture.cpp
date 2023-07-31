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
	// ���� : https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagew
	// hInst �� nullptr �� �ִ� ������ MSDN�� "���� ���ǵ� �̹��� �Ǵ� ���� ������ ���ҽ�(������, Ŀ�� �Ǵ� ��Ʈ�� ����)�� �ε��Ϸ��� NULL �� �����϶�" ��� ���־
	// name : ���� ���
	// type : �ε��� �̹��� ����, ��Ʈ �������� �Ǵ���(IMAGE_BITMAP, IMAGE_ICON, IMAGE_CURSOR ����)
	// cx, cy : �ε��� ��Ʈ�� ũ��(�ȼ�), ���� 0�� ��� default size�� �����
	// fuLoad : ������ �߰����� �÷��� ���� ����(MSDN ���� Ȯ��)
	// LR_CREATEDIBSECTION | LR_LOADFROMFILE <<-- ���ǿ����� �̰� ���� �⺻���� �÷��׶�� �����ϱ� ��
	_hBitmap = (HBITMAP)LoadImage(nullptr, filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(_hBitmap);

	// ��Ʈ�ʰ� ������ DC ����
	_hDC = CreateCompatibleDC(mainDC);

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(_hDC, _hBitmap);
	DeleteObject(hPrevBitmap);

	// ��Ʈ�� ���� ��������(���� ���� ���� ����� ������ ����)
	GetObject(_hBitmap, sizeof(BITMAP), &_bitmapInfo);
}
