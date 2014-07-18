#pragma once
#include "RC.h"
#include "Common.h"
#include "CommonPacket.h"
#include "BufferInPlace.h"
#include "BufferBaseRate.h"
#include "BufferOutputAudioEngine.h"
#include "BufferOutputVideoEngine.h"
#include <map>

using namespace std;

class CBufferOutputEngine:public RCObject,public ITransInPlace
{
public:
	CBufferOutputEngine(UInt32 iRoomId);
	~CBufferOutputEngine();
	
	void Initialize();
	void UnInitialize();

	void AddOutputPacket(UInt32 iFromUin,Packet* pDataPacket,UInt32 iSequence,bool bA);
	void ClearOutputPackets(UInt32 iFromUin,bool bA=false);

	void SetRoomOnMic(bool bEnable); 
	void ClearExpireUser();
	unsigned int GetBufferSize(unsigned int uin,En_Buffer_Type en);
	void SetBufferSize(unsigned int uin,En_Buffer_Type en,unsigned int bufsize);
	virtual void SetRecvTime(unsigned int uin,En_Buffer_Type en,DWORD dwtime);
	virtual DWORD GetRecvTime(unsigned int uin,En_Buffer_Type en);
protected:
	RCPtr<CBufferOutputAudioEngine> GetBufferOutputEngineA(UInt32 iFromUin);
	RCPtr<CBufferOutputVideoEngine> GetBufferOutputEngineV(UInt32 iFromUin);
private:
	Mutex m_mutexA;	//�����߳� socket�߳� m_mapOutputAudioEngine
	Mutex m_mutexV; //�����߳� socket�߳� m_mapOutputVideoEngine
 	UInt32 m_iRoomId;
	IBufferBaseRate* m_pIBaseAudioRate; //��ǰ�����������ʿ����û��߼�������
	IBufferBaseRate* m_pIBaseVideoRate; //��ǰ������Ƶ���ʿ����û��߼�������
	std::map<unsigned int,unsigned int> m_mapAudioBufferSize;//�����Ƶ��������С fromuin <--> buffersize
	std::map<unsigned int,unsigned int> m_mapVideoBufferSize;//�����Ƶ��������С fromuin <--> buffersize
	std::map<unsigned int,DWORD> m_mapAudioBufferRecvTime;//�����Ƶ�������ݿ�ʼʱ�� fromuin <--> recvtime
	std::map<unsigned int,DWORD> m_mapVideoBufferRecvTime;//�����Ƶ�������ݿ�ʼʱ�� fromuin <--> recvtime
	map<UInt32,RCPtr<CBufferOutputAudioEngine>> m_mapOutputAudioEngine;// FromUin -- OutputAudioEngine
	map<UInt32,RCPtr<CBufferOutputVideoEngine>> m_mapOutputVideoEngine;// FromUin -- OutputVideoEngine
	typedef pair<UInt32,RCPtr<CBufferOutputAudioEngine>> pair_outputA;
	typedef pair<UInt32,RCPtr<CBufferOutputVideoEngine>> pair_outputV;
};