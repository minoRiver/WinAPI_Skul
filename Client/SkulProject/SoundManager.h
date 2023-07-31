#pragma once
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class Sound;

class SoundManager
{
	SINGLETON(SoundManager);

private:
	LPDIRECTSOUND8	_soundDevice;
	Sound* _BGM;

public:
	int init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return _soundDevice; }
	void RegisterToBGM(Sound* _pSound);
};