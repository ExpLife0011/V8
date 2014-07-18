#include "stdafx.h"
#include "StatReport.h"
#include "Avdefine.h"
#include "WinSock2.h"
#include "..\..\CommonLibrary\include\utility\StringHelper.h"
#include "coredefine.h"
#include "..\room.h"

#define ROOM_STATREPORT_BUFFER_SIZE   10240
#define ROOM_NETSTATE_MIN_TOTALPACKET  10000  //����Ƶ�����հ�����ܰ�����

#define WM_ROOM_STATREPORT_STEP1  1   //��ȡ����IP��ַ���� ��һ�� ��ҳ��http://www.ip138.com
#define WM_ROOM_STATREPORT_STEP2  2    //��ȡ����IP��ַ���� �ڶ��� ���ϲ�ҳ���з����õ��Ļ�ȡIP��url

CString CStatReport::m_ipCity = _T("");

CStatReport::CStatReport()
{
	m_AsyOpenURL = NULL;
	m_hRcvWnd = NULL;
	m_Buffer = NULL;
}

CStatReport::~CStatReport()
{
	ClearAsyOpenURL();
	ClearBuffer();
}

void CStatReport::IPStatReportRequest(HWND hRcvWnd,UINT umMessage)
{
	m_hRcvWnd = hRcvWnd;
	m_umMessage = umMessage;

	CString IpUrl = _T("http://www.ip138.com");
	OpenIPUrl(m_hRcvWnd,m_umMessage,WM_ROOM_STATREPORT_STEP1,IpUrl);


}

//��ȡ����IP��ַ����ķ��غ���
void CStatReport::IPStatReportResp(UINT unParam)
{
	if(m_Buffer== NULL)
	{
		return ;
	}


	if(unParam == WM_ROOM_STATREPORT_STEP1) 
	{
		IPStatReportRespStep1();
	}
	else //WM_ROOM_STATREPORT_STEP2
	{
		IPStatReportRespStep2();
	}
		
}

void CStatReport::IPStatReportRespStep1()
{
	CString ipUrl = AnalysisIPUrl();
	if(!ipUrl.IsEmpty())
	{
		OpenIPUrl(m_hRcvWnd,m_umMessage,WM_ROOM_STATREPORT_STEP2,ipUrl);
		return ;
	}
}

void CStatReport::IPStatReportRespStep2()
{
	CString ipCity;
	CStringA ipBuffer;
	ipBuffer.Format("%s",m_Buffer);

	CString cIpBuffer(ipBuffer);
	cIpBuffer.MakeLower(); //תСд

	//������ȡIP��ַ
	CString sfind = _T("<center>");
	int ibegin = cIpBuffer.Find(sfind);
	if(ibegin != -1)
	{
		ibegin = ibegin+sfind.GetLength();
		int iend = cIpBuffer.Find(_T("</center>"),ibegin);
		if(iend != -1)
		{
			CString sbody = cIpBuffer.Mid(ibegin,iend-ibegin);
			int iCity = sbody.Find(_T("���ԣ�"));
			if(iCity != -1)
			{
				ipCity = sbody.Mid(iCity+3);
			}

		}
	}

	ClearAsyOpenURL();
	ClearBuffer();

	m_ipCity = ipCity;		
}


//������ȡIP��url
CString CStatReport::AnalysisIPUrl()
{
	if(m_Buffer== NULL)
	{
		return _T("");
	}

	CString ipUrl;
	CStringA ipBuffer;
	ipBuffer.Format("%s",m_Buffer);

	CString cIpBuffer(ipBuffer);
	cIpBuffer.MakeLower(); //תСд

	//������ȡIP��ַ
	int ifind = cIpBuffer.Find(_T("<iframe"));
	if(ifind != -1)
	{
		int ibegin = cIpBuffer.Find(_T("\""),ifind);
		if(ibegin != -1)
		{
			int iend = cIpBuffer.Find(_T("\""),ibegin+1);
			if(iend != -1)
			{					
				ipUrl = cIpBuffer.Mid(ibegin+1,iend-ibegin-1);				

			}
		}			
	}

	return ipUrl;
}

