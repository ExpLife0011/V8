#include "stdafx.h"
#include "UdpChannel.h"
#include "UdpSocketHandler.h"

#include "NetInterface.h"
#include "TimeUtils.h"
#include "MyAssert.h"
#include "Setting.h"
//#include "P2PManger.h"
#include "statisticdatadef.h"
#include "RelayAlivePacket.h"
#include "RelayPacket.h"
#include "TimersManager.h"
//#include "ChannelInterface.h"
//#include "ChannelModule.h"
#include <iostream>
#include <string.h>
#include <assert.h>
#include "Buffers/BufferManager.h"
#include "ChannelManager.h"


#define  DEFAULT_BEGIN_UDP_PORT                  10000
#define  MAX_WAIT_MSG_TIME                        3000
#define  MAX_WAIT_CMD_TIME                        3000
#define  SEND_CYCLE_TIME                          1000

#define  MAX_NO_ALIVE_TIME                       15000
#define  NETTEST_TIME							    10
#define  MAX_SEND_NETTEST_TIME					  5000
#define  MAX_GETIP_PORT_TIME					 15000
#define  MAX_RECV_NETTEST_ACK_TIME				MAX_SEND_NETTEST_TIME + 1000


UdpChannel::UdpChannel(UInt32 iMyUin, UInt32 iRoomId,IModuleManager *pModuleManager)
           : m_iSocketID(-1),
             m_iMyUin(iMyUin),
			 m_iRoomId(iRoomId),
			 m_iMyPrvIP(g_Setting.getMyIP()),
			 m_sMyPrvPort(DEFAULT_BEGIN_UDP_PORT),
			 m_iRelayIP(g_Setting.getRelayIP()),
			 m_sRelayPort(g_Setting.getRelayPort()),
			 m_iMaxConnTime(g_Setting.getMaxConnTime()),
			 m_lLastAliveSendTime(0),
			 m_lLastAliveRcvTime(0),
			 m_sRelaySeq(1),
			 m_cLogicSeed(0),
			 m_sStatus(CHANNEL_READY),
			 m_pModuleManager(pModuleManager),
			 m_lConnectBeginTime(0),//��ʼ����ʱ��
			 m_bCreatingRelaySession(true),//���ڴ�����ת����Session
			 m_bLastValue(false), //�Ƿ��������ӳɹ�ʱ���IP Port
			 m_iAliveIP(0), 
			 m_sAlivePort(0),
			 s_audio_sequence(0),
			 s_video_sequence(0),
			 m_bChangeServer(false),
			 m_keep_count(0),
			 m_iLastAudioReqSequence(0),
			 m_iRequestAudioCount(0),
			 m_iLastVideoReqSequence(0),
			 m_iRequestVideoCount(0),
			 m_iSendAudioCount(0),
			 m_iSendVideoCount(0),
			 m_dwLastRateTime(GetTickCount()),
			 m_iRequestAudioCountEx(0),
			 m_iRequestVideoCountEx(0),
			 m_iSendAudioCountEx(0),
			 m_iSendVideoCountEx(0)
{
	::srand((unsigned)time(NULL));
 	m_cLogicSeed = (UInt8) ::rand();
	if (m_cLogicSeed<10)  m_cLogicSeed += 10;//1-9ΪԤ�����߼�ID
	Trace("UdpChannel: Constructor...time = %I64d \n", GetTickCount());
}

UdpChannel::~UdpChannel()
{
	if (m_iSocketID>=0)
	{
		NetInterface::unregisterSocket(m_iSocketID);
		m_iSocketID = -1;
	}
	Trace("UdpChannel: Destructor...time = %I64d \n", GetTickCount());
}

void UdpChannel::Start()
{
	Trace("UdpChannel: Start(),Cur status=%d \n",GetStatus());
	if (CHANNEL_READY==GetStatus())
	{
		StartListen(); //���������Ķ˿�
		SetStatus(CHANNEL_CONNECTING); //��������״̬
		Trace("UdpChannel: Start(),status change into CHANNEL_CONNECTING time = %I64d \n", GetTickCount());
	}
}

