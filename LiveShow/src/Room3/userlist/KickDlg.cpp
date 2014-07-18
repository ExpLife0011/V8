// KickDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "KickDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "..\RoomParentDlg.h"
#include "..\SendEventManager.h"
#include "..\..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\..\CommonLibrary/include\utility\FileHelper.h"
#include "..\..\CommonLibrary\include\utility\StringHelper.h"
#include "utility/expat++/expat_document.h"
#include "..\..\CommonLibrary\include\ui\C179MsgBox.h"

#define  SKIN_ON_CLICK_CLOSE                     1
#define  SKIN_ON_CLICK_BTN_CONFIRM               2

#define  NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE       3

#define  SKIN_ON_CLICK_BTN_DELETE                4
#define  SKIN_ON_CLICK_BTN_SAVE_TO_REASON        5

#define  DEFAULT_REASON_TEMPTATION               _T("�ջ����(Ĭ��)")
#define  DEFAULT_REASON_PORN                     _T("ɫ�����(Ĭ��)")
#define  DEFAULT_REASON_AD                       _T("�������(Ĭ��)")
#define  DEFAULT_REASON_DISCRUPT                 _T("���ҷ�������(Ĭ��)")
#define  DEFAULT_REASON_ATTACK                   _T("�����ٷ�(Ĭ��)")
#define  DEFAULT_REASON_USER_DEFINE              _T("�Զ�������")

#define  DEFAULT_TIME_5_MINS                       _T("5����")
#define  DEFAULT_TIME_10_MINS                      _T("10����")
#define  DEFAULT_TIME_20_MINS                      _T("20����")
#define  DEFAULT_TIME_30_MINS                      _T("30����")
#define  DEFAULT_TIME_60_MINS                      _T("1Сʱ")
#define  DEFAULT_TIME_12_HOURS					   _T("12Сʱ")
// CKickDlg �Ի���

IMPLEMENT_DYNAMIC(CKickDlg, CDialog)

CKickDlg::CKickDlg(CRoomParentDlg* pParentDlg, uint32 unDstUIN, uint8 unType, CWnd* pParent /*=NULL*/)
	: CDialog(CKickDlg::IDD, pParent),
	m_pParentDlg(pParentDlg),
	m_unDstUIN(unDstUIN),
	m_unType(unType)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);
}

CKickDlg::~CKickDlg()
{
}

void CKickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_KICK_REASON, m_comboReason);
	DDX_Control(pDX, IDC_COMBO_KICK_TIME, m_comboTime);
}


BEGIN_MESSAGE_MAP(CKickDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_CBN_SELCHANGE(IDC_COMBO_KICK_REASON, &CKickDlg::OnCbnSelchangeComboKickReason)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CKickDlg ��Ϣ�������

int CKickDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"KickDlg");
		ASSERT(hr == S_OK && __LINE__);
	}

	//����������ѡ΢���ź�
	std::wstring strFont;
	common::utility::systemhelper::GetDefaultFontName(strFont);
	CComVariant var = (CComVariant) strFont.c_str();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textTitle",L"fontFamily",var);

	return 0;
}

BOOL CKickDlg::PreTranslateMessage(MSG* pMsg)
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

LRESULT CKickDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_CLOSE:
		{
           //PostMessage(WM_CLOSE,NULL,NULL);
			ShowWindow(SW_HIDE);
		}
        break;
	case SKIN_ON_CLICK_BTN_CONFIRM:
		{
           OnClickConfirm();
		}
		break;
	case SKIN_ON_CLICK_BTN_DELETE:
		{
		   OnClickDeleteReason();
		}
		break;
	case SKIN_ON_CLICK_BTN_SAVE_TO_REASON:
		{
			OnClickSaveReason();
		}
		break;
	default:break;
	}


	return TRUE;
}

