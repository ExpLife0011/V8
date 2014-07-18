#pragma once
#include "AudioTransport.h"
#include "audio_pch.h"
#include "Common.h"


class AudioOutputEngine
{
public:
	AudioOutputEngine(void);
	~AudioOutputEngine(void);

	static AudioOutputEngine g_audioOutputEngine;

	void Init(AudioTransport *trans);

	void Destory();

	bool Start();

	void Stop();

	bool IsInit();

	bool IsStart();

	//��Ƶ����
	void SetAudioTest(bool bAudioTest);

	//������������
	void AddUserSession(UInt64 uin);

	//ɾ����������
	void RemoveUserSession(UInt64 uin);

	//�Ƴ��÷�����������
	void RemoveRoomSession(UInt32 iRoomId);
	
	//�Ƴ����з�����������
	void RemoveRoomAllSession();

	//��ͣ��������
	void PauseUserSession(UInt64,bool);

	//������յ�����������
	void OnRecvAudioData(UInt64 uin, unsigned char* data, unsigned int len);

	std::vector<wstring> GetAudioOutputDevice();

	void SetAudioOutputDevice(int iOutputDevice);

	//��������
	void SetVolumeOutput(int iVolume);

	int GetVolumeOutput();

	//ϵͳѡ��
	void SetSystemType(wstring strAudioSystem);

	int GetOutputLevel();

	
private:
	bool bInit;
	bool bStart;

	std::vector<wstring> lstrOutputDevice;
};

extern AudioOutputEngine g_audioOutputEngine;
