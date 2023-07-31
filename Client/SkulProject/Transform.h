#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

public:
	const Vector2& GetPosition() const { return _position; }

	void SetPosition(Vector2 position) { _position = position; }

public:
	void AddPosition(Vector2 position);

public:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	Vector2 _position;
};

