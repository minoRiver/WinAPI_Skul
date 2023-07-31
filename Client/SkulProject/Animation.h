#pragma once
#include "Component.h"

class Animator;
class Texture;

struct AnimFrameData
{
	float duration;
	Vector2 startPoint;
	Vector2 elemSize;
	Vector2 offset;
};

class Animation final : public Component
{
public:
	Animation();
	Animation(const Animation& other);
	~Animation();

public:
	void SetName(const wstring& name) { _name = name; }
	void SetAnimator(Animator* animator) { _animator = animator; }

	const wstring& GetName() const { return _name; }
	bool IsAnimFinish() const { return _isAnimFinished; }
	const AnimFrameData& GetCurFrameData(int index) { return _frameDatas[index]; }

public:
	void Update();
	void Render(HDC hDC);

	void Create(Texture* texture, Vector2 startPoint, Vector2 elemSize, Vector2 nextStep, float duration, UINT frameCount);
	void Reset();

private:
	wstring _name = L"";
	Animator* _animator = nullptr;
	Texture* _texture = nullptr;
	vector<AnimFrameData> _frameDatas;

	int _curFrameIndex = 0;
	float _accTime = 0.f;
	bool _isAnimFinished;
};

