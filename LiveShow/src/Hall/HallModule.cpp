#include "StdAfx.h"
#include "HallModule.h"
#include "HallWindow/HallDlg.h"
#include "LoginWindow/LoginDlg.h"
#include "HallDefine.h"
#include "Hall.h"
#include "SysSettingIni.h"
#include "..\CommonLibrary\include\utility\SystemHelper.h"
#include "../CommonLibrary/include/utility/StringHelper.h"
#include "..\CommonLibrary\include\ui\MenuEx.h"
#include "..\CommonLibrary\include\ui\UIHelper.h"
#include "coredefine.h"
#include "webdefine.h"
#include "LoginWindow/VerifyDlg.h"
#include "LoginWindow/LoginVerifyHander.h"
#include "SysNotify/SysNotifyDlg.h"
#include "RoomDefine.h"
#include "..\CommonLibrary\include\ui\C179MsgBox.h"
#include "LoginWindow/RegisterDlg.h"
#include "HallWindow/SearchDlg.h"
#include "UserInfo.h"
#include "../CommonLibrary/include/utility/ConfigManager.h"
#include "GlobalManager.h"

#define COMMAND_TOKEN_51AUTOLOGIN L"caihong" //51�ʺ��¼179�ͻ���
#define COMMAND_TOKEN_51_ENTER_ROOM L"room" //51�ʺ��¼179�ͻ��˽�������
#define COMMAND_TOKEN_PREFIX L"x179://" //��������
#define COMMAND_TOKEN_ENTER_ROOM L"go" //��������

HallModule::HallModule(void)
:m_pModuleManager(NULL)
{
	m_pHallDlg = NULL;
	m_pLoginDlg=NULL;	
	m_pHeadSettingDlg = NULL;
	m_trayMgrCur = 0;
	m_bCommandLineProcessed = false;
}

HallModule::~HallModule(void)
{
	//�����˳�ʱɾ������
	if (NULL != m_trayMgr.GetWindowHandle())
	{
		m_trayMgr.DeleteEventHandler(this);
		m_trayMgr.Delete(true);	
	}	
}


core::CurInfo GetCurInfo()
{
	core::CurInfo user_info;
	IModuleManager * pModuleManager = g_HallModule->m_pModuleManager;
	if (pModuleManager != NULL)
	{
		pModuleManager->CallService(core::SERVICE_VALUE_CORE_GET_CUR_INFO, (param)&user_info);
	}

	return user_info;
}


void HallModule::Load(IModuleManager* p)
{
	m_pModuleManager = p;
	DeferPicPathMgr->LoadDeferPicPathList() ;
}

void HallModule::Unload()
{
	DeferPicPathMgr->Release() ;

	CloseNonModalDlg((CDialog*&)m_pLoginDlg);
	CloseNonModalDlg((CDialog*&)m_pHallDlg);
	CloseNonModalDlg((CDialog*&)m_pHeadSettingDlg);

	for(std::map<CString, common::ui::CImageImpl*>::iterator it = m_mapPath2Image.begin();
		it != m_mapPath2Image.end(); ++it)
	{
		it->second->Destroy();
	}
	m_mapPath2Image.clear();
}

void HallModule::ProcessEvent(Event const& evt)
{
	switch(evt.eventValue)
	{
	case Hall::EVENT_VALUE_HALL_ENTER_ROOM_REQUEST:  //�������
		{							
			enterRoomInfo roomid;
			roomid.m_RoomID = evt.param0;				
			m_pHallDlg->m_EnterRoomRequest.EnterRoomEventRequest(roomid);
		}
		break;
	case core::EVENT_VALUE_CORE_ENTER_ROOM_RSP: //�������������Ϣ
		{				
			m_pHallDlg->m_EnterRoomRequest.OnEnterRoomEventRep(evt);
		}
		break;
	case core::EVENT_VALUE_CORE_GET_ROOMINFO_RSP: //�����ȡ������Ϣ������Ϣ
		{
			m_pHallDlg->m_EnterRoomRequest.OnGetRoomInfoEventRep(evt);
		}
		break;
	case Hall::EVENT_VALUE_HALL_CREATEANDSHOW:  //��������ʾ����
		{
			ProcessHallCreateAndShow(evt);
		}
		break;
	case Hall::EVENT_VALUE_HALL_HEAD_UPLOAD:  //ͷ���ϴ�
		{
			PrcoessHallHeadUpload(evt);
		}
		break;
	case Hall::EVENT_VALUE_HALL_ACTIVATE_SHOW: //����������ʾ
		{
			PrcoessHallActivateShow(evt);
		}
		break;
	case Hall::EVENT_VALUE_HALL_InLineURL_SHOW: //�����Ҳ����Ƕ����  (�����Ҳ���Ƕҳ��)
		{
			PrcoessInLineURLShow(evt);
		}
		break;
	case core::EVENT_VALUE_CORE_BE_KICKED_NOTIFY:  //�˺��ص�½�����û���������
		{
			ProcessKicked(evt);
		}
		break;
	case core::EVENT_VALUE_CORE_LOGIN_RSP:  //��¼������Ӧ
		{
			ProcessLoginResp(evt);			
		}
		break;			
	case core::EVENT_VALUE_CORE_NOTIFY_SYSTEM_MESSAGE:   //����֪ͨ
		{
			m_SysMessagePopup.OnSystemMessageEvent(evt);  //ϵͳ������Ӧ����	
		}
		break;
	case webinterface::event_value_web_get_login_identify_code_resp:  //��ȡ��½��֤����Ӧ
		{
			ProcessWebGetLoginIdentifyResp(evt);
		}
		break;
	case webinterface::event_value_web_download_file_resp:  //web�������ʱ�ķ�����Ӧ
		{
			ProcessWebDownFileResp(evt);
		}
		break;
	case webinterface::event_value_web_download_head_image_resp:  //web����ͷ�����ʱ�ķ�����Ӧ
		{
			ProcessWebHeadImageResp(evt);
		}
		break;
	case webinterface::event_value_web_get_http_resp:     //ͨ�õ�Web���ʽӿڷ�����Ӧ
		{
			ProcessWebGetHttpResp(evt);
		}
		break;	
	case webinterface::event_value_web_upload_head_image_resp: //�ϴ��û�ͷ����Ӧ
		{
			ProcessWebHeadUpLoadResp(evt);
		}
		break;		
	case core::EVENT_VALUE_CORE_NOTIFY_PASSWORD_SAFE:
		{
			ProcessPassWordSafe( evt ) ;
		}
		break;
	case core::EVENT_VALUE_CORE_NOTIFY_MY_INFO_UPDATE:  //�ҵ���Ϣ���(�ǳƣ��Ա�)
		{
			PrcoessMyInfoUpdate(evt);
		}
		break;	
	case core::EVENT_VALUE_CORE_DISCONNECTED_NOTIFY:  //������
		{
			ProcessDisconnected(evt);
		}
		break;
	case Room::EVENT_VALUE_ROOM_SHOW_REGISTER:
		{
			ProcessRegisterResp(evt);
		}
		break;
	case core::EVENT_VALUE_CORE_NOTIFY_RICH_UPDATE_MONEY_CHANGE:  //�����ȼ���������Ҫ��Ǯ����
		{
			ProcessRichUpdateMoneyResp(evt);
		}
		break;
	default:
		break;
	}
}

