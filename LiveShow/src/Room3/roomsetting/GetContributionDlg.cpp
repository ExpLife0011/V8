// GetContributionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "GetContributionDlg.h"
#include "skin_i.h"
#include "SkinUtil.h"
#include "..\..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\..\CommonLibrary\include\ui\C179MsgBox.h"
#include "HallDefine.h"
#include "..\GlobalRoomDefine.h"


#define SKIN_ON_CLICK_CLOSE                    1
#define SKIN_ON_CLICK_GETIT                    2
#define SKIN_ON_CLICK_LINK_TO_INTRO            3   //�����ϸ���乱��˵�� 

// CGetContributionDlg �Ի���

IMPLEMENT_DYNAMIC(CGetContributionDlg, CDialog)

CGetContributionDlg::CGetContributionDlg(CWnd* pParent, uint32 unRoomID)
	: CDialog(CGetContributionDlg::IDD, pParent),m_nRoomID(unRoomID)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);
}

CGetContributionDlg::~CGetContributionDlg()
{
}

void CGetContributionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGetContributionDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CGetContributionDlg ��Ϣ�������

int CGetContributionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if(NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"GetContributionDlg");
		ASSERT(hr==S_OK && __LINE__);
	}

	//����������ѡ΢���ź�
	std::wstring strFont;
	common::utility::systemhelper::GetDefaultFontName(strFont);
	CComVariant var = (CComVariant) strFont.c_str();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textTitle",L"fontFamily",var);

	return 0;
}

BOOL CGetContributionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//���������
	m_htmlGetContribute.CreateFromStatic(IDC_HTML_GET_CONTRIBUTE,this);
	CComVariant var = (LONG)m_htmlGetContribute.GetSafeHwnd();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"itemHtmlGetContribute",L"hwnd",var);

	InitTheBrowser();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CGetContributionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//����ESC������ENTER��
	if ( pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:

			return TRUE ;
		default: break;
		}	
	}

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CGetContributionDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_CLOSE:
		{
           //DestroyWindow();
			ShowWindow(SW_HIDE);
		}
		break;
	case SKIN_ON_CLICK_GETIT:
		{
           OnClickGetContribution();
		}
		break;
	case SKIN_ON_CLICK_LINK_TO_INTRO:
		{
			common::utility::systemhelper::OpenUrl(_T("about:blank"));
		}
		break;
	default:break;
	}

	return TRUE;
}

void CGetContributionDlg::OnClickGetContribution()
{

	C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING, L"��ϲ������ȡ�ɹ���");
}

void CGetContributionDlg::InitTheBrowser()
{
	Hall::WebInterfaceUrl weburl;
	weburl.m_WebWithPara = true;
	weburl.m_WebInterfaceKeyName = SYSSET_INI_KEYNAME_GETCONTRIBUTE;
	g_RoomModule->m_pModuleManager->CallService(Hall::SERVICE_VALUE_HALL_GET_WEBINTERFACEURL, (param)&weburl);
	CString temp;
	temp.Format(L"&roomid=%d", m_nRoomID);
	weburl.m_WebInterfaceUrl += temp.GetBuffer();
	m_htmlGetContribute.SetUrl(weburl.m_WebInterfaceUrl, false, true);
	m_htmlGetContribute.UpdateURL();
}

LRESULT CGetContributionDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_MISSION_SHOW_MESSAGEBOX:  //����messagebox��Ϣ
		{
			CString sMessage = (LPCTSTR)wParam;
			C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,sMessage );
		}
	default:
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CGetContributionDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if (bShow)
	{
		InitTheBrowser();
	}
}
