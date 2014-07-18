// QQLoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../Hall.h"
#include "QQLoginDlg.h"
#include "Skin_i.h"
#include "SkinUtil.h"
#include "../SysSettingIni.h"
#include "webdefine.h"
#include "../CommonLibrary/include/utility/json/json.h"
#include "../CommonLibrary/include/utility/StringHelper.h"
#include "../CommonLibrary/include/utility/SystemHelper.h"
#include "LoginDlg.h"

#define  TIMER_GRADUALLY_SHOW    1  //����
#define  TIMER_GRADUALLY_HIDE    2  //����

#define  GRADUALLY_SPEED         70

#define WM_QQLOGIN_GET_PRELOADQQ WM_USER + 230

#define QQLOGIN_RESULTS_179ACCOUNT "vdcID"
#define QQLOGIN_RESULTS_179PASSWORD "password"
#define QQLOGIN_RESULTS_179ERROR "error"

#define QQLOGIN_TIMER_IDEVENT 3     //��ʱ�� QQ��¼ҳ���С
#define QQLOGIN_TIMER_INTERVALTIME  200  //��ʱ����� QQ��¼ҳ���ȡҳ���С���ʱ�䣨��λ�����룩

#define QQLOGIN_OPENERROR			L"resource\\html\\qq\\qq_err_mes.html"
#define QQLOGIN_LOAD 			L"resource\\html\\qq\\qq_loading.html"

// CQQLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CQQLoginDlg, CDialog)

CQQLoginDlg::CQQLoginDlg(CWnd* pParent /*=NULL*/)
: CDialog(CQQLoginDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);

	m_alpha = 255;//(����0-255�� 0Ϊȫ͸��)
	m_hInst = NULL;
	SetLayeredWindowAttributes = NULL;
	m_QQLoginURL = NULL;
	m_bLayered = FALSE;

	m_nSeqNo= 0;
	m_IE6 = false;
	m_HtmlHeight = 0;
	m_HtmlWidth = 0;
	m_defineHeight = QQ_LOGIN_DLG_HEIGHT;
	m_defineWidth = QQ_LOGIN_DLG_WIDTH;

}

CQQLoginDlg::~CQQLoginDlg()
{
	m_htmlQQLogin.DestroyWindow();
	if (m_hInst != NULL)
	{
		FreeLibrary(m_hInst);
		m_hInst = NULL;
		SetLayeredWindowAttributes = NULL;
	}

	if(m_QQLoginURL != NULL)
	{
		delete m_QQLoginURL;
		m_QQLoginURL = NULL;
	}	
}

void CQQLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQQLoginDlg, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()	
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CQQLoginDlg ��Ϣ�������

int CQQLoginDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"QQLoginDlg");
		ASSERT(hr == S_OK && __LINE__);
	}

	return 0;
}

LRESULT CQQLoginDlg::OnSkinMessage(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{

	default:break;
	}

	return TRUE;
}

void CQQLoginDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{		
		SetTimer(QQLOGIN_TIMER_IDEVENT,QQLOGIN_TIMER_INTERVALTIME,NULL);
	}
	else
	{
		KillTimer(QQLOGIN_TIMER_IDEVENT);
	}
}

LRESULT CQQLoginDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{

	case WM_QQLOGIN_GET_PRELOADQQ:
		{
			OnQQloginGetProLoad(); //Ԥ����QQ��¼ҳ����Ӧ����
		}
		break;
	case WM_MISSION_HTML_ERROR:
		{
			QQloginLoadError(); //QQ��¼ҳ�����ʧ��
		}
		break;
	case WM_MISSION_HYPERLINK_ONCLICK:
		{
			OnQQloginClick(lParam); //QQ��¼�е������
		}
		break;		
	case WM_MISSION_NAVIGATECOMPLETE2:
		{
			OnQQLoginUserCannel();
			OnQQloginGet179AccountPwd(); //��ȡOpenID��Ӧ��179�ź�MD5��������
		}
		break;

	default:
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}


