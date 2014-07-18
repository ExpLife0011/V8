#pragma once

#include "Common.h"
#include "AvDefine.h"

#ifdef CLIENT_TEST
	#ifdef AV_EXPORTS
		#define AV_ENGINE_API __declspec(dllexport)
	#else
		#define AV_ENGINE_API __declspec(dllimport)
	#endif
#else
	#define AV_ENGINE_API                        
#endif

class AV_ENGINE_API AVManager
{
public:
	AVManager(void);
	~AVManager(void);

	//���òɼ���Ƶ���� ����������ͷ ֱ����һ������ʹ������ͷʱ�Ųɼ�
	bool                          ConfigVideoParam(unsigned int iWidth, unsigned int iHeight, unsigned int iQuality, int iDeviceID,unsigned int iVideoMode);
	//ȥ�����з���͸�����ͷ�豸�Ĺ��������ر�����ͷ��
	void                          FinishVideoParam(int iDeviceID);
	//������ӱ�����ʾ���ھ������������ͷû�п�������������ͷ��ʼ�ɼ�
	bool						  StartRoomVideo(UInt32 iRoomId,HWND localHwnd,int iDeviceID,enuVIDEO_TYPE enType = VIDEO_PRIV_MIC);
	//�����Ƴ�������ʾ���ھ������������ͷֻ�б��������ã��������˳��󣬽�ֱ�ӹر�����ͷ�ɼ�
	void						  CloseRoomVideo(UInt32 iRoomId,HWND localHwnd,int iDeviceID);
	//���������Լ�������������˽��˽��������ʼ��������׼�� 
	bool                          StartRoomAudio(UInt32 iRoomId, const UInt8& cLogicID = 0);
	//�رշ����Լ�������������˽��˽�������رգ�����û����������������Ƶ�豸�����ر���Ƶ�ɼ�    �����豸ֻ��һ�� ����ͷ�豸�����ж����
	bool						  CloseRoomAudio(UInt32 iRoomId, const UInt8& cLogicID = 0);
	//������Ƶ���롢����豸��	
	bool						  SetAudioDevice(UInt32 iInputDev,UInt32 iOutputDev);			  
	//����ת�������������� ������������ͨ
	bool						  StartRoomConn(UInt32 iRoomId);//���俪ʼ����UDP���ӣ���ʼ����
	//�����˳�ʱ���رշ���UDP����
	bool						  CloseRoomConn(UInt32 iRoomId);//�����˳����ر�UDP����
	//�����û���ʾ����
	bool						  ChangePartnerHwnd(UInt32 iRoomId,UInt32 iDesUin, HWND hPartnerWnd, UInt32 iWidth, UInt32 iHeight, HWND hOldWnd);
	//���ı����Լ���ʾ�Ĵ���
	bool						  ChangeLocalHwnd(UInt32 iRoomId, HWND hLocalNewWnd, HWND hOldWnd);
	//���ñ�����Ƶ��ʾΪ�������ݽ�����Ч��
	bool						  ChangeLocalEffact(UInt32 iRoomId,HWND localHwnd,bool bEnable);
	//�Ƿ������˱�����ʾԶ��ͼ��Ч��
	bool						  IsLocalEffact(UInt32 iRoomId,HWND localHwnd);
	//�رշ������������� �û������˳�ʱ���������еı����佨���������߼�ͨ����
	bool						  ClearRoomAudio(UInt32 iRoomId);
	//����˳�ʱ�������з��佨�����߼�ͨ�����ر�����
	bool						  ClearAllRoomAudio();
	//�رշ���������Ƶ
	bool						  ClearRoomVideo(UInt32 iRoomId);
	//�ر����з��������ͷ
	bool						  ClearAllRoomVideo();
	//����ͷ�豸�Ƿ��Ѿ���ʼ��
	bool						  IsVideoDevInit(UInt32 iDeviceId);
	//���Ʊ��ر���ͼ��
	bool						  PaintLocal(UInt32 iRoomId,HWND hWnd);
	//����Զ�̱���ͼ��
	bool						  PaintRemote(UInt32 iRoomId,UInt32 iFromUin,HWND hWnd);
	//��ȡ����ͷ״̬
	Enum_Camera_Status			  GetCamerStatus(int iDevice);
	//��ȡ��������״̬
	bool						  GetAVNetStatus(Service_Av_Net_Status_All_Ex& sa);

