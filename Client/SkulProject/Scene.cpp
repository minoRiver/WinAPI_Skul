#include "global_include.h"
#include "Scene.h"

#include "GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GroupType::End; ++i)
	{
		for (size_t j = 0; j < _objectGroups[i].size(); ++j)
		{
			delete _objectGroups[i][j];
		}

		_objectGroups[i].clear();
	}
}

void Scene::Init()
{
}

void Scene::FixedUpdate()
{
	for (UINT i = 0; i < (UINT)GroupType::End; ++i)
	{
		for (size_t j = 0; j < _objectGroups[i].size(); ++j)
		{
			_objectGroups[i][j]->FixedUpdate();
		}
	}
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)GroupType::End; ++i)
	{
		for (size_t j = 0; j < _objectGroups[i].size(); ++j)
		{
			_objectGroups[i][j]->Update();
		}
	}
}

void Scene::LateUpdate()
{
	for (UINT i = 0; i < (UINT)GroupType::End; ++i)
	{
		for (size_t j = 0; j < _objectGroups[i].size(); ++j)
		{
			_objectGroups[i][j]->LateUpdate();
		}
	}
}

void Scene::Render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)GroupType::End; ++i)
	{
		for (size_t j = 0; j < _objectGroups[i].size(); ++j)
		{
			_objectGroups[i][j]->Render(hDC);
		}
	}
}

void Scene::ReleaseDynamicObject()
{
	for (UINT i = 0; i < (UINT)GroupType::End; ++i)
	{
		for (size_t j = 0; j < _objectGroups[i].size(); ++j)
		{
			delete _objectGroups[i][j];
		}

		_objectGroups[i].clear();
	}
}
