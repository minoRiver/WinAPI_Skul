#pragma once
class PathManager
{
private:
	PathManager() = delete;
	~PathManager() = delete;

public:
	static const wchar_t* GetContentPath() { return _contentPath; }

public:
	static void Initialize();

private:
	static wchar_t _contentPath[255];
};

