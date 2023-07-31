#include "global_include.h"
#include "ColliderManager.h"

#include "SceneManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

void ColliderManager::Init()
{
}

void ColliderManager::Update()
{
	for (UINT row = 0; row < (UINT)GroupType::End; ++row)
	{
		for (UINT column = row + 1; column < (UINT)GroupType::End; ++column)
		{
			if (_checkFlags[row] & (1 << column))
			{
				CheckCollision((GroupType)row, (GroupType)column);
			}
		}
	}
}

void ColliderManager::Reset()
{
	
}

void ColliderManager::CheckGroup(GroupType dstGroup, GroupType srcGroup)
{
	if (dstGroup == srcGroup)
	{
		return;
	}

	Scene* curScene = SceneManager::GetInstance()->GetCurScene();

	const vector<Collider*>& dstObjectGroup = _colliders[(UINT)dstGroup];
	const vector<Collider*>& srcObjectGroup = _colliders[(UINT)srcGroup];

	for (size_t i = 0; i < dstObjectGroup.size(); ++i)
	{
		if (!dstObjectGroup[i])
		{
			continue;
		}

		Collider* dstCollider = dstObjectGroup[i];
		if (!dstCollider)
		{
			continue;
		}

		for (size_t j = 0; j < srcObjectGroup.size(); ++j)
		{
			if (!srcObjectGroup[i])
			{
				continue;
			}

			Collider* srcCollider = srcObjectGroup[i];
			if (!srcCollider)
			{
				continue;
			}

			if (IsCollision(dstCollider, srcCollider))
			{
				dstCollider->OnCollisionEnter(srcCollider);
				srcCollider->OnCollisionEnter(dstCollider);
			}
		}
	}
}

void ColliderManager::CheckCollision(GroupType dstGroup, GroupType srcGroup)
{
	for (UINT i = 0; i < (UINT)GroupType::End; ++i)
	{
		for (UINT j = 0; j < (UINT)GroupType::End; ++j)
		{
			if (i == j)
				continue;
			if (!(_checkFlags[i] & (1 << j)))
				continue;

			CheckGroup((GroupType)i, (GroupType)j);
		}
	}
}

bool ColliderManager::IsCollision(Collider* dstCollider, Collider* srcCollider)
{
	Vector2 dstPos = dstCollider->GetPos();
	Vector2 dstScale = dstCollider->GetScale();

	Vector2 srcPos = srcCollider->GetPos();
	Vector2 srcScale = srcCollider->GetScale();

	if (abs(srcPos.x - dstPos.x) < (dstScale.x + srcScale.x) * 0.5f &&
		abs(srcPos.y - dstPos.y) < (dstScale.y + srcScale.y) * 0.5f)
	{
		return true;
	}

	return false;
}
