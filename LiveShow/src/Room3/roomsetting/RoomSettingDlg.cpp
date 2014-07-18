// RoomSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "RoomSettingDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "..\..\CommonLibrary\include\utility\StringHelper.h"
#include "..\..\CommonLibrary\include\ui\C179MsgBox.h"

#include "..\RoomParentDlg.h"
#include "RoomOption.h"

#define SKIN_ON_CLICK_BTN_CONFIRM_MODIFY      1

// CRoomSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CRoomSettingDlg, CDialog)

CRoomSettingDlg::CRoomSettingDlg( CRoomParentDlg* pParentDlg , CWnd* pParent /*=NULL*/)
	: CDialog(CRoomSettingDlg::IDD, pParent),
	m_pParentDlg(pParentDlg)
{ 
	m_pSkinEngine = NULL;
	m_bInited = false;
	::GetSkinEngine(&m_pSkinEngine);
}

CRoomSettingDlg::~CRoomSettingDlg()
{
}

void CRoomSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRoomSettingDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_EN_CHANGE(IDC_EDIT_ROOM_NAME, &CRoomSettingDlg::OnEnChangeEditRoomName)
	ON_EN_CHANGE(IDC_EDIT_ROOM_THEME, &CRoomSettingDlg::OnEnChangeEditRoomTheme)
	ON_BN_CLICKED(IDC_RADIO_ROOMSTATE_CLOSE, &CRoomSettingDlg::OnBnClickedRadioRoomstateClose)
	ON_BN_CLICKED(IDC_RADIO_ROOMSTATE_OPEN, &CRoomSettingDlg::OnBnClickedRadioRoomstateOpen)
	ON_BN_CLICKED(IDC_RADIO_PUBLICCHAT_RIGESTER, &CRoomSettingDlg::OnBnClickedRadioPublicchatClose)
	ON_BN_CLICKED(IDC_RADIO_PUBLICCHAT_VIP, &CRoomSettingDlg::OnBnClickedRadioPublicchatOpen)
	ON_BN_CLICKED(IDC_RADIO_CAIZI_CLOSE, &CRoomSettingDlg::OnBnClickedRadioCaiziClose)
	ON_BN_CLICKED(IDC_RADIO_CAIZI_OPEN, &CRoomSettingDlg::OnBnClickedRadioCaiziOpen)
	ON_BN_CLICKED(IDC_RADIO_USERINOUT_CLOSE, &CRoomSettingDlg::OnBnClickedRadioUserinoutClose)
	ON_BN_CLICKED(IDC_RADIO_USERINOUT_OPEN, &CRoomSettingDlg::OnBnClickedRadioUserinoutOpen)
	ON_EN_CHANGE(IDC_EDIT_ROOM_PWD, &CRoomSettingDlg::OnEnChangeEditRoomPwd)
END_MESSAGE_MAP()


// CRoomSettingDlg ��Ϣ�������

int CRoomSettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"RoomSettingDlg");
		ASSERT(hr == S_OK && __LINE__);
	}

	return 0;
}

BOOL CRoomSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


LRESULT CRoomSettingDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_BTN_CONFIRM_MODIFY:
		{
			//OutputDebugString(L"\n####################ȷ���޸�####################\n");
			OnConfirm();
		}
		break;
	
	default:break;
	}

	return TRUE;
}

