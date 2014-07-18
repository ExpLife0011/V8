#include "stdafx.h"
#include "Common.h"
#include "Event.h"
#include "IOThread.h"
#include "AsyncCom.h"
#include "ThreadsManager.h"

#include <vector>

void IOThread::Entry()
{
	AsyncCom::initialize();

	//�������ҷ�������IO�¼�;
	std::vector<LPEvent> vEvents;
	SInt32		theRetValue		= EINTR;
	UInt32		iUniqueID		= 0;
	UInt32		iThreadIndex	= 0;

	while (!IsStopRequested())
	{
		theRetValue		= EINTR;

		theRetValue	=	AsyncCom::waitEvents(vEvents);

		if(theRetValue==EINTR) continue;
		
		iUniqueID	= 0;
		iThreadIndex= 0;

		//�����е�I/O�߳��յ����¼���ӵ������߳�
		for(UInt32 iEventCount=0; iEventCount<(UInt32)vEvents.size();iEventCount++)
		{
			iUniqueID		= vEvents[iEventCount]->m_iUniqueID;
			Assert(iUniqueID>=0);
			
			iThreadIndex	= iUniqueID%ThreadsManager::s_iWorkThreadsNum;
			ThreadsManager::s_pWorkThreads[iThreadIndex]->addCommandEvent(vEvents[iEventCount]);
		}

		vEvents.clear();
	}
	
	m_bKilled =1;

	AsyncCom::destroy();
}


//////////////////////////////////////////////////////////////////////////
//��������: ֹͣIO�߳�
//�������: ��
//����ֵ:   ��
void		IOThread::stopIOThread()
{
//			{
//				MutexLocker locker(&m_mutex);
//				m_bStopRequested = 1;
//			}

			SendStopRequest();

			if(!m_bKilled)
			{
				::PostMessage(AsyncCom::getMsgWindow(),WM_QUIT,0,0);
				DWORD theErr = ::WaitForSingleObject(m_nThreadID, INFINITE);
				Assert(theErr==WAIT_OBJECT_0);
			}
}