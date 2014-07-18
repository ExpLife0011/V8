// ShowBasicSettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "ShowBasicSettingDlg.h"
#include "skin_i.h"
#include "SkinUtil.h"
#include "SysSettingDlg.h"
#include "utility/ConfigManager.h"
#include "utility/FileHelper.h"
#include "utility\StringHelper.h"
#include "ui\C179MsgBox.h"
#include "..\personalsetting/VideoManager.h"

// CShowBasicSettingDlg �Ի���

IMPLEMENT_DYNAMIC(CShowBasicSettingDlg, CDialog)

CShowBasicSettingDlg::CShowBasicSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowBasicSettingDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);
}

CShowBasicSettingDlg::~CShowBasicSettingDlg()
{
}

void CShowBasicSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ATROOM_CHECK_AUTOLOGIN, m_autoLogin);
	DDX_Control(pDX, IDC_ATROOM_CHECK_AUTORUN, m_PowerRun);
	DDX_Control(pDX, IDC_ATROOM_CHECK_OPENSOUND, m_openSound);
}


BEGIN_MESSAGE_MAP(CShowBasicSettingDlg, CDialog)

	ON_SKIN_MESSAGE
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_ATROOM_CHECK_AUTOLOGIN, &CShowBasicSettingDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_ATROOM_CHECK_AUTORUN, &CShowBasicSettingDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_ATROOM_CHECK_OPENSOUND, &CShowBasicSettingDlg::OnBnClickedCheck)
END_MESSAGE_MAP()


// CShowBasicSettingDlg ��Ϣ�������

int CShowBasicSettingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(NULL != m_pSkinEngine);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"ShowBasicSettingDlg_AtRoom");
		ASSERT(hr== S_OK && __LINE__);
	}

	return 0;
}

LRESULT CShowBasicSettingDlg::OnSkinMessage(WPARAM wParam,LPARAM lParam)
{

	return TRUE;
}

//��ȡ�Ƿ񿪻�����
bool CShowBasicSettingDlg::ReadRegeditAutoRun()
{
	//C:\Documents and Settings\�û���\����ʼ���˵�\����\����\����KTV

	TCHAR szBuffer[MAX_PATH];
	LPITEMIDLIST lpItemIdList;
	SHGetSpecialFolderLocation(0, CSIDL_STARTUP, &lpItemIdList);
	SHGetPathFromIDList(lpItemIdList, szBuffer);

	wchar_t szShortcutFile[MAX_PATH] = {0};
	wsprintf( szShortcutFile, _T("%s\\%s.lnk"), szBuffer, _T("����KTV"));

	BOOL bShortcutFile = common::utility::filehelper::IsFileExist(szShortcutFile);
	return bShortcutFile;

}
 //���ÿ�������
void CShowBasicSettingDlg::SetRegeditAutoRun()
{
	//C:\Documents and Settings\�û���\����ʼ���˵�\����\����\����KTV

	TCHAR szBuffer[MAX_PATH] ;
	LPITEMIDLIST lpItemIdList ;
	SHGetSpecialFolderLocation( 0 , CSIDL_STARTUP , &lpItemIdList ) ;
	SHGetPathFromIDList( lpItemIdList , szBuffer ) ;

	wchar_t szShortcutFile[MAX_PATH] = {0} ;
	wsprintf( szShortcutFile , _T("%s\\%s.lnk") , szBuffer ,_T("����KTV") ) ;

	IShellLink* pShellLink = NULL ;
	if ( CoCreateInstance( CLSID_ShellLink , NULL , CLSCTX_INPROC_SERVER , IID_IShellLink ,(void**)&pShellLink ) == S_OK )
	{
		IPersistFile* pPersistFile = NULL ;
		if ( pShellLink->QueryInterface( IID_IPersistFile , (void**)&pPersistFile ) == S_OK )
		{
			std::wstring strModulePath = common::utility::filehelper::GetCurPath();
			std::wstring strModuleDir = common::utility::filehelper::GetParentDir(strModulePath);
			pShellLink->SetPath( strModulePath.c_str() ) ;
			pShellLink->SetWorkingDirectory( strModuleDir.c_str() ) ;
			pShellLink->SetShowCmd( SW_SHOWNORMAL ) ;
			pPersistFile->Save( szShortcutFile , TRUE ) ;
			pPersistFile->Release() ;
		}
		pShellLink->Release() ;

	}


}
//��ɾ��������
void CShowBasicSettingDlg::ClearRegeditAutoRun()
{	

	//C:\Documents and Settings\�û���\����ʼ���˵�\����\����\����KTV

	TCHAR szBuffer[MAX_PATH];
	LPITEMIDLIST lpItemIdList;
	SHGetSpecialFolderLocation(0, CSIDL_STARTUP, &lpItemIdList);
	SHGetPathFromIDList(lpItemIdList, szBuffer);

	wchar_t szShortcutFile[MAX_PATH] = {0};
	wsprintf( szShortcutFile, _T("%s\\%s.lnk"), szBuffer, _T("����KTV"));

	DeleteFile(szShortcutFile);

}


void CShowBasicSettingDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

//	CDialog::OnOK();
}

void CShowBasicSettingDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

//	CDialog::OnCancel();
}


LRESULT CShowBasicSettingDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_NOTIFY_ROOM_SYSSET_CLICKOK:  //��ȷ������Ť����Ϣ		
	case WM_NOTIFY_ROOM_SYSSET_CLICKAPPLI:  // "Ӧ��"��Ť����Ϣ
		{
			Confirm();
		}
		break;	
	default:
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CShowBasicSettingDlg::Confirm()
{
	core::CurInfo m_MyCurInfo = GetCurInfo();

	//���ÿ�������
	BOOL powerRun = m_PowerRun.GetCheck();	//����������ѡ���Ƿ�ѡ��
	if(powerRun)
	{
		SetRegeditAutoRun();
	}
	else
	{
		ClearRegeditAutoRun();
	}

	//�����Զ���¼	
	bool isSave = false;
	UserInfoLogin userinfo;	
	CConfigManager::Instance()->GetUserInfo_Login(m_MyCurInfo.unUIN,userinfo);
	if(userinfo.bAutoLogin != (bool)m_autoLogin.GetCheck())
	{
		userinfo.bAutoLogin = (bool)m_autoLogin.GetCheck();	
		if(userinfo.bAutoLogin)
		{
			userinfo.bSavePassword = true;
		}
		isSave = true;
	}

	//���ô�����
	if(userinfo.bOpenSound != (bool)m_openSound.GetCheck())
	{
		userinfo.bOpenSound = (bool)m_openSound.GetCheck();	
		isSave = true;	
	
		RoomAVLogic* pRoomAvLogic= VideoManager::GetInstance()->GetRoomAvLogic();
		if ( pRoomAvLogic != NULL )
		{
			pRoomAvLogic->SetAllSoundMute( !userinfo.bOpenSound);
		}
		
	}

	if(isSave)
	{
		CConfigManager::Instance()->SetUserInfo_Login(userinfo);
	}


}
void CShowBasicSettingDlg::Init()
{
	core::CurInfo m_MyCurInfo = GetCurInfo();
	BOOL autoLogin,powerRun,openSound;

	UserInfoLogin userinfo;	
	CConfigManager::Instance()->GetUserInfo_Login(m_MyCurInfo.unUIN,userinfo);		

	powerRun = (BOOL)ReadRegeditAutoRun();
	autoLogin = (BOOL)userinfo.bAutoLogin;
	openSound = (BOOL)userinfo.bOpenSound;
	m_autoLogin.SetCheck(autoLogin);
	m_PowerRun.SetCheck(powerRun);
	m_openSound.SetCheck(openSound);

}
void CShowBasicSettingDlg::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)  //��ʾ���˻�������
	{
		Init();
	}

}

void CShowBasicSettingDlg::OnBnClickedCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(GetParent()->GetSafeHwnd(),WM_NOTIFY_ROOM_SYSSET_MODIFY,0,0); //����������(�˵�����)�������öԻ������޸ĵ���Ϣ

}

BOOL CShowBasicSettingDlg::PreTranslateMessage(MSG* pMsg)
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

void CShowBasicSettingDlg::SetApplyEffect(BOOL bEffect)
{
	CComVariant var = bEffect;
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(), L"imgApplyEffect", L"visible", var);
}