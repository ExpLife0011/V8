#pragma once
#include "51ktvtype.h"
#include <vector>
#include "..\RoomModule.h"
#include <map>
#include "..\..\CommonDll\RC.h"
#include "avdefine.h"
#include "..\..\CommonDll\Mutex.h"

using namespace std;

//�û�����������Ƶ״̬
enum enuROOM_AV_STATE
{
	ROOM_AV_NONE = 0, //û������˽�ĵ�
	ROOM_AV_AUDIO, //˽�� ������
	ROOM_AV_AV //���� ����Ƶ������
};

//�������߼�����״̬ �Է�
enum enuROOM_AV_USER_STATE
{
	ROOM_AV_OPP_NONE = 0, 
	ROOM_AV_OPP_AUDIO,
	ROOM_AV_OPP_VIDEO
};

//���汻������Ƶ����������
struct strucROOMAVUSER:public RCObject
{
	uint32 iFromUin;
	uint8 cLogicId;
	HWND hWndPartner;
	enuROOM_AV_USER_STATE eState;
};

#define MAX_CONNECTING_TIME              10000
#define RECV_VIDEO_WIDTH				 640
#define RECV_VIDEO_HIEGHT				 420

class RoomAVLogic
{
public:
	RoomAVLogic(uint32 iRoomId,uint32 iSelfUin,RoomModule &module):
			m_iRoomId(iRoomId),
			m_iSelfUin(iSelfUin),
			m_module(module),
			m_bIsStart(false),
			m_nRelayStartTime(0),
			m_iWidth(0),
			m_iHeight(0),
			m_iQuality(0),
			m_iRelayIP(0),
			m_sRelayPort(0),
			m_iDevice(0),
			m_cLogicId(0),
			m_rState(ROOM_AV_NONE),
			m_eVideoMode(ROOM_VIDEO_CRF_MODE)
	  {}
	~RoomAVLogic(void){}
	
	void ConnectRelayServer(uint32 iRelayIP,uint32 iRelayPort); //��ʼ��������ת�����������������ӣ������ò���
	void SetVideoCfg(int iDevice,int iHeight,int iWidth,int iQuality,enuROOM_AV_VIDEO_MODE eMode = /*ROOM_VIDEO_CRF_MAX*/ROOM_VIDEO_CRF_MODE); //������Ƶ�ɼ�����
	void SetAudioCfg(int iInputDev,int iOutputDev);//������Ƶ�豸�����豸 ����豸
	void SetKeyCfg(uint32 iKey);//��������Ƶ����Key
    bool FlushVideoDev(int iDev);//ˢ����Ƶ�豸 ���ڴ���������ͷ����
	bool ChangeRelayServer(uint32 iRelayIp,uint16 sRelayPort);//�����ת������IP

	void UpSelf(HWND hWndLocal,enuVIDEO_TYPE enVideoType = VIDEO_PRIV_MIC);//�û��Լ����� �������ص���Ƶ������ ��������
	void DownSelf();//�û��Լ�����
	void UpSelfVoice();//�������� ��������������������Ƶ
	void DownSelfVoice();//�ر�����
	bool SetAudioMode(enuROOM_AV_AUDIO_MODE mode);//������Ƶ�������
	Enum_Camera_Status GetCameraStatus(int iDevice);//��ȡ����ͷ״̬
	
	void RecvAV(uint32 iFromUin,HWND hWndPartner,UInt32 iWidth = 320, UInt32 iHeight=240,enuVIDEO_TYPE enVideoType = VIDEO_PRIV_MIC,enuROOM_AV_VIDEO_MODE eMode = /*ROOM_VIDEO_CRF_MAX*/ROOM_VIDEO_CRF_MODE);//���չ���˽��˽����Ƶ+����
	void RecvAVChg(uint32 iFromUin,HWND hPartnerWnd, UInt32 iWidth, UInt32 iHeight, HWND hOldWnd);//���Ľ����û���Ƶ��ʾ���ڼ�ͼ�������С
	void LocalAVChg(HWND hNewWnd,HWND hOldWnd);//���ı�����Ƶ��ʾ����
	void LocalAVEffact(HWND hLocalWnd,bool bEnable);//�Ƿ���ʾ������ƵΪ�������ݽ�ѹ���Ч�� bEnable=TRUE ��
	bool LocalPaintBk(HWND hLocalWnd);//���Ʊ������һ֡ͼ��
	bool RemotePaintBk(uint32 iFromUin,HWND hPartnerWnd);//����Զ���û����һ֡����

