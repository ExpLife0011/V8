#include "StdAfx.h"
#include "ChannelManager.h"
#include "TimeUtils.h"
#include "TimersManager.h"
#include "ChannelMaintainTimer.h"
#include "Setting.h"

RCPtr<ChannelManager>  ChannelManager::s_pInstance = RCPtr<ChannelManager>(NULL);

UInt64  g_Index(UInt32 iDesUin)
{
	//���Ž�һ����չ�ã���ʱ����
	UInt64 lIndex = 0;
	return ((lIndex<<32)+iDesUin);
}

void  ChannelManager::Initialize()
{
	if (!s_pInstance)
	{
		s_pInstance = RCPtr<ChannelManager>(new ChannelManager());
	}
}

RCPtr<ChannelManager> ChannelManager::Instance()
{
	return s_pInstance;
}

void  ChannelManager::DestroyInstance()
{
	s_pInstance->Destroy();
	s_pInstance = RCPtr<ChannelManager>(NULL);
}

ChannelManager::ChannelManager()
               :m_iChannelMaintainTimeID(0)
{
	StartMaintainTimer();
}

ChannelManager::~ChannelManager()
{
	//Destroy();
	//Trace("��ʼ���ѭ������ m_CmdPacketCircleBuffer time = %I64d \n", GetTickCount());
	UInt32   iLen  = 0;
	UInt32   iRoomId = 0;
	Packet*  pPacket  = NULL;
	while(m_CmdPacketCircleBuffer.pop_front(pPacket, iLen, iRoomId))
	{
		SAFE_DELETE(pPacket);
	}
}

RCPtr<UdpChannel> ChannelManager::CreateUdpChannel(UInt32 iRoomId,IModuleManager *pModuleManager)
{
	MutexLocker locker(&m_Mutex);//m_ChannelMap ���߳� �����߳�

	RCPtr<UdpChannel> pChannel(new UdpChannel(g_Setting.getMyUin(), iRoomId, pModuleManager));
	m_ChannelMap.insert(channel_pair(g_Index(iRoomId), pChannel));

	return pChannel;
}

RCPtr<UdpChannel>  ChannelManager::FindUdpChannel(UInt32 iRoomId)
{
	RCPtr<UdpChannel> pChannel(NULL);

	std::map<UInt64, RCPtr<UdpChannel> >::iterator iter;
	MutexLocker locker(&m_Mutex);//m_ChannelMap ���߳� �����߳�
	iter = m_ChannelMap.find(g_Index(iRoomId));
	if (iter!=m_ChannelMap.end())
	{
		pChannel = iter->second;
	}

	return pChannel;
}

void ChannelManager::RemoveUdpChannel(UInt32 iRoomId)
{
	RCPtr<UdpChannel> pChannel(NULL);
	{
		std::map<UInt64, RCPtr<UdpChannel> >::iterator iter;
		MutexLocker locker(&m_Mutex);//m_ChannelMap ���߳� �����߳�
		iter = m_ChannelMap.find(g_Index(iRoomId));
		if (iter!=m_ChannelMap.end())
		{
			pChannel = iter->second;
			m_ChannelMap.erase(iter);
		}
	}
}

void ChannelManager::GetAllChannel(std::vector<RCPtr<UdpChannel> >& vAllChannels)
{
	std::map<UInt64, RCPtr<UdpChannel> >::iterator iter;
	MutexLocker locker(&m_Mutex);//m_ChannelMap ���߳� �����߳�
	for (iter=m_ChannelMap.begin(); iter!=m_ChannelMap.end(); iter++)
	{
		RCPtr<UdpChannel> pChannel = iter->second;
		vAllChannels.push_back(pChannel);
	}
}

void  ChannelManager::ClearChannels()
{
	Trace("��� m_ChannelMap time = %I64d \n",GetTickCount());
	MutexLocker locker(&m_Mutex);//m_ChannelMap ���߳� �����߳�
	m_ChannelMap.clear();
}

void ChannelManager::Maintain()
{
	MutexLocker locker(&m_Mutex);//m_ChannelMap ���߳� �����߳�
	SInt64 lCurTime = TimeUtils::Milliseconds();
	std::vector< RCPtr<UdpChannel> > vAllChannels;
	GetAllChannel(vAllChannels);

	for (UInt32 i=0; i<vAllChannels.size(); i++)
	{
		if (vAllChannels[i]->Maintain(lCurTime))
		{
			RemoveUdpChannel(vAllChannels[i]->GetRoomId());
		}
	}
}

void ChannelManager::StartMaintainTimer()
{
	ChannelMaintainTimer* pTimer = new ChannelMaintainTimer();

	TimersManager* pTimersManager   = TimersManager::getInstance();
	Assert(pTimersManager!=NULL);

	m_iChannelMaintainTimeID= pTimersManager->registerTimerHandler(0, 100, pTimer);
	Assert(m_iChannelMaintainTimeID>0);
}

void ChannelManager::StopMaintainTimer()
{
	if (m_iChannelMaintainTimeID!=0)
	{
		TimersManager* pTimersManager = TimersManager::getInstance();
		Assert(pTimersManager!=NULL);
		Trace("ChannelManager::StopMaintainTimer() removeTimerHandler \n");
		Assert(0);
		pTimersManager->removeTimerHandler(m_iChannelMaintainTimeID, true);
		m_iChannelMaintainTimeID = 0;
	}
}

void ChannelManager::Destroy()
{
	//Trace("ChannelManager::Destroy()���� time = %I64d \n", GetTickCount());

	StopMaintainTimer();

	ClearChannels();

	//Trace("��ʼ���ѭ������ m_CmdPacketCircleBuffer time = %I64d \n", GetTickCount());
	UInt32   iLen  = 0;
	UInt32   iRoomId = 0;
	Packet*  pPacket  = NULL;
	while(m_CmdPacketCircleBuffer.pop_front(pPacket, iLen, iRoomId))
	{
		SAFE_DELETE(pPacket);
	}
}

void  ChannelManager::PutCmdPacket(UInt32 iRoomId, UInt8* pCmd, UInt32 iCmdLen)
{
	Trace("ChannelManager::PutCmdPacket ��������� time = %I64d \n", GetTickCount());
	Packet* pPacket = new Packet(-1);
	Assert(NULL!=pPacket);
	pPacket->setContent(pCmd, iCmdLen);
	m_CmdPacketCircleBuffer.push_back(pPacket, 0, iRoomId);
}

void  ChannelManager::ProcessCmdPacket()
{
	UInt32   iLen  = 0;
	UInt32   iRoomId = 0;
	Packet*  pPacket  = NULL;
	while(m_CmdPacketCircleBuffer.pop_front(pPacket, iLen, iRoomId))
	{
		Trace("ChannelManager::ProcessCmdPacket ��������� time = %I64d \n", GetTickCount());

		Assert(NULL!=pPacket);
		RCPtr<UdpChannel> pUdpChannel = FindUdpChannel(iRoomId);
		if (pUdpChannel)
		{
		 	pUdpChannel->ProcessCmdPacket(pPacket);
		}
		else
		{
			Assert(0);
		}

		SAFE_DELETE(pPacket);
	}
}