void CRoomSettingDlg::OnConfirm()
{
	IUserItem* pSelfItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem() ;
	if ( pSelfItem == NULL )
	{
		return ;
	}
	CString strName;
	GetDlgItemText(IDC_EDIT_ROOM_NAME, strName);
	int nLen = common::utility::stringhelper::CalcStringAsciiLength(strName.GetBuffer(0));
	if (nLen < 5 || nLen > 20)
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING, L"�������Ƴ���Ϊ5-20���ַ�");
		return;
	}

	CString strTheme;
	GetDlgItemText(IDC_EDIT_ROOM_THEME, strTheme);
	nLen = common::utility::stringhelper::CalcStringAsciiLength(strTheme.GetBuffer(0));
	if (nLen > 40)
	{
		C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING, L"�������ⲻ�ܳ���40���ַ�");
		return;
	}

	CString strPassword;
	GetDlgItemText(IDC_EDIT_ROOM_PWD, strPassword);

	wchar_t* pPwd = strPassword.GetBuffer(0);
	size_t len  = wcslen(pPwd);
	for (size_t i = 0; i < len; i++)
	{
		if(!common::utility::stringhelper::IsCharAscii(pPwd[i]))
		{
			C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING, L"�������벻֧������");
			return;
		}
	}	
	RoomOption* pRoomOption = m_pParentDlg->GetRoomBusiness()->GetRoomOption() ;


	bool bOpen = (((CButton*)GetDlgItem(IDC_RADIO_ROOMSTATE_OPEN))->GetCheck() == TRUE);

	if (pSelfItem != NULL && pSelfItem->GetUserTitleLevel() < core::TITLELEVEL_SECOND_OWNER)
	{
		if (strName.Compare(pRoomOption->GetRoomName().c_str()) != 0 || strTheme.Compare( pRoomOption->GetRoomSignature().c_str()) != 0
			|| strPassword.Compare(pRoomOption->GetRoomPassword().c_str()) != 0 || bOpen != pRoomOption->IsOpen())
		{
			C179MsgBox::Show(this, NewMsgBox::MSGBOX_OK_ONE_STRING, L"��Ǹ������Ȩ�޲���");
			return;
		}
	}

	if (strName.Compare(pRoomOption->GetRoomName().c_str()) != 0)
	{
		m_pParentDlg->GetHtmlOutPutManager()->OnModifyRoomName();
	}

	//bool bPublicChat = (((CButton*)GetDlgItem(IDC_RADIO_PUBLICCHAT_OPEN))->GetCheck() == TRUE);
	ENM_RoomPublicChat enmPublicChatType = (((CButton*)GetDlgItem(IDC_RADIO_PUBLICCHAT_RIGESTER))->GetCheck() == TRUE ? PUBLICCHAT_ABOVE_REGISTER : PUBLICCHAT_ABOVE_VIP);

	bool bUserInOut = (((CButton*)GetDlgItem(IDC_RADIO_USERINOUT_OPEN))->GetCheck() == TRUE);

	bool bColorText = (((CButton*)GetDlgItem(IDC_RADIO_CAIZI_OPEN))->GetCheck() == TRUE);

	pRoomOption->OnConfirmRoomSetting(strName.GetBuffer(0), strTheme.GetBuffer(0), bOpen, strPassword.GetBuffer(0), enmPublicChatType, bColorText, bUserInOut);
}

