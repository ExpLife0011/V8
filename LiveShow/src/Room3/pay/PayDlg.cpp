// PayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "PayDlg.h"
#include "skin_i.h"
#include "SkinUtil.h"

#define  SKIN_ON_CLICK_CLOSE        1
// CPayDlg �Ի���

IMPLEMENT_DYNAMIC(CPayDlg, CDialog)

CPayDlg::CPayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPayDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);
}

CPayDlg::~CPayDlg()
{
}

void CPayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPayDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
END_MESSAGE_MAP()


// CPayDlg ��Ϣ�������

int CPayDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(NULL != m_pSkinEngine);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"PayDlg");
		ASSERT(hr== S_OK && __LINE__);
	}

	return 0;
}

BOOL CPayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_htmlPay.CreateFromStatic(IDC_ROOM_HTML_PAY,this);
	CComVariant var = (LONG)m_htmlPay.GetSafeHwnd();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"itemHtmlPay",L"hwnd",var);
	InitPayBrowser();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CPayDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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

void CPayDlg::InitPayBrowser()
{
	CString strUrl = L"about:blank";
	m_htmlPay.SetUrl(std::wstring(strUrl.GetBuffer()), true);
	m_htmlPay.UpdateURL();
}

LRESULT CPayDlg::OnSkinMessage(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_CLOSE:
		{
			ShowWindow(SW_HIDE);
		}
		break;
	default:break;
	}

	return TRUE;
}

void CPayDlg::SetTheUrl( CString strUrl )
{
	if (m_htmlPay.GetSafeHwnd() == NULL)
	{
		return;
	}

	m_htmlPay.SetUrl(std::wstring(strUrl.GetBuffer()), true);
	m_htmlPay.UpdateURL();
}