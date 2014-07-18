// ScrollBtnDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "ScrollBtnDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "..\RoomParentDlg.h"
#include "..\personalsetting\PersonalConfig.h"

#define  SKIN_ON_CLICK_BTN_SCROLL        1
#define  SKIN_ON_CLICK_BTN_CLEAN         2
// CScrollBtnDlg �Ի���

IMPLEMENT_DYNAMIC(CScrollBtnDlg, CDialog)

CScrollBtnDlg::CScrollBtnDlg( CRoomParentDlg* pParentDlg  , CWnd* pParent /*=NULL*/)
	: CDialog(CScrollBtnDlg::IDD, pParent),
	m_pParentDlg( pParentDlg )
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);

	m_bScrool = TRUE;
}

CScrollBtnDlg::~CScrollBtnDlg()
{
}

void CScrollBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScrollBtnDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CScrollBtnDlg ��Ϣ�������

BOOL CScrollBtnDlg::PreTranslateMessage(MSG* pMsg)
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

int CScrollBtnDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"ScrollBtnDlg");
		ASSERT(hr == S_OK && __LINE__);
	}
	ModifyStyleEx( WS_EX_APPWINDOW , 0 ) ;
	ModifyStyleEx( WS_EX_TOOLWINDOW , 0 ) ;
	return 0;
}

LRESULT CScrollBtnDlg::OnSkinMessage(WPARAM wParam,LPARAM lParam)
{
    switch(wParam)
	{
	case SKIN_ON_CLICK_BTN_SCROLL:
		{
			OnClickBtnScroll();
		}
		break;
	case SKIN_ON_CLICK_BTN_CLEAN:
		{
			OnClickBtnClean();
		}
		break;
	default:break;
	}

	return TRUE;
}

void CScrollBtnDlg::OnClickBtnScroll()
{

	if (m_bScrool)//����ǰ���Զ�����״̬���������Ϊ������״̬
	{
		//ֹͣ���Զ�����
		switch( m_nHtmlType )
		{
		case HTML_TYPE_PUBLIC:
			{
				m_pParentDlg->SetPublicOutputGotoEndAble( FALSE ) ;
				CPersonalConfig::GetInstance()->SetPublicAutoScroll( false ) ;
			}
			break;
		case HTML_TYPE_PRIVATE:
			{
				m_pParentDlg->SetPrivateOutputGotoEndAble( FALSE ) ;
				CPersonalConfig::GetInstance()->SetPrivateAutoScroll( false ) ;
			}
			break;
		case HTML_TYPE_SPEAK:
			{
				m_pParentDlg->SetSpeakerOutputGotoEndAble( FALSE ) ;
				CPersonalConfig::GetInstance()->SetIsAutoScrollSpeaker( false ) ;
			}
			break;
		default:break;
		}
		
		//��ʾ�����Զ�����
		CComVariant var = _T("RoomV3_btnNotScroll_N.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"normalImage",var);
		var = _T("RoomV3_btnNotScroll_H.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"hoverImage",var);
		var = _T("RoomV3_btnNotScroll_D.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"downImage",var);
		var = _T("�����Զ�����");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"tip",var);
		m_bScrool = FALSE;		
	}
	else
	{
		//�������Զ�����
		switch( m_nHtmlType )
		{
		case HTML_TYPE_PUBLIC:
			{
				m_pParentDlg->SetPublicOutputGotoEndAble( TRUE ) ;
				CPersonalConfig::GetInstance()->SetPublicAutoScroll( true ) ;
			}
			break;
		case HTML_TYPE_PRIVATE:
			{
				m_pParentDlg->SetPrivateOutputGotoEndAble( TRUE ) ;
				CPersonalConfig::GetInstance()->SetPrivateAutoScroll( true ) ;
			}
			break;
		case HTML_TYPE_SPEAK:
			{
				m_pParentDlg->SetSpeakerOutputGotoEndAble( TRUE ) ;
				CPersonalConfig::GetInstance()->SetIsAutoScrollSpeaker( true ) ;
			}
			break;
		default:break;
		}

			
		//��ʾֹͣ�Զ�����
		CComVariant var = _T("RoomV3_btnScroll_N.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"normalImage",var);
		var = _T("RoomV3_btnScroll_H.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"hoverImage",var);
		var = _T("RoomV3_btnScroll_D.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"downImage",var);
		var = _T("ֹͣ�Զ�����");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"tip",var);
		m_bScrool = TRUE;			
	}
	
}

//ÿ�ζԻ�����ʾ��ʱ����ô˺���
void CScrollBtnDlg::Init( ENM_HTML_TYPE nHtmlType ) 
{
	m_nHtmlType = nHtmlType ;
	switch( m_nHtmlType )
	{
	case HTML_TYPE_PUBLIC:
		{
			m_bScrool = CPersonalConfig::GetInstance()->GetPublicAutoScroll() ;
		}
		break;
	case HTML_TYPE_PRIVATE:
		{
			m_bScrool = CPersonalConfig::GetInstance()->GetPrivateAutoScroll() ;
		}
		break;
	case HTML_TYPE_SPEAK:
		{
			m_bScrool = CPersonalConfig::GetInstance()->GetIsAutoScrollSpeaker() ;
		}
		break;
	default:break;
	}

	if (m_bScrool)
	{
		CComVariant var = _T("RoomV3_btnScroll_N.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"normalImage",var);
		var = _T("RoomV3_btnScroll_H.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"hoverImage",var);
		var = _T("RoomV3_btnScroll_D.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"downImage",var);
		var = _T("ֹͣ�Զ�����");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"tip",var);		
	}
	else
	{
		CComVariant var = _T("RoomV3_btnNotScroll_N.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"normalImage",var);
		var = _T("RoomV3_btnNotScroll_H.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"hoverImage",var);
		var = _T("RoomV3_btnNotScroll_D.png");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"downImage",var);
		var = _T("�����Զ�����");
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"btnScroll",L"tip",var);
	}
}
void CScrollBtnDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);
	ShowWindow( SW_HIDE ) ;
	// TODO: �ڴ˴������Ϣ����������
}

BOOL CScrollBtnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//return TRUE;  // return TRUE unless you set the focus to a control
	return FALSE;
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CScrollBtnDlg::OnClickBtnClean()
{
	switch( m_nHtmlType )
	{
	case HTML_TYPE_PUBLIC:
		{
			m_pParentDlg->CleanPublicOutput();
		}
		break;
	case HTML_TYPE_PRIVATE:
		{
			m_pParentDlg->CleanPrivateOutput();
		}
		break;
	case HTML_TYPE_SPEAK:
		{
			m_pParentDlg->CleanSpeakerOutput();
		}
		break;
	default:break;
	}
}