//WM_QQLOGIN_GET_PRELOADQQ ��Ϣ����Ӧ������Ԥ����QQ��¼ҳ��
void CQQLoginDlg::OnQQloginGetProLoad()
{
	CStringA qqBuffer;
	qqBuffer.Format("%s",m_QQBuffer); 
	if(qqBuffer.IsEmpty())
	{
		QQloginLoadError();
	}
	else
	{
		QQloginLoad(); 

	}

}

//QQ��¼��Ȩҳ�����û�ȡ����Ȩ�󷵻ص�ҳ��
void CQQLoginDlg::OnQQLoginUserCannel() 
{
	CString qqCannel = _T("http://www.179.com");
	CString strURL = m_htmlQQLogin.GetLocationURL();
	if(strURL.Right(1) == _T("/"))
	{
		strURL = strURL.Left(strURL.GetLength()-1);
	}
	if(strURL == qqCannel)
	{
		QQloginUse179login(); //ת��179��¼����
	}

}

void CQQLoginDlg::OnQQloginGet179AccountPwd()
{
	CString strURL = m_htmlQQLogin.GetLocationURL();
	CString codePre;
	CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_QQLOGIN_179ACCOUNT,codePre);  	

	int index = strURL.Find(codePre);	
	if(index >= 0 )
	{
		CString QQ179Account,QQ179Pwd,QQError;
		m_htmlQQLogin.GetElementValue(_T("QQ_vdcID"),QQ179Account);
		m_htmlQQLogin.GetElementValue(_T("QQ_password"),QQ179Pwd);
		m_htmlQQLogin.GetElementValue(_T("QQ_error"),QQError);
		if(QQError == _T("0"))
		{
			if(!QQ179Account.IsEmpty() && !QQ179Pwd.IsEmpty())  //��ȡQQ��Ӧ��179�ź�MD5��������ɹ�
			{
				QQLogin179Account qqAcount;
				qqAcount.m_Account = QQ179Account;
				qqAcount.m_Password = QQ179Pwd;
				::SendMessage(GetParent()->GetSafeHwnd(),UM_QQLOGIN_AUTOLOGIN,(WPARAM)&qqAcount,0);  //����QQ��Ӧ179�˺��Զ���¼��Ϣ

			}
			else //��ȡQQ��Ӧ��179�Ż�MD5��������ʧ��
			{
				QQloginError();  //QQ��¼ʧ��
			}
		}
	}

}

//WM_MISSION_HYPERLINK_ONCLICK ��Ϣ����Ӧ������ QQ��¼�е������
void CQQLoginDlg::OnQQloginClick(LPARAM lParam)
{
	IHTMLEventObj *pEvtObj = (IHTMLEventObj *)lParam;

	if(pEvtObj == NULL)
	{
		assert(false);
		return ;
	}

	CComPtr<IHTMLElement> pElement;
	pEvtObj->get_srcElement(&pElement);

	if(pElement == NULL)
	{
		assert(false);
		return ;
	}	

	CComBSTR tag;
	pElement->get_tagName(&tag);
	if(tag == _T("A") || tag == _T("a"))
	{		

		CString strName = m_htmlQQLogin.GetValue( pElement , _T("name") ) ;
		if(strName =="againload")  //����һ��
		{
			QQloginAgainLoad();
			return ;
		}		
		if(strName == _T("use179login"))  //ʹ��179�˺ŵ�¼
		{	
			QQloginUse179login();
			return ;
		}	
		if(strName == _T("register179web"))
		{
			QQloginRegister179Web(); //ע��179�˺ţ� ʹ��������򿪹ٷ�179�˺�ע��ҳ��
			return ;
		}		

	}

	return ;
}

