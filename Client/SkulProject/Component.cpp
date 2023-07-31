#include "global_include.h"
#include "Component.h"

Component::Component()
	: _gameObject(nullptr)
{
}

Component::Component(const Component& other)
	: _gameObject(other._gameObject)
{
}

Component::~Component()
{
}

Component* Component::Clone()
{
	assert(false);
	return nullptr;
}

void Component::Initialize()
{
}

void Component::FixedUpdate()
{
}

void Component::Update()
{
}

void Component::LateUpdate()
{
}

void Component::Render(HDC hDC)
{
}

void Component::Release()
{
}
