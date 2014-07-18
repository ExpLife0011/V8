// AutoReplySettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "AutoReplySettingDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "..\..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\..\CommonLibrary\include\ui\C179MsgBox.h"
#include "EditAutoReplyDlg.h"
#include "AutoReplyConfig.h"

#define SKIN_ON_CLICK_CLOSE          1
#define SKIN_ON_CLICK_BTN_MODIFY     2
#define SKIN_ON_CLICK_BTN_ADD        3
#define SKIN_ON_CLICK_BTN_DELETE     4
#define SKIN_ON_CLICK_BTN_CONFIRM    5

// CAutoReplySettingDlg �Ի���

IMPLEMENT_DYNAMIC(CAutoReplySettingDlg, CDialog)

CAutoReplySettingDlg::CAutoReplySettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoReplySettingDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);

	m_nMySelelected = -1;
	m_bChange = FALSE;
}

CAutoReplySettingDlg::~CAutoReplySettingDlg()
{
}

void CAutoReplySettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AUTOREPLY, m_autoReplyListCtrl);
	DDX_Control(pDX, IDC_CHECK_OPEN_AUTOREPLY, m_OpenAutoReply);
}


BEGIN_MESSAGE_MAP(CAutoReplySettingDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_NOTIFY(NM_HOVER, IDC_LIST_AUTOREPLY, &CAutoReplySettingDlg::OnNMHoverListAutoreply)
END_MESSAGE_MAP()


// CAutoReplySettingDlg ��Ϣ�������

int CAutoReplySettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(NULL != m_pSkinEngine);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"AutoReplySettingDlg");
		ASSERT(hr == S_OK && __LINE__);
	}

	//����������ѡ΢���ź�
	std::wstring strFont;
	common::utility::systemhelper::GetDefaultFontName(strFont);
	CComVariant var = (CComVariant) strFont.c_str();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textTitle",L"fontFamily",var);

	return 0;
}

BOOL CAutoReplySettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitListCtrl();
	m_OpenAutoReply.SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAutoReplySettingDlg::InitListCtrl()
{
	DWORD dwStyle = 0;
	LONG lStyle; 
	lStyle = GetWindowLong(m_autoReplyListCtrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style 
	lStyle = lStyle | LVS_REPORT | LVS_SINGLESEL; //����style 
	SetWindowLong(m_autoReplyListCtrl.m_hWnd, GWL_STYLE, lStyle);
	dwStyle = m_autoReplyListCtrl.GetExtendedStyle();
	dwStyle = dwStyle|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES; 
	m_autoReplyListCtrl.SetExtendedStyle(dwStyle); //������չ���
	m_autoReplyListCtrl.SetBkColor(RGB(255,255,255));
	m_autoReplyListCtrl.SetTextBkColor(RGB(255,255,255));

	m_autoReplyListCtrl.InsertColumn(0,L"",LVCFMT_CENTER,320);

	m_vAutoReplyList = AutoReplyMgr->GetAutoReplyList();
	std::vector<stAutoReplyMenuItem>::iterator iter ;
	for ( iter = m_vAutoReplyList.begin(); iter != m_vAutoReplyList.end(); ++iter )
	{
		CString strTemp = (*iter).strMenuItem.c_str();
		m_autoReplyListCtrl.InsertItem( m_autoReplyListCtrl.GetItemCount(), strTemp) ;
	}
	m_autoReplyListCtrl.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);//���õ�һ��Ϊѡ��
}

BOOL CAutoReplySettingDlg::PreTranslateMessage(MSG* pMsg)
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

HRESULT CAutoReplySettingDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_CLOSE:
		{
			//PostMessage(WM_CLOSE,NULL,NULL);
			OnClickBtnClose();
		}
		break;
	case SKIN_ON_CLICK_BTN_ADD:
		{
			OnClickBtnAdd();
		}
		break;
	case SKIN_ON_CLICK_BTN_DELETE:
		{
			OnClickBtnDelete();
		}
		break;
	case SKIN_ON_CLICK_BTN_MODIFY:
		{
			OnClickBtnModify();
		}
		break;
	case SKIN_ON_CLICK_BTN_CONFIRM:
		{
			OnClickBtnConfirm();
		}
		break;
	default:break;
	}

	return TRUE;
}

void CAutoReplySettingDlg::OnClickBtnAdd()
{
	if (m_autoReplyListCtrl.GetItemCount() > 4)
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"��Ǹ���Զ��ظ���������Ѵ�����" );
		return;
	}
	SwitchResourceToModule(_T("Room"));
	CEditAutoReplyDlg pDlg;
	pDlg.SetAutoReplyEditTitle(L"����Զ��ظ�");
	if (IDOK == pDlg.DoModal())
	{
		CString strAutoReply = pDlg.GetInPutString();
		m_autoReplyListCtrl.InsertItem(m_autoReplyListCtrl.GetItemCount(), strAutoReply);
		stAutoReplyMenuItem stItem;
		stItem.strMenuItem = strAutoReply;
		stItem.bChecked = false;
		m_vAutoReplyList.push_back(stItem);
		m_bChange = TRUE;
	}
}

