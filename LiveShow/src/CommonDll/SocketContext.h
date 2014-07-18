#ifndef  __SOCKETCONTEXT_H__
#define  __SOCKETCONTEXT_H__

#include "Common.h"
#include "Mutex.h"
#include "CommonPacket.h"
#include "SocketHandler.h"
#include "Event.h"

#include <string>
#include <deque>
#include <vector>

//////////////////////////////////////////////////////////////////////////
//Socket��״̬;
enum
{
	SOCKET_INITIALIZE				= 0,
	SOCKET_LISTEN					= 1,
	SOCKET_CLOSED					= 2
};

typedef UInt32 SOCKET_STATE;

class SocketContext
{
public:
	SocketContext(SInt32 iFd,
				  SInt32 iUniqueID,
				  UInt32  iMaxPacketLen,
				  SocketHandler* pHandler,
				  UInt32 iReadBufferSize,
				  UInt32 iWriteBufferSize);

	~SocketContext();

	inline  void  setState(UInt32 iState)
	{
		m_iState = iState;
	}

	//�������Socket�¼�
	void					processEvent(LPEvent pEvent);

private:

	//�������Socket�������¼�;
	void					handleAdd();

	//����ر�Socket�������¼�;
    void					handleKill();


	//���ո�Socket�ϵ�������ݰ����ҽ�����Ӧ�Ĵ���;
	void					handleInput();


	//�رո�Socket;
	void					handleClosed();

	//��Socket�Ϸ���UDP��Ϣ;
	SInt32					sendUDPPacket(Packet* packet);
	
	
	//�¼��������֮��Ĳ���;
	void					postProcessEvent();

	//����������˵��¼�;
	inline   void  clearEvent(UInt32 iEventMask)
	{
		m_iRequestedEvent &= ~iEventMask;
	}


	SInt32					m_iFd;								//Socket��FD��
	SOCKET_STATE			m_iState;							//Socket��״̬;

	UInt32					m_iMaxPacketLen;					//��Socket�ϵ����Packet����,//��λ:�ֽ�

	UInt8*					m_pReceiveBuffer;					//���յ���TCP��

	SocketHandler*			m_pSocketHandler;					//��Socket�ϵ��¼�������;

	UInt32                  m_iRequestedEvent;					//�����������Socket�¼�;

	SInt32					m_iUniqueID;                        //Socket��UniqueIDֵ;

	Packet					m_curRecvedPacket;					//��ǰ�����յ������ݰ�;

	Bool					m_bKillExected;						//ָʾKill�����Ƿ��Ѿ���ִ�й���;

};

#endif //__SOCKETCONTEXT_H__