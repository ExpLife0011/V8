#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__

#include	"Common.h"
#include	"CondQueue.h"
#include	"Event.h"
#include	"Thread.h"
#include	"Mutex.h"
#include	"SocketContext.h"
#include    "Heap.h"

class ThreadsManager;

class WorkThread:public BaseThread
{
public:
	//////////////////////////////////////////////////////////////////////////
	//���������������
	WorkThread(UInt32 iSocketArraySize): 
	  BaseThread(), 
	  m_EventQueue(),
	  m_iSocketsArraySize(iSocketArraySize),
	  m_iTotalSocketNum(0)
	{
		m_pSocketContexts = new SocketContext*[m_iSocketsArraySize];
		::memset(m_pSocketContexts,0,sizeof(SocketContext*)*m_iSocketsArraySize);
	}

   	virtual ~WorkThread()
	{
		clearTimerHeap();
		clearCommandEvents();

		if(m_pSocketContexts!=NULL)
		{
			for (int i = 0 ; i < m_iSocketsArraySize ; i++)
			{
				SAFE_DELETE(m_pSocketContexts[i]);
			}
			delete []m_pSocketContexts;
			m_pSocketContexts = NULL;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	//�����������̵߳�����ں���
	//����������ޣ�
	//����ֵ��  �ޣ�
	virtual void Entry();

	//////////////////////////////////////////////////////////////////////////
	//��������: ����߳����һ�������¼�;
	//�������: @����1: pEvent; ����ӵ������¼�;
	//����ֵ: 0: ��ʾ�ɹ�; <0; ��ʾʧ�ܵ�ԭ����;

	inline  void addCommandEvent(LPEvent pEvent)
	{
		return m_EventQueue.enQueue(&(pEvent->m_QueueElem));
	}

private:
	//////////////////////////////////////////////////////////////////////////
	//����������������߳��ϵ��¼���
	//���������@����1: pEvent; ָ�򱻴�����¼���ָ��;
	//����ֵ�� ��;
	void			processEvent(LPEvent pEvent);

	SInt32          processTimer();

	//////////////////////////////////////////////////////////////////////////
	//������������ȡ���߳����յ��������¼�; �ú��������ȴ�5ms;
	//���������@����1: pEvent; ���ܵ��������¼�;
	//����ֵ��1: �������¼�����; 0: ��ʾû�������¼�����;
	inline Bool		getCommandEvent(LPEvent& pEvent, SInt32 iTimeOut=1)
	{
		QueueElem* pCurElem = m_EventQueue.deQueueBlocking(iTimeOut);
		if(pCurElem!=NULL)
		{
			pEvent	=(LPEvent)(pCurElem->getEnclosingObject());
			return 1;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//��������:  ������е������¼�;
	//�������:
	//����ֵ:
	void         clearCommandEvents();

	//������еĶ�ʱ��
	void            clearTimerHeap();

	//////////////////////////////////////////////////////////////////////////
	//��Ա������
	Queue_Blocking    m_EventQueue;				//���߳��ϵ������¼�����;	  

	Heap              m_TimerHeap;              //��ʱ����

	//////////////////////////////////////////////////////////////////////////
	//SocketContext������ԣ�
	SocketContext**   m_pSocketContexts;		//���̴߳����SocketContext�б�
	UInt32            m_iTotalSocketNum;		//���߳������ڴ����SocketContext������;
	SInt32            m_iSocketsArraySize;		//Socket����Ĵ�С;

	friend class	  ThreadsManager;
};

#endif //__WORKTHREAD_H__