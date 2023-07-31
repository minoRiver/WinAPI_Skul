#include "global_include.h"
#include "Time.h"

float Time::_accTime = 0.f;
float Time::_deltaTime = 0.f;
float Time::_timeScale = 0.f;
float Time::_frameInterval = 0.f;
LARGE_INTEGER Time::_curCount = { 0 };
LARGE_INTEGER Time::_prevCount = { 0 };
LARGE_INTEGER Time::_frequency = { 0 };

void Time::Initialize()
{
	// 현재 카운트
	QueryPerformanceCounter(&_prevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&_frequency);

	_frameInterval = 1.f / static_cast<float>(FPS);
}

bool Time::Update()
{
	QueryPerformanceCounter(&_curCount);

	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구한다.
	_accTime += (float)(_curCount.QuadPart - _prevCount.QuadPart) / (float)(_frequency.QuadPart);

	// 이전 카운트 값을 현재 값으로 갱신(다음 번 계산을 위해)
	_prevCount = _curCount;

	if (_frameInterval <= _accTime)
	{
		_deltaTime = _accTime;
		_accTime = 0.f;
		return true;
	}

	return false;
}
