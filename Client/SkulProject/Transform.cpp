#include "global_include.h"
#include "Transform.h"

Transform::Transform()
	: _position(0.f, 0.f)
{
}

Transform::~Transform()
{
}

void Transform::AddPosition(Vector2 position)
{
	_position += position;
}

void Transform::Initialize()
{
	_position = Vector2(0.f, 0.f);
}

void Transform::Release()
{
}
