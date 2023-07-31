#pragma once

class Time
{
private:
	Time() = delete;
	~Time() = delete;

public:
	static float GetDeltaTime() { return _deltaTime; }
	static float GetTimeScale() { return _timeScale; }

	static void SetTimeScale(float timeScale) { _timeScale = timeScale; }

public:
	static void Initialize();
	static bool Update();

private:
	static LARGE_INTEGER _curCount;
	static LARGE_INTEGER _prevCount;
	static LARGE_INTEGER _frequency;

	// 프레임 간의 시간값
	static float _accTime;
	static float _deltaTime;
	static float _timeScale;
	static float _frameInterval;
};