	void RemoveAV(uint32 iFromUin);//�Ƴ�����˽��˽���û���Ƶ+����
	void RecvAudio(uint32 iFromUin);//����˽������
	void RemoveAudio(uint32 iFromUin);//�Ƴ�˽������

	void ClearRoomAV();//�����˳�ʱ�������俪������Ƶ����˷����Ϣ �Լ�UDP������Ϣ

	void PauseLocalAudio(bool bPause); //��ͣ���ָ���������
	void PauseRemoteAudio(uint32 iFromUin,bool bPause); //��ͣ���ָ�Զ���û�����
	void PauseLocalVideo(bool bPause);//��ͣ���ָ�������Ƶ
	void PauseRemoteVideo(uint32 iFromUin,bool bPause); //��ͣ���ָ�Զ���û���Ƶ
	
	bool IsPhotoableLocalHwnd(HWND localHwnd);//�Ƿ��������
	bool IsPhotoableRemoteHwnd(UInt32 iFromUin, HWND partnerHwnd);
	bool IsVideoVirtualDevice(UInt32 iDevId);//ָ���豸�Ƿ�Ϊ������Ƶ�豸
	
	bool IsStartAVEngine(); //�÷����Ƿ���������Ƶ
	bool IsLocalAVEffact(HWND localHwnd); //�����Ƿ�������ʾ��ѹ����Ч��
	
	//���ݵ�����
	void   SetSpeakerVolume(UInt32 iVolume);//���ò�������   -���з���
	UInt32 GetSpeakerVolume();//��ȡ��������
	void   SetSpeakerRoomVolume(UInt32 iVolume);//���õ�����������   -��������
	UInt32 GetSpeakerRoomVolume();//��ȡ������������

	void   SetMicRoomAllVolume(UInt32 iVolume); //���ñ������˷�������С  ���з���
	UInt32 GetMicRoomAllVolume();//��ȡ�������˷�������С  ���з���

	bool   SetSondMute(bool bMute);//���÷��侲��  ����ǰ���侲��
	bool   GetSoundMute(bool& bMute);//��ȡ�����Ƿ���
	bool   GetAllSoundMute(bool& bMute);//��ȡ���з����Ƿ���
	bool   SetAllSoundMute(bool bMute);//�������з����Ƿ���
	bool   GetAllMicMute(bool& bMute);//��ȡ���з�����˷羲��
	bool   SetAllMicMute(bool bMute);//�������з�����˷羲��
	
	//ϵͳ����
	void   SetSysPlayerVolume(UInt32 iVolume);//����ϵͳ������С
	UInt32 GetSysPlayerVolume();//��ȡϵͳ������С
	void   SetMicVolume(UInt32 iVolume);//������˷�����
	UInt32 GetMicVolume();//��ȡ��˷�����

	bool   SetMicMute(bool bMute);//������˷羲��
	bool   GetMicMute(bool& bMute);//��ȡ��˷��Ƿ���
	bool   SetPlayerMute(bool bMute);//����ϵͳ����������
	bool   GetPlayerMute(bool& bMute);//��ȡϵͳ�������Ƿ���

	void   GetSoundLevel(UInt32 &iOutput, UInt32 &iInput);//��ȡ��˷� ��������ǿ
	bool   SetMicGreater(bool bEnable);//������˷��ǿ
	bool   GetMicGreater(bool& bEnable);//��ȡ��˷��Ƿ��ǿ
	void   SetViewFFTALL(bool bEnable);//���������Ƿ���ʾ����ͼ
	void   SetViewFFTME(bool bEnable);//�����Լ��Ƿ���ʾ����ͼ
	void   SetViewFFTWav(UInt32 iFromUin,bool bEnable);//��ʾ���յ����û��Ĳ���ͼ
	bool   GetViewFFTWav(UInt32 iFromUin);//�Ƿ���ʾ����ͼ
	void   GetNetState(float& fRate);//fRate 0 ~ 1 ��ǰ�������綪����
	bool   GetNetState(uint32&iRelayIP,struct Service_Av_Net_Status_All& sansa); //��ȡ����Ƶ�����հ������ʵ�״̬

