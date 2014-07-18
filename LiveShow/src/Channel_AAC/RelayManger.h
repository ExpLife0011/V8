#pragma once

#include "ILogicListener.h"
#include "Common.h"
#include "51ktv.h"

enum
{
	OPTION_AUTO_RELAY  =  0,        //�Զ�������ת
	OPTION_FORCE_RELAY =  1,        //ֱ��ǿ����ת
	OPTION_NO_RELAY    =  2         //��������ת
};

#ifdef CHANNEL_EXPORTS
#define CHANNEL_OUT_CLASS  _declspec(dllexport)
#else
#define CHANNEL_OUT_CLASS  _declspec(dllimport)
#endif

class CHANNEL_OUT_CLASS RelayManger
{
public:

 	static void        Initialize(IModuleManager* pModuleManager);
	static void        Initialize();
	static RelayManger*  Instance();
	static void        DestroyInstance();
	static void        DestroyBufferInstance();

	static __int64     GetLibSymbolTime();

	//����ȫ�ֲ���
    static void       Config(UInt32 iMyUin, UInt32 iRelayIP, UInt16 sRelayPort, UInt32 iMaxConnTime);

	//��iRoomId֮�佨��һ���߼�ͨ��, ����������ͨ���ĵ�ǰ״̬
	bool			  RegisterLogicChannel(SInt64 lSymbolTime, UInt32 iRoomId, UInt32 iFromUin, ILogicListener* pLogicListener, UInt8& cLogicID,bool bA = false);

    //�ͷ�iDesUin֮���һ���߼�ͨ��
	void              UnregisterLogicChannel (UInt32 iRoomId, UInt32 iFromUin, UInt8 cLogicID, bool bNotify=true);
	
	//ע��UDPͨ��
	bool			  RegisterUDPChannel(UInt32 iRoomId);
	//�ͷ�UDPͨ��
	void              UnregisterUDPChannel(UInt32 iRoomId,bool bFace=true);

	//��ѯ��iDesUin֮�������ͨ��״̬
	//����ֵ��No_Exist�� Ready��Connecting��Success��Disconnect��
	unsigned short    QueryChannelStatus (UInt32 iRoomId);

	//�ж���iRoomId֮�������ͨ���Ƿ�����
	bool              IsUsingChannel (UInt32 iRoomId);

	//��ָ����Channel�Ϸ�������
	void              SendData (UInt32 iRoomId, UInt8* pData, UInt16 sDataLen,bool bA=false);

	//����ͨ��imͨ����������������
    void              ProcessCmd(UInt32 iRoomId, UInt8* pCmd, UInt16 sCmdLen);

	//�޸���ת������IP �˿�
	void              ChangeRelayServer(UInt32 iRoomId,UInt32 iRelayIP, UInt16 sRelayPort);
	
	//����AVkey
	void			  SetAVKey(UInt32 iRoomId,UInt32 iKey);
	
	//��ȡ��������Ƶ����״̬
	void			  GetAVNetSendStatus(UInt32 iRoomId,UInt32& iAudioTotalPacket,UInt32& iLostAudioPacket, UInt32& iVideoTotalPacket, UInt32& iLostVideoPacket);

	//��ȡ���ж�����
	float             GetLostRate();
private:

	RelayManger();
	~RelayManger();

private:

	static RelayManger*            s_pInstance;
	static IModuleManager*       s_pModuleManager;

};
