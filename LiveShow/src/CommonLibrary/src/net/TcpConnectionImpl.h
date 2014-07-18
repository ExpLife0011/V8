/**
* TwoByteTcpConnectionImpl.h
* 
*
* @version 1.0 (06 ,04, 2008)
* @author reinhardt ken
*
*/
#pragma  once

#include "ConnectionBase.h"
#define SECURITY_WIN32
#include <security.h>

namespace netlayer
{
	class ConnectionLayerImpl;

	class TcpConnectionImpl : public ConnectionBase  
	{
	public:
		TcpConnectionImpl(ConnectionLayerImpl& oCommMgr, Packet::HEADTYPE enmRecvHeadType, SOCKET oSock = INVALID_SOCKET);
		virtual ~TcpConnectionImpl();

		virtual bool Create(const IpPort& oAddr);
		virtual bool Close();
		virtual bool SendTo(const IpPort& oAddr, Packet& oPacket);
		virtual void OnRead(SOCKET oSock);
		virtual void OnExcept(SOCKET oSock);
		virtual void OnWrite(SOCKET oSock);
		int GetSockName();

	protected:
		int RecvAll(InnerUtility::BUF& oBuf, bool bTcp = true);

		void OnTwoByteRead(SOCKET oSock);
		void OnThreeByteRead(SOCKET oSock);
		void OnFourByteRead(SOCKET oSock);

	protected:
		enum STATE {
			CLOSED,
			CONNECTING,
			CONNECTED,
			HTTPAUTH, //HTTP��֤
			HTTPNTLMAUTH1, //HTTP��֤ step1(ntlm)
			HTTPNTLMAUTH2, //HTTP��֤ step2(ntlm)
			SOCK4AUTH, //sock4��֤
			SOCK5VERSION, // sock5���Ͱ汾
			SOCK5AUTH, //��Ҫ����sock5��֤
			SOCK5AUTHSENT, //sock5��֤�������
			SOCK5AUTHOK, //sock5��֤���
			SOCK5IP,//����ip����Ϣ
			SOCK5SETCONTYPE, //sock5������������
		};


	protected:
		Packet::HEADTYPE m_enmRecvHeadType;//����tcp�İ�ͷ
		SOCKET m_oSock;
		STATE m_enState;
		InnerUtility::BUF m_oSendData; //���ͻ�����
		InnerUtility::BUF m_oRecvData; //���ܻ�����
	};

};