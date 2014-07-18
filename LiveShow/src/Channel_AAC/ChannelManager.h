#pragma once
#ifdef _DEBUG
//#include <vld.h>
#endif
#include <map>
#include <vector>
#include "UdpChannel.h"
#include "Mutex.h"
#include "CircleBuffer.h"

//ȫ����, ���ڶ�ȫ��ChannelUDP�Ĺ���

class ChannelManager : public RCObject
{
public:

 	static void                    Initialize();
 	static RCPtr<ChannelManager>   Instance();
 	static void                    DestroyInstance();

	ChannelManager();
	~ChannelManager();

 	RCPtr<UdpChannel>        CreateUdpChannel(UInt32 iRoomId,IModuleManager *pModuleManager);

 	RCPtr<UdpChannel>        FindUdpChannel(UInt32 iRoomId);
 	void                     RemoveUdpChannel(UInt32 iRoomId);
	void                     GetAllChannel(std::vector<RCPtr<UdpChannel> >& vAllChannels);
 	void                     ClearChannels();
	void                     Maintain();
 	void                     StartMaintainTimer();
	void					 StopMaintainTimer();
 	void                     Destroy();
 	void                     PutCmdPacket(UInt32 iRoomId, UInt8* pCmd, UInt32 iCmdLen);
 	void                     ProcessCmdPacket();

private:

	typedef std::pair<UInt64, RCPtr<UdpChannel> > channel_pair;

	Mutex                                  m_Mutex; //m_ChannelMap ���߳� �����߳�
	std::map<UInt64, RCPtr<UdpChannel> >   m_ChannelMap;                 //��ʶ�ǶԷ���Uin
	UInt32                                 m_iChannelMaintainTimeID;     //��ʱ��ID
	CircleBuffer<Packet*>                  m_CmdPacketCircleBuffer;

	static RCPtr<ChannelManager>           s_pInstance;
};