void UdpChannel::StartListen()
{
	//���ѡ��Udp�˿ڽ��а�
	::srand( (UInt32)::time( NULL ) );
	UdpSocketHandler* pUdpHandler = new UdpSocketHandler(m_iRoomId);

	unsigned int loop=0;
	do 
	{
		m_sMyPrvPort = DEFAULT_BEGIN_UDP_PORT;
		m_sMyPrvPort = m_sMyPrvPort + ::rand()%40000;

		m_iMyPrvIP = GetLocalIP("60.190.39.200");
		m_iSocketID = NetInterface::registerSocketHandler(m_iMyPrvIP, ::htons(m_sMyPrvPort), pUdpHandler);
	} 
	while( m_iSocketID<0 && ((loop++)<200) );

	Trace("UdpChannel: [MyUin= %d] ��������Ķ˿� [ Port = %d ] \n", m_iMyUin, m_sMyPrvPort);
}

void UdpChannel::Stop(UInt8 cReason)
{
	Trace("UdpChannel::Stop [reason=%d]\n",cReason);
	if (SetStatus( CHANNEL_DESTROY ))
	{
	    Trace("UdpChannel:֪ͨ��ת������destory,�������� time = %I64d \n", GetTickCount());
	    SendToRelayServer(AV_CMD_DESTROY, ++m_sRelaySeq);

		//��ȡ��������еļ�����
		{
			std::vector<RCPtr<WrapListener> > vAllListeners;
			std::map<UInt8, RCPtr<WrapListener> >::iterator iter;
			{
				MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
				for (iter=m_ListenersMap.begin(); iter!=m_ListenersMap.end(); ++iter)
				{
					vAllListeners.push_back(iter->second);
				}
				m_ListenersMap.clear();
			
				//֪ͨ�ϲ�ļ����
				for (UInt32 i=0; i< vAllListeners.size(); i++)
				{
					vAllListeners[i]->onDisconnect(cReason);
				}
			}
		}
	}
}

bool UdpChannel::Maintain(SInt64 lCurTime)
{
	m_lCurTime = lCurTime;
	bool bRemove = false;

	switch(GetStatus()&CHANNEL_MASK) 
	{
	case CHANNEL_READY: 
		break;
	case CHANNEL_CONNECTING:
		{
			if (0==m_lConnectBeginTime) m_lConnectBeginTime = lCurTime;
			//if (lCurTime-m_lConnectBeginTime>2000)//���뷿��2���������ת������
			{
				Trace("������[MyUin=%d]������������ת������  time = %I64d \n",m_iMyUin ,GetTickCount());
				SwitchToRelay(m_iRelayIP, m_sRelayPort);
			}
		}
		break;
	case CHANNEL_RELAYING:
// 		if (lCurTime-m_lConnectBeginTime<m_iMaxConnTime)  =========================haosl  ����  ���� �պ�ʱ��û������������ ��ʾ�ϲ㴦��
// 		{
			if (m_bCreatingRelaySession)
			{
				//����������ת������
				if (lCurTime-m_lLastAliveSendTime>MAX_WAIT_MSG_TIME)
				{
					Trace("����ת������[%s:%d]����RELAY_CREATE time = %I64d \n",NetInterface::IPUInt32ToString(m_iRelayIP).c_str(), m_sRelayPort, GetTickCount());
					if (lCurTime-m_lLastAliveSendTime>SEND_CYCLE_TIME*3)
					{
						for (int i=0; i<ALIVE_PACK_COUNT ; i++)
						{
							SendToRelayServer(AV_CMD_KEEPALIVE, ++m_sRelaySeq);
						}
					}
					m_lLastAliveSendTime = lCurTime;
				}
			}
			else
			{
				//�յ�Relay��������Relay_Success����, ��ʼ����RelayKeepAlive
				if (lCurTime-m_lLastAliveSendTime>SEND_CYCLE_TIME)
				{
					Trace("����������ת������[%s:%d]������AV_CMD_KEEPALIVE time = %I64d \n", NetInterface::IPUInt32ToString(m_iRelayIP).c_str(), m_sRelayPort, GetTickCount());
					for (UInt16 i=0; i<ALIVE_PACK_COUNT; i++)
					{
						SendToRelayServer(AV_CMD_KEEPALIVE, ++m_sRelaySeq);
					}
					m_lLastAliveSendTime = lCurTime;
					SetStatus(CHANNEL_SUCCESS);
				}
			}
//		}
// 		else
// 		{
// 			//�������ʱ����������ת������ʧ��
// 			Stop(REASON_RELAY_FAIL);
// 			bRemove = true;
// 			Trace("������[MyUin=%d]������������ת������ʧ�ܣ�REASON_RELAY_FAIL\n",m_iMyUin);
// 		}
		break;
	case CHANNEL_SUCCESS:
		if (lCurTime-m_lLastAliveSendTime>SEND_CYCLE_TIME*3) //&& lCurTime-m_lLastAliveRcvTime>SEND_CYCLE_TIME*3
		{
			Trace("--------------���ڷ���keep Alive,�������ӳ�ͨ�������� time = %I64d \n", GetTickCount());
			if (m_bChangeServer)
			{
				KeepAlive();
			}

			if (++m_keep_count%10 == 0 || m_bChangeServer)
			{
				Trace("--------------����ע����������� time = %I64d \n", GetTickCount());
				KeepAlive();
				m_bChangeServer = false;
			}
			else
			{
				Trace("--------------��������ά�ְ��������� time = %I64d \n", GetTickCount());
				KeepAliveEx();
			}
		}
		else
		{
			static unsigned int s_count = 0;
			s_count ++;
			//if (++s_count%50 == 0)
			//{
				Trace("+++++++++++++++++û�з���keep Alive,�������ӳ�ͨ�������� time = %I64d \n", GetTickCount());
			//}
		}

// 		if (lCurTime-m_lLastAliveRcvTime>MAX_NO_ALIVE_TIME) ==================================haosl����   ����
// 		{
// 			Assert(0);
// 			Stop(REASON_ALIVE_TIMEOUT_FAIL);
// 			bRemove = true;
// 			Trace("RoomId[=%d]��ʱ��û���յ�Alive, �Ͽ���REASON_RELAY_FAIL\n",m_iRoomId);
// 		}

		ResetRateCount();
		break;
	case CHANNEL_DESTROY:
		bRemove = true;
		break;
	default:
		Assert(0);
		break;
	}

	return bRemove;
}

