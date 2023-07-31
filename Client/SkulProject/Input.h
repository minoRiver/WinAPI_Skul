#pragma once

const short MAXKEYCOUNT = 256;

class Input
{
private:
	enum KeyState
	{
		None = 0x00,		// 아무 상태도 아님(그냥 키 눌리지도 때지지도 않은 상태)
		Tab = 0x01,			// 키를 처음 누름
		Hold = 0x02,		// 키를 계속 누름
		KeyPress = 0x03,	// 키가 눌림(처음이든 계속이든 상관없이)
		Away = 0x04			// 키를 땜
	};

private:
	Input() = delete;
	~Input() = delete;

public:
	static bool IsAnyKeyPressed() { return _anyKeyDown; }
	static bool GetKey(int keyCode) { return _keys[keyCode] & KeyState::KeyPress; }
	static bool GetKeyDown(int keyCode) { return _keys[keyCode] & KeyState::Tab; }
	static bool GetKeyUp(int keyCode) { return _keys[keyCode] & KeyState::Away; }

public:
	static void Initialize();
	static void Update();

private:
	static byte _keys[MAXKEYCOUNT];
	static bool _anyKeyDown;
};

