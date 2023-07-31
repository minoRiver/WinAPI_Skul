#pragma once

const short MAXKEYCOUNT = 256;

class Input
{
private:
	enum KeyState
	{
		None = 0x00,		// �ƹ� ���µ� �ƴ�(�׳� Ű �������� �������� ���� ����)
		Tab = 0x01,			// Ű�� ó�� ����
		Hold = 0x02,		// Ű�� ��� ����
		KeyPress = 0x03,	// Ű�� ����(ó���̵� ����̵� �������)
		Away = 0x04			// Ű�� ��
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