	void   GetRecordDeviceName(int iIndex, wchar_t *pDeviceName,int iNameLen);//��ȡ��Ƶ�����豸����
	void   GetPlayoutDeviceName(int iIndex, wchar_t *pDeviceName, int iNameLen);//��ȡ��Ƶ����豸

	void   GetAudioDeviceList(int &iDeviceNum,wchar_t wsDeviceName[][DEVICE_NAME_LEN], bool bInput);//��ȡ��Ƶ��������豸�б�
	void   GetVideoDeviceList(int &iDeviceNum,wchar_t wsDeviceName[][DEVICE_NAME_LEN]);//��ȡ��Ƶ�豸�б�
	void   GetVideoDeviceInfoList(int&iDeviceNum,Service_Video_Info struDeviceInfo[]);//��ȡ��Ƶ�豸��Ϣ�б�
	void   GetNumOfSoundDevices(int &iPlayNum, int &iRecordNum);//��ȡ��Ƶ��������豸����

	bool TestSetAudioDevice(int iInputDevice, int iOutputDevice);//������Ƶ���롢����豸 ��������ʱ����
	bool TestCheckSoundDevice(bool bOpen);//������Ƶ����  ����TestSetAudioDevice������Ƶ�豸 �ٵ��øú��� 
	bool TestSetDefaultAudioDevice();//���û�Ĭ����Ƶ�豸  �����û�û�б����Ƶ�豸���˳����Դ���ʱ���øú������ָ�ΪĬ������
	void TestSafeCloseInputDevice(); //�ر���Ƶ�����豸�����Ǹ��豸û�з���ʹ�ùرգ����߲��ر� ��Ƶ����ʱ��ѡ�������豸ǰ�����һ��

	bool ShowVideoAjustDlg(HWND hParentWnd,uint32 iDeviceId);//��ʾ��Ƶ���Ե����Ի���
	void TestSetVideoDevice(int iDeviceId);//������Ƶ�豸
	bool TestStartVideoDevice(int iDeviceId,HWND hWnd,UInt32 &iResult);//�������õ���Ƶ�豸
	bool TestStopVideoDevice(int iDeviceId,HWND hWnd);
	void SavePhotoToBmp(HWND hWnd, CString strPath);//��������ΪBMP��ָ����·�� BMP��ʽ
	void SetEnableShapen(bool bEnable); //�����û���ʾ��ͼ���Ƿ��񻯺���ʾ  ��ʡCPU
	