void HallModule::PrcoessHallActivateShow(Event const &evt)
{
	if( m_pHallDlg != NULL)
	{
		if(m_pHallDlg->IsIconic()) //�����Ƿ���С��
		{
			m_pHallDlg->ShowWindow(SW_RESTORE);
		}
		m_pHallDlg->SetForegroundWindow();
	}
	
}

void HallModule::PrcoessInLineURLShow(Event const &evt)
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	Hall::InLineUrl *pInfo = (Hall::InLineUrl*)(evt.m_pstExtraInfo) ;
	
	m_pHallDlg->SetAllRoomBrowser(pInfo->m_InLineUrl);  //���ò��򿪴����Ҳ���Ƕָ��ҳ��
	PrcoessHallActivateShow(evt);  //����������ʾ

}


void HallModule::ProcessMessage(Message const& msg)
{
	switch(msg.messageValue)
	{
	case core::MESSAGE_VALUE_CORE_LOGIN_COMPLETE:
		{
			
		}
		break;
	case core::MESSAGE_VALUE_CORE_PRE_LOGIN: //�л��û�
		{
			m_pHallDlg->CloseAllDialog();
			m_pHallDlg->HeadInit();//ͷ����Ϣ��ʼ��
			CloseNonModalDlg((CDialog*&)m_pHeadSettingDlg);
			m_SysMessagePopup.ClearSysMessage();
		}
		break;
	case Hall::MESSAGE_VALUE_HALL_HEAD_IMAGE_UPDATE:  //������ͷ���������
		{			
			m_pHallDlg->OnHeadImageUpdate(msg.param0);

		}
		break;
	case core::MESSAGE_VALUE_CORE_MY_VIPLEVEL_UPDATE:  //vip�ȼ����
		{
			MessageMyVipLevelUpdate(msg);
		}
		break;
	case core::MESSAGE_VALUE_CORE_MY_RICHLEVEL_UPDATE:  //�����ȼ����
		{
			MessageMyRichLevelUpdate(msg);
		}
		break;
	
	default:
		break;
	}
	
}

int32 HallModule::Invoke(ServiceValue const serviceValue, param st)
{
	switch(serviceValue)
	{	
	case Hall::SERVICE_VALUE_HALL_GET_WEBINTERFACEURL:
		return InvokeGetServiceWebInterfaceUrl(st);
		break;
	case Hall::SERVICE_VALUE_HALL_GET_TOKEN_URL:
		return InvokeGetTokenURL(st);
		break;
	case Hall::SERVICE_VALUE_HALL_OPEN_TOKEN_URL:
		return InvokeOpenTokenURL(st);
		break;
	case Hall::SERVICE_MSGBOX_SHOW:
		return InvokeMsgBoxShow(st);
		break;	
	case Hall::SERVICE_VALUE_HALL_GET_HEAD_IMAGE_PATH:
		return InvokeGetHeadImagePath(st); //SERVICE ��ȡָ���û�unUIN��ͷ��·��
		break;
	case Hall::SERVICE_VALUE_HALL_UPDATE_HEAD_IMAGE_PATH:
		return InvokeUpDateHeadImagePath(st); //SERVICE ��ȡָ���û�unUIN��ͷ��·������������ͷ��
		break;
	default:
		break;
	}

	return -1;
}

