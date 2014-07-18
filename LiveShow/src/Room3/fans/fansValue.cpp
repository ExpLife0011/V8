
#include "stdafx.h"
#include "fansValue.h"
#include "..\include\utility\SystemHelper.h"

#define FANS_NUMBER                 _T("number")
#define FANS_NAME					_T("name")
#define FANS_VALUE					_T("value")
#define FANS_ERROR                  _T("��ȡ��˿����ʧ��")
#define FANS_DAY_EMPTY              _T("�հ��˿��ȱŶ~")
#define FANS_MONTH_EMPTY            _T("�°��˿��ȱŶ~")
#define FANS_ALL_EMPTY              _T("�������˿��ȱŶ~")
#define FANS_NOFANS                 _T("����ǰ��û�з�˿")

CFansValue::CFansValue()
{
	m_unAnchorUin = 0;
	m_htmlFans = NULL;
}

void CFansValue::Init(CMLHtmlView *htmlFans)
{
	m_htmlFans = htmlFans;
}

//��ȡ��˿����
void CFansValue::OnGetFans(uint32 unUin)
{
	m_unAnchorUin = unUin;  
	Event _event = MakeEvent<MODULE_ID_ROOM>()(core::EVENT_VALUE_CORE_GET_FANS, 
		MODULE_ID_CORE,(param)m_unAnchorUin,0,0,0);   //���ͻ�ȡ��˿����

	g_RoomModule->m_pModuleManager->PushEvent(_event);
	
}


//��ȡ��˿���ݷ�����Ӧ����
void CFansValue::OnGetFansRsp(Event const&evt,CString failText)
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	core::GetFansRspEvent* pFansEvent =(core::GetFansRspEvent* ) (evt.m_pstExtraInfo);
	if(pFansEvent->uin != m_unAnchorUin)
	{
		return;
	}	

	ASSERT(m_htmlFans != NULL);
	if(m_htmlFans == NULL)
	{
		return;
	}

	if(pFansEvent->result != 0)
	{
		//��ȡ��˿����ʧ��		
		_variant_t pResult;
		m_htmlFans->CallJScript(_T("AnchorFansToday"),FANS_ERROR,_T(""),&pResult);
		m_htmlFans->CallJScript(_T("AnchorFansMonth"),FANS_ERROR,_T(""),&pResult);
		m_htmlFans->CallJScript(_T("AnchorFansSuper"),FANS_ERROR,_T(""),&pResult);
		
		return;
	}
	

	CString strFansDay,strFansMonth,strFansAll,fansDay,fansMonth,fansAll;
	CString strFansTemp,strFansLine;
	bool bFans = false; //�Ƿ��з�˿

	for(int i=0;i<5;i++)
	{
		core::GetFansRspEvent::FansInfo &fansDay = pFansEvent->day[i];
		core::GetFansRspEvent::FansInfo &fansMonth = pFansEvent->month[i];
		core::GetFansRspEvent::FansInfo &fansAll = pFansEvent->all[i];
		if(fansDay.uin != 0)
		{
			strFansLine.Format(_T("{\"%s\":%d,\"%s\":\"%s\",\"%s\":%u},"),FANS_NUMBER,fansDay.uin,FANS_NAME,fansDay.nickname.c_str(),FANS_VALUE,fansDay.money);
			strFansDay += strFansLine;
			bFans = true;
		}
		
		if(fansMonth.uin != 0)
		{
			strFansLine.Format(_T("{\"%s\":%d,\"%s\":\"%s\",\"%s\":%u},"),FANS_NUMBER,fansMonth.uin,FANS_NAME,fansMonth.nickname.c_str(),FANS_VALUE,fansMonth.money);
			strFansMonth += strFansLine;
			bFans = true;
		}
		
		if(fansAll.uin != 0)
		{
			strFansLine.Format(_T("{\"%s\":%d,\"%s\":\"%s\",\"%s\":%u},"),FANS_NUMBER,fansAll.uin,FANS_NAME,fansAll.nickname.c_str(),FANS_VALUE,fansAll.money);
			strFansAll += strFansLine;
			bFans = true;
		}
		
	}
	
	if(!bFans)
	{
		_variant_t pResult;
		CString noFansText;
		core::CurInfo myCurInfo = GetCurInfo() ;
		if(myCurInfo.unUIN == m_unAnchorUin) //���Ѳ鿴��˿ʱ���������޷�˿
		{
			noFansText = FANS_NOFANS;
		}
		else //���˲鿴��˿ʱ���������޷�˿
		{
			noFansText = failText;
		}

		
		//�������޷�˿
		m_htmlFans->CallJScript(_T("AnchorFansToday"),noFansText,_T(""),&pResult);
		m_htmlFans->CallJScript(_T("AnchorFansMonth"),noFansText,_T(""),&pResult);
		m_htmlFans->CallJScript(_T("AnchorFansSuper"),noFansText,_T(""),&pResult);
		return;
	
	}
		
	_variant_t pResult;

	if(strFansDay.IsEmpty())
	{
		m_htmlFans->CallJScript(_T("AnchorFansToday"),FANS_DAY_EMPTY,_T(""),&pResult);
	}
	else
	{
		strFansDay = strFansDay.Left(strFansDay.GetLength()-1);
		fansDay.Format(_T("[%s];"),strFansDay);
		m_htmlFans->CallJScript(_T("AnchorFansToday"),_T(""),fansDay,&pResult);
	}

	if(strFansMonth.IsEmpty())
	{
		m_htmlFans->CallJScript(_T("AnchorFansMonth"),FANS_MONTH_EMPTY,_T(""),&pResult);
	}
	else
	{
		strFansMonth = strFansMonth.Left(strFansMonth.GetLength()-1);
		fansMonth.Format(_T("[%s];"),strFansMonth);
		m_htmlFans->CallJScript(_T("AnchorFansMonth"),_T(""),fansMonth,&pResult);
	}

	if(strFansAll.IsEmpty())
	{
		m_htmlFans->CallJScript(_T("AnchorFansSuper"),FANS_ALL_EMPTY,_T(""),&pResult);
	}
	else
	{
		strFansAll = strFansAll.Left(strFansAll.GetLength()-1);
		fansAll.Format(_T("[%s];"),strFansAll);
		m_htmlFans->CallJScript(_T("AnchorFansSuper"),_T(""),fansAll,&pResult);
	}
	
	
	
}

