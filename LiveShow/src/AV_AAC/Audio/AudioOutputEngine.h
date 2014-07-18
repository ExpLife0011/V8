#pragma once
#include "AudioTransport.h"
#include "audio_pch.h"
#include "Common.h"

#define AUDIO_LOST_PACKET_TIME_INTERVAL  30*1000

class ClientUser;

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
	void OnRecvAudioData(UInt64 uin, unsigned char* data, unsigned int len,unsigned int iSeq);
	std::vector<wstring> GetAudioOutputDevice();
	void SetAudioOutputDevice(int iOutputDevice);

	//�������� ���з���
	void SetVolumeOutput(int iVolume);
	int GetVolumeOutput();

	//ϵͳѡ��
	void SetSystemType(wstring strAudioSystem);

	int GetOutputLevel();

	//�������ϵͳ����
	void SetSysVolume(int iVolume);
	
	//��ȡϵͳ�������
	int GetSysvolume();

	bool SetSysPlayerMute(bool bMute);
	bool GetSysPlayerMute(bool& bMute);

	float GetLostPacketRate();
private:
	bool bInit;
	bool bStart;

	int nRcvTotalPacket; //�յ��İ�
	int nRcvLostPacket;  //�����İ�
	float fLostRate;     //������
	UInt64 iTimeInterval; //���㶪����ʱ����
	UInt64 iLastTimeTick; //�ϴμ���ʱ��

	std::vector<wstring> lstrOutputDevice;

	void CalcLostRate(ClientUser *p,unsigned int iSeqence);
};

extern AudioOutputEngine g_audioOutputEngine;