void HallModule::OnTrayEvent(WPARAM w, LPARAM l)
{
	uint32 uMsgId = l;

	switch(uMsgId){
		case WM_RBUTTONUP:
			{
				CreateHallTrayMenu();
			}
			break;
		case WM_LBUTTONDBLCLK:  //˫������ͼ��
			{
				//���´���������޸� plushu 2012-8-3

				if (m_pHallDlg != NULL && m_pLoginDlg != NULL)
				{
					bool bLoginDlgShow = m_pLoginDlg->IsWindowVisible();

					if(m_pHallDlg->IsIconic()) //�����Ƿ���С��
					{
						m_pHallDlg->ShowWindow(SW_RESTORE);
					}
					m_pHallDlg->SetForegroundWindow();

					if(bLoginDlgShow)
					{
						if(m_pLoginDlg->IsIconic()) //�����Ƿ���С��
						{
							m_pLoginDlg->ShowWindow(SW_RESTORE);
						}
						m_pLoginDlg->SetForegroundWindow();
					}
					else
					{
						m_pLoginDlg->ShowWindow(SW_HIDE);
					}
				}
			}

			break;
		default:
			break;
	}
}

void HallModule::OnFlashStart(DWORD dwParam)
{

}

void HallModule::OnFlashEnd(DWORD dwParam)
{

}

void HallModule::ShowLoginDialog(bool bShow)
{
	if(m_pHallDlg != NULL)
	{
		m_pHallDlg->EnableWindow(bShow ? FALSE:TRUE);
	}

	if(m_pLoginDlg != NULL)
	{
		m_pLoginDlg->ShowWindow(bShow ? SW_SHOW:SW_HIDE);
		if(bShow && m_pLoginDlg->IsIconic()) //�����Ƿ���С��
		{			
			m_pLoginDlg->ShowWindow(SW_RESTORE);
			m_pLoginDlg->CenterWindow(m_pHallDlg);
		}
		
	}			
}


CWnd* HallModule::GetLoginDlgWnd()
{
	return m_pLoginDlg;
}

void HallModule::CloseHallRegisterDlg()
{
	if(m_pHallDlg != NULL)
	{
		m_pHallDlg->CloseRegisterDlg();		
	}
}

void HallModule::CloseHallGameDlg()
{
	if(m_pHallDlg != NULL)
	{
		m_pHallDlg->CloseHallGameDlg();		
	}
}

//���ش�������¼���˳���������ͼ��
void HallModule::HideLoginHallDialog()
{
	if(m_pHallDlg != NULL)
	{
		m_pHallDlg->ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);  //����ϵͳ״̬������ʾ����ʱ�ı���
		m_pHallDlg->ShowWindow(SW_HIDE);		
	}

	if(m_pLoginDlg != NULL)
	{
		m_pLoginDlg->ShowWindow(SW_HIDE);
	}		

	if (NULL != m_trayMgr.GetWindowHandle())
	{
		m_trayMgr.DeleteEventHandler(this);
		m_trayMgr.Delete(true);	
	}

	
	
}

void HallModule::ShowLoginHallDialog()
{
	if(m_pHallDlg != NULL)
	{
		m_pHallDlg->ShowWindow(SW_SHOW);
		m_pHallDlg->EventUpdateTicker();
		m_pHallDlg->InitAllRoomBrowser();
	}

	ShowLoginDialog(TRUE);

}

 //��ȡ����ͷ��ͼƬ·������δ�ҵ�ָ��unUIN�Ķ�Ӧͷ��ͼƬ��ʹ��Ĭ����ŮͼƬ�� ��unUINΪ0ʱ��ʹ��Ĭ���ο�ͼƬ
CString HallModule::GetLoaclHeadImage(uint32 unUIN,bool bMan)
{
	CString headPath;
	if(unUIN > 0 )
	{
		headPath =  m_headDownload.GetLocalHeadImage(unUIN,bMan);
	}
	else
	{
		headPath =  m_headDownload.GetGuestHeadImage();
	}
	return headPath;
}

int32 HallModule::InvokeGetServiceWebInterfaceUrl(param st)
{
	Hall::WebInterfaceUrl *pWebUrl = (Hall::WebInterfaceUrl *)st;
	if(pWebUrl != NULL)
	{
		CString sUrl,sTemp;
		CSysSettingIni::GetWebInterfaceUrl(pWebUrl->m_WebInterfaceKeyName.c_str(),sTemp);  //��ȡWebInterfaceUrl���µļ�ֵurl
		if(pWebUrl->m_WebWithPara)  //��web�ӿ�֮�����, (url֮��Ӳ���uin,tokentype,token)  
		{
			sUrl = AppendUrlParamet(sTemp);
		}
		else  //web�ӿ�֮�󲻴���
		{
			sUrl = sTemp;
		}

		pWebUrl->m_WebInterfaceUrl = sUrl.GetBuffer();
		return 0;
	}
	return -1;
}

int32 HallModule::InvokeGetTokenURL(param st)
{
	std::wstring& strURL = *(std::wstring*)st;
	CString strURL2 = AppendUrlParamet(strURL.c_str());
	strURL = strURL2.GetBuffer();
	return 0;
}

int32 HallModule::InvokeOpenTokenURL(param st)
{
	InvokeGetTokenURL(st);
	std::wstring& strURL = *(std::wstring*)st;
	common::utility::systemhelper::OpenUrl(strURL);
	return 0;
}

int32 HallModule::InvokeMsgBoxShow(param st)
{
	m_pHallDlg->ShowWindow(SW_SHOW);
	if(m_pHallDlg->IsIconic()) //�����Ƿ���С��
	{
		m_pHallDlg->ShowWindow(SW_RESTORE);
	}
	m_pHallDlg->SetForegroundWindow();	
	m_pHallDlg->SendMessage(WM_MODULE_MSGBOX_SHOW,(WPARAM)st,0);

	return 0;

}