BOOL CKickDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComVariant var;
	if (m_pParentDlg != NULL && m_unDstUIN != 0)
	{
		IUserItem * pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN(m_unDstUIN);
		if (pUserItem != NULL)
		{
			CString strName;
			strName.Format(L"%s(%d)", pUserItem->GetUserName().c_str(), pUserItem->GetUser179ID());
			var = strName;
			m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textUser", L"text", var);
		}
	}

	if (m_unType == 0)
	{
		var = L"��ȷ��Ҫ��";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt1", L"text", var);
		var = L"�߳���������";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt2", L"text", var);
	}
	else
	{
		var = L"��ȷ��Ҫ��ͣ";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt1", L"text", var);
		var = L"��IP��ַ��";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt2", L"text", var);
	}

	m_comboReason.AddString(DEFAULT_REASON_USER_DEFINE);
	m_comboReason.AddString(DEFAULT_REASON_TEMPTATION);
	m_comboReason.AddString(DEFAULT_REASON_PORN);
	m_comboReason.AddString(DEFAULT_REASON_AD);
	m_comboReason.AddString(DEFAULT_REASON_DISCRUPT);
	m_comboReason.AddString(DEFAULT_REASON_ATTACK);
	LoadCustomizeReason();
	if (m_vecCustomizeReason.size() != 0)
	{
		for (std::vector<CString>::iterator it = m_vecCustomizeReason.begin(); it != m_vecCustomizeReason.end(); ++it)
		{
			CString strReason = *it;
			int nLen = common::utility::stringhelper::CalcStringAsciiLength(strReason.GetBuffer(0));
			if (nLen <= 10)
			{
				strReason += L"(�Զ���)";
				m_comboReason.InsertString(0,strReason);
			}
		}
		m_comboReason.SetCurSel(0);
		NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE,(LONG)1);
	}
	else
	{
		m_comboReason.SetCurSel(0);
		NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE,(LONG)2);
	}

	//m_setDefaultReason.insert(DEFAULT_REASON_USER_DEFINE);
	m_setDefaultReason.insert(DEFAULT_REASON_TEMPTATION);
	m_setDefaultReason.insert(DEFAULT_REASON_PORN);
	m_setDefaultReason.insert(DEFAULT_REASON_AD);
	m_setDefaultReason.insert(DEFAULT_REASON_DISCRUPT);
	m_setDefaultReason.insert(DEFAULT_REASON_ATTACK);

	m_comboTime.AddString(DEFAULT_TIME_5_MINS);
	m_comboTime.AddString(DEFAULT_TIME_10_MINS);
	m_comboTime.AddString(DEFAULT_TIME_20_MINS);
	m_comboTime.AddString(DEFAULT_TIME_30_MINS);
	m_comboTime.AddString(DEFAULT_TIME_60_MINS);
	m_comboTime.AddString(DEFAULT_TIME_12_HOURS);
	m_comboTime.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CKickDlg::OnCbnSelchangeComboKickReason()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSel;
	m_comboReason.GetLBText(m_comboReason.GetCurSel(),strSel);
    if (strSel.Compare(DEFAULT_REASON_USER_DEFINE) == 0)//ѡ������Զ�������
    {
		NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE,(LONG)0);
		((CEdit*)GetDlgItem(IDC_EDIT_KICK_REASON))->SetWindowText(L"");
    }
	else
	{
		if (m_setDefaultReason.find(strSel) != m_setDefaultReason.end())
		{
			NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE,(LONG)2);
		}
		else
		{
			NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE,(LONG)1);
		}
	}
}

