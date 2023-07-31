#pragma once
#include "IBehaviour.h"

class Component;
class Collider;
class Transform;

class GameObject : public IBehaviour
{
public:
	GameObject();
	virtual ~GameObject();

public:
	Transform* GetTransform() const { return _transform; }

public:
	virtual void Initialize();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();

public:
	virtual void OnCollisionEnter(Collider* collider) {}
	virtual void OnCollisionStay(Collider* collider) {}
	virtual void OnCollisionExit(Collider* collider) {}

private:
	vector<Component*> _components;
	Transform* _transform;
};

