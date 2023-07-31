#pragma once
#include "GameResource.h"

class Texture : public GameResource
{
private:
	Texture();
	virtual ~Texture();

public:
	HDC GetDC() const { return _hDC; }

	UINT GetWidth() const { return _bitmapInfo.bmWidth; }

	UINT GetHeight() const { return _bitmapInfo.bmHeight; }

public:
	void Create(UINT width, UINT height, HDC mainDC);
	void Load(const wstring& filePath, HDC mainDC);

private:
	HDC _hDC;
	HBITMAP _hBitmap;

	BITMAP _bitmapInfo;

	friend class ResourceManager;
};

