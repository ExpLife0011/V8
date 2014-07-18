#pragma once

#include <list>
#include <atlbase.h>
#include <winsock2.h>
#include <vector>
#include <map>
#include <time.h>
#include "..\Common.h"

#pragma comment(lib, "ws2_32.lib")

namespace common
{
	namespace net
	{

class INetSpeedDetectorEvent
{
public:
	/*! \fn virtual void OnDetectReply(LPCTSTR lpszIP, DWORD dwTimeout) = 0;
	*  \brief �������ٻ�Ӧ,���η���ÿ����Ӧ�ķ������Լ���Ӧʱ��
	*  \param lpszIP [out]���صķ�������Ϣ
	*  \param dwTimeout [out]��������Ӧʱ��
	*  \param index [out]��������Ӧ˳��
	*  \return ��
	*/	
	virtual void OnDetectReply(std::wstring& strIP, DWORD dwTimeout, int index) = 0;

	virtual void OnDetectTimeout() = 0;
};

// NetSpeedDetector socket event procedure entry
LRESULT CALLBACK NSDWindowWinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Net Speed Detector
class COMMON_INTERFACE CNetSpeedDetector 
{
public:

	CNetSpeedDetector::CNetSpeedDetector();
	virtual CNetSpeedDetector::~CNetSpeedDetector();

	virtual BOOL Initialize(const INetSpeedDetectorEvent * pEventHandler);
	virtual void Detect(std::vector<std::wstring>& vecIPArray);
	virtual BOOL Finalize();

	UINT GetNextSequenceID()
	{
		return m_uSequenceID++;
	}

// socket message
public:
	void OnRead(SOCKET hSocket, int nErrorCode);
	void OnTimeout();

protected:
	
	BOOL CreateNSDWindow();
	BOOL DestoryNSDWindow();	
	BOOL CreateSocket();	
	int  CloseSocket();
	BOOL SetSocketTimeout(DWORD dwTimeout);
	BOOL SetTimeoutTimer();
	BOOL KillTimeoutTimer();
	void Cleanup();
	void OnErrorToCloseDetect();
	BOOL SendRequest(std::wstring& strIP);

private:

	struct IP2Time
	{
		std::wstring strIP;
		LARGE_INTEGER nTime;
	};

	std::vector<IP2Time>	m_mapIP2BeginTime;
	LARGE_INTEGER			m_performanceFrequency;

	int						m_index;

	HWND					m_hWnd;							// main windows handler
	SOCKET					m_hSocket;						// socket handler
	INetSpeedDetectorEvent* m_pEventHandler;				// callback event handler
	BYTE *					m_pReceiveBuffer;				// buffer for recv socket I/O data
	UINT					m_unReceiveBufferLen;			// default socket buffer length
	BOOL					m_bInitSuccess;					// initialize successed flag
	UINT					m_uSequenceID;					// pdu order ID
};

	}
}