BOOL CQQLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComVariant var;

	m_htmlQQLogin.CreateFromStatic(IDC_HTML_QQ_LOGIN,this);
	var = (LONG)m_htmlQQLogin.GetSafeHwnd();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"itemHtmlQQLogin",L"hwnd",var);	

	//���뵭����
	LONG dwstyle = GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE) ;
	dwstyle |= WS_EX_LAYERED;
	SetWindowLong( GetSafeHwnd() , GWL_EXSTYLE , dwstyle) ;
	m_bLayered = TRUE;

	m_hInst = LoadLibrary(_T("User32.DLL") ) ;
	SetLayeredWindowAttributes = (FSetLayeredWindowAttributes)GetProcAddress(m_hInst ,("SetLayeredWindowAttributes") ) ;	

	m_IE6 = IEversion6();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CQQLoginDlg::Show()//����Ч��
{
	if (!m_bLayered)
	{
		LONG dwstyle = GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE) ;
		dwstyle |= WS_EX_LAYERED;
		SetWindowLong( GetSafeHwnd() , GWL_EXSTYLE , dwstyle) ;
		m_bLayered = TRUE;
	}
	m_alpha = 0;
	SetTimer(TIMER_GRADUALLY_SHOW, 50, NULL);
}

void CQQLoginDlg::Hide()//����Ч��
{	
	if (!m_bLayered)
	{
		LONG dwstyle = GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE) ;
		dwstyle |= WS_EX_LAYERED;
		SetWindowLong( GetSafeHwnd() , GWL_EXSTYLE , dwstyle) ;
		m_bLayered = TRUE;
	}
	m_alpha = 255;
	SetTimer(TIMER_GRADUALLY_HIDE, 50, NULL);
}
void CQQLoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case TIMER_GRADUALLY_SHOW:
		{
			m_alpha += GRADUALLY_SPEED;
			if (m_alpha > 255)
			{
				m_alpha = 255;
			}

			if ( SetLayeredWindowAttributes)
			{
				SetLayeredWindowAttributes( m_hWnd , RGB(0,0,0) ,m_alpha ,LWA_COLORKEY|LWA_ALPHA) ;
				::RedrawWindow( m_hWnd , NULL ,NULL , RDW_ERASE|RDW_INVALIDATE|RDW_FRAME|RDW_ALLCHILDREN) ;
				ShowWindow(SW_SHOWNOACTIVATE);
			}

			if (255 == m_alpha)
			{
				KillTimer(TIMER_GRADUALLY_SHOW);
				LONG dwstyle = GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE) ;
				if (m_bLayered)
				{
					dwstyle &= ~WS_EX_LAYERED;
					SetWindowLong( GetSafeHwnd() , GWL_EXSTYLE , dwstyle) ;
					m_bLayered = FALSE;
				}
				
			}

		}
		break;
	case TIMER_GRADUALLY_HIDE:
		{
			m_alpha -= GRADUALLY_SPEED;
			if (m_alpha < 0)
			{
				m_alpha = 0;
			}

			if ( SetLayeredWindowAttributes)
			{
				SetLayeredWindowAttributes( m_hWnd , RGB(0,0,0) ,m_alpha ,LWA_COLORKEY|LWA_ALPHA) ;
				::RedrawWindow( m_hWnd , NULL ,NULL , RDW_ERASE|RDW_INVALIDATE|RDW_FRAME|RDW_ALLCHILDREN) ;
				ShowWindow(SW_SHOWNOACTIVATE);
			}

			if (0 == m_alpha)
			{
				KillTimer(TIMER_GRADUALLY_HIDE);
				ShowWindow(SW_HIDE);
			}
		}
		break;
	case QQLOGIN_TIMER_IDEVENT:
		{			
			QQSetHTMLSize();

		}
		break;

	default:break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CQQLoginDlg::OnSysCommand(UINT nID,LPARAM lParam)
{
	if(nID == SC_CLOSE && lParam == 0) //Ƶ�� ALT + F4
	{
		return;
	}

	CWnd::OnSysCommand(nID,lParam);

}