//SERVICE ��ȡָ���û�unUIN��ͷ��·��
int32 HallModule::InvokeGetHeadImagePath(param st)
{
	Hall::HeadImage *phead = (Hall::HeadImage *)st;
	if(!phead->m_isGuest)
	{
		phead->m_HeadImagePath = m_headDownload.GetLocalHeadImage(phead->m_unUIN,phead->m_bMan); //��ȡ����ͷ��ͼƬ·��
	}
	else
	{
		phead->m_HeadImagePath = m_headDownload.GetGuestHeadImage();  //��ȡ����Ĭ���ο�ͼƬ
	}
	return 0;
}

//SERVICE ��ȡָ���û�unUIN��ͷ��·������������ͷ��
int32 HallModule::InvokeUpDateHeadImagePath(param st)
{
	Hall::HeadImage *phead = (Hall::HeadImage *)st;
	if(!phead->m_isGuest)
	{
		phead->m_HeadImagePath = m_headDownload.GetLocalHeadImage(phead->m_unUIN,phead->m_bMan); //��ȡ����ͷ��ͼƬ·������δ�ҵ�ָ��unUIN�Ķ�Ӧͷ��ͼƬ��ʹ��Ĭ��ͼƬ
		m_headDownload.EventSendNewHeadDown(phead->m_unUIN);  //��������ͷ����������
	}
	else
	{
		phead->m_HeadImagePath = m_headDownload.GetGuestHeadImage();  //��ȡ����Ĭ���ο�ͼƬ
	}
	
	return 0;
}


void HallModule::InitTrayMgr()
{
	HICON icon;
	CString strModulePath	= common::utility::systemhelper::Get179AppPath().c_str();	
	CString updateTray;
	updateTray.Format(_T("%sresource\\listicon\\TrayLogining.ico"),strModulePath);  //��ɫ��������ͼ��
	icon = (HICON)LoadImage( AfxGetResourceHandle(), updateTray, 
		IMAGE_ICON,	16, 16, LR_LOADFROMFILE );
	m_trayMgrPath.push_back(icon);

	updateTray.Format(_T("%sresource\\listicon\\TrayLogined.ico"),strModulePath);  //��ɫ��������ͼ��
	icon = (HICON)LoadImage( AfxGetResourceHandle(), updateTray,  
		IMAGE_ICON,	16, 16, LR_LOADFROMFILE );
	m_trayMgrPath.push_back(icon);

	m_trayMgrCur = 0;
	m_trayMgr.Init(No_Care_HWND, eTNMode_Event, eTFSMode_Click);
	m_trayMgr.AddEventHandler(this);	
	
}

//��¼�����д������̶�̬�л���ʾ
void HallModule::LoginingTrayMgr()
{
	m_trayMgr.Add(m_trayMgrPath[m_trayMgrCur], _T("����KTV"));	

	m_trayMgrCur ++ ;
	if(m_trayMgrCur >= m_trayMgrPath.size())
	{
		m_trayMgrCur = 0;
	}

}

//�����������Զ���¼
void HallModule::FirstAutoLogin()
{
	m_pLoginDlg->OnFirstLogin();
}

//���ش���ͼ��
//isLogined ΪTRUEʱ ������ɫ��������ͼ��, ΪFALSEʱ ���ػ�ɫ��������ͼ��
void HallModule::LoadTrayMgr(BOOL isLogined)
{
	if(m_trayMgrPath.size()>=2)
	{
		if(isLogined) //������ɫ��������ͼ��
		{
			m_trayMgr.Add(m_trayMgrPath[1], _T("����KTV"));	
		}
		else  //���ػ�ɫ��������ͼ��
		{
			m_trayMgr.Add(m_trayMgrPath[0], _T("����KTV"));	
		}
	}
}

void HallModule::CreateHallTrayMenu()
{
	core::CurInfo m_MyCurInfo = GetCurInfo();
	UINT setflags,abortflags,userflas;

	if(m_pHallDlg == NULL)
	{
		assert(0);
		return;
	}
	
	//�������ܲ���ʱ
	if(!m_pHallDlg->IsWindowEnabled())
	{
		setflags = MF_GRAYED ;  //ʹ�˵�����Ч����ң�ʹ�䲻�ܱ�ѡ
		abortflags = MF_GRAYED;
		userflas = MF_GRAYED;	
	}
	else  //�������Բ���ʱ
	{
		if(m_MyCurInfo.enmAccountType == core::ACCOUNTTYPE_VISITOR)  //�ο�
		{
			setflags = MF_GRAYED ;  
		}
		else  //���ο�
		{
			setflags = MF_ENABLED;  //ʹ�˵�����Ч�����ӱ��״̬�лָ�
		}

		abortflags = MF_ENABLED;
		userflas = MF_ENABLED;
	}

	common::ui::CMenuEx * pm = new common::ui::CMenuEx();
	pm->CreatePopupMenu();
	if(m_pHallDlg->IsWindowVisible())
		pm->AppendMenuEx(MF_ENABLED,ID_TRAYMENU_HIDEWND,L"���ش���(H)");
	else
		pm->AppendMenuEx(MF_ENABLED,ID_TRAYMENU_HIDEWND,L"��ʾ����(S)");
	pm->AppendMenuEx(setflags,ID_TRAYMENU_USERSETTING,L"��������");
	pm->AppendMenuEx(setflags,ID_TRAYMENU_VEDIOSETTING,L"��Ƶ����");
	pm->AppendMenuEx(MF_SEPARATOR);
	pm->AppendMenuEx(MF_ENABLED,ID_TRAYMENU_HELP,L"����");
	pm->AppendMenuEx(abortflags,ID_TRAYMENU_ABOUT,L"���ڴ����");
	pm->AppendMenuEx(MF_SEPARATOR);
	pm->AppendMenuEx(userflas,ID_TRAYMENU_CHANGEUSER,L"�����û�");
	pm->AppendMenuEx(MF_ENABLED,ID_TRAYMENU_EXIT,L"��ȫ�˳�");

	common::ui::CCursorPos pt;
	SetForegroundWindow(m_pHallDlg->GetSafeHwnd());
	pm->TrackPopupMenu(0, pt.x, pt.y, m_pHallDlg);
	pm->DestroyMenu();

	delete pm;
	pm = NULL;

}