void CKickDlg::OnClickSaveReason()
{
	CString strReason;
	((CEdit*)GetDlgItem(IDC_EDIT_KICK_REASON))->GetWindowText(strReason);

	strReason.Trim();

	//if (strReason != L"")
	//{
		int nLen = common::utility::stringhelper::CalcStringAsciiLength(strReason.GetBuffer(0));
		if (nLen == 0 || nLen > 10)
		{
			C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING , L"���ݲ���Ϊ���Ҳ�����10���ַ�" );
			return;
		}

		if (strReason.Find(L"(�Զ���)") !=  -1 || strReason.Find(L"(Ĭ��)") != -1 || strReason.Find(L"���Զ��壩") != -1 || strReason.Find(L"��Ĭ�ϣ�") != -1)
		{
			C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"������ӡ�Ĭ�ϡ����Զ��塱����" );
			return;
		}

		if (m_vecCustomizeReason.size() >= 10)
		{
			C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING , L"�Զ����������ɱ���10��" );
			return;
		}

		for (std::vector<CString>::iterator it = m_vecCustomizeReason.begin(); it != m_vecCustomizeReason.end(); ++it)
		{
			if ((*it).Compare(strReason) == 0)
			{
				C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"�Ѵ�����ͬ�ķ������ɣ������ظ����" );
				return;
			}
		}
		m_vecCustomizeReason.push_back(strReason);
		strReason += L"(�Զ���)";
		m_comboReason.InsertString(0,strReason);
		m_comboReason.SetCurSel(0);
		SaveCustomizeReason();
		NOTIFY_SKIN_HELPER(NOTIFY_SKIN_ON_CHOOSE_USER_DEFINE,(LONG)1);
	//}
}

void CKickDlg::OnClickDeleteReason()
{
	CString strReason;
	int nSel = ((CComboBox*)GetDlgItem(IDC_COMBO_KICK_REASON))->GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}

	((CComboBox*)GetDlgItem(IDC_COMBO_KICK_REASON))->GetLBText(nSel, strReason);
	strReason = strReason.Left(strReason.GetLength() - 5);
	((CComboBox*)GetDlgItem(IDC_COMBO_KICK_REASON))->DeleteString(nSel);

	for (std::vector<CString>::iterator it = m_vecCustomizeReason.begin(); it != m_vecCustomizeReason.end();)
	{
		if (*it == strReason)
		{
			it = m_vecCustomizeReason.erase(it);
		}
		else
		{
			++it;
		}
	}

	SaveCustomizeReason();
}

void CKickDlg::OnClickConfirm()
{
	int nSel = m_comboReason.GetCurSel();
	if (nSel == CB_ERR)
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING , L"��ѡ��������ɣ�" );
		return;
	}
	CString strReason;
	m_comboReason.GetLBText(nSel, strReason);
	if (strReason.Compare(DEFAULT_REASON_USER_DEFINE) == 0)
	{
		C179MsgBox::Show( this, NewMsgBox::MSGBOX_OK_ONE_STRING ,L"���ȱ����Զ������ɣ�" );
		return;
	}
	else
	{
		if (m_setDefaultReason.find(strReason) != m_setDefaultReason.end())
		{
			strReason = strReason.Left(strReason.GetLength() - 4);
		}
		else
		{
			strReason = strReason.Left(strReason.GetLength() - 5);
		}
	}
	nSel = m_comboTime.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strTime;
	m_comboTime.GetLBText(nSel, strTime);

	uint16 unTime = GetKickTime(strTime);
	if (unTime != 0 && strReason != L"")
	{
		if (m_pParentDlg != NULL && m_unDstUIN != 0)
		{
			if (m_unType == 0)
			{
				CSendEventManager::SendKickOutEvent(m_pParentDlg->GetRoomID(), m_unDstUIN,strReason.GetBuffer(0), unTime);
			}
			else if (m_unType == 1)
			{
				CSendEventManager::SendLockIPEvent(m_pParentDlg->GetRoomID(), m_unDstUIN,strReason.GetBuffer(0), unTime);
			}
			
		}
	}

	ShowWindow(SW_HIDE);
}

bool CKickDlg::LoadCustomizeReason()
{
	CString strPath;
	strPath.Format(L"%s\\userdata\\%d", common::utility::systemhelper::Get179AppPath().c_str(), GetCurInfo().unUIN);

	CString strFullFilePath;
	strFullFilePath.Format(L"%s\\CustomizeKickReason.xml", strPath.GetBuffer(0));

	common::utility::expat_document xmlDoc;
	if (!xmlDoc.load_from_file(strFullFilePath))
	{
		return false;
	}

	m_vecCustomizeReason.clear();

	common::utility::expat_element * pRoot = xmlDoc.get_root();
	if (!pRoot)
	{
		return false;
	}

	common::utility::expat_element * pElement = pRoot->get_first_child_element();
	while (pElement)
	{
		std::wstring strReason = pElement->get_element_by_name(L"Text")->get_element_contents();
		m_vecCustomizeReason.push_back(strReason.c_str());

		pElement = pElement->get_sibling_element();
	}
	return true;
}

