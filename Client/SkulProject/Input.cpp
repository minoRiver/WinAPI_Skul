#include "global_include.h"
#include "Input.h"

byte Input::_keys[MAXKEYCOUNT] = { Input::KeyState::None };
bool Input::_anyKeyDown = false;

void Input::Initialize()
{
	for (int i = 0; i < MAXKEYCOUNT; ++i)
	{
		_keys[i] = KeyState::None;
	}
}

void Input::Update()
{
	// ������ ��Ŀ�� �˾Ƴ���
	HWND hWnd = GetFocus();

	// ������ ��Ŀ�� ���� �� Ű �̺�Ʈ ����
	if (nullptr != hWnd)
	{
		_anyKeyDown = false;

		for (int i = 0; i < MAXKEYCOUNT; ++i)
		{
			// �Է��� ���Դ��� üũ
			if (GetAsyncKeyState(i) & 0x8000)
			{
				_anyKeyDown = true;

				// ���� �����ӿ� Tab(ù �Է�)�� ���
				if (0 != (_keys[i] & KeyState::Tab))
				{
					_keys[i] = KeyState::Hold;
				}
				else if (0 == (_keys[i] & KeyState::Hold))	// ��� ���� ���°� �ƴϴ�(Tab�� �ƴϱ� ������ Ű�� ���� ���¿��� �ٽ� ���� ���·� �� ���̴�)
				{
					_keys[i] = KeyState::Tab;
				}
			}
			else
			{
				// �Է��� �ȵ��Դµ� Ű �Է��� �ִ� ���
				if (0 != (_keys[i] & KeyState::KeyPress))
				{
					_keys[i] = KeyState::Away;
				}
				else if (0 != (_keys[i] & KeyState::Away))	// Ű �� ���¿��� �� �Է� �ȵ���
				{
					_keys[i] = KeyState::None;
				}
			}
		}
	}
	else
	{
		_anyKeyDown = false;

		for (int i = 0; i < MAXKEYCOUNT; ++i)
		{
			// �Է��� �ȵ��Դµ� Ű �Է��� �ִ� ���
			if (0 != (_keys[i] & KeyState::KeyPress))
			{
				_keys[i] = KeyState::Away;
			}
			else if (0 != (_keys[i] & KeyState::Away))	// Ű �� ���¿��� �� �Է� �ȵ���
			{
				_keys[i] = KeyState::None;
			}
		}
	}
}
