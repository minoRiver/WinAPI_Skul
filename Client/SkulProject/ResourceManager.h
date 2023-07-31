#pragma once

class Texture;

class ResourceManager
{
	SINGLETON(ResourceManager)

public:
	Texture* CreateTexture(const wstring& key, UINT width, UINT height);
	Texture* LoadTexture(const wstring& key, const wstring& relativePath);
	Texture* FindTexture(const wstring& key);

private:
	map<wstring, Texture*> _textures;
};

