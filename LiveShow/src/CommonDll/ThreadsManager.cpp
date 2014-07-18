#include "stdafx.h"
#include "Common.h"
#include "ThreadsManager.h"
#include "SocketIDGenerater.h"

WorkThread**		ThreadsManager::s_pWorkThreads			=	NULL;				//�����߳�ָ���б�;
UInt32				ThreadsManager::s_iWorkThreadsNum		=   0;					//�ܹ����߳���;
UInt32              ThreadsManager::s_iSocketNumPerThread   =   0;

IOThread*			ThreadsManager::s_pIOThread				=	NULL;


void	ThreadsManager::startThreads(UInt32 iWorkThreadsNum,UInt32 iSocketNumPerThread)
{
		BaseThread::Initialize();

		Assert(iWorkThreadsNum>=0);

		if(iWorkThreadsNum==0)
		{
			s_iWorkThreadsNum=1;
		}
		else
		{
			s_iWorkThreadsNum	=	iWorkThreadsNum;
		}

		s_iSocketNumPerThread   = iSocketNumPerThread;

		UInt32  iTotalEventNum	= s_iSocketNumPerThread*s_iWorkThreadsNum;

		s_pWorkThreads=(WorkThread**)::malloc(s_iWorkThreadsNum*sizeof(WorkThread*));

		for(UInt32 i=0;i<s_iWorkThreadsNum;i++)
		{
			s_pWorkThreads[i]= new WorkThread(iSocketNumPerThread);
			s_pWorkThreads[i]->SetSeqNo(i);
			s_pWorkThreads[i]->Start();
			BaseThread::Sleep(200);		//���߳�˯��200ms;�Ա������߳��л�������;
		}

		//////////////////////////////////////////////////////////////////////////
		//����IOThread��
		if(s_pIOThread==NULL)
		{
			s_pIOThread= new IOThread(iTotalEventNum);
			s_pIOThread->Start();
			BaseThread::Sleep(200);
		}

		SocketIDGenerater::initialize(iTotalEventNum);
}

//////////////////////////////////////////////////////////////////////////
//ֹͣ���й����̣߳�
void	ThreadsManager::stopThreads()
{
	Trace("ThreadsManager::stopThreads()\n");
	if(s_pIOThread!=NULL)
	{
		s_pIOThread->stopIOThread();
	}

	if(s_pWorkThreads!=NULL)
	{
		UInt32 i=0;

		for(;i<s_iWorkThreadsNum;i++)
		{
			if (s_pWorkThreads[i])
			{
				s_pWorkThreads[i]->StopAndWaitForThread();
			}
		}

		i=0;
		
		for(;i<s_iWorkThreadsNum;i++)
		{
		    SAFE_DELETE( s_pWorkThreads[i]);
		}
		::free(s_pWorkThreads);
		s_pWorkThreads=NULL;
	}
	SAFE_DELETE(s_pIOThread);
	SocketIDGenerater::destroy();
	BaseThread::Destroy();
}
