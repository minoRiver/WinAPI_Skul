#include "global_include.h"
#include "SceneManager.h"

#include "ColliderManager.h"

#include "Scene.h"

SceneManager::SceneManager()
	: _curScene(nullptr)
	, _nextSceneType(SceneType::End)
{
}

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (SceneType::End != _nextSceneType)
	{
		ChangeScene();
	}

	_curScene->FixedUpdate();

	ColliderManager::GetInstance()->Update();

	_curScene->Update();
	_curScene->LateUpdate();
}

void SceneManager::Render(HDC hDC)
{
	_curScene->Render(hDC);
}

void SceneManager::Release()
{
	_curScene->Release();
	delete _curScene;
	_curScene = nullptr;
}

void SceneManager::LoadScene(SceneType nextSceneType)
{
	_nextSceneType = nextSceneType;
}

void SceneManager::ChangeScene()
{
	if (_curScene)
	{
		Release();
	}

	switch (_nextSceneType)
	{
		case SceneType::Tool:
			break;
		case SceneType::Start:
			break;
	}

	_nextSceneType = SceneType::End;
}
