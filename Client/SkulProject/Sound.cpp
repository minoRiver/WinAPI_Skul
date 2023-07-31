#include "global_include.h"
#include "Sound.h"

#include "SoundManager.h"

Sound::Sound()
	: _soundBuffer(nullptr)
	, _bufferInfo{}
	, _volume(0)
{
}

Sound::~Sound()
{
	if (nullptr != _soundBuffer)
		_soundBuffer->Release();
}

int Sound::Load(const wstring& path)
{
	assert(SoundManager::GetInstance()->GetSoundDevice());

	wchar_t szExt[10] = { 0 };
	_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);

	if (!wcscmp(szExt, L".wav")) // WAV ���� �ε�
	{
		if (false == LoadWaveSound(path))
			assert(nullptr);
	}
	else
		assert(nullptr);

	return S_OK;
}

bool Sound::LoadWaveSound(const wstring& _strPath)
{
	HMMIO	hFile; // File Handle

	wstring strFilePath = _strPath;

	//CreateFile
	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);

	if (nullptr == hFile)
	{
		MessageBox(NULL, L"File Open Fail", L"Error", MB_OK);
		return false;
	}

	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);



	memset(&_bufferInfo, 0, sizeof(DSBUFFERDESC));
	_bufferInfo.dwBufferBytes = pChild.cksize;
	_bufferInfo.dwSize = sizeof(DSBUFFERDESC);
	_bufferInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	_bufferInfo.lpwfxFormat = &wft;

	if (FAILED(SoundManager::GetInstance()->GetSoundDevice()->CreateSoundBuffer(&_bufferInfo, &_soundBuffer, NULL)))
	{
		MessageBox(NULL, L"������ۻ�������", L"", MB_OK);
		return false;
	}

	void* pWrite1 = NULL;
	void* pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	_soundBuffer->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0L);

	if (pWrite1 != nullptr)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 != nullptr)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	_soundBuffer->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	SetVolume(50.f);

	return true;
}


void Sound::Play(bool _bLoop)
{
	_soundBuffer->SetCurrentPosition(0);

	if (_bLoop)
		_soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		_soundBuffer->Play(0, 0, 0);
}

void Sound::PlayToBGM(bool _bLoop)
{
	SoundManager::GetInstance()->RegisterToBGM(this);

	if (_bLoop)
		_soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		_soundBuffer->Play(0, 0, 0);
}

void Sound::Stop(bool _bReset)
{
	_soundBuffer->Stop();

	if (_bReset)
		_soundBuffer->SetCurrentPosition(0);
}


void Sound::SetVolume(float _fVolume)
{
	_volume = GetDecibel(_fVolume);
	_soundBuffer->SetVolume(_volume);
}

void Sound::SetPosition(float _fPosition)
{
	Stop(true);

	DWORD dwBytes = (DWORD)((_fPosition / 100.f) * (float)_bufferInfo.dwBufferBytes);
	_soundBuffer->SetCurrentPosition(dwBytes);

	Play();
}

int Sound::GetDecibel(float _fVolume)
{
	if (_fVolume > 100.f)
		_fVolume = 100.f;
	else if (_fVolume <= 0.f)
		_fVolume = 0.00001f;

	// 1 ~ 100 ���̰��� ���ú� ������ ����
	int iVolume = (LONG)(-2000.0 * log10(100.f / _fVolume));

	if (iVolume < -10000)
		iVolume = -10000;
	return  iVolume;
}
