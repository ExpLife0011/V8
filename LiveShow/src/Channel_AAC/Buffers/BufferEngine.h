#pragma once
#include "Common.h"
#include "CommonPacket.h"
#include "RC.h"
#include <map>
#include "Mutex.h"
#include "Thread.h"
#include "BufferInputEngine.h"
#include "BufferOutputEngine.h"
// #include "BufferOutputTask.h"

using namespace std;

class CBufferEngine
{
friend class TimerInputWatch;
friend class CBufferOutputTask;
public:
	CBufferEngine();
	~CBufferEngine();
	
	void	Initialize(); //��ʼ��
	void	UnInitialize();//ж�ص���
	void    DestroyInstance();//���ٲ����߳�

	void	AddInputPacket(UInt32 iRoomId,Packet* pDataPacket,UInt32 iSequence,bool bA=false); //��ӱ���ɼ���Ƶ��Ƶ���ݰ�
	bool	GetInputPacket(UInt32 iRoomId,Packet* &pDataPacket,UInt32 iSequence,bool bA=false); //��ȡ�ɼ����ݵ�ָ�����ݰ�

	void	ClearInputPackets(UInt32 iRoomId,bool bA=false);//����ָ�������������ݰ�
	void    ClearInputPackets();//�������з�����Ƶ����Ƶ�������ݰ�
	void	SetRoomOnMic(UInt32 iRoomId,bool bEnable);//���÷���Ϊ��������״̬

	void	AddOutputPacket(UInt32 iRoomId,UInt32 iFromUin,Packet* pDataPacket,UInt32 iSequence,bool bA=false);//����յ�����Ƶ��Ƶ���ݰ�
	void	ClearOutputPackets(UInt32 iRoomId,UInt32 iFromUin,bool bA=false);//����ָ�������û���������ݰ�	
	void	PlayOutputAudio();//��������������е���Ƶ
	void	PlayOutputVideo();//��������������е���Ƶ
	
	void	ClearExpireUser();//������Ч�û�����
	void	EchoAudioInputInfo(UInt32 iRoomId);//��ӡ�ɼ��������е���ƵsequenceId��Χ
	void	EchoVideoInputInfo(UInt32 iRoomId);//��ӡ�ɼ��������е���ƵsequenceId��Χ
protected:
	void	InitInputTimer(); //initialize input data timer
	void	InitOutputTimer();//initialize output data timer 
	void	RemoveInputTimer();//remove input data timer
	void	RemoveOutputTimer();//remove output data timer
	void	UInitInputEngine();//execute all inputengine's uninitialize function
	void	UInitOutputEngine();//execute all outputengine's uninitialize function

	RCPtr<CBufferInputEngine>	GetBufferInputEngine(UInt32 iRoomId);
	RCPtr<CBufferOutputEngine>  GetBufferOutputEngine(UInt32 iRoomId);
	
 	map<UInt32,RCPtr<CBufferInputEngine>>	m_inputEngineMap; //RoomId  - InputEngine
 	typedef pair<UInt32,RCPtr<CBufferInputEngine>> input_pair;
	map<UInt32,RCPtr<CBufferOutputEngine>> m_outputEngineMap;//RoomId - OutputEngine
	typedef pair<UInt32,RCPtr<CBufferOutputEngine>> output_pair;

	static Mutex m_InputMutex;//m_inputEngineMap
	UInt32  m_iInputTimerID; //����timerID

	BaseThread* pThreadVideo;
	BaseThread* pThreadAudio;
	BOOL IsThreadStartVideo;
	BOOL IsThreadStartAudio;
	volatile BOOL IsThreadDestroy;
};

extern CBufferEngine g_bufferEngine;

//Monitor buffer size and remove expire packet
#include "TimerHandler.h"
class TimerInputWatch : public TimerHandler
{
public:
	virtual  void onPeriodExpired()
	{
		//input operations
		{
			BufferTrace("TimerInputWatch::onPeriodExpired() begin %d\n",GetTickCount());

			MutexLocker locker(&CBufferEngine::m_InputMutex);

			map<UInt32,RCPtr<CBufferInputEngine>>::iterator iter;
			for (iter=g_bufferEngine.m_inputEngineMap.begin();iter!=g_bufferEngine.m_inputEngineMap.end();iter++)
			{
				BufferTrace("TimerInputWatch::onPeriodExpired() while %d\n",GetTickCount());
				iter->second->KeepBalance();
			}
			
			BufferTrace("TimerInputWatch::onPeriodExpired() mid %d\n",GetTickCount());

			//remove expire packets
			iter=g_bufferEngine.m_inputEngineMap.begin();
			while (iter!=g_bufferEngine.m_inputEngineMap.end())
			{
				BufferTrace("TimerInputWatch::onPeriodExpired() while2 %d\n",GetTickCount());
				if (!iter->second->GetEngineUsed())
				{
					BufferTrace("TimerInputWatch::onPeriodExpired() g_bufferEngine.m_inputEngineMap erase(iter)room=%d time=%d\n",iter->first,GetTickCount());
					iter = g_bufferEngine.m_inputEngineMap.erase(iter);
				}
				else
				{
					BufferTrace("TimerInputWatch::onPeriodExpired() ++ \n");
					++iter;
				}
			}

			BufferTrace("TimerInputWatch::onPeriodExpired() while end \n");
			if(g_bufferEngine.m_inputEngineMap.size()==0)  
			{
				BufferTrace("TimerInputWatch::onPeriodExpired() g_bufferEngine.RemoveInputTimer() time=%d\n",GetTickCount());
				g_bufferEngine.RemoveInputTimer();
			}

			BufferTrace("TimerInputWatch::onPeriodExpired() .... end \n");
		}

		//Other Operations
	}
};

#define TIMER_INPUT_DATA_INTERVAL  60 //60ms���һ�λ���������� Ϊ�������ݰ����ʱ��3��
