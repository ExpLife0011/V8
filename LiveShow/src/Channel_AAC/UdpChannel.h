#pragma once

#include <vector>
#include <map>
#include "CommonPacket.h"

#include "WrapListener.h"
#include "TimerHandler.h"
#include "51ktv.h"


struct StructVLogic:public RCObject
{
	UInt32 iRoomId;
	UInt32 iFromUin;
	UInt8  cLogicId;
	HWND hWnd;
};

struct StructALogic:public RCObject
{
	UInt32 iRoomId;
	UInt32 iFromUin;
	UInt8  cLogicId;
};

class UdpChannel : public RCObject
{
public:

	UdpChannel(UInt32 iMyUin, UInt32 iRoomId,IModuleManager *pModuleManager);

	~UdpChannel();

	void                            Start();
	void                            Stop(UInt8 cReason);

	bool                            Maintain(SInt64 lCurTime);
	void                            KeepAlive(UInt16 sNum=1, bool bAck=false);
	void							KeepAliveEx(UInt16 sNum=1);
	void                            SendData(UInt8* pData, UInt16 sDataLen,bool bA=false);
	void							SendRepeatData(Packet* pRePacket,bool bA=false);
	void                            ProcessCmdPacket(Packet* pCmdPacket){}; //ռ������TCP������������Ϣ�������Ժ󲹳�

	//���������
	bool                            RegisterListener(ILogicListener* pLogicListener, UInt8& cLogicID,UInt32 iRoomId,UInt32 iFromUin,bool bA = false);
	void                            UnregisterListener(UInt8 cLogicID, UInt32 iRoomId,UInt32 iFromUin, bool bCallBack=false);
	RCPtr<WrapListener>             GetListener(UInt8 cLogicID,bool addRef=false);
	RCPtr<StructVLogic>				GetListenerLogicV(UInt32 iRoomId,UInt32 iFromUin);
	RCPtr<StructALogic>				GetListenerLogicA(UInt32 iRoomId,UInt32 iFromUin);
	void                            GetAllListener(std::vector<RCPtr<WrapListener> >& vAllListeners);
	bool                            IsExistListener();

	bool                            SetStatus(UInt16 sStatus);
	void                            SetRelayIPAddr();

	void                            SetAliveIPAddr(UInt32 iAliveIP, UInt16 sAlivePort, bool bLastValue=false);
	void                            SwitchToRelay(UInt32 iRelayIP, UInt16 sRelayPort);
	void                            SendToRelayServer(UInt16 cCmdType, UInt16 sSeq=0);
	void                            FinishCreatingRelaySession();
	inline UInt32                   GetRelayIP()             { return m_iRelayIP; }
	inline UInt16                   GetRelayPort()           { return m_sRelayPort; }

	inline UInt32                   GetRoomId()                      {  return m_iRoomId; }
	inline UInt16                   GetStatus()                      {  return m_sStatus; }
	inline UInt32                   GetMyUin()						 {  return m_iMyUin;  }

	inline  void                    SetLastAliveRcvTime(SInt64 lTime){ m_lLastAliveRcvTime = lTime; }
	void                            SetRelayIP(UInt32 iRelayIP, UInt16 sRelayPort);

	void							UploadInfoToServer();
	UInt64							LogicIndex(UInt32 iRoomId,UInt32 iFromUin);

	bool							IsExistsListener(UInt32 iRoomId,UInt32 iFromUin,bool bA=false);
	static void						PlayAudioPacket(UInt32 iRoomId,UInt32 iFromUin,Packet* pPacket,unsigned int iSeq);
	static void						PlayVideoPacket(UInt32 iRoomId,UInt32 iFromUin,Packet* pPacket);
	static void                     RequestCompenPacket(UInt32 iRoomId,UInt32 iFromUin,Packet* pPakcet);
	void							SendPacket(Packet* pPakcet);
	void							ResetRateCount();

	unsigned int				    m_iLastAudioReqSequence; //�ϴ��������ƵSeqId.
	unsigned int				    m_iRequestAudioCount;//������Ƶ��������
	unsigned int				    m_iLastVideoReqSequence;//��һ����Ƶ���к�
	unsigned int				    m_iRequestVideoCount;//������Ƶ��������
	unsigned int					m_iSendAudioCount;//������Ƶ������
	unsigned int				    m_iSendVideoCount;//������Ƶ������

	unsigned int					m_iRequestAudioCountEx;
	unsigned int					m_iRequestVideoCountEx;
	unsigned int					m_iSendAudioCountEx;
	unsigned int					m_iSendVideoCountEx;

	DWORD                           m_dwLastRateTime;
private:
	void                            StartListen();

private:
	SInt32                                 m_iSocketID;      //ע��ɹ���socketID��ʶ
	UInt32								   m_iRoomId;		 //����ID���÷����socketChannel

	UInt32                                 m_iMyUin;         //�����Uin
	UInt32                                 m_iMyPrvIP;       //���������IP
	UInt16                                 m_sMyPrvPort;     //���������Port

	bool                                   m_bLastValue;		 //�������ӽ����ɹ�ʱ���IP PORT
	SInt64                                 m_lLastAliveSendTime; //�ϴ�Alive�ķ���ʱ��
	SInt64                                 m_lLastAliveRcvTime;  //���һ�ν��յ�Alive��ʱ��

	SInt64                                 m_lConnectBeginTime; //��ʼ����ʱ��

	UInt16                                 m_sRelaySeq;			//��ת��������
	UInt32                                 m_iRelayIP;			//��ת������IP��ַ
	UInt16                                 m_sRelayPort;		//��ת�������˿�
	UInt32								   m_iAliveIP;			//������ӳɹ�ʱ���IP
	UInt16								   m_sAlivePort;		//������ӳɹ�ʱ���Port


	Mutex                                  m_Mutex;          
	UInt16                                 m_sStatus;               //Channel�ĵ�ǰ״̬
	bool                                   m_bCreatingRelaySession; //�Ƿ��Ѿ�������תSession
	bool								   m_bChangeServer;

	Mutex                                  m_ListenerMutex;   //�����߳� �����߳�  m_ListenersMap
	std::map<UInt8, RCPtr<WrapListener> >  m_ListenersMap;    //���е��ϲ������
	UInt8                                  m_cLogicSeed;      //����LogicID������
	SInt64								   m_lCurTime;		  //��ǰʱ��
	UInt32								   m_iMaxConnTime;    //�������ʱ��
 
	unsigned int						   s_audio_sequence;
	unsigned int						   s_video_sequence;
	unsigned int						   m_keep_count;

	IModuleManager *m_pModuleManager;
	typedef std::pair<UInt8, RCPtr<WrapListener> > listener_pair;

	std::map<UInt64,RCPtr<StructVLogic> >  m_ListenersRoomDestVMap; //VideoChannel LogicId �� RoomId FromUinӳ��
	typedef std::pair<UInt64,RCPtr<StructVLogic> > listenerRoomDesV_pair;

	std::map<UInt64,RCPtr<StructALogic> >  m_ListenersRoomDestAMap; //AudioChannel LogicId �� RoomId FromUinӳ��
	typedef std::pair<UInt64,RCPtr<StructALogic> > listenerRoomDesA_pair;
};

