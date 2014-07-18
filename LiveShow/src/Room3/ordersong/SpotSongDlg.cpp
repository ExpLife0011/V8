// SpotSongDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "SpotSongDlg.h"
#include "OrderSongDlg.h"
#include "skin_i.h"
#include "SkinUtil.h"
#include "utility\StringHelper.h"

#define SKIN_ON_CLICK_CLOSE     1
#define SKIN_ON_CLICK_OK        2

// CSpotSongDlg �Ի���

IMPLEMENT_DYNAMIC(CSpotSongDlg, CDialog)

CSpotSongDlg::CSpotSongDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpotSongDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);
}

CSpotSongDlg::~CSpotSongDlg()
{
}

void CSpotSongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SPOTSONG_NUM, m_editSongNum);
}


BEGIN_MESSAGE_MAP(CSpotSongDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CSpotSongDlg ��Ϣ�������

int CSpotSongDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(NULL != m_pSkinEngine);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"SpotSongDlg");
		ASSERT(hr== S_OK && __LINE__);
	}

	return 0;
}

BOOL CSpotSongDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editSongNum.SetLimitText(5);
	m_editSongNum.SetWindowText(L"3");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

LRESULT CSpotSongDlg::OnSkinMessage( WPARAM wParam,LPARAM lParam )
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_CLOSE:
		{
			ShowWindow(SW_HIDE);
			SetNoEnoughMoney(FALSE, 3);
		}
		break;
	case SKIN_ON_CLICK_OK:
		{
			OnClickOK();
		}
		break;
	default:break;
	}
	
	return TRUE;
}

void CSpotSongDlg::SetNoEnoughMoney( BOOL bShow, int songNum )
{
	if (!bShow)
		return;

	CString strTemp;
	strTemp.Format(L"%d", songNum);
	CComVariant var = strTemp.GetBuffer(0);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textNoEnoughMoneyMid", L"text",var);
	var = bShow;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textNoEnoughMoneyLeft", L"visible", var);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textNoEnoughMoneyMid", L"visible", var);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textNoEnoughMoneyRight", L"visible", var);

}

void CSpotSongDlg::SetTheSongPrice( CString songPrice )
{
	CComVariant var = songPrice.GetBuffer(0);
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textWarmTip2Mid", L"text",var);
}

void CSpotSongDlg::OnClickOK()
{
	CString strNum;
	m_editSongNum.GetWindowText(strNum);
	int nNum = common::utility::stringhelper::StringToInt(strNum.GetBuffer(0));

	if (nNum < 3)
	{
		SetNoEnoughMoney(TRUE, 3);
		return;
	}
	else
	{
		SetNoEnoughMoney(FALSE, 3);
		((COrderSongDlg*)GetParent())->OnPriority(nNum);
		ShowWindow(SW_HIDE);
	}
}

BOOL CSpotSongDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_KEYDOWN )
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE;

		default: 
			break;
		}
	}	

	return CDialog::PreTranslateMessage(pMsg);
}

void CSpotSongDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if (bShow)
	{
		m_editSongNum.SetWindowText(L"3");
	}
}