//��url֮��Ӳ���uin,tokentype,token
CString AppendUrlParamet(CString url)
{
	if(url.IsEmpty())
	{
		return _T("");
	}

	CString reUrl,tokenType;
	uint32 unUIN;
	core::CurInfo m_MyCurInfo = GetCurInfo();

	if(m_MyCurInfo.enmAccountType == core::ACCOUNTTYPE_QQ)
	{
		tokenType = _T("QQ");		
	}	
	else
	{
		tokenType = _T("179");		
	}
	unUIN = m_MyCurInfo.unUIN;

	if(url.Right(1) == _T("?"))
	{
		url = url.Left(url.GetLength()-1);
	}
	if(url.Find(_T("?")) != -1)
	{
		reUrl.Format(_T("%s&uin=%d&tokentype=%s&token=%s"),url,unUIN,tokenType,m_MyCurInfo.strToken.c_str());
	}
	else
	{
		reUrl.Format(_T("%s?uin=%d&tokentype=%s&token=%s"),url,unUIN,tokenType,m_MyCurInfo.strToken.c_str());
	}
	

	return reUrl;
}

CComVariant HallModule::LoadImageWrapper(CString imagePath,bool isUpload)
{
	common::ui::CImageImpl* pImage = NULL;

	std::map<CString, common::ui::CImageImpl*>::iterator it = m_mapPath2Image.find(imagePath);

	if(it != m_mapPath2Image.end())
	{
		pImage = it->second;	
		if(isUpload)
		{
			if(!pImage->Load(imagePath))
			{
				assert(0);
				return 0;
			}
		}

	}
	else
	{
		pImage = new common::ui::CImageImpl;
		if(!pImage->Load(imagePath))
		{
			assert(0);
			return 0;
		}
		m_mapPath2Image[imagePath] = pImage;
	}

	LONG lValue = (LONG)((IUnknown*)pImage);
	CComVariant varImage = lValue;

	return varImage;
}

//�ͻ��˷�����֤�����󷵻���Ӧ����
void HallModule::ProcessWebGetLoginIdentifyResp( Event const &evt )
{
	m_pLoginDlg->OnVerfiyCodeResp(evt);
}

void HallModule::ExcuteWebPluginCommand(CString strCommand)
{
	strCommand.Replace(L"\"", L"");
	if(strCommand.GetAt(strCommand.GetLength()-1) == '/')
	{
		strCommand = strCommand.Left(strCommand.GetLength()-1);
	}
	
	if(strCommand.Find(COMMAND_TOKEN_PREFIX) != 0)
	{
		return;	
	}

	strCommand = strCommand.Right(strCommand.GetLength()-wcslen(COMMAND_TOKEN_PREFIX));
	
	if(strCommand.Find(COMMAND_TOKEN_ENTER_ROOM) != 0)
	{
		assert(0);
		return;
	}

	strCommand = strCommand.Right(strCommand.GetLength()-wcslen(COMMAND_TOKEN_ENTER_ROOM));

	if(common::utility::stringhelper::IsNumeric(std::wstring(strCommand.GetBuffer())))
	{
		enterRoomInfo roomid;
		roomid.m_RoomID = _wtoi(strCommand.GetBuffer());
		m_pHallDlg->m_EnterRoomRequest.EnterRoomEventRequest(roomid);
	}
}

void HallModule::ExcuteCommandCaihong()
{
	if(__argc < 6)
	{
		return;
	}

	CString strCaiHong = __targv[1]; //51�ʺ��Զ���¼����KTVʱ����Ϊ caihong 	
	if(strCaiHong != COMMAND_TOKEN_51AUTOLOGIN)
	{
		return;  //���Ǵ�51�ʺ��¼����KTV��
	}

	//������    "caihong  801000507 701a2e6fdc0e4322b554cd5d9067ce64 room 100000"
	CString strAccount = __targv[2]; //51�ʺ��Զ���¼����KTVʱ����Ϊ ��Ӧ��179��
	CString strPassword = __targv[3]; //51�ʺ��Զ���¼����KTVʱ����Ϊ ��Ӧ��MD5����
	CString strRoom = __targv[4]; //51�ʺ��Զ���¼����KTVʱ����Ϊ ��������
	CString strRoomID = __targv[5]; //51�ʺ��Զ���¼����KTVʱ����Ϊ ��������ID

	CString str;
	str.Format(_T("����:  %s %s %s %s %s"),strCaiHong,strAccount,strPassword,strRoom,strRoomID);
	OutputDebugString(str);

	if(strRoom != COMMAND_TOKEN_51_ENTER_ROOM)
	{
		return;
	}

	//�Ƿ���л�ӭ�Ի�����ʾ
	core::CurInfo m_MyCurInfo = GetCurInfo();
	if(!(m_MyCurInfo.enmAccountType != core::ACCOUNTTYPE_VISITOR && m_MyCurInfo.strName == _T("") && m_MyCurInfo.bFirstLogin))
	{																							
		if(common::utility::stringhelper::IsNumeric(wstring(strRoomID)))
		{
			enterRoomInfo roomid;
			roomid.m_RoomID = _wtoi(strRoomID.GetBuffer());
			m_pHallDlg->m_EnterRoomRequest.EnterRoomEventRequest(roomid);
		}
		OutputDebugString(_T("ExcuteCommandCaihong  ����ִ�� ����"));
	}
}

