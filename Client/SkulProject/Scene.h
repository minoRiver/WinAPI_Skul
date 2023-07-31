#pragma once

class GameObject;

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	void SetName(const wstring& name) { _name = name; }
	const wstring& GetName() { return _name; }

	const vector<GameObject*>& GetGroupObject(GroupType type) { return _objectGroups[(UINT)type]; }

public:
	virtual void Init() = 0;
	virtual void Update();
	virtual void LateUpdate();
	virtual void FixedUpdate();
	virtual void Render(HDC hDC);
	virtual void Release() = 0;

	void ReleaseDynamicObject();

	inline void AddObject(GameObject* object, GroupType groupType)
	{
		_objectGroups[(int)groupType].push_back(object);
	}

private:
	vector<GameObject*> _objectGroups[(UINT)GroupType::End];
	wstring _name;
};

