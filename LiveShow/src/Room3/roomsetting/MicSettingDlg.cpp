// MicSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "MicSettingDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "..\RoomParentDlg.h"
#include "RoomOption.h"

#define  SKIN_ON_CLICK_BTN_CONFIRM_MODIFY    1
// CMicSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CMicSettingDlg, CDialog)

CMicSettingDlg::CMicSettingDlg( CRoomParentDlg* pParentDlg , CWnd* pParent /*=NULL*/)
	: CDialog(CMicSettingDlg::IDD, pParent),
	m_pParentDlg(pParentDlg)
{
	m_pSkinEngine = NULL;
	m_bInited = false;
	::GetSkinEngine(&m_pSkinEngine);
}

CMicSettingDlg::~CMicSettingDlg()
{
}

void CMicSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_MIC_TIME, m_comboMicTime);
}


BEGIN_MESSAGE_MAP(CMicSettingDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_BN_CLICKED(IDC_RADIO_FREE_MIC_CLOSE, &CMicSettingDlg::OnBnClickedRadioFreeMicClose)
	ON_BN_CLICKED(IDC_RADIO_FREE_MIC_OPEN, &CMicSettingDlg::OnBnClickedRadioFreeMicOpen)
	ON_CBN_SELCHANGE(IDC_COMBO_MIC_TIME, &CMicSettingDlg::OnCbnSelchangeComboMicTime)
	ON_BN_CLICKED(IDC_CHECK_LIMIT_MGR_TIME, &CMicSettingDlg::OnBnClickedCheckLimitMgrTime)
	ON_BN_CLICKED(IDC_CHECK_MODIFY_MGR_TIME, &CMicSettingDlg::OnBnClickedCheckModifyMgrTime)
	ON_BN_CLICKED(IDC_RADIO_ROOM_PRIVATEMIC_CLOSE, &CMicSettingDlg::OnBnClickedRadioRoomPrivatemicClose)
	ON_BN_CLICKED(IDC_RADIO_ROOM_PRIVATEMIC_OPEN, &CMicSettingDlg::OnBnClickedRadioRoomPrivatemicOpen)
END_MESSAGE_MAP()


// CMicSettingDlg ��Ϣ�������

int CMicSettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"MicSettingDlg");
		ASSERT(hr == S_OK && __LINE__);
	}

	return 0;
}

LRESULT CMicSettingDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_BTN_CONFIRM_MODIFY:
		{
			//OutputDebugString(L"\n##################ȷ���޸�#################\n");
			OnConfirm();
		}
		break;
	default:break;
	}


	return TRUE;
}

BOOL CMicSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMicSettingDlg::InitDlgData()
{
	RoomOption* pRoomOption = m_pParentDlg->GetRoomBusiness()->GetRoomOption() ;
	if ( pRoomOption == NULL)
	{
		return;
	}
	IUserItem* pSelfUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem() ;
	if ( pSelfUserItem == NULL )
	{
		return ;
	}

	m_bInited = false;
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(0, L"3����");
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(1, L"4����");
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(2, L"5����");
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(3, L"6����");
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(4, L"7����");
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(5, L"8����");
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(6, L"9����");
	((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->InsertString(7, L"10����");

	uint32 unFreeShowTime = pRoomOption->GetFreeShowTime();
	if (unFreeShowTime >= 3 && unFreeShowTime <= 10)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->SetCurSel(unFreeShowTime - 3);
	}
	else
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->SetCurSel(0);
		CString strTemp;
		strTemp.Format(L"CMicSettingDlg::InitDlgData() GetFreeShowTime Error time = %d", unFreeShowTime);
		OutputDebugString(strTemp);
	}

	bool bFreeShowStatus = pRoomOption->CanFreeShow();
	if (bFreeShowStatus)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREE_MIC_OPEN))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_FREE_MIC_CLOSE))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREE_MIC_CLOSE))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_FREE_MIC_OPEN))->SetCheck(FALSE);
	}

	bool bFreeShowForManager = pRoomOption->IsFreeShowForManager();
	if (!bFreeShowForManager)
	{
		((CButton*)GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME))->SetCheck(FALSE);
	}

	bool bFreeShowEditTime = pRoomOption->CanEditFreeShowTime();
	if (bFreeShowEditTime)
	{
		((CButton*)GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME))->SetCheck(FALSE);
	}

	if ( pSelfUserItem->GetUserTitleLevel() < core::TITLELEVEL_SECOND_OWNER)
	{
		((CButton*)GetDlgItem(IDC_RADIO_FREE_MIC_OPEN))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_FREE_MIC_CLOSE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME))->EnableWindow(FALSE);
		if (bFreeShowEditTime)
		{
			GetDlgItem(IDC_COMBO_MIC_TIME)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_COMBO_MIC_TIME)->EnableWindow(FALSE);
		}
	}
	else
	{
		if (bFreeShowStatus)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME))->EnableWindow(TRUE);
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME))->EnableWindow(FALSE);
		}
	}

	bool bPrivateShowEnable = pRoomOption->IsPrivateEnable();
	if (!bPrivateShowEnable)
	{
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_OPEN))->SetCheck(TRUE);
		CComVariant var = L"δ����";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textState",L"text",var);
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_OPEN))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_CLOSE))->EnableWindow(FALSE);
		//((CButton*)GetDlgItem(IDC_CHECK_CLOSE_PRIVATE_MIC))->EnableWindow(FALSE);//todo by lwh
	}
	else
	{
		//((CButton*)GetDlgItem(IDC_CHECK_CLOSE_PRIVATE_MIC))->SetCheck(FALSE);
		CComVariant var = L"�ѿ���";
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"textState",L"text",var);
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_OPEN))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_CLOSE))->EnableWindow(TRUE);
	}

	bool bCanPrivateShow = pRoomOption->CanPrivateShow();
	if (bCanPrivateShow)
	{
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_OPEN))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_CLOSE))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_CLOSE))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_OPEN))->SetCheck(FALSE);
	}

	m_bInited = true;
}