void HallModule::ProcessCommandLine()
{	
	std::wstring strCommand = L"";

	if(!m_bCommandLineProcessed)
	{
		strCommand = common::utility::systemhelper::GetCommandLineCommand();
		m_bCommandLineProcessed = true;
	}

	if(!strCommand.empty())
	{
		ExcuteWebPluginCommand(strCommand.c_str());
		ExcuteCommandCaihong();
	}
	else if(!m_cacheWebPluginCommand.IsEmpty())
	{
		ExcuteWebPluginCommand(m_cacheWebPluginCommand);
		m_cacheWebPluginCommand = "";
	}
}

void HallModule::OnWebPluginCommand(CString strCommand)
{
	//��½���ڣ�δ��¼�ɹ�����������
	if(m_pLoginDlg->IsWindowVisible())
	{
		m_cacheWebPluginCommand = strCommand;
	}
	else
	{
		ExcuteWebPluginCommand(strCommand);
	}
}

bool HallModule::InitShareMemInfo(HWND hwndHall, HWND hwndLogin)
{
	HANDLE hMutex = ::OpenMutex(SYNCHRONIZE, FALSE, _T("Global\\51KTVMainApp"));
	if(hMutex == NULL)
	{
		DWORD d = ::GetLastError();
		assert(0);
		return false;
	}

	if(WAIT_OBJECT_0 == ::WaitForSingleObject(hMutex, INFINITE))
	{
		HANDLE hMapFile = ::OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE, FALSE, _T("Local\\51KTVMainFileMap"));
		if(hMapFile == NULL)
		{
			ReleaseMutex(hMutex);
			CloseHandle(hMutex);
			return true;
		}

		ShareMemInfo* pMemInfo = (ShareMemInfo*)MapViewOfFile(hMapFile, FILE_MAP_WRITE|FILE_MAP_READ, 0, 0, sizeof(ShareMemInfo));
		if(pMemInfo == NULL)
		{
			CloseHandle(hMapFile);
			ReleaseMutex(hMutex);
			CloseHandle(hMutex);
			return false;
		}

		pMemInfo->hwndHall = hwndHall;
		pMemInfo->hwndLogin = hwndLogin;

		UnmapViewOfFile(pMemInfo);
		CloseHandle(hMapFile);
		ReleaseMutex(hMutex);
		CloseHandle(hMutex);
		return true;
	}

	CloseHandle(hMutex);

	return false;
}

void HallModule::ProcessHallCreateAndShow(Event const &evt)
{
	SwitchResourceToModule(_T("Hall"));
	m_pHallDlg = new CHallDlg(m_pModuleManager);
	if (NULL != m_pHallDlg)
	{
		if(!m_pHallDlg->Create(CHallDlg::IDD,NULL))
		{
			AfxMessageBox(L"�Բ���UI����ʧ�ܣ��볢�����°�װ�ͻ��ˡ�");
			TerminateProcess(OpenProcess(PROCESS_TERMINATE, FALSE, GetCurrentProcessId()), 0);
			return;
		}

		if (m_pLoginDlg==NULL)
		{
			m_pLoginDlg=new CLoginDlg(m_pModuleManager,m_pHallDlg);
			m_pLoginDlg->Create(CLoginDlg::IDD, m_pHallDlg);
		}
		m_pHallDlg->EnableWindow(FALSE);		
		m_pLoginDlg->ShowWindow(SW_HIDE);	
		m_pHallDlg->ShowWindow(SW_HIDE);

		//���ʧ��(�࿪?)
		if(!InitShareMemInfo(m_pHallDlg->GetSafeHwnd(), m_pLoginDlg->GetSafeHwnd()))
		{
			TerminateProcess(OpenProcess(PROCESS_TERMINATE, FALSE, GetCurrentProcessId()), 0);
			return;
		}

		m_AutoUpdate.ShowCheckUpdateDlg(m_pHallDlg); //��ʾ�����¶Ի��򣬲���ʼ������°汾
		InitTrayMgr();
		LoadTrayMgr(FALSE);  //���ػ�ɫ��������ͼ��		

	}
}


void HallModule::ProcessLoginSuccess()
{
	m_pLoginDlg->OnLoginSuccess();
	m_pHallDlg->OnLoginSuccess() ;

	core::CurInfo m_MyCurInfo = GetCurInfo();

	if(m_MyCurInfo.enmAccountType != core::ACCOUNTTYPE_VISITOR) //���ο�
	{
		if(m_MyCurInfo.strName == _T("") && m_MyCurInfo.bFirstLogin) //���û����ϲ����ƣ��򵯳��״ε�¼��ӭ�Ի��� 
		{																							
			PostMessage(m_pHallDlg->GetSafeHwnd(),UM_QQFRISTLOGIN_INFO,0,0);  //��̨�����״ε�¼��ӭ�Ի���
		}
		if(m_MyCurInfo.enmAccountType == core::ACCOUNTTYPE_QQ && m_MyCurInfo.bFirstLogin) 
		{																							 
			PostMessage(m_pHallDlg->GetSafeHwnd(),UM_QQFRISTLOGIN_INFO,0,0);  //QQ�״ε�¼��ӭ�Ի���
		}
		m_headDownload.EventSendNewHeadDown(m_MyCurInfo.unUIN);//��¼�ɹ���������������ͷ��	
	}	

	ProcessCommandLine();


}

