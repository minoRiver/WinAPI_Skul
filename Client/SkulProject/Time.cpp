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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&_prevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&_frequency);

	_frameInterval = 1.f / static_cast<float>(FPS);
}

bool Time::Update()
{
	QueryPerformanceCounter(&_curCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�.
	_accTime += (float)(_curCount.QuadPart - _prevCount.QuadPart) / (float)(_frequency.QuadPart);

	// ���� ī��Ʈ ���� ���� ������ ����(���� �� ����� ����)
	_prevCount = _curCount;

	if (_frameInterval <= _accTime)
	{
		_deltaTime = _accTime;
		_accTime = 0.f;
		return true;
	}

	return false;
}
