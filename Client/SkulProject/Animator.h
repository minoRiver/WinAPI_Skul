#pragma once
#include "Component.h"

class GameObject;
class Animation;
class Texture;

class Animator : public Component
{
public:
	Animator();
	Animator(const Animator& other);
	~Animator();

public:
	void Update();
	void Render(HDC hDC);

	void CreateAnimation(const wstring& animName, Texture* texture, Vector2 startPoint, Vector2 elemSize, Vector2 nextStep, float duration, UINT frameCount);
	Animation* FindAnimation(const wstring& animName);
	void Play(const wstring& animName, bool isRepeat);

private:
	Animation* _curAnimation;
	map<wstring, Animation*> _animations;
	bool _isRepeatPlay;		// 반복 재생
};