//����ת����������
void UdpChannel::SendToRelayServer(UInt16 cCmdType, UInt16 sSeq)
{
	Packet* pPacket = NULL;

	if (AV_CMD_ALIVE == cCmdType)
	{
		pPacket = new Packet(-1,0);
		UInt16 cmdType = htons(cCmdType);
		pPacket->setContent((UInt8*)&cmdType,2);
	}
	else
	{
		UInt32 iKey = g_Setting.getAVKey(m_iRoomId);
		AssertVS(iKey!=0,iKey,"iKey==0");
		pPacket = RelayAlivePacket::makePacket(-1, m_iMyUin, m_iRoomId,iKey);
		if (!pPacket)
		{
			Trace("UdpChannel::SendToRelayServer: �����ڴ�ʧ�� time = %I64d\n",GetTickCount());
			return;
		}
		Trace("NetInterface::sendUDPPacket *****RoomId=%d,IP=%s,port=%d ע���\n",m_iRoomId,NetInterface::IPUInt32ToString(m_iRelayIP).c_str(), m_sRelayPort);
	}

	pPacket->AddReference();
	NetInterface::sendUDPPacket(m_iSocketID, m_iRelayIP, ::htons(m_sRelayPort), pPacket);
	Trace("NetInterface::sendUDPPacket *****RoomId=%d,IP=%s,port=%d\n",m_iRoomId,NetInterface::IPUInt32ToString(m_iRelayIP).c_str(), m_sRelayPort);
}

//ѡ����ת������IP��Port
void  UdpChannel::SwitchToRelay(UInt32 iRelayIP, UInt16 sRelayPort)
{
	if (GetStatus()!=CHANNEL_SUCCESS)
	{
		SetRelayIP(iRelayIP, sRelayPort);
		SetStatus(CHANNEL_RELAYING);
		m_lConnectBeginTime = TimeUtils::Milliseconds();
	}
}

//������ת������IP��Port
void UdpChannel::SetRelayIP(UInt32 iRelayIP, UInt16 sRelayPort)
{
	m_iRelayIP   = iRelayIP;
	m_sRelayPort = sRelayPort;
	m_bChangeServer = true;
	
	Trace("UdpChannel::SetRelayIP *****RoomId=%d,IP=%s,port=%d\n",m_iRoomId,NetInterface::IPUInt32ToString(iRelayIP).c_str(), sRelayPort);
}

