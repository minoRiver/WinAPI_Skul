#include "global_include.h"
#include "Animation.h"

#include "Time.h"

#include "Animator.h"
#include "GameObject.h"
#include "Texture.h"
#include "Transform.h"

Animation::Animation()
	: _animator(nullptr)
	, _name(L"")
	, _curFrameIndex(0)
	, _accTime(0.f)
{
}

Animation::Animation(const Animation& other)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (true == _isAnimFinished)
		return;

	_accTime += Time::GetDeltaTime();

	if (_accTime >= _frameDatas[_curFrameIndex].duration)
	{
		_accTime -= _frameDatas[_curFrameIndex].duration;
		++_curFrameIndex;

		if (_curFrameIndex >= _frameDatas.size())
		{
			_isAnimFinished = true;
			--_curFrameIndex;
		}
	}
}

void Animation::Render(HDC hDC)
{
	GameObject* object = _animator->GetGameObject();
	Vector2 position = object->GetTransform()->GetPosition();
	
	const AnimFrameData& curFrameData = _frameDatas[_curFrameIndex];
	
	//position = Camera::GetInst()->GetRenderPos(position);
	
	TransparentBlt(
		hDC
		, (int)(position.x - curFrameData.offset.x - curFrameData.elemSize.x / 2.f)
		, (int)(position.y - curFrameData.offset.y - curFrameData.elemSize.y / 2.f)
		, (int)(curFrameData.elemSize.x)
		, (int)(curFrameData.elemSize.y)
		, _texture->GetDC()
		, (int)(curFrameData.startPoint.x)
		, (int)(curFrameData.startPoint.y)
		, (int)(curFrameData.elemSize.x)
		, (int)(curFrameData.elemSize.y)
		, RGB(255, 0, 255)
	);
}

void Animation::Create(Texture* texture, Vector2 startPoint, Vector2 elemSize, Vector2 nextStep, float duration, UINT frameCount)
{
	_frameDatas.clear();
	_frameDatas.reserve(frameCount);

	_texture = texture;

	AnimFrameData frameData = {};
	for (UINT i = 0; i < frameCount; ++i)
	{
		frameData.duration = duration;
		frameData.elemSize = elemSize;
		frameData.startPoint = startPoint + nextStep * (int)i;

		_frameDatas.push_back(frameData);
	}
}

void Animation::Reset()
{
	_isAnimFinished = false;
	_curFrameIndex = 0;
	_accTime = 0.f;
}