bool CKickDlg::SaveCustomizeReason()
{
	CString strPath;
	strPath.Format(L"%s\\userdata\\%d", common::utility::systemhelper::Get179AppPath().c_str(), GetCurInfo().unUIN);

	if (!PathFileExists(strPath))
	{
		common::utility::filehelper::CreateAllDirectory(strPath.GetBuffer(0));
	}

	CString strFullFilePath;
	strFullFilePath.Format(L"%s\\CustomizeKickReason.xml", strPath.GetBuffer(0));
	CFile xmlFile;
	if (!xmlFile.Open(strFullFilePath, CFile::modeCreate|CFile::modeWrite))
	{
		return false;
	}

	char chHead[] = {0xEF, 0xBB, 0xBF};
	xmlFile.Write(chHead, 3);

	std::wstring strHead = L"<?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n<REASON>";
	std::wstring strEnd = L"</REASON>";

	std::string strTemp = common::utility::stringhelper::UnicodeToUTF8(strHead);
	xmlFile.Write(strTemp.c_str(), strTemp.length());

	for (std::vector<CString>::iterator it = m_vecCustomizeReason.begin(); it != m_vecCustomizeReason.end(); it++)
	{
		CString strReason;
		strReason.Format(L"<Item><Text>%s</Text></Item>", (*it).GetBuffer(0));

		strTemp = common::utility::stringhelper::UnicodeToUTF8(strReason.GetBuffer(0));
		xmlFile.Write(strTemp.c_str(), strTemp.length());
	}

	strTemp = common::utility::stringhelper::UnicodeToUTF8(strEnd);
	xmlFile.Write(strTemp.c_str(), strTemp.length());

	xmlFile.Close();

	return true;
}

uint16 CKickDlg::GetKickTime( CString strTime )
{
	if (strTime == DEFAULT_TIME_5_MINS)
	{
		return 300;
	}
	else if (strTime == DEFAULT_TIME_10_MINS)
	{
		return 600;
	}
	else if (strTime == DEFAULT_TIME_20_MINS)
	{
		return 1200;
	}
	else if (strTime == DEFAULT_TIME_30_MINS)
	{
		return 1800;
	}
	else if (strTime == DEFAULT_TIME_60_MINS)
	{
		return 3600;
	}
	else if (strTime == DEFAULT_TIME_12_HOURS)
	{
		return 43200;
	}
	else
	{
		return 0;
	}

	return 0;
}

void CKickDlg::SetKickType( uint8 unType )
{
	m_unType = unType;
}
void CKickDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if (bShow)
	{
		CComVariant var;
		if (m_pParentDlg != NULL && m_unDstUIN != 0)
		{
			IUserItem * pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN(m_unDstUIN);
			if (pUserItem != NULL)
			{
				CString strName;
				strName.Format(L"%s(%d)", pUserItem->GetUserName().c_str(), pUserItem->GetUser179ID());
				var = strName;
				m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textUser", L"text", var);
			}
		}
		
		if (m_unType == 0)
		{
			var = L"��ȷ��Ҫ��";
			m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt1", L"text", var);
			var = L"�߳���������";
			m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt2", L"text", var);
		}
		else
		{
			var = L"��ȷ��Ҫ��ͣ";
			m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt1", L"text", var);
			var = L"��IP��ַ��";
			m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"textPrompt2", L"text", var);
		}
	}
}

void CKickDlg::SetKickDstUIN( uint32 unDstUIN )
{
	m_unDstUIN = unDstUIN;
}