#include "stdafx.h"
#include "NetInterface.h"
#include "ThreadsManager.h"
#include "SocketIDGenerater.h"
#include "EventPool.h"

using namespace std;

vector<string>    NetInterface::s_vLocalIPAddresses;

SInt32	NetInterface::initialize()
{
		WSADATA wsaData;
		::WSAStartup(MAKEWORD(2, 2), &wsaData);

		UInt32  iNumIPAddrs			= 0;
		UInt32	iCurrentIndex		= 0;
		string  strIPAddress		= "";
		struct  sockaddr_in* pAddr  = NULL; 
		SInt32	iTempSocket			= ::socket(AF_INET, SOCK_DGRAM, 0);
		if (iTempSocket == -1)
		{
			Assert(0);
			return EOPENFAILED;
		}

		static const UInt32 kMaxAddrBufferSize = 2048;
		char				pInBuffer[kMaxAddrBufferSize];
		char				pOutBuffer[kMaxAddrBufferSize];
		UInt32				iReturnedSize	=	0;

		//
		// Use the WSAIoctl function call to get a list of IP addresses
		SInt32 theErr = ::WSAIoctl(	iTempSocket, 
									SIO_GET_INTERFACE_LIST, 
									pInBuffer, 
									kMaxAddrBufferSize,
									pOutBuffer,
									kMaxAddrBufferSize,
									(LPDWORD)&iReturnedSize,
									NULL,
									NULL);
		if (theErr != 0)
		{
			Assert(0);
			::closesocket(iTempSocket);
			return EIOFAILED;
		}

		LPINTERFACE_INFO pAddrList = (LPINTERFACE_INFO)&pOutBuffer[0];
		iNumIPAddrs = iReturnedSize / sizeof(INTERFACE_INFO);

		for (;iCurrentIndex < iNumIPAddrs; iCurrentIndex++)
		{
			strIPAddress= "";
			pAddr = (struct sockaddr_in*)&pAddrList[iCurrentIndex].iiAddress;
			strIPAddress  += ::inet_ntoa(pAddr->sin_addr);

			//store the IP addr
			if(strIPAddress!="127.0.0.1")
			{
				s_vLocalIPAddresses.push_back(strIPAddress);
			}		
		}
		::closesocket(iTempSocket);
		return ENOERR;
}

void	NetInterface::destroy()
{
	    s_vLocalIPAddresses.clear();

		//���EventPool
		EventPool::destroy();

		::WSACleanup();
}

SInt32	NetInterface::registerSocketHandler(UInt32				iLocalIp,							//Socket�ı���IP��ַ;�����ֽ���;
											UInt16				sLocalPort, 						//Socket�ı����˿ںţ������ֽ�����;
											SocketHandler*		pHandler,							//Socket�ϵĴ�����;
											SInt32*             pISocketID,                         //����ϵͳ�����SocketID
											UInt32				iMaxPacketLen,						//Socket���������������ݰ��Ĵ�С;
											UInt32              iReceiveBufferSize,					//Socket�Ľ��ջ����С;
											UInt32              iWriteBufferSize					//Socket�ķ��ͻ����С;
											)
{
	int re;
		if(pHandler==NULL)
		{
			return EPARAMATERS;
		}
		//����һ��Socket������;
		SInt32 iFd = (SInt32)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (iFd < 0)
		{
			return EOPENFAILED;
		}

		setNBlock(iFd);

		struct sockaddr_in servaddr;
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = sLocalPort;
		servaddr.sin_addr.s_addr = iLocalIp;
		if (bind(iFd, (struct sockaddr *)(&servaddr), sizeof(struct sockaddr)) == -1)
		{
			re= WSAGetLastError();
			closesocket(iFd);
			return EBINDFAILED;
		}
		
		//����ϵͳ�����Socket ID
		if (pISocketID!=NULL)
		{
			*pISocketID = iFd;
		}

		//���ý��ջ������ͷ��ͻ������Ĵ�С;
		setRecvBufferSize(iFd, iReceiveBufferSize);
		setWriteBufferSize(iFd,iWriteBufferSize);
		
		//���µ�SocketContext����һ��ID; ���Ҹ��ݷ����ID��SocketContext���뵽ָ�����߳�;
		SInt32	iUniqueID		= SocketIDGenerater::getNewID();
		pHandler->setSocketID(iUniqueID);
		SocketContext* pNewSocketContext	= new SocketContext(iFd,
																iUniqueID,
																iMaxPacketLen,
																pHandler,
																iReceiveBufferSize,
																iWriteBufferSize);

		sendCommadEvent(iUniqueID, kAddSocketEvent, (void*)pNewSocketContext);
		
		return iUniqueID;
}