void HallModule::ProcessLoginResp(Event const &evt)
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	core::LoginRspEvent *pEvent=static_cast<core::LoginRspEvent*>(evt.m_pstExtraInfo);

	m_pLoginDlg->StopLoginingHallTray(); //ֹͣ��¼�����д������̶�̬�л���ʾ��
										 //ע�����˺�������������Ƿ���m_pLoginDlg->OnLoginResp�е����Ƿ�ֹ�е�¼ʧ����ʾʱ���̶�ʱ����ɫ��������ͼ��  

	LoadTrayMgr(FALSE);  //���ػ�ɫ��������ͼ�� (����¼ʧ��������ʾ�򵯳�ʱ���˴����ã����ڷ�ֹ�е�¼ʧ����ʾʱ���̶�ʱ����ɫ��������ͼ��)
	if(pEvent->enmLoginResult == core::LOGIN_ERROR_SUCCESS)
	{
		ProcessLoginSuccess();
		LoadTrayMgr(TRUE);  //������ɫ��������ͼ��
	}
	else
	{
		//����m_pLoginDlg����
  	   m_pLoginDlg->OnLoginResp(evt); //�����¼������Ӧ����
	   m_pHallDlg->OnLoginFailed() ;
	   LoadTrayMgr(FALSE);  //���ػ�ɫ��������ͼ��	

	}
	
	
}

void HallModule::ProcessKicked(Event const &evt)
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	core::BeKickedNotifyEvent *pInfo = (core::BeKickedNotifyEvent*)(evt.m_pstExtraInfo) ;	

	m_pLoginDlg->StopLoginingHallTray(); //ֹͣ��¼�����д������̶�̬�л���ʾ
	LoadTrayMgr(FALSE);  //���ػ�ɫ��������ͼ��	
	
	CloseNonModalDlg((CDialog*&)m_pHeadSettingDlg);	
	m_SysMessagePopup.ClearSysMessage();
	m_pLoginDlg->CloseReconnectMsgBox();

	m_pHallDlg->CloseAllDialog();
	m_pLoginDlg->UIEnable(TRUE);
	ShowLoginDialog(true);

	switch (pInfo->result)
	{					

	case core::BeKickedNotifyEvent::KICK_RE_LOGIN ://�˺��ص�½
		{
			CString passUrl;
			core::CurInfo m_MyCurInfo = GetCurInfo();
			if(m_MyCurInfo.enmAccountType == core::ACCOUNTTYPE_QQ)
			{
				CSysSettingIni::GetWebInterfaceUrl(SYSSET_INT_KEYNAME_QQMODIFYPASSWORD,passUrl); //�޸�����url
			}
			else
			{
				CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_179MODIFYPASSWORD,passUrl); //�޸�����url
			}
			
			C179MsgBox::Show(m_pLoginDlg->Get179MsgBoxParent(),NewMsgBox::MSGBOX_OK_TWO_STRING_WITH_LINK,_T("�����˺���ص�¼�����������ߡ�"),_T("��Ǳ��˲�����������               "),_T(""),_T("�޸�����"),passUrl);				

		}
		break;

	case core::BeKickedNotifyEvent::KICK_ACCOUNT_LOCK : //�˺ű�����
		{
		
			if ( pInfo->lockDays >= 365*10 )
			{
				CString strKick;
				strKick.Format(_T("����\"%s\"�����÷�ͣ�˺�"),pInfo->strReason.c_str() );
				C179MsgBox::Show(m_pLoginDlg->Get179MsgBoxParent(),NewMsgBox::MSGBOX_OK_TWO_STRING ,strKick,L"�������ʣ�����ϵ�ٷ��ͷ�" );	
			}			
			else
			{
				CString strKick;
				strKick.Format(_T("����\"%s\"����ͣ�˺�%d��"),pInfo->strReason.c_str() , pInfo->lockDays );
				C179MsgBox::Show(m_pLoginDlg->Get179MsgBoxParent(),NewMsgBox::MSGBOX_OK_TWO_STRING ,strKick,L"�������ʣ�����ϵ�ٷ��ͷ�" );	
			}
		}
		break;

	case core::BeKickedNotifyEvent::KICK_IP_LOCK : //ip������
		{			
			if ( pInfo->lockDays >= 365*10 )
			{
				CString strKick;
				strKick.Format(_T("����\"%s\"�����÷�ͣIP"),pInfo->strReason.c_str() );
				C179MsgBox::Show(m_pLoginDlg->Get179MsgBoxParent(),NewMsgBox::MSGBOX_OK_TWO_STRING ,strKick,L"�������ʣ�����ϵ�ٷ��ͷ�" );	
			}			
			else
			{
				CString strKick;
				strKick.Format(_T("����\"%s\"����ͣIP%d��"),pInfo->strReason.c_str() , pInfo->lockDays );
				C179MsgBox::Show(m_pLoginDlg->Get179MsgBoxParent(),NewMsgBox::MSGBOX_OK_TWO_STRING ,strKick,L"�������ʣ�����ϵ�ٷ��ͷ�" );	
			}
		}
		break;
	case core::BeKickedNotifyEvent::KICK_MAC_LOCK: //mac������
		{		
			if ( pInfo->lockDays >= 365*10 )
			{
				CString strKick;
				strKick.Format(_T("����\"%s\"�����÷�ͣmac��ַ"),pInfo->strReason.c_str() );
				C179MsgBox::Show(m_pLoginDlg->Get179MsgBoxParent(),NewMsgBox::MSGBOX_OK_TWO_STRING ,strKick,L"�������ʣ�����ϵ�ٷ��ͷ�" );	
			}			
			else
			{
				CString strKick;
				strKick.Format(_T("����\"%s\"����ͣmac��ַ%d��"),pInfo->strReason.c_str() , pInfo->lockDays );
				C179MsgBox::Show(m_pLoginDlg->Get179MsgBoxParent(),NewMsgBox::MSGBOX_OK_TWO_STRING ,strKick,L"�������ʣ�����ϵ�ٷ��ͷ�" );	
			}
		}
		break;
	case core::BeKickedNotifyEvent::KICK_OTHER: //����		
	default:
		{		
			
			//C179MsgBox::Show(NewMsgBox::MSGBOX_OK_ONE_STRING ,_T("���ѱ���"));
		}
		break;
	}


}