//ά��������
void UdpChannel::KeepAlive(UInt16 sNum/* =1 */, bool bAck)
{
	for (int i=0; i<sNum; ++i)
	{
		SendToRelayServer(AV_CMD_KEEPALIVE, ++m_sRelaySeq);
	}
	m_lLastAliveSendTime = TimeUtils::Milliseconds();
}

void UdpChannel::KeepAliveEx(UInt16 sNum/*=1*/)
{
	for (int i=0; i<sNum; ++i)
	{
		SendToRelayServer(AV_CMD_ALIVE, ++m_sRelaySeq);
	}
	m_lLastAliveSendTime = TimeUtils::Milliseconds();
}

void UdpChannel::SendData(UInt8* pData, UInt16 sDataLen,bool bA)
{
	if (CHANNEL_SUCCESS==GetStatus())
	{
		Packet* pDataPacket = NULL;
		//pDataPacket = RelayDataPacket::makePacket(-1, sDataLen, pData);
		static unsigned int s_data = 0;
		if (++s_data%500 == 0 )
		{
			ErrTrace("����%s���ݰ���������time = %I64d \n",bA?"��Ƶ":"��Ƶ", GetTickCount());
		}
		
		unsigned int iSequence = bA?++s_audio_sequence:++s_video_sequence;

// 		static unsigned int icount = 0;
// 		if (bA && icount++ % 20==1) //+++++++++++++++++++++++++++++++++++++
// 			return;

		pDataPacket = RelayDataPacket::makePacket(-1,m_iMyUin,m_iRoomId,bA?AV_CMD_AUDIO:AV_CMD_VIDEO,iSequence,sDataLen,pData);
		if (!pDataPacket)
		{
			Trace("UdpChannel::SendData: �����ڴ�ʧ��[len=%d] time = %I64d\n", sDataLen,GetTickCount());
			return;
		}

		pDataPacket->AddReference();
		g_bufferManager.AddInputPacket(m_iRoomId,pDataPacket,iSequence,bA);
		
		NetInterface::sendUDPPacket(m_iSocketID, m_iRelayIP, ::htons(m_sRelayPort), pDataPacket);
		//Trace("UdpChannel::SendData IP=%s ,port=%d, len=%d\n",NetInterface::IPUInt32ToString(m_iRelayIP).c_str(),ntohs(m_sRelayPort),sDataLen);

		bA?m_iSendAudioCount++:m_iSendVideoCount++;
		bA?m_iSendAudioCountEx++:m_iSendVideoCountEx++;
	}
	else
	{
		Assert(0);
		static unsigned int s_count = 0;
		if (s_count++%50 == 0){
			ErrTrace("UdpChannel not CHANNEL_SUCCESS status \n");
		}
	}
}

void UdpChannel::SendRepeatData(Packet* pRePacket,bool bA)
{
	if (CHANNEL_SUCCESS==GetStatus())
	{
		Packet* pDataPacket = NULL;
		static unsigned int s_data = 0;
		if (++s_data%10 == 0 )
		{
			Trace("SendRepeatData ��%s���ݰ���������time = %I64d \n",bA?"��Ƶ":"��Ƶ", GetTickCount());
		}
		pRePacket->AddReference();
		NetInterface::sendUDPPacket(m_iSocketID, m_iRelayIP, ::htons(m_sRelayPort), pRePacket);
	}
	else
	{
		Assert(0);
	}
}


