#include "global_include.h"
#include "ResourceManager.h"

#include "PathManager.h"
#include "HandleStore.h"

#include "Texture.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	map<wstring, Texture*>::iterator iter = _textures.begin();
	for (; iter != _textures.end(); ++iter)
	{
		delete iter->second;
	}

	_textures.clear();
}

Texture* ResourceManager::CreateTexture(const wstring& key, UINT width, UINT height)
{
	Texture* texture = FindTexture(key);
	if (texture)
	{
		return texture;
	}

	texture = new Texture();
	texture->Create(width, height, HandleStore::GetMainDC());

	_textures.insert(make_pair(key, texture));

	return texture;
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& relativePath)
{
	Texture* texture = FindTexture(key);
	if (texture)
	{
		return texture;
	}

	wstring filePath = PathManager::GetContentPath();
	filePath += relativePath;

	texture = new Texture();
	texture->Load(filePath, HandleStore::GetMainDC());
	
	texture->SetRelativePath(relativePath);

	_textures.insert(make_pair(key, texture));

	return texture;
}

Texture* ResourceManager::FindTexture(const wstring& key)
{
	map<wstring, Texture*>::iterator iter = _textures.find(key);

	if (_textures.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}