void CRoomSettingDlg::InitDlgData()
{
	RoomOption* pRoomOption = m_pParentDlg->GetRoomBusiness()->GetRoomOption() ;
	if ( pRoomOption == NULL )
	{
		return ;
	}

	m_bInited = false;

	std::wstring strName = pRoomOption->GetRoomName();
	if (strName != L"")
	{
		SetDlgItemText(IDC_EDIT_ROOM_NAME, strName.c_str());
	}

	std::wstring strTheme = pRoomOption->GetRoomSignature();
	if (strTheme != L"")
	{
		SetDlgItemText(IDC_EDIT_ROOM_THEME, strTheme.c_str());
	}

	std::wstring strPassword = pRoomOption->GetRoomPassword();
	if (strPassword != L"")
	{
		SetDlgItemText(IDC_EDIT_ROOM_PWD, strPassword.c_str());
	}

	bool bOpen = pRoomOption->IsOpen();
	if (bOpen)
	{
		CheckRadioButton(IDC_RADIO_ROOMSTATE_CLOSE, IDC_RADIO_ROOMSTATE_OPEN, IDC_RADIO_ROOMSTATE_OPEN);
	}
	else
	{
		CheckRadioButton(IDC_RADIO_ROOMSTATE_CLOSE, IDC_RADIO_ROOMSTATE_OPEN, IDC_RADIO_ROOMSTATE_CLOSE);
	}

	//bool bPublicChat = pRoomOption->CanPublicChat();
	//if (bPublicChat)
	//{
	//	CheckRadioButton(IDC_RADIO_PUBLICCHAT_CLOSE, IDC_RADIO_PUBLICCHAT_OPEN, IDC_RADIO_PUBLICCHAT_OPEN);
	//}
	//else
	//{
	//	CheckRadioButton(IDC_RADIO_PUBLICCHAT_CLOSE, IDC_RADIO_PUBLICCHAT_OPEN, IDC_RADIO_PUBLICCHAT_CLOSE);
	//}
	ENM_RoomPublicChat enmType = pRoomOption->GetPublicChatType();
	if (enmType == PUBLICCHAT_ABOVE_REGISTER)
	{
		CheckRadioButton(IDC_RADIO_PUBLICCHAT_RIGESTER, IDC_RADIO_PUBLICCHAT_VIP, IDC_RADIO_PUBLICCHAT_RIGESTER);
	}
	else
	{
		CheckRadioButton(IDC_RADIO_PUBLICCHAT_RIGESTER, IDC_RADIO_PUBLICCHAT_VIP, IDC_RADIO_PUBLICCHAT_VIP);
	}
	//(GetDlgItem(IDC_RADIO_PUBLICCHAT_RIGESTER))->EnableWindow(FALSE);
	//(GetDlgItem(IDC_RADIO_PUBLICCHAT_VIP))->EnableWindow(FALSE);
	//(GetDlgItem(IDC_RADIO_PUBLICCHAT_RIGESTER))->ShowWindow(SW_HIDE);
	//(GetDlgItem(IDC_RADIO_PUBLICCHAT_VIP))->ShowWindow(SW_HIDE);

	bool bUserInOut = pRoomOption->IsShowUserInOut();
	if (bUserInOut)
	{
		CheckRadioButton(IDC_RADIO_USERINOUT_CLOSE, IDC_RADIO_USERINOUT_OPEN, IDC_RADIO_USERINOUT_OPEN);
	}
	else
	{
		CheckRadioButton(IDC_RADIO_USERINOUT_CLOSE, IDC_RADIO_USERINOUT_OPEN, IDC_RADIO_USERINOUT_CLOSE);
	}

	bool bColorText = pRoomOption->CanColorText();
	if (bColorText)
	{
		CheckRadioButton(IDC_RADIO_CAIZI_CLOSE, IDC_RADIO_CAIZI_OPEN, IDC_RADIO_CAIZI_OPEN);
	}
	else
	{
		CheckRadioButton(IDC_RADIO_CAIZI_CLOSE, IDC_RADIO_CAIZI_OPEN, IDC_RADIO_CAIZI_CLOSE);
	}

	((CEdit*)GetDlgItem(IDC_EDIT_ROOM_PWD))->SetLimitText(12);

	m_bInited = true;
}
BOOL CRoomSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//����ESC������ENTER��
	if ( pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
			{
				return TRUE;
			}
			break;
		case VK_RETURN:
			{
				OnConfirm();
				return TRUE;
			}
			break;
		default: break;
		}	
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CRoomSettingDlg::Refresh()
{
	InitDlgData();
}

void CRoomSettingDlg::SetApplyEffect(BOOL bEffect)
{
	CComVariant var = bEffect;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgApplyEffect", L"visible", var);
}

void CRoomSettingDlg::OnEnChangeEditRoomName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnEnChangeEditRoomTheme()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioRoomstateClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioRoomstateOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioPublicchatClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioPublicchatOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioCaiziClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioCaiziOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioUserinoutClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnBnClickedRadioUserinoutOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::OnEnChangeEditRoomPwd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CRoomSettingDlg::NotifyParentModify()
{
	if (!m_bInited)
	{
		return;
	}
	GetParent()->PostMessage(WM_NOTIFY_ROOM_SYSSET_MODIFY, 0, 0);
}