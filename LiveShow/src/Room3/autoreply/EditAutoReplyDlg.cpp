// SelfDefInputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "EditAutoReplyDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "..\..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\..\CommonLibrary\include\ui\C179MsgBox.h"

#define SKIN_ON_CLICK_CLOSE           1
#define SKIN_ON_CLICK_BTN_CONFIRM     2

#define AUTO_REPLY_MAX_LENGTH         50

// CEditAutoReplyDlg �Ի���

IMPLEMENT_DYNAMIC(CEditAutoReplyDlg, CDialog)

CEditAutoReplyDlg::CEditAutoReplyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditAutoReplyDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);

	m_strInput = L"";
}

CEditAutoReplyDlg::~CEditAutoReplyDlg()
{
	m_strInput = L"";
}

void CEditAutoReplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AUTO_REPLY, m_InputEdit);
}


BEGIN_MESSAGE_MAP(CEditAutoReplyDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CEditAutoReplyDlg ��Ϣ�������

int CEditAutoReplyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(NULL != m_pSkinEngine);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"EditAutoReplyDlg");
		ASSERT(hr== S_OK && __LINE__);
	}
	//����������ѡ΢���ź�
	std::wstring strFont;
	common::utility::systemhelper::GetDefaultFontName(strFont);
	CComVariant var = (CComVariant) strFont.c_str();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textTitle",L"fontFamily",var);

	return 0;
}

BOOL CEditAutoReplyDlg::PreTranslateMessage(MSG* pMsg)
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


LRESULT CEditAutoReplyDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_CLOSE:
		{
           PostMessage(WM_CLOSE,NULL,NULL);
		}
		break;
	case SKIN_ON_CLICK_BTN_CONFIRM:
		{
			UpdateData() ;
			m_InputEdit.GetWindowText( m_strInput ) ;
			CString strTemp = m_strInput;
			if ((strTemp.Trim() == L"") || (strTemp.GetLength() > AUTO_REPLY_MAX_LENGTH))
			{
				//AfxMessageBox(L"����Ϊ��");
				C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"���벻��Ϊ���Ҳ��ܳ���50���ַ�" );
				return FALSE;
			}
			
			EndDialog( IDOK ) ;
		}
		break;
 
	default:break;
	}


    return TRUE;
}

CString CEditAutoReplyDlg::GetInPutString() 
{
	return m_strInput ;
}

void CEditAutoReplyDlg::SetAutoReplyEditTitle(CString strTitle)
{
    m_strTitle = strTitle;
}

void CEditAutoReplyDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if (bShow)
	{
		CComVariant var = m_strTitle;
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textTheTitle", L"text", var);
		m_InputEdit.SetWindowText(m_strInput);
		m_InputEdit.SetLimitText(50);
	}
}

void CEditAutoReplyDlg::SetEditText(CString strEdit)
{
	//m_InputEdit.SetWindowText(strEdit.GetBuffer(0));
	m_strInput = strEdit;
}
