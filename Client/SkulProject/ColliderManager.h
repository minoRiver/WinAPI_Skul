#pragma once

class Collider;

class ColliderManager
{
	SINGLETON(ColliderManager)

public:
	void Init();
	void Update();
	void Reset();

private:
	void CheckGroup(GroupType dstGroup, GroupType srcGroup);
	void CheckCollision(GroupType dstGroup, GroupType srcGroup);

	bool IsCollision(Collider* dstCollider, Collider* srcCollider);

private:
	vector<Collider*> _colliders[(UINT)GroupType::End];
	UINT _checkFlags[(UINT)GroupType::End];

};

