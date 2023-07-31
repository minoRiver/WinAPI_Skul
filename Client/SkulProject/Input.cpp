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
	// 윈도우 포커싱 알아내기
	HWND hWnd = GetFocus();

	// 윈도우 포커싱 중일 때 키 이벤트 동작
	if (nullptr != hWnd)
	{
		_anyKeyDown = false;

		for (int i = 0; i < MAXKEYCOUNT; ++i)
		{
			// 입력이 들어왔는지 체크
			if (GetAsyncKeyState(i) & 0x8000)
			{
				_anyKeyDown = true;

				// 이전 프레임에 Tab(첫 입력)인 경우
				if (0 != (_keys[i] & KeyState::Tab))
				{
					_keys[i] = KeyState::Hold;
				}
				else if (0 == (_keys[i] & KeyState::Hold))	// 계속 눌린 상태가 아니다(Tab도 아니기 때문에 키가 때진 상태에서 다시 누른 상태로 온 것이다)
				{
					_keys[i] = KeyState::Tab;
				}
			}
			else
			{
				// 입력이 안들어왔는데 키 입력이 있는 경우
				if (0 != (_keys[i] & KeyState::KeyPress))
				{
					_keys[i] = KeyState::Away;
				}
				else if (0 != (_keys[i] & KeyState::Away))	// 키 땐 상태에서 또 입력 안들어옴
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
			// 입력이 안들어왔는데 키 입력이 있는 경우
			if (0 != (_keys[i] & KeyState::KeyPress))
			{
				_keys[i] = KeyState::Away;
			}
			else if (0 != (_keys[i] & KeyState::Away))	// 키 땐 상태에서 또 입력 안들어옴
			{
				_keys[i] = KeyState::None;
			}
		}
	}
}