//logic Listener,ÿһ��Ӧ��һ��Listener ע��һ���߼�ͨ��
bool UdpChannel::RegisterListener(ILogicListener* pLogicListener, UInt8& cLogicID,UInt32 iRoomId,UInt32 iFromUin,bool bA)
{
	Trace("UdpChannel::RegisterListener..begin time = %I64d \n", GetTickCount());
	if (pLogicListener)
	{
		{
			MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
			if (GetStatus()==CHANNEL_DESTROY)
			{
				Assert(0);
				return false;
			}

			if (0==cLogicID)
			{
				//��ע��ļ����ߣ���Ҫ�����µ�LogicID
				int  iCount = 255;
				while (m_ListenersMap.find(m_cLogicSeed)!=m_ListenersMap.end())
				{
					--iCount;
					if( iCount<0)
					{
						Assert(0);
						return false;
					}
					m_cLogicSeed+=2;
					if (m_cLogicSeed<10) m_cLogicSeed += 10;
				}

				cLogicID              = m_cLogicSeed;
				m_cLogicSeed+=2;
				if (m_cLogicSeed<10) m_cLogicSeed += 10;
			}
			else
			{
				//ʹ�öԷ�������LogicID, ��IDӦ����û�б��ù���
				if(m_ListenersMap.find(cLogicID)!=m_ListenersMap.end())
				{
					Assert(0);
					return false;
				}
			}
			RCPtr<WrapListener> pWrapListener(new WrapListener(pLogicListener));
			m_ListenersMap.insert(listener_pair(cLogicID, pWrapListener));
			
			//ӳ�䴦��
			if (bA) //����
			{
				RCPtr<StructALogic> pLogic (new StructALogic());
				pLogic->cLogicId = cLogicID;
				pLogic->iFromUin=iFromUin;
				pLogic->iRoomId=iRoomId;
				m_ListenersRoomDestAMap.insert(listenerRoomDesA_pair(LogicIndex(iRoomId,iFromUin),pLogic));
			}
			else //��Ƶ
			{
				RCPtr<StructVLogic> pLogic (new StructVLogic());
				pLogic->cLogicId = cLogicID;
				pLogic->iFromUin=iFromUin;
				pLogic->iRoomId=iRoomId;
				m_ListenersRoomDestVMap.insert(listenerRoomDesV_pair(LogicIndex(iRoomId,iFromUin),pLogic));
			}

		}

		if (GetStatus()==CHANNEL_SUCCESS)
		{
			pLogicListener->onConnected(); //֪ͨListener
		}
		Trace("UdpChannel::RegisterListener success logicId=%d time = %I64d \n",cLogicID,GetTickCount());
		return true;
	}
	return false;
}

void  UdpChannel::UnregisterListener(UInt8 cLogicID, UInt32 iRoomId,UInt32 iFromUin, bool bCallBack)
{
	Trace("UdpChannel::UnregisterListener time = %I64d \n", GetTickCount());
	RCPtr<WrapListener> pWrapListener(NULL);
	{
		std::map<UInt8, RCPtr<WrapListener> >::iterator iter;
		MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
		iter = m_ListenersMap.find(cLogicID);
		if (iter!=m_ListenersMap.end())
		{
			pWrapListener = iter->second;
			m_ListenersMap.erase(iter);
		}
	}
	
	//ӳ�䴦�� ȡ��ע��
	RCPtr<StructALogic>  pALogic(NULL);
	{
		std::map<UInt64,RCPtr<StructALogic> >::iterator iter;
		iter = m_ListenersRoomDestAMap.find(LogicIndex(iRoomId,iFromUin));
		if (iter!=m_ListenersRoomDestAMap.end())
		{
			pALogic = iter->second;
			m_ListenersRoomDestAMap.erase(iter);
		}
	}

	RCPtr<StructVLogic>  pVLogic(NULL);
	{
		std::map<UInt64,RCPtr<StructVLogic> >::iterator iter;
		iter = m_ListenersRoomDestVMap.find(LogicIndex(iRoomId,iFromUin));
		if (iter!=m_ListenersRoomDestVMap.end())
		{
			pVLogic = iter->second;
			m_ListenersRoomDestVMap.erase(iter);
		}
	}

	if (pWrapListener)
	{
		pWrapListener->WaitUnshared();

		if (bCallBack)
		{
			Trace("UdpChannel::UnregisterListener[logicid = %d] onDisconnect time = %I64d\n", cLogicID,GetTickCount());
			pWrapListener->onDisconnect(REASON_CANCEL_FAIL);
		}
	}
}

RCPtr<WrapListener> UdpChannel::GetListener(UInt8 cLogicID,bool addRef)
{
	RCPtr<WrapListener> pWrapListener(NULL);
	{
		std::map<UInt8, RCPtr<WrapListener> >::iterator iter;
		MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
		iter = m_ListenersMap.find(cLogicID);
		if (iter!=m_ListenersMap.end())
		{
			pWrapListener = iter->second;
			if (addRef) pWrapListener->AddReference();
		}
	}

	return pWrapListener;
}