void CStatReport::OnGetNetState(uint32&iRelayIP, struct Service_Av_Net_Status_All& sansa)
{
	if(iRelayIP == 0 || GetIpCity().IsEmpty())
	{
		return;
	}

// 	if(sansa.iVideoOutTotalPacket < ROOM_NETSTATE_MIN_TOTALPACKET && sansa.iAudioOutTotalPacket < ROOM_NETSTATE_MIN_TOTALPACKET
// 		&& sansa.iVideoInTotalPacket < ROOM_NETSTATE_MIN_TOTALPACKET && sansa.iAudioInTotalPacket < ROOM_NETSTATE_MIN_TOTALPACKET)
// 	{
// 		return;
// 	}

	std::string strRelayIp = "";
	struct sockaddr_in addr;
	addr.sin_addr.s_addr = iRelayIP;
	strRelayIp = inet_ntoa(addr.sin_addr);

	std::wstring wRelayIp = common::utility::stringhelper::AsciiToUnicode(strRelayIp);

	core::ReportCollectInfoEvent *collectInfoEvent = new core::ReportCollectInfoEvent();	
	core::ReportCollectInfoEvent::Key2Value upDown;

	CString upPackVideo,upPackAudio,downPcakVideo,downPcakAudio;
	int irate =0;

	// ��ʽ��   �㶫����:Video:60.130.43.1:950
	if(sansa.iVideoOutTotalPacket >= ROOM_NETSTATE_MIN_TOTALPACKET) //������Ƶ���ݰ��ܸ���
	{
		irate = sansa.fVideoOutLostRate*100*100;
		upPackVideo.Format(_T("%s:Video:%s:%d"),m_ipCity,wRelayIp.c_str(),irate);  //������Ƶ����

		upDown.key = COLLECT_INFO_DOWN;
		upDown.value = upPackVideo;
		collectInfoEvent->vecCollecInfo.push_back(upDown);
	}
	if(sansa.iAudioOutTotalPacket >= ROOM_NETSTATE_MIN_TOTALPACKET) //������Ƶ���ݰ��ܸ���
	{
		irate = sansa.fAudioOutLostRate*100*100;
		upPackAudio.Format(_T("%s:Audio:%s:%d"),m_ipCity,wRelayIp.c_str(),irate);  //������Ƶ����
		upDown.key = COLLECT_INFO_DOWN;
		upDown.value = upPackAudio;
		collectInfoEvent->vecCollecInfo.push_back(upDown);
	}
	if(sansa.iVideoInTotalPacket >= ROOM_NETSTATE_MIN_TOTALPACKET) //�ϴ���Ƶ���ݰ��ܸ���
	{
		irate = sansa.fVideoInLostRate*100*100;
		downPcakVideo.Format(_T("%s:Video:%s:%d"),m_ipCity,wRelayIp.c_str(),irate);  //�ϴ���Ƶ����
		upDown.key = COLLECT_INFO_UPLOST; 
		upDown.value = downPcakVideo;
		collectInfoEvent->vecCollecInfo.push_back(upDown);
	}
	if(sansa.iAudioInTotalPacket >= ROOM_NETSTATE_MIN_TOTALPACKET) //�ϴ�����Ƶ���ݰ��ܸ���
	{
		irate = sansa.fAudioInLostRate*100*100;
		downPcakAudio.Format(_T("%s:Audio:%s:%d"),m_ipCity,wRelayIp.c_str(),irate);  //�ϴ���Ƶ����
		upDown.key = COLLECT_INFO_UPLOST;
		upDown.value = downPcakAudio;
		collectInfoEvent->vecCollecInfo.push_back(upDown);
	}

	if(collectInfoEvent->vecCollecInfo.size() > 0)
	{
		Event _event = MakeEvent<MODULE_ID_ROOM>()(core::EVENT_VALUE_CORE_REPORT_COLLECT_INFO, 
			MODULE_ID_CORE,0,0,0,collectInfoEvent);
		g_RoomModule->m_pModuleManager->PushEvent(_event);
	}
	else
	{
		delete collectInfoEvent;
	}
}

void CStatReport::OpenIPUrl(HWND hRcvWnd,UINT umMessage,UINT unParam,CString strUrl)
{
	ClearAsyOpenURL();

	if(m_Buffer == NULL)
	{
		m_Buffer = new BYTE[ROOM_STATREPORT_BUFFER_SIZE];
	}

	if(m_Buffer != NULL)
	{
		memset(m_Buffer,0,ROOM_STATREPORT_BUFFER_SIZE);
		//ʹ��sizeof(m_Buffer)-1 ����Ϊ���m_Buffer��С����ʱ�����һλ�ɴ��'\0',����(����ʹ��sizeof(m_Buffer))�������'\0'ʱ�����±곬��
		m_AsyOpenURL = new common::utility::CAsynOpenURL(hRcvWnd,umMessage,unParam,m_Buffer,ROOM_STATREPORT_BUFFER_SIZE-1);

		m_AsyOpenURL->OpenURL(strUrl);
		
	}
}

CString CStatReport::GetIpCity()
{
	return m_ipCity;
}



void CStatReport::ClearAsyOpenURL()
{
	if(m_AsyOpenURL != NULL)
	{
		delete m_AsyOpenURL;
		m_AsyOpenURL = NULL;
	}
}

void CStatReport::ClearBuffer()
{
	if(m_Buffer != NULL)
	{
		delete m_Buffer;
		m_Buffer = NULL;
	}
}