#pragma once

class GameResource abstract
{
protected:
	GameResource();
public:
	virtual ~GameResource();

public:
	const wstring& GetRelativePath() const { return _relativePath; }

	void SetRelativePath(const wstring& path) { _relativePath = path; }

private:
	wstring _relativePath;	// 상대 경로
};