RCPtr<StructVLogic> UdpChannel::GetListenerLogicV(UInt32 iRoomId,UInt32 iFromUin)
{
	RCPtr<StructVLogic> pLogic(NULL);
	{
		std::map<UInt64, RCPtr<StructVLogic> >::iterator iter;
		MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
		iter = m_ListenersRoomDestVMap.find(LogicIndex(iRoomId,iFromUin));
		if (iter!=m_ListenersRoomDestVMap.end())
		{
			pLogic = iter->second;
		}
	}
	return pLogic;
}

RCPtr<StructALogic> UdpChannel::GetListenerLogicA(UInt32 iRoomId,UInt32 iFromUin)
{
	RCPtr<StructALogic> pLogic(NULL);
	{
		std::map<UInt64, RCPtr<StructALogic> >::iterator iter;
		MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
		iter = m_ListenersRoomDestAMap.find(LogicIndex(iRoomId,iFromUin));
		if (iter!=m_ListenersRoomDestAMap.end())
		{
			pLogic = iter->second;
		}
	}
	return pLogic;
}

UInt64	UdpChannel::LogicIndex(UInt32 iRoomId,UInt32 iFromUin)
{
	UInt64 lIndex = iRoomId;
	return ((lIndex<<32)+iFromUin);
}

void  UdpChannel::GetAllListener(std::vector<RCPtr<WrapListener> >& vAllListeners)
{
	std::map<UInt8, RCPtr<WrapListener> >::iterator iter;
	MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
	for (iter=m_ListenersMap.begin(); iter!=m_ListenersMap.end(); ++iter)
	{
		vAllListeners.push_back(iter->second);
	}
}

bool UdpChannel::IsExistListener()
{
	MutexLocker locker(&m_ListenerMutex);//�����߳� �����߳�  m_ListenersMap
	return m_ListenersMap.empty() ? false : true;
}

bool UdpChannel::IsExistsListener(UInt32 iRoomId,UInt32 iFromUin,bool bA)
{
	std::map<UInt64,RCPtr<StructALogic> >::iterator iterA;
	std::map<UInt64,RCPtr<StructVLogic> >::iterator iterV;
	if (bA)
	{
		iterA = m_ListenersRoomDestAMap.find(LogicIndex(iRoomId,iFromUin));
		return iterA!=m_ListenersRoomDestAMap.end();
	}
	else
	{
		iterV = m_ListenersRoomDestVMap.find(LogicIndex(iRoomId,iFromUin));
		return iterV!=m_ListenersRoomDestVMap.end();
	}
}

bool UdpChannel::SetStatus(UInt16 sStatus)
{

	MutexLocker locker(&m_Mutex); // ��ֹͬʱ����GetAllListener���������ܻ�����                                

	if (sStatus==m_sStatus) return false;
	if (   (CHANNEL_SUCCESS!=m_sStatus)
		|| ( (CHANNEL_SUCCESS==m_sStatus)&&(sStatus>CHANNEL_SUCCESS) ) )
	{
		m_sStatus          = sStatus;
	}

	if (CHANNEL_DESTROY!=sStatus)//��������ϱ�״̬
	{
		std::vector<RCPtr<WrapListener> > vAllListeners;
		GetAllListener(vAllListeners);
		for (UInt32 i=0; i< vAllListeners.size(); i++)
		{
			//������ӳɹ�������onConnect
			if (CHANNEL_SUCCESS==sStatus)
			{
				vAllListeners[i]->onConnected();
			}
			else
			{
				vAllListeners[i]->onStatus(sStatus);
			}
		}
		vAllListeners.clear();
	}

	return true;
}

void UdpChannel::SetRelayIPAddr()
{
	m_iRelayIP		= g_Setting.getRelayIP();
	m_sRelayPort	= g_Setting.getRelayPort();
}

void UdpChannel::SetAliveIPAddr(UInt32 iAliveIP, UInt16 sAlivePort, bool bLastValue)
{
	if (!m_bLastValue)
	{
		m_iAliveIP    = iAliveIP;
		m_sAlivePort  = sAlivePort;
		m_bLastValue  = bLastValue;
		Trace("�������ӽ����ɹ�ʱ���[IP=%s, port=%d]\n",NetInterface::IPUInt32ToString(m_iAliveIP).c_str(),m_sAlivePort);
	}
}