void CAutoReplySettingDlg::OnClickBtnDelete()
{
	if (m_autoReplyListCtrl.GetSelectedCount() != 1)
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"��ѡ��һ���Զ��ظ�����ɾ��") ;
		return;
	}

	if ((m_autoReplyListCtrl.GetItemCount() - m_autoReplyListCtrl.GetSelectedCount()) < 3)
	{
		//AfxMessageBox(L"�Զ��ظ�ɾ�������Ѵ�����");
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"��Ǹ���Զ��ظ�ɾ�������Ѵ�����" );
		return;
	}
	//POSITION pos = NULL ;
	//vector<int> vSelectedItem ;
	//vector<int>::reverse_iterator iter ;
	//pos = m_autoReplyListCtrl.GetFirstSelectedItemPosition() ;
	//while( pos != NULL )
	//{
	//	int nItem = m_autoReplyListCtrl.GetNextSelectedItem(pos) ;
	//	vSelectedItem.push_back( nItem ) ;
	//}

	//for ( iter = vSelectedItem.rbegin() ; iter != vSelectedItem.rend() ; ++iter )
	//{
	//	m_autoReplyListCtrl.DeleteItem( *iter ) ;

	//	if ( *iter < m_vAutoReplyList.size() )
	//	{
	//		vector<stAutoReplyMenuItem>::iterator autoReply_iter = m_vAutoReplyList.begin();
	//		//int npos= *iter ;
	//		advance(autoReply_iter, (*iter)) ;//�õ�����autoReply_iterǰ��(*iter)��λ��
	//		m_vAutoReplyList.erase(autoReply_iter) ;
	//	}
	//}
	POSITION pos = NULL;
	int nSelItem = -1;
	pos = m_autoReplyListCtrl.GetFirstSelectedItemPosition();
	while( pos != NULL )
	{
		int nItem = m_autoReplyListCtrl.GetNextSelectedItem(pos) ;
		nSelItem = nItem;
		break;
	}
    if (nSelItem >= 0)
    {
		m_autoReplyListCtrl.DeleteItem(nSelItem) ;
		vector<stAutoReplyMenuItem>::iterator autoReply_iter = m_vAutoReplyList.begin();
		advance(autoReply_iter, nSelItem) ;//�õ�����autoReply_iterǰ��(*iter)��λ��
		m_vAutoReplyList.erase(autoReply_iter) ;
		m_bChange = TRUE;
    }

}

void CAutoReplySettingDlg::OnClickBtnModify()
{
	if (m_autoReplyListCtrl.GetSelectedCount() != 1)
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"��ѡ��һ���Զ��ظ������޸�" );
		return;
	}
	POSITION pos = NULL ;
	pos = m_autoReplyListCtrl.GetFirstSelectedItemPosition();
	CString strSelected;
	int nSelectedItem;
	if( pos != NULL )
	{
		nSelectedItem = m_autoReplyListCtrl.GetNextSelectedItem(pos) ;
		strSelected = m_autoReplyListCtrl.GetItemText(nSelectedItem,0);
    }
	SwitchResourceToModule(_T("Room"));
	CEditAutoReplyDlg pDlg;
	pDlg.SetAutoReplyEditTitle(L"�޸��Զ��ظ�");
	pDlg.SetEditText(strSelected);
	if (IDOK == pDlg.DoModal())
	{
		CString strAutoReply = pDlg.GetInPutString();
		//m_autoReplyListCtrl.InsertItem(nSelectedItem, strAutoReply);
		m_autoReplyListCtrl.SetItemText(nSelectedItem, 0, strAutoReply);
		if (nSelectedItem < m_vAutoReplyList.size())
		{
			vector<stAutoReplyMenuItem>::iterator autoReply_iter = m_vAutoReplyList.begin();
			advance(autoReply_iter, nSelectedItem);
			(*autoReply_iter).strMenuItem = strAutoReply;
			m_bChange = TRUE;
		}
		
	}
}

void CAutoReplySettingDlg::OnNMHoverListAutoreply(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 1;
}

BOOL CAutoReplySettingDlg::GetAutoReplyState()
{
	return m_bCheck;
}

void CAutoReplySettingDlg::OnClickBtnConfirm()
{
	m_bCheck = m_OpenAutoReply.GetCheck();

	POSITION pos = NULL;
	int nSelItem = -1;
	pos = m_autoReplyListCtrl.GetFirstSelectedItemPosition();
	while( pos != NULL )
	{
		int nItem = m_autoReplyListCtrl.GetNextSelectedItem(pos) ;
		nSelItem = nItem;
		break;
	}

	if (nSelItem >= 0)//˵����ѡ��
	{
		m_nMySelelected = nSelItem;
		vector<stAutoReplyMenuItem>::iterator autoReply_iter;
		for (autoReply_iter = m_vAutoReplyList.begin(); autoReply_iter != m_vAutoReplyList.end(); autoReply_iter++)
		{
			(*autoReply_iter).bChecked = false;
		}
        autoReply_iter = m_vAutoReplyList.begin(); 
		advance(autoReply_iter, m_nMySelelected);
		(*autoReply_iter).bChecked = true;
	}
	/*m_autoReplyListCtrl*/
	EndDialog( IDOK ) ;
}

void CAutoReplySettingDlg::OnClickBtnClose()
{
	if (m_bChange)
	{
		if (C179MsgBox::Show(this, NewMsgBox::MSGBOX_ICO_OK_CANCEL_ONE_STRING, NewMsgBox::ICONTYPE_WARNING, L"���Ƿ񱣴�˴��޸ģ�") == RET_OK)
		{
			OnClickBtnConfirm();
			EndDialog(IDOK);
			return;
		}
	}
	EndDialog( IDCANCEL ) ;
}