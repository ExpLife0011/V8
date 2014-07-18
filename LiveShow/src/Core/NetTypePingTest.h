#pragma  once

#include "51ktv.h"
#include <algorithm>
#include "imodulemanager.h"
#include "Net\ipport.h"
#include "net\NetSpeedDetector.h"
#include "Utility\StringHelper.h"
#include "InnerDefine.h"

class INetTypePingTestEvent
{
public:
	//�״η���(����������������)
	virtual void OnReturn1stNetType(ENM_NET_TYPE) = 0;

	//����3s��ʱ����������˳������
	virtual void OnPingTestComplete(std::vector<ENM_NET_TYPE>&) = 0;
};

class NetTypePingTest : public common::net::INetSpeedDetectorEvent
{
public:

	NetTypePingTest(INetTypePingTestEvent* pEventToken, INetTypePingTestEvent* pEventHall);
	
	//��ʼ������������ip
	void Initialize(std::map<ENM_NET_TYPE, uint32>& ips);

	bool IsPingTested()
	{
		return m_bTested;
	}

	void PingTest();

private:

	void OnDetectReply(std::wstring& strIP, DWORD dwTimeout, int index);
	void OnDetectTimeout();

	//�������Ƿ񷵻ع�
	bool IsNetTypeReturned(ENM_NET_TYPE);
	
	bool m_bTested;
	std::map<ENM_NET_TYPE, std::wstring> m_type2IP;
	INetTypePingTestEvent* m_pNetTypePingTestEvent4Token;
	INetTypePingTestEvent* m_pNetTypePingTestEvent4Hall;
	std::vector<ENM_NET_TYPE> m_testResult;
	common::net::CNetSpeedDetector m_netSpeedDetector;
};