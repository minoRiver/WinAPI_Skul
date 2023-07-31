#include "global_include.h"
#include "SoundManager.h"

#include "HandleStore.h"
#include "ResourceManager.h"

#include "Sound.h"

SoundManager::SoundManager()
	: _soundDevice(nullptr)
	, _BGM(nullptr)
{
}

SoundManager::~SoundManager()
{
}

int SoundManager::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &_soundDevice, NULL)))
	{
		MessageBox(NULL, L"Create Sound Fail", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	HWND hWnd = HandleStore::GetMainHWnd();
	if (FAILED(_soundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		// 협조 레벨 실패(http://telnet.or.kr/directx/input/ref/ifaces/idirectinputdevice9/setcooperativelevel.htm)
		MessageBox(NULL, L"Cooperative Fail", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void SoundManager::RegisterToBGM(Sound* _pSound)
{
	if (_BGM != nullptr)
		_BGM->Stop(true);

	_BGM = _pSound;
}