	//��ʼ��������
	void InitMixerControl(HWND hWnd);
	//�����е���������0~255
	bool SetMixerControlTotalVolume(unsigned int nVolume);//����������
	bool GetMixerControlTotalVolume(unsigned int& nVolume);//��ȡ������
	bool SetMixerControlWavoutVolume(unsigned int nVolume);//���ð���
	bool GetMixerControlWavoutVolume(unsigned int& nVolume);//��ȡ��������
	bool SetMixerControlOutmicVolume(unsigned int nVolume);//�������������е���˷�
	bool GetMixerControlOutmicVolume(unsigned int& nVolume);//��ȡ���������е���˷�����
	//¼������0~255
	bool SetMixerControlMixerVolume(unsigned int nVolume);//����������
	bool GetMixerControlMixerVolume(unsigned int& nVolume);//��ȡ��������������
	bool SetMixerControlInmicVolume(unsigned int nVolume);//¼�������е���˷�
	bool GetMixerControlInmicVolume(unsigned int& nVolume);//��ȡ¼�������е���˷�����
	bool SetMixerControlWavInVolume(unsigned int nVolume);//������Ƶ�����豸����
	bool GetMixerControlWavInVolume(unsigned int& nVolume);//��ȡ��Ƶ�����豸����
	//��������
	bool SetMixerControlTotalMute(bool bEnable);    //������//��������������
	bool GetMixerControlTotalMute(bool& bEnable);//��ȡ�������Ƿ���
	bool SetMixerControlWavoutMute(bool bEnable);   //����//���ð�������
	bool GetMixerControlWavoutMute(bool& bEnable);//��ȡ�����Ƿ���
	bool SetMixerControlOutmicMute(bool bEnable);   //���������//�������������е���˷�ľ���
	bool GetMixerControlOutmicMute(bool& bEnable);//��ȡ���������е���˷�ľ���
	bool SetMixerControlMixerMute(bool bEnable);   //����·����//��������������  ����ѡ�� ��Ϊѡ�� �� ��ѡ��
	bool GetMixerControlMixerMute(bool& bEnable);//��ȡ��������Ӧ�Ƿ���
	bool SetMixerControlInmicMute(bool bEnable);   //����˷�//����¼�������е���˷羲��
	bool GetMixerControlInmicMute(bool& bEnable);//��ȡ¼�������е���˷��Ƿ���
	//����ģʽ
	bool SetMixerControlSingMode(bool bEnable);//���ó���ģʽ
	bool GetMixerControlSingMode(bool& bEnable);//��ȡ�Ƿ񳪸�ģʽ
	bool SetMixerControlChatMode(bool bEnable);//������������ģʽ
	bool GetMixerControlChatMode(bool& bEnable);//��ȡ�Ƿ���������ģʽ
	bool SetMixerControlPlayMode(bool bEnable);//���������ϷŸ�ģʽ
	bool GetMixerControlPlayMode(bool& bEnable);//��ȡ�Ƿ������ϳ���ģʽ
	bool GetMixerControlMode(EnMixerControlMode& enMode);//��ȡϵͳ��ǰģʽ
	bool SetMixerControlMode(EnMixerControlMode enMode);//����ϵͳ��ǰģʽ
	//��ȡ��������ǰϵͳ�Ƿ����
	bool GetMixerControlTotalEnable();//��ȡ��ǰ�������Ƿ����
	bool GetMixerControlWavoutEnable();//��ȡ�����Ƿ����
	bool GetMixerControlOutmicEnable();//��ȡ���������е���˷��Ƿ����
	bool GetMixerControlMixerEnable();//��ȡ�����������Ƿ����
	bool GetMixerControlInmicEnable();//��ȡ��Ƶ�����豸��������С
	bool GetMixerControlWavInEnable();//��ȡ������˷�������С�Ƿ����
private:
	void AddUserMap(uint32 iFromUin,uint8 cLogicId,enuROOM_AV_USER_STATE eState,HWND hWndPartner=NULL);
	RCPtr<strucROOMAVUSER> FindUserMap(uint32 iFromUin,enuROOM_AV_USER_STATE eState);
	void RemoveUserMap(uint8 cLogicId);
	bool IsVideoDeviceInit(int iDevice);//��Ƶ�豸�Ƿ��ʼ��

	uin m_iRoomId;
	uin m_iSelfUin;
	int64 m_nRelayStartTime;
	uin m_iRelayIP;//��ת������IP
	UInt16 m_sRelayPort;//��ת�������˿�
	uin m_iSelfIP;//�ͻ��˹���IP

	bool m_bIsStart;//�Ƿ��Ѿ���ʼ����

	int m_iWidth;//��Ƶ�ɼ����
	int m_iHeight;//��Ƶ�ɼ��߶�
	int m_iQuality;//��Ƶ�ɼ�����
	int m_iDevice; //����ͷ�豸���� ��Ƶ�豸

	int m_iInputDev;//��Ƶ�����豸
	int m_iOutputDev;//��Ƶ����豸
	uin m_iKey; //����Ƶkey

	HWND m_hWndLocal; //�Լ����ش��ڵľ��
	uint8 m_cLogicId; //������ת�ѷ�������LogicId
	Mutex m_mutex; //�����߳� 
	
	enuROOM_AV_STATE m_rState;
	enuROOM_AV_VIDEO_MODE m_eVideoMode;//��Ƶѹ��ģʽ

	RoomModule &m_module;

	std::map<uint8,RCPtr<strucROOMAVUSER> > m_userMap;
};