void HallModule::ProcessWebDownFileResp(Event const &evt)
{
	m_pHallDlg->OnUpdateHallTreeResp(evt);  //����Ŀ¼���ļ��������
	m_AutoUpdate.OnEventRespWebDown(evt); //���°汾�����ļ������°�װ��\���°��������		
}

void HallModule::ProcessWebHeadImageResp(Event const &evt)
{
	m_headDownload.OnEventRespNewHeadDown(evt); //����ͷ���������󷵻���Ӧ������������ͷ�����سɹ����Զ�������Ϣ MESSAGE_VALUE_HALL_NEW_HEAD_IMAGE
}

void HallModule::ProcessWebGetHttpResp(Event const &evt)
{
	CSearchDlg *pSearchDlg = m_pHallDlg->GetSearchDlg();
	if(pSearchDlg != NULL)
	{
		pSearchDlg->OnEventRespSearch(evt); //�����������󷵻���Ӧ����
	}
	m_pHallDlg->OnUpdateTickerResp(evt);

}


//ͷ���ϴ�
void HallModule::PrcoessHallHeadUpload(Event const &evt)
{
	//����ͷ���ϴ��Ի���
	ASSERT(evt.m_pstExtraInfo != NULL);
	Hall::HeadSetting *pInfo = (Hall::HeadSetting*)(evt.m_pstExtraInfo) ;

	CloseNonModalDlg((CDialog*&)m_pHeadSettingDlg);
	if(m_pHeadSettingDlg == NULL)
	{
		SwitchResourceToModule(_T("Hall"));
		CWnd *pParentWnd = CWnd::FromHandle(pInfo->m_parentHwnd);
		m_pHeadSettingDlg = new CHeadSettingDlg(pParentWnd);		
		m_pHeadSettingDlg->Create(CHeadSettingDlg::IDD, pParentWnd);		
	}

	m_pHeadSettingDlg->ShowWindow(SW_SHOW);	

}
void HallModule::ProcessWebHeadUpLoadResp(Event const &evt)
{	
	if(m_pHeadSettingDlg != NULL)
	{
		m_pHeadSettingDlg->OnEventRespHeadUpload(evt);//�û��ϴ��Զ���ͷ�񷵻���Ӧ����
			
		CloseNonModalDlg((CDialog*&)m_pHeadSettingDlg);
	}


}

//������(��ȫ����)�ܱ�
void HallModule::ProcessPassWordSafe(Event const &evt ) 
{
	m_pHallDlg->OnPassWordSafe() ;
}

void HallModule::PrcoessMyInfoUpdate(Event const &evt)
{	
	::SendMessage(m_pHallDlg->GetSafeHwnd(),UM_USERINFO_UPDATE,0,0);		
	m_pLoginDlg->SaveUserAccount();
}

void HallModule::MessageMyVipLevelUpdate(Message const& msg)
{
	::SendMessage(m_pHallDlg->GetSafeHwnd(),UM_USERINFO_UPDATE,0,0);	
}

void HallModule::MessageMyRichLevelUpdate(Message const& msg)
{
	::SendMessage(m_pHallDlg->GetSafeHwnd(),UM_USERINFO_UPDATE,0,0);
	m_SysMessagePopup.OnSystemMessageOther(SystemMessage::SystemMessageType::SYSTEMMESSAGETYPE_MAGNATE);  //�����ȼ������ϵͳ��Ϣ����

}

void HallModule::ProcessDisconnected(Event const &evt)
{
	m_pHallDlg->CloseAllDialog();
	ShowLoginDialog(true);
	LoadTrayMgr(FALSE); //���ػ�ɫ��������ͼ��
	CloseNonModalDlg((CDialog*&)m_pHeadSettingDlg);
	m_pLoginDlg->ReLogin();
	m_pHallDlg->EnableWindow(FALSE);
}

void HallModule::ProcessRegisterResp(Event const &evt)
{	
	ASSERT(evt.m_pstExtraInfo != NULL);
	RoomShowRegister *pInfo = (RoomShowRegister*)(evt.m_pstExtraInfo) ;

	CWnd *pParentWnd = CWnd::FromHandle(pInfo->m_parentHwnd);
	m_pHallDlg->CreateAndShowRegisterDlg(true,pParentWnd);  //��������ʾע��Ի���
	m_pHallDlg->EnableWindow(TRUE);
	m_pHallDlg->SetRoomRegister(); //����Ϊ����ע��Ի���

}

void HallModule::ProcessRichUpdateMoneyResp(Event const &evt)
{
	m_pHallDlg->SetRickLevelTip();  //���ø����ȼ�TIP��ʾ��
}

//�رշ�ģ̬�Էſ�
void CloseNonModalDlg(CDialog*& dlg)
{
	if(dlg != NULL)
	{
		dlg->DestroyWindow();
		delete dlg;
		dlg = NULL;
	}
}