	//iDeviceID �贫��  ��ȡָ������ͷ�豸�Ĳ���
	void                          GetVideoParam(const UInt32 &iDeviceID, UInt32 &iWidth, UInt32 &iHeight, UInt32 &iQuality);
	//��ӽ��շ��乫��˽��˽������ 
	bool                          RecvRoomAudioOpp(__int64 lSymbolTime, UInt32 iRoomId, UInt32 iFromUin, UInt8& cLogicID);
	//��ӽ��շ��乫��˽��˽����Ƶ
	bool                          RecvRoomVideoOpp(__int64 lSymbolTime, UInt32 iRoomId, UInt32 iFromUin, UInt8& cLogicID,HWND partnerHwnd, UInt32 iWidth, UInt32 iHeight, UInt32 iQuality,UInt32 iVideoMode,enuVIDEO_TYPE enType=VIDEO_PRIV_MIC);
	//�Է��뿪���䣬����ֹͣ��������
	void						  CloseRoomAudioOpp(UInt32 iRoomId, UInt32 iFromUin, UInt8& cLogicID);
	//�Է��뿪���䣬����ֹͣ��Ƶ����
	void						  CloseRoomVideoOpp(UInt32 iRoomId, UInt32 iFromUin, UInt8& cLogicID,HWND partnerHwnd);

	//��ͣ/����������Ƶ ��ͣʱ�����������ݰ� �Է������ղ�������
	void                          PauseLocalVideo(UInt32 iRoomId,HWND selfHwnd);
	void                          ContinueLocalVideo(UInt32 iRoomId,HWND selfHwnd);

	//��ͣ/�����Է���Ƶ���������յ��ǲ���ʾ����
	void                          PauseRemoteVideo(UInt32 iRoomId, UInt32 iFromUin, HWND partnerHwnd);
	void                          ContinueRemoteVideo(UInt32 iRoomId, UInt32 iFromUin, HWND partnerHwnd);
	
	//��ͣ/������������
	void                          PauseLocalAudio(UInt32 iRoomId);
	void                          ContinueLocalAudio(UInt32 iRoomId);

	//��ͣ/�����Է����� 
	void						  PauseRemoteAudio(UInt32 iRoomId, UInt32 iFromUin);
	void						  ContinueRemoteAudio(UInt32 iRoomId, UInt32 iFromUin);

	//�Ƿ��������
	bool                          IsPhotoableLocalHwnd(UInt32 iRoomId, HWND localHwnd);
	bool                          IsPhotoableRemoteHwnd(UInt32 iRoomId, UInt32 iFromUin, HWND partnerHwnd);

	//ָ�������Ƿ���������Ƶ
	bool                          IsStartAVEngine(UInt32 iRoomId);

	//�ж�ָ���豸�Ƿ�Ϊ������Ƶ�豸
	bool						  IsVideoVirtualDevice(int iDevId);
	
	//���÷���ý�������IP Port
	bool						  ChangeRelayServer(UInt32 iRoomId,UInt32 iRelayIP,UInt16 sRelayPort);

	//------------------------------------��������Ƶ ����\���
	//�������� ��������������
	void                          SetSpeakerVolume(UInt32 iRoomId,UInt32 iVolume);
	//��ȡ��Ƶ�������
 	UInt32						  GetSpeakerVolume();
	//��ȡָ����������
	UInt32						  GetSpeakerRoomVolume(UInt32 iRoomId);
	//����ָ����������
	void                          SetSpeakerRoomVolume(UInt32 iRoomId,UInt32 iVolume);
	//���÷�����˷�����  ���з���
	void						  SetMicRoomAllVolume(UInt32 iVolume);
	//��ȡ������˷�����  ���з���
	UInt32						  GetMicRoomAllVolume();
	//���÷����Ƿ���
	bool						  SetRoomSoundMute(UInt32 iRoomId, bool bMute);
	//��ȡ�����Ƿ���
	bool						  GetRoomSoundMute(UInt32 iRoomId, bool& bMute);
	//�������з����Ƿ���
	bool						  SetAllRoomSoundMute(bool bMute);
	//��ȡ���з����Ƿ���
	bool						  GetAllRoomSoundMute(bool& bMute);
	//��ȡ���з�����˷��Ƿ���
	bool						  GetAllRoomMicMute(bool& bMute);
	//�������з�����˷��Ƿ���
	bool						  SetAllRoomMicMute(bool bMute);
	//------------------------------------����ϵͳ��Ƶ ����\���
	//����ϵͳ��Ƶ����豸����
	void						  SetSysPlayerVolume(UInt32 iRoomId,UInt32 iVolume);
	//��ȡϵͳ��Ƶ����豸����
	UInt32						  GetSysPlayerVolume();
	//������˷�����
	void                          SetMicVolume(UInt32 iRoomId, UInt32 iVolume);
	//��ȡ��˷�����
	UInt32						  GetMicVolume();
	// ���þ��� 
	bool						  SetMicInputMute(UInt32 iRoomId, bool bMute);
	//��ȡ��˷��Ƿ���
	bool						  GetMicInputMute(UInt32 iRoomId, bool& bMute);
	//����ϵͳ�������Ƿ���
	bool						  SetSysPlayerMute(UInt32 iRoomId, bool bMute);
	//��ȡϵͳ�������Ƿ���
	bool						  GetSysPlayerMute(UInt32 iRoomId, bool& bMute);