BOOL CQQLoginDlg::PreTranslateMessage(MSG* pMsg)
{

	if(pMsg && pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN )  //Ƶ�� ESC
		{
			return TRUE;
		}

	}

	return CDialog::PreTranslateMessage(pMsg);
}




void CQQLoginDlg::QQloginOpenURL(UINT unMessage,CString strURL)
{
	if(m_QQLoginURL != NULL)
	{
		delete m_QQLoginURL;
		m_QQLoginURL = NULL;
	}	
	memset(m_QQBuffer,0,sizeof(m_QQBuffer));
	//ʹ��sizeof(m_QQBuffer)-1 ����Ϊ���m_QQBuffer��С����ʱ�����һλ�ɴ��'\0'������(����ʹ��sizeof(m_QQBuffer))�������'\0'ʱ�����±곬��
	m_QQLoginURL = new common::utility::CAsynOpenURL(this->m_hWnd,unMessage,NULL, m_QQBuffer, sizeof(m_QQBuffer)-1);   

	m_QQLoginURL->OpenURL(strURL);	

}

//��ȡNewVersion.ini�����ļ���QQ��¼���Ĭ�ϴ�С
void CQQLoginDlg::GetDefineSize()
{
	
	CString strModulePath	= common::utility::systemhelper::Get179AppPath().c_str();	
	CString NewVerFile,AppTip;
	NewVerFile.Format(_T("%s%s\\%s"),strModulePath,VERDOWN_LOCAL_DIR,VERSION_FILE_NEW);//NewVersion.ini���°汾�����ļ�·��	

	CString strWidth,strHeight;	
	if(m_IE6)  
	{				
		GetPrivateProfileString(_T("QQLoginWindow"),_T("ie6Width"),_T("0"),strWidth.GetBuffer(INI_SIZE_16),INI_SIZE_16,NewVerFile);
		strWidth.ReleaseBuffer();
		GetPrivateProfileString(_T("QQLoginWindow"),_T("ie6Height"),_T("0"),strHeight.GetBuffer(INI_SIZE_16),INI_SIZE_16,NewVerFile);
		strHeight.ReleaseBuffer();  

	}
	else
	{
		GetPrivateProfileString(_T("QQLoginWindow"),_T("Width"),_T("0"),strWidth.GetBuffer(INI_SIZE_16),INI_SIZE_16,NewVerFile);
		strWidth.ReleaseBuffer(); 
		GetPrivateProfileString(_T("QQLoginWindow"),_T("Height"),_T("0"),strHeight.GetBuffer(INI_SIZE_16),INI_SIZE_16,NewVerFile);
		strHeight.ReleaseBuffer(); 

	}

	m_defineWidth = _wtoi(strWidth);
	m_defineHeight = _wtoi(strHeight);

	if(m_defineWidth == 0  )
	{
		if(m_IE6) //����ǰΪie6�汾�����������Ƕҳ��������Ϊ516������ΪĬ�Ͽ��(540)
		{
			m_defineWidth = 516;
		}
		else
		{
			m_defineWidth = QQ_LOGIN_DLG_WIDTH;
		}
		
	}
	if(m_defineHeight == 0)
	{
		m_defineHeight = QQ_LOGIN_DLG_HEIGHT;
	}

	m_HtmlWidth = m_defineWidth;
	m_HtmlHeight = m_defineHeight;	

	CComVariant var;
	var = m_HtmlWidth; 		
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"Window",L"width",var);
	var = m_HtmlHeight; 		
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"Window",L"height",var);

	
	::SendMessage(GetParent()->GetSafeHwnd(),UM_QQLOGIN_MOVEWINDOW,0,0);  
	
}
void CQQLoginDlg::QQSetHTMLSize()
{
	int qqWidth,qqHeight;
	qqWidth = 0;
	qqHeight = 0;
	m_htmlQQLogin.GetScrollSize(qqWidth,qqHeight);	
	CComVariant var = qqWidth; 		
	//m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"Window",L"width",var);
	if(qqHeight < m_defineHeight)
	{
		qqHeight = m_defineHeight;
	} 	

	if(m_HtmlHeight != qqHeight)
	{
		var = qqHeight;
		m_HtmlHeight = qqHeight ;
		m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"Window",L"height",var);
		::SendMessage(GetParent()->GetSafeHwnd(),UM_QQLOGIN_MOVEWINDOW,0,0);  
	}
	
}

