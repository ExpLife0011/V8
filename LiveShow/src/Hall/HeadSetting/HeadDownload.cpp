#include "stdafx.h"
#include "HeadDownload.h"
#include "webdefine.h"
#include "../hall.h"
#include "../CommonLibrary/include/utility/FileHelper.h"
#include "../CommonLibrary/include/utility/SystemHelper.h"
#include <algorithm>

CHeadDownload::CHeadDownload()
{
	strHeadImageDir.Format(_T("%sresource\\head\\"),common::utility::systemhelper::Get179AppPath().c_str());
}

CHeadDownload::~CHeadDownload()
{

}

 //��������ͷ����������
void CHeadDownload::EventSendNewHeadDown(uint32 unUIN)
{
	CString formUrl,headImageDown,unUinImage;		
	unUinImage.Format(_T("%s%d.jpg"),strHeadImageDir,unUIN);//�û�ͷ��·��

	WIN32_FIND_DATA filedata;   //���´���Ϊ��ȡimage�ļ�����޸�ʱ�䲢תΪtime_t 
	time_t writeTime = 0;
	HANDLE hFile2  = FindFirstFile(unUinImage,&filedata);

	if(hFile2 != INVALID_HANDLE_VALUE)
	{
		common::utility::filehelper::FileTimeToUinxTime(&filedata.ftLastWriteTime,&writeTime); //FILETIME ת time_t
	}
	
	FindClose(hFile2);         //���´���Ϊ��ȡimage�ļ�����޸�ʱ�䲢תΪtime_t 

	formUrl.Format(_T("%s?uin=%d&modifytime=%ld"),_T("http://interface.179.com/user/userDown"),unUIN,writeTime);  //ͷ�����ص�ַ	
	headImageDown.Format(_T("%s%d.jpg"),strHeadImageDir,unUIN);  //ͷ�����������ص�ַ

	webinterface::download_head_image_event_req getDownloadEventReq;
	getDownloadEventReq.srcMId	=	MODULE_ID_HALL;
	getDownloadEventReq.desMId	=	MODULE_ID_WEBSERVICE;
	getDownloadEventReq.unUIN = unUIN;
	getDownloadEventReq.wstrUrl = formUrl;
	getDownloadEventReq.wstrImagePath = headImageDown;

	IModuleManager* pModuleManager = g_HallModule->m_pModuleManager;
	if (pModuleManager != NULL)
	{
		uint32 nHeadSeqNo = pModuleManager->CallService(getDownloadEventReq.eventValue,(param)&getDownloadEventReq);
		m_VecHeadSeqNO.push_back(nHeadSeqNo);
	}
}

//����ͷ���������󷵻���Ӧ������������ͷ�����سɹ����Զ�������Ϣ MESSAGE_VALUE_HALL_NEW_HEAD_IMAGE
void CHeadDownload::OnEventRespNewHeadDown(Event const& e)
{	
	uint32 nSeqNo = e.param2;

	if(!FindSeqNoInMapHeadImage(nSeqNo)) //��ѯnSeqNo���к��Ƿ���ͷ���������кű���
	{
		return ;
	}	

	if( e.param0 == webinterface::WEB_RET_SUCCESS)  //����������ͷ��
	{		
		ASSERT(e.m_pstExtraInfo != NULL);
		webinterface::download_head_image_event_resp* pDownEvent =(webinterface::download_head_image_event_resp* ) (e.m_pstExtraInfo);
		MessageHeadDownResp(pDownEvent->unUIN); //��������ͷ�����������Ϣ
	}

	//m_VecHeadSeqNO.erase(nSeqNo);


}

//��ȡ����ͷ��ͼƬ·������δ�ҵ�ָ��unUIN�Ķ�Ӧͷ��ͼƬ��ʹ��Ĭ����Ůͷ��ͼƬ
CString CHeadDownload::GetLocalHeadImage(uint32 unUIN,bool bMan)
{	
	CString unUinImage;
	unUinImage.Format(_T("%s%d.jpg"),strHeadImageDir,unUIN);//�û�ͷ��·��

	WIN32_FIND_DATA filedata;  
	HANDLE hFile2  = FindFirstFile(unUinImage,&filedata);
	if(hFile2 == INVALID_HANDLE_VALUE)  //δ�ҵ��û�unUIN����Ӧ��ͷ��ͼƬ  ����Ҫʹ��Ĭ����Ůͷ��ͼƬ
	{
		if(bMan)
		{
			unUinImage.Format(_T("%smen.jpg"),strHeadImageDir);
		}
		else
		{
			unUinImage.Format(_T("%swomen.jpg"),strHeadImageDir);
		}

	}	
	FindClose(hFile2); 
	return unUinImage;

}

//��ȡ����Ĭ���ο�ͼƬ
CString CHeadDownload::GetGuestHeadImage()
{
	CString unUinImage;		
	unUinImage.Format(_T("%sdefault.png"),strHeadImageDir);	
	return unUinImage;
}

void CHeadDownload::MessageHeadDownResp(uint32 unUIN)
{
	IModuleManager * pModuleManager = g_HallModule->m_pModuleManager;	
	if (pModuleManager != NULL)
	{
		pModuleManager->PushMessage(MakeMessage<MODULE_ID_HALL>()(Hall::MESSAGE_VALUE_HALL_HEAD_IMAGE_UPDATE,(param)unUIN , 0, 0, 0));
	}
}

//��ѯnSeqNo���к��Ƿ���ͷ���������кű���
bool CHeadDownload::FindSeqNoInMapHeadImage(uint32 nSeqNo)
{
	bool seqNoOK = false;	
	vector<uint32>::iterator result = ::find(m_VecHeadSeqNO.begin(),m_VecHeadSeqNO.end(),nSeqNo); //��ͷ���������кű��в���nSeqNo
	if(result != m_VecHeadSeqNO.end()) //�ҵ�
	{
		seqNoOK = true;
	}

	return seqNoOK;

}
