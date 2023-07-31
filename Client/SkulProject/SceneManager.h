#pragma once

class Scene;

class SceneManager
{
	SINGLETON(SceneManager)

public:
	Scene* GetCurScene() { return _curScene; }

public:
	void Init();
	void Update();
	void Render(HDC hDC);
	void Release();

	void LoadScene(SceneType nextSceneType);

private:
	void ChangeScene();

private:
	Scene* _curScene;
	SceneType _nextSceneType;
};