//QQ��¼ҳ��Ԥ����
void CQQLoginDlg::QQloginPreLoad()
{
	GetDefineSize();

	if(m_IE6) //��ǰIE�汾�Ƿ�ΪIE6
	{
		QQloginLoad();  //IE6�汾ʱ��ֱ�Ӽ���QQ��¼ҳ��
		return;

	}
	
	std::wstring strUrl = common::utility::systemhelper::Get179AppPath() + QQLOGIN_LOAD;	
	m_htmlQQLogin.SetUrl(strUrl,true);
	m_htmlQQLogin.UpdateURL();

	CString sQQUrl;
	CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_QQLOGIN,sQQUrl);  
	QQloginOpenURL(WM_QQLOGIN_GET_PRELOADQQ,sQQUrl);
}

//QQ��¼ҳ�����
void CQQLoginDlg::QQloginLoad()
{
	CString sQQUrl;
	CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_QQLOGIN,sQQUrl);
	m_htmlQQLogin.SetUrl(std::wstring(sQQUrl),true);
	m_htmlQQLogin.UpdateURL();

}

//QQ��¼ҳ�����ʧ��
void CQQLoginDlg::QQloginLoadError()
{	
	std::wstring strUrl = common::utility::systemhelper::Get179AppPath() + QQLOGIN_OPENERROR;
	m_htmlQQLogin.SetUrl(strUrl,true);
	m_htmlQQLogin.UpdateURL();
}

//QQ��¼ʧ��
void CQQLoginDlg::QQloginError()
{
	CString sQQError;
	CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_QQLOGIN_ERROR,sQQError);  
	m_htmlQQLogin.SetUrl(std::wstring(sQQError),true);
	m_htmlQQLogin.UpdateURL();

}

//����һ��,���´�QQ��¼ҳ��
void CQQLoginDlg::QQloginAgainLoad()
{
	QQloginPreLoad();
}


//ʹ��179�˺ŵ�¼��ת��179��¼
void CQQLoginDlg::QQloginUse179login()
{
	::SendMessage(GetParent()->GetSafeHwnd(),UM_QQLOGIN_SET,0,0);  

}


//ע��179�˺ţ� ʹ��������򿪹ٷ�179�˺�ע��ҳ��
void CQQLoginDlg::QQloginRegister179Web()
{
	CString strUrl;
	CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_179REGISTER_OFFICAL,strUrl);  
	common::utility::systemhelper::OpenUrl(wstring(strUrl));    //ʹ��������򿪹ٷ�179�˺�ע��ҳ��

}

//��ǰIE�汾�Ƿ�ΪIE6
bool CQQLoginDlg::IEversion6()
{
	bool isIE6 = false;
	CString strIEVer = common::utility::systemhelper::GetIEVersion().c_str();
	if(strIEVer.Left(2) == _T("6."))  //��ע�����SOFTWARE\\Microsoft\\Interent Explorer �µ�Version��ֵǰ2�ַ�����6. ��ΪIE6
	{
		isIE6 = true;
	}

	return isIE6;
}


void CQQLoginDlg::GetQQHtmlSize(int &qqWidth,int &qqHeight)
{
	qqWidth = m_HtmlWidth;
	qqHeight = m_HtmlHeight;
}