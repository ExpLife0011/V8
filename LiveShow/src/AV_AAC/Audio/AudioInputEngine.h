#pragma once
#include "AudioTransport.h"
#include "audio_pch.h"
#include "AvDefine.h"


class AudioInputEngine
{
public:
	AudioInputEngine(void);
	~AudioInputEngine(void);

	static AudioInputEngine g_audioInputEngine;

	void Init(AudioTransport *trans);

	void Destory();

	bool Start();

	void Stop();

	bool IsInit();

	bool IsStart();

	//�豸ѡ��
	std::vector<wstring> GetAudioInputDevice();

	void SetAudioDevice(int iInputDevice);

	void SetVolumeInput( int iVolume);
	int  GetVolumeInput();

	//������С
	int GetInputLevel();

	void SetAudioTest(bool bAudioTest);

	bool SetMicInputMute(bool bMute);
	bool GetMicInputMute(bool& bMute);

	void SetMicRoomAllVolume(int iVolume);
	int  GetMicRoomAllVolume();
	
	//������Ƶ�������
	bool SetMode(enuROOM_AV_AUDIO_MODE mode);
private:
	bool bInit;
	bool bStart;

	std::vector<wstring> lstrInputDevice;
};

extern AudioInputEngine g_audioInputEngine;