	//������Ƶ����
 	void                          CheckSoundDevice(bool bOpen); 
	//��ȡ������ ��˷���ǿ
	void                          GetSoundLevel(UInt32 &iOutput, UInt32 &iInput);
	//������Ƶ�����豸  �����豸
	bool                          SetSoundDevices(int iRecordIndex, int iPlayIndex);
	//��ȡ��Ƶ�����豸����
	bool                          GetRecordDeviceName(int iIndex, wchar_t *pDeviceName, int iNameLen);
	//��ȡ��Ƶ�����豸����
	bool						  GetPlayoutDeviceName(int iIndex, wchar_t *pDeviceName, int iNameLen);
	#define DEVICE_NAME_LEN                   128
	#define MAX_VIDEO_DEVICE_NUM               10
	//��ȡ������Ƶ�豸
	void						  GetAudioDeviceList(int &iDeviceNum, wchar_t pDeviceName[][DEVICE_NAME_LEN],bool bInput);
	//��ȡ���е���Ƶ�豸
	void                          GetVideoDeviceList(int &iDeviceNum, wchar_t pDeviceName[][DEVICE_NAME_LEN]);
	//��ȡ������Ƶ�豸��ϸ��Ϣ
	void						  GetVideoDeviceInfoList(int &iDeviceNum,Service_Video_Info struDeviceInfo[]);
	//��ʾ��Ƶ���Դ���
	bool                          ShowVideoAdjustDlg(HWND hParWnd, unsigned int iDeviceID);
	//�ر�����û��ʹ�õ�����ͷ�豸
	void                          OperateVideoEngine();
	//��ȡ��Ƶ���� ����豸������
	bool                          GetNumOfSoundDevices(int &iPlayNum, int &iRecordNum);
	//��ȫ�ر���Ƶ  �رղ��Կ�������Ƶ�豸
	void						  SafeAudioInputStop();
	//������Ƶ�����豸
	bool						  StartVideoTest(int iDeviceId,HWND hWnd,UInt32& iResult);
	//�ر���Ƶ�����豸
	bool						  CloseVideoTest(int iDeviceId,HWND hWnd);
	//��ȡ���綪����
	float						  GetNatLostRate();
	//��ȡ�Ƿ�����˷��ǿ
	bool						  GetMicGreater(bool& bEnable);
	//������˷��ǿ
	bool						  SetMicGreater(bool bEnable);
	//�Ƿ���������ʾ����
	bool						  GetFFTView(UInt32 iRoomId,UInt32 iFromUin);
	//������ʾ����ͼ
	void						  SetFFTView(UInt32 iRoomId,UInt32 iFromUin,bool bEnable);
	//�����Ƿ���ʾ����ͼ ȫ��
	void						  SetFFTALL(bool bEnable);
	//��ȡ�Ƿ���ʾ����ͼ  ȫ��
	void						  GetFFTALL(bool& bEnable);
	//�����Լ��Ƿ���ʾ����ͼ
	void						  SetFFTME(bool bEnable);
	//��ȡ�Լ��Ƿ���ʾ����ͼ
	void						  GetFFTME(bool& bEnable);

	//ˢ����Ƶ�豸 �������ٹر�
	bool                          flushVideoDev(unsigned int iDev);
	//������Ƶ�������
	bool						  SetAudioMode(enuROOM_AV_AUDIO_MODE mode);
	//��������Ƶkey
	bool						  SetAvKey(unsigned int iRoomId,unsigned int iKey);
	//������Ƶ��ʾ�Ƿ���
	bool						  SetVideoSharpen(bool bEnable);
};
