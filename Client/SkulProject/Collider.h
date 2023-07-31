#pragma once
#include "Component.h"

class Transform;

class Collider : public Component
{
public:
	Collider();
	Collider(const Collider& other);
	~Collider();

public:
	const Vector2& GetScale() { return _scale; }
	const Vector2& GetOffsetPos() const { return _offsetPos; }
	const Vector2& GetPos() const { return _finalPos; }

	void SetScale(Vector2 scale) { _scale = scale; }
	void SetOffsetPos(Vector2 offset) { _offsetPos = offset; }

public:
	Collider& operator =(Collider& collider) = delete;

public:
	void Update();
	void Render(HDC hDC);

	void OnCollisionEnter(Collider* otherCollider);
	void OnCollisionStay(Collider* otherCollider);
	void OnCollisionExit(Collider* otherCollider);

private:
	Transform* _transform;

	Vector2 _offsetPos;
	Vector2 _finalPos;
	Vector2 _scale;
};

