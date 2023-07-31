#pragma once
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#include "GameResource.h"

class Sound :
	public GameResource
{
private:
	LPDIRECTSOUNDBUFFER		_soundBuffer;
	DSBUFFERDESC			_bufferInfo;
	int						_volume;

public:
	int Load(const wstring& path);

	// �Ϲ� ���
	void Play(bool _bLoop = false);

	// BGM ���� ���
	void PlayToBGM(bool _bLoop = false);

	void Stop(bool _bReset = false);

	// ���� ���� (0 ~ 100)
	void SetVolume(float _fVolume);

	// �������� ��ġ ����
	void SetPosition(float _fPosition); // 0 ~ 100 ����

private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);

public:
	Sound();
	virtual ~Sound();
};

