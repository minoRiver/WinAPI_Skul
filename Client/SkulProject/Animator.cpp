#include "global_include.h"
#include "Animator.h"

#include "Animation.h"

Animator::Animator()
	: _curAnimation(nullptr)
	, _isRepeatPlay(false)
{
}

Animator::Animator(const Animator& other)
	: _curAnimation(nullptr)
	, _isRepeatPlay(other._isRepeatPlay)
{
}

Animator::~Animator()
{
	for (auto pair : _animations)
	{
		delete pair.second;
	}

	_animations.clear();
}

void Animator::Update()
{
	if (_curAnimation)
	{
		_curAnimation->Update();

		if (_isRepeatPlay && _curAnimation->IsAnimFinish())
		{
			_curAnimation->Reset();
		}
	}
}

void Animator::Render(HDC hDC)
{
	if (_curAnimation)
	{
		_curAnimation->Render(hDC);
	}
}

void Animator::CreateAnimation(const wstring& animName, Texture* texture, Vector2 startPoint, Vector2 elemSize, Vector2 nextStep, float duration, UINT frameCount)
{
	Animation* findAnim = FindAnimation(animName);
	assert(nullptr == findAnim);

	Animation* newAnim = new Animation();
	newAnim->SetName(animName);
	newAnim->SetAnimator(this);
	newAnim->Create(texture, startPoint, elemSize, nextStep, duration, frameCount);

	_animations.insert(make_pair(animName, newAnim));
}

Animation* Animator::FindAnimation(const wstring& animName)
{
	auto iter = _animations.find(animName);
	if (iter == _animations.end())
	{
		return nullptr;
	}

	return iter->second;
}

void Animator::Play(const wstring& animName, bool isRepeat)
{
	Animation* findAnim = FindAnimation(animName);
	assert(nullptr != findAnim);
	_curAnimation = findAnim;

	_isRepeatPlay = isRepeat;
}