void UdpChannel::FinishCreatingRelaySession()
{
	if (m_bCreatingRelaySession) 
	{
		m_bCreatingRelaySession = false;
		Trace("CreatingRelaySession Success!!!");
	}
		
}

void UdpChannel::PlayAudioPacket(UInt32 iRoomId,UInt32 iFromUin,Packet* pPacket,unsigned int iSeq)
{
	RCPtr<ChannelManager> pChannelMgr = ChannelManager::Instance();
	if (!pChannelMgr)
	{
		Assert(0);
		return;
	}
	RCPtr<UdpChannel> pUdpChannel = pChannelMgr->FindUdpChannel(iRoomId);
	if (pUdpChannel)
	{
		RCPtr<StructALogic> pLogic = pUdpChannel->GetListenerLogicA(iRoomId,iFromUin);
		if (pLogic)
		{
			RCPtr<WrapListener> pListener = pUdpChannel->GetListener(pLogic->cLogicId,true);
			if (pListener)
			{
				try
				{
					pListener->onReceive(pPacket->getPacketContent(),pPacket->getPacketLen(),iSeq);
					pListener->RemoveReference();
				}
				catch (...)
				{
					ErrTrace("UdpChannel::PlayAudioPacket Err\n");
				}
			}
			else
			{
				AssertV(0,iFromUin);
			}
		}
		else
		{
			AssertV(0,iRoomId);
		}
	}
	else
	{
		AssertV(0,iRoomId);
	}
}

void UdpChannel::PlayVideoPacket(UInt32 iRoomId,UInt32 iFromUin,Packet* pPacket)
{
	RCPtr<ChannelManager> pChannelMgr = ChannelManager::Instance();
	if (!pChannelMgr)
	{
		Assert(0);
		return;
	}
	RCPtr<UdpChannel> pUdpChannel = pChannelMgr->FindUdpChannel(iRoomId);
	if (pUdpChannel)
	{
		RCPtr<StructVLogic> pLogic = pUdpChannel->GetListenerLogicV(iRoomId,iFromUin);
		if (pLogic)
		{
			RCPtr<WrapListener> pListener = pUdpChannel->GetListener(pLogic->cLogicId,true);
			if (pListener)
			{
				try
				{
					pListener->onReceive(pPacket->getPacketContent(),pPacket->getPacketLen(),0);
					pListener->RemoveReference();
				}
				catch (...)
				{
					AssertVS(0,iFromUin,"UdpChannel::PlayVideoPacket Err\n");
				}
			}
			else
			{
				AssertV(0,iFromUin);
			}
		}
		else
		{
			AssertV(0,iRoomId);
		}
	}
	else
	{
		AssertV(0,iRoomId);
	}
}

void  UdpChannel::RequestCompenPacket(UInt32 iRoomId,UInt32 iFromUin,Packet* pPakcet)
{
	RCPtr<ChannelManager> pChannelMgr = ChannelManager::Instance();
	if (!pChannelMgr)
	{
		pPakcet->RemoveReference();
		AssertV(0,iRoomId);
		return;
	}
	RCPtr<UdpChannel> pUdpChannel = pChannelMgr->FindUdpChannel(iRoomId);
	if (pUdpChannel)
	{
		pUdpChannel->SendPacket(pPakcet);
	}
	else
	{
		pPakcet->RemoveReference();
		AssertV(0,iRoomId);
	}
}

void UdpChannel::SendPacket(Packet* pPakcet)
{
	NetInterface::sendUDPPacket(m_iSocketID, m_iRelayIP, ::htons(m_sRelayPort), pPakcet);
}

void UdpChannel::ResetRateCount()
{
	if (GetTickCount() - m_dwLastRateTime > 1000*60*5) //5����ͳ��һ��
	{
		if (m_iSendAudioCountEx>0 || m_iSendVideoCountEx>0)
		{
			g_Setting.m_iLostRate = ((float)(m_iRequestAudioCountEx+m_iRequestVideoCountEx)) /(m_iSendAudioCountEx+m_iSendVideoCountEx+m_iRequestAudioCountEx+m_iRequestVideoCountEx);
		}

		m_iRequestAudioCountEx = 0;
		m_iRequestVideoCountEx = 0;
		m_iSendAudioCountEx = 0;
		m_iSendVideoCountEx = 0;

		m_dwLastRateTime = GetTickCount();
	}
}