void CMicSettingDlg::OnConfirm()
{
	RoomOption* pRoomOption = m_pParentDlg->GetRoomBusiness()->GetRoomOption() ;
	if ( pRoomOption == NULL)
	{
		return;
	}
	IUserItem* pSelfUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem() ;
	if ( pSelfUserItem == NULL )
	{
		return ;
	}
	uint32 unFreeShowTime = pRoomOption->GetFreeShowTime();
	if (((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->GetCurSel() != -1)
	{
		unFreeShowTime = ((CComboBox*)GetDlgItem(IDC_COMBO_MIC_TIME))->GetCurSel() + 3;
	}
		

	bool bFreeShowStatus = (((CButton*)GetDlgItem(IDC_RADIO_FREE_MIC_OPEN))->GetCheck() == TRUE);

	bool bFreeShowForManager = (((CButton*)GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME))->GetCheck() == FALSE);

	bool bFreeShowEditTime = (((CButton*)GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME))->GetCheck() == TRUE);

	bool bPrivateShowStatus = (((CButton*)GetDlgItem(IDC_RADIO_ROOM_PRIVATEMIC_OPEN))->GetCheck() == TRUE);

	if ( pSelfUserItem->GetUserTitleLevel() < core::TITLELEVEL_SECOND_OWNER)
	{
		if (unFreeShowTime != pRoomOption->GetFreeShowTime() && !pRoomOption->CanEditFreeShowTime())
		{
			return;
		}

		if (bFreeShowStatus != pRoomOption->CanFreeShow())
		{
			return;
		}

		if (bFreeShowForManager != pRoomOption->IsFreeShowForManager())
		{
			return;
		}

		if (bFreeShowEditTime != pRoomOption->CanEditFreeShowTime())
		{
			return;
		}
	}

	pRoomOption->OnConfirmMicSetting(unFreeShowTime, bFreeShowStatus, bFreeShowForManager, bFreeShowEditTime, bPrivateShowStatus);
}

BOOL CMicSettingDlg::PreTranslateMessage(MSG* pMsg)
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

void CMicSettingDlg::Refresh()
{
	InitDlgData();
}

void CMicSettingDlg::SetApplyEffect(BOOL bEffect)
{
	CComVariant var = bEffect;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgApplyEffect", L"visible", var);
}

void CMicSettingDlg::OnBnClickedRadioFreeMicClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_COMBO_MIC_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME)->EnableWindow(FALSE);
	NotifyParentModify();
}

void CMicSettingDlg::OnBnClickedRadioFreeMicOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_COMBO_MIC_TIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_LIMIT_MGR_TIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_MODIFY_MGR_TIME)->EnableWindow(TRUE);
	NotifyParentModify();
}

void CMicSettingDlg::OnCbnSelchangeComboMicTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CMicSettingDlg::OnBnClickedCheckLimitMgrTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CMicSettingDlg::OnBnClickedCheckModifyMgrTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CMicSettingDlg::OnBnClickedRadioRoomPrivatemicClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CMicSettingDlg::OnBnClickedRadioRoomPrivatemicOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NotifyParentModify();
}

void CMicSettingDlg::NotifyParentModify()
{
	if (!m_bInited)
	{
		return;
	}
	GetParent()->PostMessage(WM_NOTIFY_ROOM_SYSSET_MODIFY, 0, 0);
}