//////////////////////////////////////////////////////////////////////////
//
void NetInterface::unregisterSocket(SInt32 iTargetID)
{
	if (iTargetID < 0 )
	{
		Assert(0);
		return;
	}

	sendCommadEvent(iTargetID, kKillSocketEvent);
}

//////////////////////////////////////////////////////////////////////////
//
/** ����ָ����UDP���ݰ�,������ͳɹ�����TRUE, ���򷵻�FALSE.*/
//����:iFD:����UDP����(Socket)��FD��iRemoteIP:Զ�˵�IP��ַ�������ֽ���sRemotePort:Զ�˵Ķ˿ںţ������ֽ���packet:������;
//���:
void	NetInterface::sendUDPPacket(SInt32 iTargetID, UInt32 iRemoteIP, UInt16 sRemotePort, Packet* pPacket)
{
	if(pPacket==NULL)
	{
		Assert(0);
		return;
	}

	//Trace("NetInterface: sendUDPPacket [%s : %d] \n", NetInterface::IPUInt32ToString(iRemoteIP).c_str(), ntohs(sRemotePort));
	pPacket->setRemoteAddr(iRemoteIP,sRemotePort);
	sendCommadEvent(iTargetID, kSocketSendPacketEvent, (void*)pPacket);
}

/************************************************************************/
/* ���ߺ���                                                             */
/************************************************************************/
/**��IP��ַ�ַ���ת��Ϊ32λ�������ֽ����ַ*/
UInt32 NetInterface::IPStringToUInt32(const std::string& strIp)
{
		return inet_addr(strIp.c_str());
}

/**��IP��ַ��32λ�������ֽ����ַת��Ϊ�ַ���*/
std::string NetInterface::IPUInt32ToString(UInt32 iIp)
{
	string strResult = "";
	struct sockaddr_in addr;
	addr.sin_addr.s_addr = iIp;
	strResult = inet_ntoa(addr.sin_addr);
	return strResult;
}

void NetInterface::getLocalIPAddresses(std::vector<std::string>& vIPAddress)
{
	 vIPAddress = s_vLocalIPAddresses;
}

/************************************************************************/
/* �ײ���ú���                                                         */
/************************************************************************/	
/**����: ����һ��socketΪ�������� */
//����: iSockFd; ������Ϊ��������Socket ������;
//���: �ޣ�
void	NetInterface::setNBlock(SInt32 iSockFd)
{
	u_long one = 1;
	int err = ::ioctlsocket(iSockFd, FIONBIO, &one);
}

//**����: ����һ��Socket�Ľ��ܻ�������С;
//����: iSockFd, �����õ�������; UInt32 iRecvBuffSize, Buffer�Ĵ�С;
void	NetInterface::setRecvBufferSize(SInt32 iSockFd,UInt32 iRecvBuffSize)
{
	int bufSize = iRecvBuffSize;
	int err = ::setsockopt(iSockFd, SOL_SOCKET, SO_RCVBUF, (char*)&bufSize, sizeof(int));
}

//**����: ����һ��Socket�ķ��ͻ�������С��
//����: iSockFd, �����õ�������; UInt32 iRecvBuffSize, Buffer�Ĵ�С;
void	NetInterface::setWriteBufferSize(SInt32 iSockFd,UInt32 iWriteBuffSize)
{
	int bufSize = iWriteBuffSize;
	int err = ::setsockopt(iSockFd, SOL_SOCKET, SO_SNDBUF, (char*)&bufSize, sizeof(int));
}

//**����: ����һ��Socket��Keep Alive����;
//����: iSockFd; �����õ�Socket ������;
//���: �ޣ�
void	NetInterface::setKeepAlive(SInt32 iSockFd)
{
	int one = 1;
	int err = ::setsockopt(iSockFd, SOL_SOCKET, SO_KEEPALIVE, (char*)&one, sizeof(int));
}

//**����: ����һ��Socket��NoDelay����;
//����: iSockFd; �����õ�Socket ������;
//���: �ޣ�
void	NetInterface::setNoDelay(SInt32 iSockFd)
{
	int one = 1;
	int err = ::setsockopt(iSockFd, IPPROTO_TCP, TCP_NODELAY, (char*)&one, sizeof(int));
	Assert(err == 0);
}

void  NetInterface::sendCommadEvent(SInt32 iTargetID, UInt32 iEventType, void* pData)
{
	LPEvent pEvent			= EventPool::getLPEvent();
	pEvent->m_iUniqueID		= iTargetID;
	pEvent->m_iEventType	= iEventType;
	pEvent->m_pCookie		= pData;

	UInt32  iThreadIndex    = iTargetID% ThreadsManager::s_iWorkThreadsNum;
	ThreadsManager::s_pWorkThreads[iThreadIndex]->addCommandEvent(pEvent);
}
