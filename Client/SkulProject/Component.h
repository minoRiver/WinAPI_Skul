#pragma once
#include "IBehaviour.h"

class GameObject;

class Component abstract : IBehaviour
{
protected:
	Component();
	Component(const Component& other);
public:
	virtual ~Component();
	Component& operator =(Component& other) = delete;
	virtual Component* Clone();

public:
	GameObject* GetGameObject() const { return _gameObject; }

	void SetGameObject(GameObject* gameObject) { _gameObject = gameObject; }

public:
	virtual void Initialize() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	GameObject* _gameObject = nullptr;

};

