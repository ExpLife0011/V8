#include "stdafx.h"
#include "AsyncCom.h"
#include "WorkThread.h"
#include "TimersManager.h"
#include "ThreadsManager.h"
#include "SocketIDGenerater.h"
#include "EventPool.h"
#include "MyAssert.h"

#include  <string>
#include  <vector>
using namespace std;

void	WorkThread::Entry()
{
	try
	{
		//Trace("WorkThread::Entry() ... begin \n");
		while(!IsStopRequested())
		{
			SetRunningState(true);
			//���ȼ�ⶨʱ��
			SInt32 theTimeout = processTimer();

			//û��ֹͣ����ʱ;����ִ��;
			LPEvent	 pCurEvent = NULL;

			//����������������е������¼�
			if (getCommandEvent(pCurEvent, theTimeout))
			{
				if(pCurEvent!=NULL)
				{
					//�ɹ���������¼�
					processEvent(pCurEvent);

					//��Ϊ�����¼�����Ҫɾ����Buffer���ͷ���Դ;
					if (!(pCurEvent->m_iEventType&kSocketNetworkEvent))
					{
						EventPool::putLPEvent(pCurEvent);
					}
					pCurEvent =NULL;
				}
			}
		}

		Trace("WorkThread::Entry() ... end \n");
	}
	catch (...)
	{
		Trace("WorkThread::Entry() �����˳�����������\n");
	}
}

void	WorkThread::processEvent(LPEvent pEvent)
{
	Assert(pEvent!=NULL);
	UInt32  iArrayIndex  = 0;

	if((pEvent->m_iEventType&kSocketEventMask)!=0)
	{
		//////////////////////////////////////////////////////////////////////////
		//�¼�ΪSocket�¼�;
		//�������Socket���ڵ��±�����;
		iArrayIndex=(pEvent->m_iUniqueID/ThreadsManager::s_iWorkThreadsNum)%m_iSocketsArraySize;

		if(pEvent->m_iEventType&kAddSocketEvent)
		{
			m_pSocketContexts[iArrayIndex] = (SocketContext*)pEvent->m_pCookie;
		}
		if(m_pSocketContexts[iArrayIndex]!=NULL)
		{
			//////////////////////////////////////////////////////////////////////////
			//����SocketContext���¼����������¼����д���;
			m_pSocketContexts[iArrayIndex]->processEvent(pEvent);			
			if(pEvent->m_iEventType&kKillSocketEvent)
			{
				delete m_pSocketContexts[iArrayIndex];
				m_pSocketContexts[iArrayIndex]=NULL;
				SocketIDGenerater::clearUniqueID(pEvent->m_iUniqueID);
			}
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////
			//��Socket�Ѿ���ɾ��, ���Ҹ��¼�Ϊ���Ͱ����¼�;��Ҫ�԰���������;
			if(pEvent->m_iEventType&kSocketSendPacketEvent)
			{
				((Packet*)(pEvent->m_pCookie))->RemoveReference();
				pEvent->m_pCookie=NULL;
			}
		}
	}
	else if ((pEvent->m_iEventType&kTimerEventMask)!=0) 
	{
		Timer* pTimer = (Timer*)pEvent->m_pCookie;
		HeapElem* pHeapElem = pTimer->getHeapElem();
		if (pEvent->m_iEventType&kAddTimerEvent) 
		{
			//				pTimer->AddReference();
			pHeapElem->SetValue(TimeUtils::Milliseconds()+pTimer->getFirstExpireInterval());
			m_TimerHeap.Insert(pHeapElem);
		}
		else if (pEvent->m_iEventType&kKillTimerEvent)
		{
			if (m_TimerHeap.Remove(pHeapElem)!=NULL)
			{
				pTimer->RemoveReference();
			}
		}
	}
}

SInt32  WorkThread::processTimer()
{
	//Trace("WorkThread::processTimer() ... begin \n");
	SInt32 iWaitTime=10;
	while (1)
	{
		//Trace("WorkThread::processTimer() ... while \n");
		if (m_TimerHeap.PeekMin()!=NULL)
		{
			SInt64 lCurTime = TimeUtils::Milliseconds();
			if(m_TimerHeap.PeekMin()->GetValue() <= lCurTime)
			{
				//���ж�ʱ��
				HeapElem* pHeapElem = m_TimerHeap.ExtractMin();
				Timer* pTimer = (Timer*) pHeapElem->GetEnclosingObject();
				if (pTimer)
				{
					pTimer->Run();

					//���¼���ʱ�����
					pHeapElem->SetValue(lCurTime+pTimer->getPeriodExpireInterval());
					m_TimerHeap.Insert(pHeapElem);
				}
			}
			else
			{
				iWaitTime = m_TimerHeap.PeekMin()->GetValue() - lCurTime;
				break;
			}
		}

		break;
	}
	//Trace("WorkThread::processTimer() ... end \n");
	return iWaitTime;
}

//////////////////////////////////////////////////////////////////////////
//��������:
//�������:
//����ֵ:
void	WorkThread::clearCommandEvents()
{
	LPEvent		 pEvent  = NULL;
	//////////////////////////////////////////////////////////////////////////
	//����������������е������¼�����������û�������¼�����ȴ�5ms;
	while (getCommandEvent(pEvent))
	{
		if(pEvent!=NULL)
		{
			//////////////////////////////////////////////////////////////////////////
			//��Ϊ�����¼�����Ҫɾ����Buffer���ͷ���Դ;
			if(pEvent->m_iEventType&kSocketSendPacketEvent)
			{
				((Packet*)pEvent->m_pCookie)->RemoveReference();
			}
			if((pEvent->m_iEventType&kAddSocketEvent) ) 
			{
				delete (SocketContext*)pEvent->m_pCookie;
			}	
			if(pEvent->m_iEventType&kKillSocketEvent)  
			{
				// 					UInt32 iArrayIndex=(pEvent->m_iUniqueID/ThreadsManager::s_iWorkThreadsNum)%m_iSocketsArraySize;
				// 					SAFE_DELETE(m_pSocketContexts[iArrayIndex]);
			}
			if(pEvent->m_iEventType&kTimerEventMask)
			{
				Timer* pTimer = (Timer*)pEvent->m_pCookie;
				if (pEvent->m_iEventType&kAddTimerEvent) 
				{
					//��ʱֱ��ɾ��
					pTimer->RemoveReference();
				}
				else if (pEvent->m_iEventType&kKillTimerEvent)
				{
					//��ʱ����Ҫ������clearTimerHeap�ͷ�
				}
			}

			pEvent->m_pCookie = NULL;
			EventPool::putLPEvent(pEvent);
			pEvent =NULL;
		}
	}			
}

void   WorkThread::clearTimerHeap()
{
	HeapElem* pHeapElem = NULL;
	while ((pHeapElem = m_TimerHeap.ExtractMin())!=NULL)
	{
		Timer* pTimer = (Timer*) pHeapElem->GetEnclosingObject();
		pTimer->RemoveReference();
	}
}