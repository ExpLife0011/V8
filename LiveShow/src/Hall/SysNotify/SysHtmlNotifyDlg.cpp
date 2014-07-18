// SysHtmlNotifyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Hall.h"
#include "SysHtmlNotifyDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "../CommonLibrary/include/utility/SystemHelper.h"

#define SYSMESSAGE_HTML			L"resource\\html\\SysMes.html"

//#define  SKIN_ON_CLICK_BTN_CLOSE  1
// CSysHtmlNotifyDlg �Ի���

IMPLEMENT_DYNAMIC(CSysHtmlNotifyDlg, CDialog)

CSysHtmlNotifyDlg::CSysHtmlNotifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysHtmlNotifyDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);
	m_bMouseLeave= TRUE;
	m_CurSysMessage = NULL;
}

CSysHtmlNotifyDlg::~CSysHtmlNotifyDlg()
{
}

void CSysHtmlNotifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSysHtmlNotifyDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE	
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_MISSION_HYPERLINK_ONCLICK_MOUSEUP,&CSysHtmlNotifyDlg::OnClick)
END_MESSAGE_MAP()


// CSysHtmlNotifyDlg ��Ϣ�������


int CSysHtmlNotifyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"SysHtmlNotifyDlg");
		ASSERT(hr == S_OK && __LINE__);
	}

	return 0;
}

BOOL CSysHtmlNotifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyleEx( WS_EX_APPWINDOW , WS_EX_TOOLWINDOW) ;

	int cx = GetSystemMetrics(SM_CXSCREEN);  //��Ļ���
	int cy = GetSystemMetrics(SM_CYSCREEN);  //��Ļ�߶�
	// pSysNotifyDlg->SetWindowPos(NULL,cx - 250,cy - 170,250,170,SWP_SHOWWINDOW);
	RECT rect;
	::SystemParametersInfo(SPI_GETWORKAREA,sizeof(RECT),&rect,0); //���������С
	RECT deskRect;
	::GetWindowRect(::GetDesktopWindow(),&deskRect); //���洰�ڴ�С
	int startHight = deskRect.bottom - rect.bottom;  //ϵͳ״̬���߶�

	CRect clientRect(0,0,0,0);
	clientRect.left = cx - SYS_HTML_NOTIFY_WIDTH;
	clientRect.top = cy - startHight - SYS_HTML_NOTIFY_HIGHT;
	clientRect.right = clientRect.left + SYS_HTML_NOTIFY_WIDTH;
	clientRect.bottom = clientRect.top + SYS_HTML_NOTIFY_HIGHT;
	MoveWindow(&clientRect);

	CComVariant var;
	m_htmlSysNotify.CreateFromStatic(IDC_HTML_SYSNOTIFY, this);
	var = (LONG)m_htmlSysNotify.GetSafeHwnd();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"itemHtmlSysNotify",L"hwnd",var);
	InitTheHtml();

	return FALSE;//�������������� 

	//return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


LRESULT CSysHtmlNotifyDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	/*case SKIN_ON_CLICK_BTN_CLOSE:
		{
			DestroyWindow();
		}
		break;*/

	default:break;
	}


	return S_OK;
}

void CSysHtmlNotifyDlg::InitTheHtml()
{
	
	std::wstring strUrl = common::utility::systemhelper::Get179AppPath() + SYSMESSAGE_HTML;
	m_htmlSysNotify.SetUrl(strUrl,true);
	m_htmlSysNotify.UpdateURL();

}

void CSysHtmlNotifyDlg::SetSystemMessage(SystemMessage* sysMes)
{
	m_CurSysMessage = sysMes;
}

//��ȡ���m_htmlSysNotifyϵͳ��Ϣҳ��ʱ����Ӧ����
LRESULT CSysHtmlNotifyDlg::OnClick(WPARAM wParam,LPARAM lParam)
{
	IHTMLEventObj *pEvtObj = (IHTMLEventObj *)lParam;

	if(pEvtObj == NULL)
	{
		assert(false);
		return FALSE;
	}

	CComPtr<IHTMLElement> pElement;
	pEvtObj->get_srcElement(&pElement);

	if(pElement == NULL)
	{
		assert(false);
		return FALSE;
	}	

	CComBSTR tag;
	pElement->get_tagName(&tag);
	if(tag == _T("A") || tag == _T("a"))
	{		
		CString strName = m_htmlSysNotify.GetValue( pElement , _T("name") ) ;
		if(strName == _T("closemes"))
		{
			DestroyWindow();
		}	
	}

	return TRUE;
}
// �޸���ҳ����ϢԪ�ص�����
void CSysHtmlNotifyDlg::PutElementHtmlMsg()
{
	if(m_CurSysMessage == NULL)
	{
		return;
	}

	vector<SystemMessage::MessageInfo> &MessInfo = m_CurSysMessage->strMessage;
	if(MessInfo.size() ==0 )
	{
		return;
	}
	
	switch(m_CurSysMessage->enmType)
	{
	case SystemMessage::SystemMessageType::SYSTEMMESSAGETYPE_TEXT:	
	case SystemMessage::SystemMessageType::SYSTEMMESSAGETYPE_WITHOUT_TITLE:
	case SystemMessage::SystemMessageType::SYSTEMMESSAGETYPE_MAGNATE:  //�����ȼ�������Ϣ
		{			
			m_htmlSysNotify.PutElementHtml(_T("title"),m_CurSysMessage->strWindowTitle.c_str()); 
			m_htmlSysNotify.PutElementHtml(_T("content"),MessInfo[0].strMessage.c_str()); 
		}
		break;
	default:
		break;
	}
	
}


LRESULT CSysHtmlNotifyDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_MISSION_COMPLETED:
		{
			PutElementHtmlMsg();			
				
		}
		break;
	
	case WM_MISSION_NAVIGATECOMPLETE2:
		{
			
		}
		break;
	default:
		break;		
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CSysHtmlNotifyDlg::IfMouseLeave()
{
	if(this->GetSafeHwnd() && this->IsWindowVisible())
	{
		CPoint point2 ;
		GetCursorPos( &point2 ) ;
		CRect rect ;
		this->GetWindowRect(&rect) ;
		if ( rect.PtInRect(point2) )
		{
			m_bMouseLeave = FALSE;
		}else
		{
			m_bMouseLeave = TRUE;
		}		

		return m_bMouseLeave;
	}
	else
	{
		return TRUE;
	}
}
